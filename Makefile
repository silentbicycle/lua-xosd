include config.mk

all:	${LIBFILE}

clean:
	rm -f ${LIBFILE}

${LIBFILE}: ${LIBNAME}.c
	${CC} -o $@ $> ${CFLAGS} ${SHARED} ${LUA_FLAGS} \
	${INC} ${LIB_PATHS} ${LIBS}

test: ${LIBFILE}
	${LUA} ${TESTSUITE}

lint: ${LIBNAME}.c
	${LINT} ${INC} ${LUA_INC} $>

install: ${LIBFILE}
	cp ${INST_LIB} ${LUA_DEST_LIB}
	cd ${LUA_DEST_LIB} && ln -s ${INST_LIB} ${LIBNAME}${LIBEXT}

uninstall: 
	rm -f ${LUA_DEST_LIB}${LIBNAME}${LIBEXT}*
