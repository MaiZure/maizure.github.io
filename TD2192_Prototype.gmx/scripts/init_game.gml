randomize()
irandom_range(1,100)

global.scale = 1//3

global.little_font = font_add_sprite_ext(LT2,'ABCDEFGHIJKLMNOPQRSTUVWXYZ<>0123456789.",-?! ',true,1)
global.mission_font = font_add_sprite_ext(CIN,'ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-?!: ',true,1)
global.big_font = font_add_sprite_ext(LTR,'ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-',true,1)

instance_create(0,0,obj_currentgame)
instance_create(0,0,obj_keyboard)
instance_create(0,0,obj_music)
