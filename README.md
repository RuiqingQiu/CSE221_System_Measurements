# CSE221_System_Measurements

## Files:

### CPU experiments
1. measure.c (rdtsc instruction overhead) 

1. cpu\_system\_call\_running\_application.c  (system call overhead)

1. loopy.c (loop overhead)

1. proc\_call\_0.c (zero argument function overhead)

1. proc\_call\_1.c (one argument function overhead)

1. proc\_call\_2.c (two argument function overhead)

1. proc\_call\_3.c (three argument function overhead)

1. proc\_call\_4.c (four argument function overhead)

1. proc\_call\_5.c (five argument function overhead)

1. proc\_call\_6.c (six argument function overhead)

1. proc\_call\_7.c (seven argument function overhead)

1. forkme.c (process creation and run time)

1. get\_thready.c (kernel thread creation and run time)

1. forcontext.c (process context switch time)

1. thread\_context.c (kernel thread context switch time)

### Memory experiments
1. jumper.c (memory latency)

1. test.c (memory bandwidth)

1. cartographer.c  (page fault latency)

### Network experiments
1. client_RTT.c server_RTT.c (roundtrip time and setup teardown time)

1. bw_client.c bw_server.c (peak bandwidth)

### File System experiments
1. file_read.c (size of file cache)

1. seq_read.c rand_read.c (file read time)

1. seq_read_remote.c rand_read_remote.c (remote file read time)

1. contentious.c (contention)

### Other
1. run\_test.sh (convenience script for running a file multiple times)

1. rds.h (header file containing macros for RDTSC, RDTSCP, and CPUID 
instructions)

