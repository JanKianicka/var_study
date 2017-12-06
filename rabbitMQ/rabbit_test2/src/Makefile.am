INCLUDES = \
	@RABBIT_INCLUDES@

bin_PROGRAMS=amqp_listenq
amqp_listenq_SOURCES= \
	amqp_listenq.c \
	utils.c

bin_PROGRAMS+=amqp_sendstring
amqp_sendstring_SOURCES= \
	amqp_sendstring.c \
	utils.c
	
bin_PROGRAMS+=tis_poc_sender
tis_poc_sender_SOURCES= \
	tis_poc_sender.c \
	utils.c

bin_PROGRAMS+=tuxshell_poc
tuxshell_poc_SOURCES= \
	tuxshell_poc.c \
	utils.c	

bin_PROGRAMS+=listen_two_queues
listen_two_queues_SOURCES = \
	listen_two_queues.c \
	utils.c

amqp_listenq_LDADD = \
	@RABBIT_LIBS@

amqp_sendstring_LDADD = \
	@RABBIT_LIBS@
	
tis_poc_sender_LDADD = \
	@RABBIT_LIBS@
	
tuxshell_poc_LDADD = \
	@RABBIT_LIBS@

listen_two_queues_LDADD = \
	@RABBIT_LIBS@
