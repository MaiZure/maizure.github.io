for (var i=0; i<20; i++)
{
    if npc_ship[i] > 0
    {
        if npc_ship[i].alignment == ALIGNMENT.enemy
            ship_activate(npc_ship[i])
    }
}

hud_message(wave_messages[1])
