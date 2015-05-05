bin=cryctl
version=1.0
distname=$(bin)-$(version)

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man

CFLAGS += -Wall

src=./src/635.c ./src/cf_packet.c ./src/serial.c src/show_packet.c
obj=$(src:.c=.o)

all: $(bin)

$(bin): $(obj)
	$(CC) $(CFLAGS) $(obj) -o $@

options:
	@echo Build Options:
	@echo CFLAGS = ${CFLAGS}

cf_packet.o: src/cf_packet.h src/typedefs.h
serial.o: src/serial.h src/typedefs.h
show_packet.o: ./src/show_packet.h src/typedefs.h
