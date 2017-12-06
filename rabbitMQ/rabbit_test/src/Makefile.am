#bin_PROGRAMS=a.out
#a_out_SOURCES=rabbit_test.c
INCLUDES = \
	@RABBIT_INCLUDES@

bin_PROGRAMS=another_out
another_out_SOURCES=another.c

#bin_PROGRAMS+=amqp_listen
#amqp_listen_SOURCES= \
#	amqp_listen.c \
#	utils.c

bin_PROGRAMS+=amqp_listenq
amqp_listenq_SOURCES= \
	amqp_listenq.c \
	utils.c
	
#amqp_listen_LDADD = \
#	@RABBIT_LIBS@

amqp_listenq_LDADD = \
	@RABBIT_LIBS@
