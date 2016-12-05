var shp = instance_create(argument0,argument1,obj_ship);

shp.ship_type = argument2
shp.x = argument0
shp.y = argument1
    
var shp_ai = instance_create(0,0,obj_ship_ai);
    shp_ai.agent = shp

shp.ai = shp_ai


with shp
    event_user(0)

return shp
