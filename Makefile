CFLAGS=-O0
ALL=jumper cartographer loopy main test cpu_system_call_running_application

all: $(ALL)

test: test.o

cpu_system_call_running_application: cpu_system_call_running_application.o

jumper: jumper.o

cartographer: cartographer.o

loopy: loopy.o

main: main.o

clean: 
	rm -f *.o a.out $(ALL)
