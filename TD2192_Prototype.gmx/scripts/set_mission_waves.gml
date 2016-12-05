/* Assign NPC ships to waves - only callable by obj_hq
   due to npc_ship[] handle scope */

switch argument0 /* current mission */
{
    case 1:
    {
        npc_ship[0].wave_number = 1;    npc_ship[1].wave_number = 1
        npc_ship[2].wave_number = 1;    npc_ship[3].wave_number = 1
        npc_ship[4].wave_number = 2;    npc_ship[5].wave_number = 2
        npc_ship[6].wave_number = 2;    npc_ship[7].wave_number = 2
        npc_ship[8].wave_number = 3;    npc_ship[9].wave_number = 3
        npc_ship[10].wave_number = 4;   npc_ship[11].wave_number = 0
        npc_ship[12].wave_number = 0;   npc_ship[13].wave_number = 0
        npc_ship[14].wave_number = 0;   npc_ship[15].wave_number = 0
        npc_ship[16].wave_number = 0;   npc_ship[17].wave_number = 0
        npc_ship[18].wave_number = 0;   npc_ship[19].wave_number = 0
        
        last_wave = 4
    } break;
    default: last_wave = 1; break;
}
