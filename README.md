Lua-XOSD
========

This is a Lua wrapper for the XOSD library.

The code for Lua-XOSD is released under the MIT License.

Please send comments, suggestions, bug reports, etc. to
<vokes.s@gmail.com> .


Building and installation
-------------------------

In order to build and install lua-xosd, you will need:

  + [Lua][] 5.1 - 5.3 and its header files (tested with 5.1.5, 5.2.4 and 5.3.3)
  + [XOSD][], naturally.

[Lua]: http://lua.org
[XOSD]: http://www.ignavus.net/software.html

To build, edit the paths in *config.mk* to match your system
configuration (or replace with one of the provided samples), and
then type "make". To run a test suite, "make test". To install, 
"make install".


Usage
-----

First,

    local xosd = require "xosd"
    disp = xosd.new()

new can be passed an optional table with the following settings:

  + x and y coordinates ("x", "y")
  + colors ("color", "shadow_color", "outline_color")
           All can be spelled "colour", as a brief nod to i18n.
           Colors can be specified by name (see *rgb.txt* in your
           X distribution) or by hex triplets such as "#66ddaa".
  + offsets ("shadow_offset", "outline_offset")
  + "timeout" (in seconds)
  + "font" (a name, e.g. "fixed", or values used by e.g. xfontsel)
  + "align" ("L", "C", "R", case insensitive - left, center, right)
  + "pos" ("T", "M", "B", case insensitive - top, middle, bottom)


For example:

    osd = xosd.new{ font="-*-helvetica-medium-r-*-*-*-240-*-*-*-*-*-*",
                    shadow_offset=2, outline_offset=1, 
                    colour="white", outline_color="DarkSlateGray", 
                    shadow_colour="MediumOrchid", timeout=4, align="c" }


The following methods can be used to change those settings later:

  + set_align( align )
  + set_color( color_name )
  + set_shadow_color( color_name )
  + set_outline_color( color_name )
  + set_font( font_key )
  + set_timeout( seconds )
  + set_horizontal_offset( pixels )
  + set_vertical_offset( pixels )
  + set_pos( (x, y) OR "Top", "Middle", or "Bottom" )
  + set_shadow_offset( pixels )
  + set_outline_offset( pixels )


Displaying is controlled by the following methods:

  + print( string, [blocking, line] ): 
        If blocking, pause until timeout, otherwise display is asynchronous.
        Line count is for multi-line displays, and defaults to 1.
  + print_percent( percent, [blocking, line] ):
        Percent is between 0 and 100.
  + print_slider( percent, [blocking, line] )
  + show()
  + hide()
  + wait():                   Wait (blocking) until timeout.


Other misc. methods:

  + is_onscreen():            Is it currently on-screen? 
  + get_line_count():         Get the number of lines in the display.
  + scroll( lines ):          Scroll a multi-line display.


For usage examples, see *test.lua*.
