//This method can only be run by obj_ship_ai

var ship;
var ship_id = -1
var ship_dist = 10000
for (var i=0;i<instance_number(obj_ship);i++)
{
    ship = instance_find(obj_ship,i)

    if ship.alignment != agent.alignment
    {
        if point_distance(agent.x,agent.y,ship.x,ship.y) < ship_dist
        {
            ship_id = ship
            ship_dist = point_distance(agent.x,agent.y,ship.x,ship.y)
        }
    }
}
return ship_id
