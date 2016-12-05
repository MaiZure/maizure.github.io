var ship;
var ship_id = -1
for (var i=0;i<instance_number(obj_ship);i++)
{
    ship = instance_find(obj_ship,i)
    if ship.is_player == true
        ship_id = ship
}
return ship_id
