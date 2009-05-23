#include <stdlib.h>
#include <xosd.h>
#include <lua.h>
#include <lauxlib.h>


/* Wrap the xosd pointer in a full userdata for garbage collection. */
typedef struct LuaXOSD {
        xosd* disp;
} LuaXOSD;


#define check_xosd(L)                                   \
        ((LuaXOSD *)luaL_checkudata(L, 1, "LuaXOSD"))


static int get_line_ct(lua_State *L);
static void init_LuaXOSD(lua_State *L, int lines);


/**************
 * Allocation *
 **************/

/* Create a new Lua XOSD object.
 * Optional arguments: int -> number of lines, table -> named options.
 * */
static int lx_new(lua_State *L) {
        int lines = get_line_ct(L);
        init_LuaXOSD(L, lines);

        if (lua_istable(L, 1)) {
                /* Do other config. */
                /* set_options(L, d,  */
        }

        return 1;               /* osd userdata on stack */
}


/* Init: Get the line count. */
static int get_line_ct(lua_State *L) {
        if (lua_isnumber(L, 1)) {
                return lua_tointeger(L, 1);
        } else if (lua_istable(L, 1)) {
                lua_getfield(L, 1, "lines");
                return luaL_optint(L, 2, 1);
        } else {
                return 1;
        }
}


/* Initialize a LuaXOSD userdata. */
static void init_LuaXOSD(lua_State *L, int lines) {
        xosd* osd;              /* pointer, to wrap in userdata. */
        LuaXOSD* d;

        luaL_argcheck(L, lines >= 1, 1, "invalid line count");
        osd = xosd_create(lines);
        if (!osd) exit(EXIT_FAILURE);
        
        d = (LuaXOSD*)lua_newuserdata(L, sizeof(LuaXOSD));
        d->disp = osd;
        
        luaL_getmetatable(L, "LuaXOSD");
        lua_setmetatable(L, -2);
}


/* Destroy xosd pointer, called by __gc. */
static int lx_destroy(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        xosd_destroy(osd->disp);
        return 0;
}


/* Get string representation of LuaXOSD. */
static int lx_tostring(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        lua_pushfstring(L, "xosd(%d, %s)",
            xosd_get_number_lines(osd->disp),
            xosd_is_onscreen(osd->disp) ? "onscreen" : "hidden");
        return 1;
}


/*********
 * Lines *
 *********/

/* Scroll. */
static int lx_scroll(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        int lines = luaL_checkint(L, 2);
        xosd_scroll(osd->disp, lines);
        return 0;
}


/* Get the number of lines. */
static int lx_get_line_ct(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        lua_pushinteger(L, xosd_get_number_lines(osd->disp));
        return 1;
}


/************
 * Settings *
 ************/

/* Set the timeout. */
static int lx_set_timeout(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        int t = luaL_checkint(L, 2);
        xosd_set_timeout(osd->disp, t);
        return 0;
}


/* Set the color. */
static int lx_set_color(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        const char *col = (const char*) luaL_checkstring(L, 2);
        xosd_set_colour(osd->disp, col);
        
        return 0;
}


/* Set the font. (What does it do with nonexistant fonts?) */
static int lx_set_font(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        const char *font = (const char*) luaL_checkstring(L, 2);

        xosd_set_font(osd->disp, font);
        
        return 0;
}


/* Set the shadow offset. */
static int lx_set_shadow_offset(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        int o = luaL_checkint(L, 2);
        xosd_set_shadow_offset(osd->disp, o);
        return 0;
}


/* Set the alignment. Uses 'L', 'C', 'R'. */
static int lx_set_align(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        const char *key = luaL_checkstring(L, 2); /* L, C, R */
        xosd_align align;
        
        switch (*key) {
                case 'l':
                case 'L': align = XOSD_left; break;
                case 'c':
                case 'C': align = XOSD_center; break;
                case 'r':
                case 'R': align = XOSD_right; break;
                default:
                        lua_pushstring(L, "Invalid align key, must be L/C/R.");
                        lua_error(L);
                }

        if (align) xosd_set_align(osd->disp, align);

        return 0;
}


/* Set the vertical offset. */
static int lx_set_vertical_offset(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        int offset = luaL_checkint(L, 2);
        xosd_set_vertical_offset (osd->disp, offset);
        return 0;
}


/* Set the horizontal offset. */
static int lx_set_horizontal_offset(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        int offset = luaL_checkint(L, 2);
        xosd_set_horizontal_offset (osd->disp, offset);
        return 0;
}


/* Set position. */
static int lx_set_pos(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        int xo = luaL_checkint(L, 2);
        int yo = luaL_checkint(L, 3);
        xosd_set_horizontal_offset (osd->disp, xo);
        xosd_set_vertical_offset (osd->disp, yo);
        return 0;
}


/**************
 * Displaying *
 **************/

/* One of XOSD_percentage,  XOSD_slider or XOSD_string. */

/* Display a string. */
static int lx_printstr(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        const char *s = (const char*) luaL_checkstring(L, 2);
        int blocking = lua_toboolean(L, 3);

        xosd_display(osd->disp, 0, XOSD_string, s);
        if (blocking) xosd_wait_until_no_display(osd->disp);
        return 0;
}



/* Block until done displaying. */
static int lx_wait(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        xosd_wait_until_no_display(osd->disp);
        return 0;
}


/* Show a hidden OSD. */
static int lx_show(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        xosd_show(osd->disp);
        return 0;
}


/* Hide the OSD. */
static int lx_hide(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        xosd_hide(osd->disp);
        return 0;
}


/* Is it onscreen? */
static int lx_is_onscreen(lua_State *L) {
        LuaXOSD* osd = check_xosd(L);
        lua_pushboolean(L, xosd_is_onscreen(osd->disp));
        return 1;
}


/****************
 * Module setup *
 ****************/

static const struct luaL_Reg xosd_metatable [] = {
        { "print", lx_printstr },
        { "destroy", lx_destroy },
        { "scroll", lx_scroll },
        { "get_line_ct", lx_get_line_ct },
        { "set_align", lx_set_align },
        { "set_color", lx_set_color },
        { "set_font", lx_set_font },
        { "set_timeout", lx_set_timeout },
        { "set_horizontal_offset", lx_set_horizontal_offset },
        { "set_vertical_offset", lx_set_vertical_offset },
        { "set_pos", lx_set_pos },
        { "set_shadow_offset", lx_set_shadow_offset },
        { "show", lx_show },
        { "hide", lx_hide },
        { "wait", lx_wait },
        { "is_onscreen", lx_is_onscreen },
        { "__gc", lx_destroy },
        { "__tostring", lx_tostring },
        { NULL, NULL },
};        


static const struct luaL_Reg lxosdlib[] = {
        { "new", lx_new },
        { NULL, NULL },
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
