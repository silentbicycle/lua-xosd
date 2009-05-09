CC=		cc
LUA_LIBPATHS=   -L/usr/local/lib/
LUA_LIBS=	-llua -lm
LUA_INC=	-I/usr/local/include/
LUA_FLAGS=	${LUA_INC} ${LUA_LIBPATHS} ${LUA_LIBS}

LIB_PATHS=	-L/usr/X11R6/lib/
LIBS=		-lxosd -lX11
INC=		-I/usr/X11R6/include/
CFLAGS=		-shared -fPIC
LIBNAME=	xosd
LIBEXT=		.so

all:	${LIBNAME}${LIBEXT}

clean:
	@rm -f ${LIBNAME}${LIBEXT}

test: ${LIBNAME}${LIBEXT}
	lua test.lua

${LIBNAME}${LIBEXT}: ${LIBNAME}.c
	${CC} -o $@ $> ${CFLAGS} ${LUA_FLAGS} ${INC} ${LIB_PATHS} ${LIBS}
