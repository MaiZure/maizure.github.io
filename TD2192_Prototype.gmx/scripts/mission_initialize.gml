/* Init mission by assigning waves to ships and activating wave 0
   Only obj_hq can call this function *
   arg0 is the current mission */

mission_wave=0

set_mission_messages(argument0)
set_mission_parameters(argument0)
set_mission_waves(argument0)

/* set player ship type */
player.ship_type = player_ship_type
   
/* ensure later waves are inactive */
for (var i=0; i<20; i++)
{
    if npc_ship[i] > 0
    {
        if npc_ship[i].wave_number > mission_wave
            ship_inactivate(npc_ship[i])
    }
}

mission_check(argument0)
