# Project
LIBNAME=	xosd
LIBVER=		0.3

# Lua-specific paths and libraries
LUA_VER=	5.1
LUA=		/usr/bin/lua
LUA_LIBPATH=	-L/usr/lib/
LUA_LIBS=	-llua$(LUA_VER) -lm
LUA_INC=	-I/usr/include/lua$(LUA_VER)/
LUA_FLAGS=	$(LUA_INC) $(LUA_LIBPATH) $(LUA_LIBS)


# Where compiled libraries and .lua sources install.
LUA_DEST_LIB=	/usr/lib/lua/${LUA_VER}/
LUA_DEST_LUA=	/usr/share/lua/${LUA_VER}/


# Additional C settings
CC=		cc
#LIB_PATHS=	-L/usr/X11R6/lib/
LIBS=		-lX11 -lxosd
INC=		-I/usr/include/X11/
CFLAGS=		-Wall
SHARED=		-shared -fPIC
LIBEXT=		.so


# Other tools, optional
LINT=		lint
TESTSUITE=	test.lua
ARCHNAME= 	lua-${LIBNAME}


# Build targets
LIBPREFIX=	l
LIBFILE=	${LIBNAME}${LIBEXT}.${LIBVER}
INST_LIB=	${LIBFILE}
