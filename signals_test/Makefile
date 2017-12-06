all:main basic_handler multi_signal inactivity_timeout using_setitimer dacs4_proto_setitimer

main:signals_main.c
	cc -o main signals_main.c

basic_handler: basic_handlers.c
	cc -o basic_handler basic_handlers.c
	
multi_signal: multi_signal.c
	cc -o multi_signal multi_signal.c

inactivity_timeout: inactivity_timeout.c
	cc -o inactivity_timeout inactivity_timeout.c
	
using_setitimer: using_setitimer.c
	cc -o using_setitimer using_setitimer.c
	
dacs4_proto_setitimer: dacs4_proto_setitimer.c
	cc -o dacs4_proto_setitimer dacs4_proto_setitimer.c

clean:
	rm main basic_handler multi_signal