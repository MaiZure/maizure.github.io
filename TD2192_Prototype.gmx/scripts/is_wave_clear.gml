/* Checks if a wave has been cleared
   arg0 is the wave to check
   don't use with wave 0 
   only callable by obj_hq */
   
for (var i=0; i<20; i++)
{
    if npc_ship[i] > 0 && instance_exists(npc_ship[i])
    {
        if npc_ship[i].wave_number == argument0 && ds_list_find_index(target_list, npc_ship[i]) >= 0
            return false
    }
}

return true
