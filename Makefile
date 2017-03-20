CFLAGS=-O0 -lpthread -lm
ALL=jumper bw_server bw_client cartographer loopy test cpu_system_call_running_application proc_call_0 proc_call_1 proc_call_2 proc_call_3 proc_call_4 proc_call_5 proc_call_6 proc_call_7 forkme get_thready forcontext thread_context measure ram_access client server 

all: $(ALL)

#contentious: contentious.c contention.h

#contentious_setup: contentious_setup.c contention.h

#bw_client: bw_client.c bw.h

#bw_server: bw_server.c bw.h

clean: 
	rm -f *.o a.out $(ALL) *.pf *.bk
