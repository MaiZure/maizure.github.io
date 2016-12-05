/* callable only from obj_ship
   arg0 = gun position
    0 = center
    1 = outside left
    2 = outside right
    3 = inside left
    4 = inside right 
   arg1 = gun type */

var new_x, new_y;    

switch argument0
{
    case 0: new_x = x+lengthdir_x(16,direction); new_y = y+lengthdir_y(16,direction); break;
    case 1: new_x = x+lengthdir_x(8,direction+90); new_y = y+lengthdir_y(8,direction+90); break;
    case 2: new_x = x+lengthdir_x(8,direction-90); new_y = y+lengthdir_y(8,direction-90); break;
    case 3: new_x = x+lengthdir_x(8,direction+20); new_y = y+lengthdir_y(8,direction+20); break;
    case 4: new_x = x+lengthdir_x(8,direction-20); new_y = y+lengthdir_y(8,direction-20); break;
}

var shot = instance_create(new_x,new_y,obj_fire);
shot.source = id
shot.direction = direction
shot.type = argument1
with shot
    event_perform(ev_other,ev_room_start)
