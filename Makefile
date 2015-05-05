
make_cmd = ${MAKE} -C src $*

all:
	${make_cmd}
	mkdir -p bin
	cp src/cryctl bin

options:
	${make_cmd}

clean:
	${make_cmd}
	rm -rf bin
