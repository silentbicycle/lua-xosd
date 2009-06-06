include config.mk

all:	${LIBNAME}${LIBEXT}

clean:
	@rm -f ${LIBNAME}${LIBEXT}

test: ${LIBNAME}${LIBEXT}
	${LUA} ${TESTSUITE}

lint: ${LIBNAME}.c
	${LINT} ${INC} ${LUA_INC} $>

install: ${LIBNAME}${LIBEXT}
	cp ${INST_LIB} ${LUA_DEST_LIB}

${LIBNAME}${LIBEXT}: ${LIBNAME}.c
	${CC} -o $@ $> ${CFLAGS} ${SHARED} ${LUA_FLAGS} ${INC} ${LIB_PATHS} ${LIBS}
