CFLAGS=-O0
ALL=jumper cartographer loopy test cpu_system_call_running_application proc_call_0 proc_call_1 proc_call_2 proc_call_3 proc_call_4 proc_call_5 proc_call_6 proc_call_7 main

all: $(ALL)

proc_call_0: proc_call_0.o

test: test.o

cpu_system_call_running_application: cpu_system_call_running_application.o

jumper: jumper.o

cartographer: cartographer.o

loopy: loopy.o

main: main.o

clean: 
	rm -f *.o a.out $(ALL)
