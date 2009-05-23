require "xosd"

x = xosd.new()
print(x)
x:print("Blah", true)

x = xosd.new(3)
print(x)
x:set_color("blue")
x:set_pos(400, 200)
x:set_font("-*-terminus-medium-*-*-*-24-*-*-*-*-*-*-*")
x:set_timeout(1)
x:print("Blah blah", true)

x = xosd.new{ x=600, y=150, 
              font="-*-terminus-medium-*-*-*-24-*-*-*-*-*-*-*",
              timeout=2, shadow_offset=3, align="R", colour="red" }
x:show()
x:print("Yea boy!", true)
print(x)

x = xosd.new()
print(x)
x:print("Blah", true)
