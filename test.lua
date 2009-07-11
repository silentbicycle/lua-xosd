require "xosd"

-- No configuration.
x = xosd.new()
x:print("no config", true)


-- No configuration, but setting options.
x = xosd.new()
x:set_color("blue")
x:set_pos(100, 200)
x:set_font("-*-fixed-medium-*-*-*-24-*-*-*-*-*-*-*")
x:set_shadow_offset(9)
x:set_align("C")
x:set_timeout(1)
x:print("procedural config", true)


-- Configuration passed in via table.
x = xosd.new{ x=300, y=100, 
              font="-*-fixed-medium-*-*-*-24-*-*-*-*-*-*-*",
              timeout=2, shadow_offset=1, align="l", colour="white",
              lines=3 }
x:print("table config", true)


-- Percentage bar.
x = xosd.new{ colour="red", timeout=1, shadow_offset = 0 }
x:print_percent(75, true)


-- Slider bar, non-blocking display.
x = xosd.new{ colour="blue", timeout=1, shadow_offset = 0 }
x:print_slider(31, false)


-- Another slider, displayed at the same time.
x = xosd.new{ color="purple", pos="Bottom", timeout=1, shadow_offset = 0 }
x:print_slider(15, true)


-- Another non-blocking display.
x = xosd.new{ font="-*-helvetica-medium-r-*-*-*-240-*-*-*-*-*-*",
              shadow_offset=2, outline_offset=1, 
              colour="white", outline_color="DarkSlateGray", shadow_colour="MediumOrchid",
              timeout=4, align="c"}
x:print("Congratulations! You're the next contestant on The Price is Right!")
while x:is_onscreen() do
   -- altrenate blocking mechanism, could yield to coroutine here
end


-- Multiline progress bar display, with hex-triplet-style color.
x = xosd.new{ lines=5, color="#66ddaa", shadow_color="black", shadow_offset=1 }
x:set_timeout(1)
x:set_align("L")
x:print("Progress", false)
local i=0
while i < 100 do
   i = i + math.random(40)
   x:print_percent(math.min(i, 100), true, 2)
end
x:scroll(1)
x:print("Complete!", true, 1)
x:scroll(1)


-- Complete!
x = xosd.new { timeout=1, align="c", color="steelblue", 
               font="-*-helvetica-medium-r-*-*-*-240-*-*-*-*-*-*",
               shadow_color="black", shadow_offset=1, lines=3 }
x:set_pos("Bottom")
x:print("If you can see this, then", true, 2)
x:scroll(1)
x:print("Congratulations", true, 2)
x:scroll(1)
x:print("All tests passed.", true, 3)
x:print("", true, 3)

