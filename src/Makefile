bin=cryctl
version=1.0
distname=${bin}-${version}

PREFIX ?= /usr/local
BINDIR ?= ${PREFIX}/bin
MANDIR ?= ${PREFIX}/share/man

CFLAGS += -Wall

src=635.c cf_packet.c serial.c show_packet.c
obj=${src:.c=.o}

all: ${bin}

options:
	@echo CFLAGS = ${CFLAGS}
	@echo PREFIX = ${PREFIX}
	@echo BINDIR = ${BINDIR}
	@echo MANDIR = ${MANDIR}

${bin}: ${obj}
	${CC} ${CFLAGS} ${obj} -o ${@}

clean:
	rm -f ${obj}
	rm -f ${bin}
	rm -f Makefile.bak

depend:
	makedepend -Y ${src}

# Dependencies
# DO NOT DELETE

635.o: typedefs.h serial.h cf_packet.h show_packet.h
cf_packet.o: typedefs.h serial.h cf_packet.h
serial.o: typedefs.h serial.h
show_packet.o: typedefs.h cf_packet.h show_packet.h
