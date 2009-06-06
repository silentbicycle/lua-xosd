require "xosd"

x = xosd.new()
x:print("no config", true)

x = xosd.new()
x:set_color("blue")
x:set_pos(100, 200)
x:set_font("-*-fixed-medium-*-*-*-24-*-*-*-*-*-*-*")
x:set_shadow_offset(9)
x:set_align("C")
x:set_timeout(1)
x:print("procedural config", true)

x = xosd.new{ x=300, y=100, 
              font="-*-fixed-medium-*-*-*-24-*-*-*-*-*-*-*",
              timeout=2, shadow_offset=1, align="l", colour="white",
              lines=3 }
x:print("table config", true)

x = xosd.new{ colour="red", timeout=1, shadow_offset = 0 }
x:print_percent(75, true)

x = xosd.new{ colour="blue", timeout=1, shadow_offset = 0 }
x:print_slider(31, false)

x = xosd.new{ color="purple", timeout=1, shadow_offset = 0 }
x:set_pos("Bottom")
x:print_slider(15, true)

x = xosd.new{ font="-*-helvetica-medium-r-*-*-*-240-*-*-*-*-*-*",
              shadow_offset=2, outline_offset=1, 
              colour="white", outline_color="DarkSlateGray", shadow_colour="MediumOrchid",
              timeout=4, align="c"}
x:print("Congratulations! You're the next contestant on The Price is Right!")
while x:is_onscreen() do
   -- altrenate blocking mechanism, could yield to coroutine here
end

x = xosd.new { timeout=3, align="c", color="steelblue", font="fixed", 
               shadow_color="black", shadow_offset=1 }
x:set_pos("Bottom")
x:print("If you could see those, all tests passed.", true)
print("If you could see those, all tests passed.")
