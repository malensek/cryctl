bin=635
version=1.0
distname=$(bin)-$(version)

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
CONFIG_FOLDER ?= $(HOME)/.config/$(bin)
LEVELDIR ?= $(PREFIX)/share/$(bin)/levels
MANDIR ?= $(PREFIX)/share/man

CFLAGS += -Wall

src=635.c cf_packet.c serial.c show_packet.c
obj=$(src:.c=.o)
distrib=$(tnibbles_src) gameboard.h terminibbles.1 levels \
		LICENSE.txt LEVELS.txt README.md Makefile

all: $(bin)

$(bin): $(obj)
	$(CC) $(CFLAGS) $(obj) -o $@

cf_packet.o: cf_packet.h typedefs.h
serial.o: serial.h typedefs.h
show_packet.o: show_packet.h typedefs.h
