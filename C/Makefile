CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wstrict-prototypes -O2 -funroll-loops -s -pipe
BINS=minigrep urandpass

all:	$(BINS)

clean:
	rm -f $(BINS)

minigrep:
	$(CC) $(CFLAGS) -o minigrep minigrep.c

urandpass:
	$(CC) $(CFLAGS) -o urandpass urandpass.c

