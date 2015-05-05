
make_cmd = ${MAKE} -C src $*

all:
	${make_cmd}

options:
	${make_cmd}

clean:
	${make_cmd}
