#ifndef LXOSD_H
#define LXOSD_H

/* Wrap the xosd pointer in a full userdata, for garbage collection. */
typedef struct LuaXOSD {
        xosd* disp;
} LuaXOSD;


/* Defaults. */
#define		LX_DEF_X_OFFSET		20
#define		LX_DEF_Y_OFFSET		20
#define		LX_DEF_SHADOW_OFFSET	0
#define		LX_DEF_SHADOW_COLOR	"black"
#define		LX_DEF_OUTLINE_OFFSET	0
#define		LX_DEF_OUTLINE_COLOR	"black"
#define		LX_DEF_TIMEOUT		1
#define		LX_DEF_FONT		"fixed"
#define		LX_DEF_ALIGN		"L"
#define		LX_DEF_COLOUR		"green"
#define 	LX_DEF_POS		"T"


static xosd_align align_of_str(lua_State *L, const char *key);
static int get_line_ct(lua_State *L);
static int get_optint_field(lua_State *L, const char* key, int def);
static const char* get_optstring_field(lua_State *L,
    const char* key, const char* def);
static void error(lua_State *L, const char* str);
static void err_wrap(lua_State *L, int status, const char* name);
static LuaXOSD* init_LuaXOSD(lua_State *L, int lines);
static xosd_pos pos_of_str(const char *key);
static int set_defaults(lua_State *L, xosd* x);

/* All direct C<->Lua functions have the type of
 * static int funcname(lua_State *L) .*/

#define check_xosd(L)                                   \
        ((LuaXOSD *)luaL_checkudata(L, 1, "LuaXOSD"))

#endif
