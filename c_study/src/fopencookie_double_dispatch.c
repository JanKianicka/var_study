
/* THIS IS A SCRATCH BOARD */

/*
 * Logging using fopencookie() and double dispatch
 *
 * Global stream objects: sysdbg, sysifo, sysntc, etc.
 * Global log manager object: sysmgr (having a topic attribute)
 * Global message topic objects: LogGen, LogRun, LogTme, LogSql, etc.
 *
 * Writer function per stream: dbg_writer, ifo_writer, ntc_writer, etc.
 * Log function per topic: gen_log_dbg, gen_log_ifo, gen_log_ntc, etc.
 *
 * 1st dispatch: Each stream has an associated writer function.
 * 2nd dispatch: Each writer function is a selector on cookie->topic vtable.
 */

#include <stddef.h>
#include <stdio.h>
#include <errno.h>

/* DEFINITIONS */

typedef struct LoggerMgr_ LoggerMgr;
typedef struct LogTopic_  LogTopic;

typedef size_t (*writer_fn)(LoggerMgr *mgr, char const *data, size_t len);
typedef size_t (*log_fn)(LogTopic *t, char const *data, size_t len);

struct LoggerMgr_
{
    LogTopic *topic; /* Pointer to virtual function table */
};

struct LogTopic_ /* Virtual function table */
{
    log_fn log_dbg;
    log_fn log_ifo;
    log_fn log_ntc;
    /* etc. */
};

/**
 * Singleton constructor - to initialize the off stream instance.
 */
static int noop(void) {return 0;}


FILE *
logger_open(FILE **stream, LoggerMgr *mgr, writer_fn writer)
{
    FILE *s;
    cookie_io_functions_t fns =
	{
	    (cookie_read_function_t *)  noop,
	    (cookie_write_function_t *) writer,
	    (cookie_seek_function_t *)  noop,
	    (cookie_close_function_t *) noop
	};

    s = fopencookie((void *) mgr, "w", fns);
    if (*stream != NULL)
	logger_close(*stream);
    *stream = s;
    return *stream;
}

size_t
dbg_writer(LoggerMgr *mgr, char const *data, size_t len)
{
    topic_t *t = mgr->topic;
    if (t->log_dbg != NULL)
	return t->log_dbg(t, data, len);
    return 0;
}

size_t
ifo_writer(LoggerMgr *mgr, char const *data, size_t len)
{
    topic_t *t = mgr->topic;
    if (t->log_ifo != NULL)
	return t->log_ifo(t, data, len);
    return 0;
}

#define TOPIC_GEN_NAME "[general]"
#define TOPIC_GEN_SIZE sizeof(TOPIC_GEN_NAME)
#define TOPIC_IFO_NAME "[info]"
#define TOPIC_IFO_SIZE sizeof(TOPIC_IFO_NAME)

size_t
gen_log_dbg(LogTopic *t, char const *data, size_t len)
{
    syslog(LOG_DEBUG, "%.*s %.*s", TOPIC_GEN_SIZE, TOPIC_GEN_NAME, len, data);
    return TOPIC_GEN_SIZE + 1 + len;
}

size_t
gen_log_ifo(LogTopic *t, char const *data, size_t len)
{
    syslog(LOG_INFO, "%.*s %.*s", TOPIC_IFO_SIZE, TOPIC_IFO_NAME, len, data);
    return TOPIC_IFO_SIZE + 1 + len;
}

/* USAGE */

FILE *sysdbg = stderr;
FILE *sysifo = stdout;

LogTopic LogGen_ =
{
    gen_log_dbg,
    gen_log_ifo,
    NULL,             /* log_ntc */
    /* etc. */
};
LogTopic *LogGen = &LogGen_;

LoggerMgr sysmgr_ =
{
    LogGen /* topic */
};
LoggerMgr *sysmgr = &sysmgr_;

main()
{
    logger_open(&sysdbg, sysmgr, dbg_writer);
    logger_open(&sysifo, sysmgr, ifo_writer);

    logtopic(sysmgr, LogGen);
    fprintf(sysdbg, "Hello World!\n");
}
