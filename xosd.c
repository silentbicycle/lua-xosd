#include <stdio.h>
#include <assert.h>
#include <xosd.h>
#include <lua.h>
#include <lauxlib.h>


static int lx_new(lua_State *L) {
        int lines;
        xosd* osd;

        lines = luaL_optint(L, 1, 1);
        luaL_argcheck(L, lines >= 1, 1, "invalid line count");

        osd = xosd_create(lines);
        assert(osd);

        /* TODO: check for optional second table with other settings */
        /* xosd_set_font(osd, "fixed");
         * xosd_set_colour(osd, "SeaGreen");
         * xosd_set_timeout(osd, 3);
         * xosd_set_shadow_offset(osd, 2); */

        lua_pushlightuserdata(L, osd);

        return 1;               /* osd userdata on stack */
}


/* #define checkxosd(L)                                   \
 *         ((NumArray *)luaL_checkudata(L, 1, "LuaXOSD")) */


static xosd* get_top_xosd(lua_State *L) {
        assert(lua_islightuserdata(L, 1));
        xosd* osd = lua_touserdata(L, 1);
        return osd;
}


static int lx_destroy(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        xosd_destroy(osd);
        lua_pop(L, 1);
        return 0;
}


static int lx_printstr(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        const char *s = (const char*) luaL_checkstring(L, 2);
        int blocking = lua_toboolean(L, 3);

        xosd_display(osd, 0, XOSD_string, s);
        if (blocking) xosd_wait_until_no_display(osd);
        return 0;
}


static int lx_set_timeout(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        int t = luaL_checkint(L, 2);
        xosd_set_timeout(osd, t);
        return 0;
}

static int lx_set_color(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        const char *col = (const char*) luaL_checkstring(L, 2);
        lua_pop(L, 2);

        xosd_set_colour(osd, col);
        
        return 0;
}
static int lx_set_font(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        const char *font = (const char*) luaL_checkstring(L, 2);
        lua_pop(L, 2);

        xosd_set_font(osd, font);
        
        return 0;
}


static int lx_wait(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        xosd_wait_until_no_display(osd);
        return 0;
}


static int lx_show(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        xosd_show(osd);
        return 0;
}
static int lx_hide(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        xosd_hide(osd);
        return 0;
}
static int lx_is_onscreen(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        lua_pushboolean(L, xosd_is_onscreen(osd));
        return 1;
}


static int lx_set_vertical_offset(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        int offset = luaL_checkint(L, 2);
        xosd_set_vertical_offset (osd, offset);
        return 0;
}
static int lx_set_horizontal_offset(lua_State *L) {
        xosd* osd = get_top_xosd(L);
        int offset = luaL_checkint(L, 2);
        xosd_set_horizontal_offset (osd, offset);
        return 0;
}
/* setpos */


static const struct luaL_Reg xosd_metatable [] = {
        {"print", lx_printstr},
        {"destroy", lx_destroy},
        {"set_color", lx_set_color},
        {"set_font", lx_set_font},
        {"set_timeout", lx_set_timeout},
        {"set_horizontal_offset", lx_set_horizontal_offset},
        {"set_vertical_offset", lx_set_vertical_offset},
        {"show", lx_show},
        {"hide", lx_hide},
        {"wait", lx_wait},
        {"is_onscreen", lx_is_onscreen},
        { NULL, NULL },
};        


static const struct luaL_Reg lxosdlib[] = {
        {"new", lx_new},
        {"print", lx_printstr},
        {"destroy", lx_destroy},
        {"set_color", lx_set_color},
        {"set_font", lx_set_font},
        {"set_timeout", lx_set_timeout},
        {"set_horizontal_offset", lx_set_horizontal_offset},
        {"set_vertical_offset", lx_set_vertical_offset},
        {"show", lx_show},
        {"hide", lx_hide},
        {"wait", lx_wait},
        {"is_onscreen", lx_is_onscreen},
        {NULL, NULL},
};


int luaopen_xosd(lua_State *L) {
        luaL_newmetatable(L, "LuaXOSD");

        /* metatable.__index -> metatable */
        lua_pushvalue(L, -1);   /* dup */
        lua_setfield(L, -2, "__index");
        luaL_register(L, NULL, xosd_metatable);
        
        luaL_register(L, "xosd", lxosdlib);
        return 1;
}
