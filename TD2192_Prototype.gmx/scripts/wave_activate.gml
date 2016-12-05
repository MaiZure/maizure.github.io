/* activate all ships in a wave - only callable by obj_hq */
for (var i=0;i<20;i++)
{
    if instance_exists(npc_ship[i]) && npc_ship[i] > 0
    {
        if npc_ship[i].wave_number == argument0
            ship_activate(npc_ship[i])
    }
}

/* set wave message */
hud_message(wave_messages[argument0])
