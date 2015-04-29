bin=cryctl
version=1.0
distname=$(bin)-$(version)

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man

CFLAGS += -Wall

src=635.c cf_packet.c serial.c show_packet.c
obj=$(src:.c=.o)

all: $(bin)

$(bin): $(obj)
	$(CC) $(CFLAGS) $(obj) -o $@

cf_packet.o: cf_packet.h typedefs.h
serial.o: serial.h typedefs.h
show_packet.o: show_packet.h typedefs.h
