CC=gcc -pthread
CFLAGS=-g 

# -Wall -Werror -Wextra -Wwrite-strings

build: prog4.c
	${CC} ${CFLAGS} -o prog4 mopt.c sem.c shbuf.c prog4.c 

clean:
	rm -f prog4