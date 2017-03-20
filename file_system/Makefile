CFLAGS=-O0 -lpthread -lm
ALL=file_read make_file_size contentious contentious_setup seq_read rand_read seq_read_remote rand_read_remote

all: $(ALL)

#contentious: contentious.c contention.h

#contentious_setup: contentious_setup.c contention.h

#bw_client: bw_client.c bw.h

#bw_server: bw_server.c bw.h

clean: 
	rm -f *.o a.out $(ALL) *.pf *.bk
