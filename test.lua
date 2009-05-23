require "xosd"

function print_and_destroy(s)
   x = xosd.new()
   x:set_color("green")
   x:set_vertical_offset(20)
   x:set_horizontal_offset(400)
   x:set_timeout(1)

   print(x)

   print("before -- ", x:is_onscreen(x))
   x:set_font("-*-terminus-medium-*-*-*-12-*-*-*-*-*-*-*")
   x:print(s)
   print(x)
   print("during -- ", x:is_onscreen(x))
   x:wait(x)
   print("after -- ", x:is_onscreen(x))
end

print_and_destroy"test passed"
print_and_destroy"yeah, boy! flavor flav!"
