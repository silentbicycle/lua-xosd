#ifndef LXOSD_H
#define LXOSD_H

/* Wrap the xosd pointer in a full userdata for garbage collection. */
typedef struct LuaXOSD {
        xosd* disp;
} LuaXOSD;


/* Defaults. */
#define		LX_DEF_X_OFFSET		20
#define		LX_DEF_Y_OFFSET		20
#define		LX_DEF_SHADOW_OFFSET	0
#define		LX_DEF_TIMEOUT		1
#define		LX_DEF_FONT		"fixed"
#define		LX_DEF_ALIGN		"L"
#define		LX_DEF_COLOUR		"green"


static int get_line_ct(lua_State *L);
static LuaXOSD* init_LuaXOSD(lua_State *L, int lines);
static xosd_align align_of_str(lua_State *L, const char *key);


#define check_xosd(L)                                   \
        ((LuaXOSD *)luaL_checkudata(L, 1, "LuaXOSD"))

#endif
