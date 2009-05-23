require "xosd"

x = xosd.new()
print(x)
x:print("Blah", true)

x = xosd.new()
print(x)
x:set_color("blue")
x:set_pos(100, 200)
x:set_font("-*-terminus-medium-*-*-*-24-*-*-*-*-*-*-*")
x:set_shadow_offset(9)
x:set_align("C")
x:set_timeout(1)
x:print("Blah blah", true)

x = xosd.new{ x=300, y=100, 
              font="-*-terminus-medium-*-*-*-24-*-*-*-*-*-*-*",
              timeout=2, shadow_offset=1, align="l", colour="white",
              lines=3 }
x:print("Yea boy!", true)
print(x)

x = xosd.new{ colour="red", timeout=1, shadow_offset = 3 }
x:print_percent(75, true)

x = xosd.new{ colour="blue", timeout=1, shadow_offset = 3 }
x:print_slider(15, true)

x = xosd.new{ colour="purple", timeout=1, shadow_offset = 3 }
x:set_pos("Bottom")
x:print_slider(15, true)
