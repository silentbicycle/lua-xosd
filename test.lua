require "xosd"

function print_and_destroy(s)
   x = xosd.new()
   xosd.set_color(x, "green")
   xosd.set_vertical_offset(x, 20)
   xosd.set_horizontal_offset(x, 400)
   xosd.set_timeout(x, 1)

   print("before -- ", xosd.is_onscreen(x))
   xosd.set_font(x, "-*-terminus-medium-*-*-*-12-*-*-*-*-*-*-*")
   xosd.print(x, s)
   print("during -- ", xosd.is_onscreen(x))
   xosd.wait(x)
   print("after -- ", xosd.is_onscreen(x))
   xosd.destroy(x)
end

print_and_destroy"test passed"
print_and_destroy"yeah, boy! flavor flav!"
