# Lua-specific paths and libraries
LUA_VER=	5.1
LUA=		/usr/local/bin/lua
LUA_LIBPATH=	-L/usr/local/lib/
LUA_LIBS=	-llua -lm
LUA_INC=	-I/usr/local/include/
LUA_FLAGS=	${LUA_INC} ${LUA_LIBPATH} ${LUA_LIBS}


# Where compiled libraries and .lua sources install.
LUA_DEST_LIB=	/usr/local/lib/lua/${LUA_VER}/
LUA_DEST_LUA=	/usr/local/share/lua/${LUA_VER}/


# Additional C settings
CC=		cc
LIB_PATHS=	-L/usr/X11R6/lib/
LIBS=		-lxosd -lX11
INC=		-I/usr/X11R6/include/
CFLAGS=		-Wall
SHARED=		-shared -fPIC
LIBEXT=		.so
LINT=		lint


# Build targets
LIBNAME=	xosd
TESTSUITE=	test.lua
INST_LIB=	${LIBNAME}${LIBEXT}
