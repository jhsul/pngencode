CC = cc
CFLAGS =  "-lpng"
pngencode: main.c encode.c
	$(CC) $(CFLAGS) main.c encode.c -o pngencode