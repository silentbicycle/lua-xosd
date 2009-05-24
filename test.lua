require "xosd"

x = xosd.new()
print(x)
x:print("no config", true)

x = xosd.new()
print(x)
x:set_color("blue")
x:set_pos(100, 200)
x:set_font("-*-terminus-medium-*-*-*-24-*-*-*-*-*-*-*")
x:set_shadow_offset(9)
x:set_align("C")
x:set_timeout(1)
x:print("procedural config", true)

x = xosd.new{ x=300, y=100, 
              font="-*-terminus-medium-*-*-*-24-*-*-*-*-*-*-*",
              timeout=2, shadow_offset=1, align="l", colour="white",
              lines=3 }
x:print("table config", true)
print(x)

x = xosd.new{ colour="red", timeout=1, shadow_offset = 3 }
x:print_percent(75, true)

x = xosd.new{ colour="blue", timeout=1, shadow_offset = 3 }
x:print_slider(31)

x = xosd.new{ colour="purple", timeout=1, shadow_offset = 3 }
x:set_pos("Bottom")
x:print_slider(15, true)

x = xosd.new{ font="-*-helvetica-medium-r-*-*-*-240-*-*-*-*-*-*",
           shadow_offset=2, timeout=3, colour="white"}
x:print("Congratulations! You're the next contestant on The Price is Right!")
while x:is_onscreen() do
   -- altrenate blocking mechanism, could yield to coroutine here
end
