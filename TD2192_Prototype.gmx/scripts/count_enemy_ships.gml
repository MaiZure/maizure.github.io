var ship, 
var count = 0;
for (var i=0;i<instance_number(obj_ship);i++)
{
    ship = instance_find(obj_ship,i)
    if ship.alignment == ALIGNMENT.enemy
        count++
}
return count
