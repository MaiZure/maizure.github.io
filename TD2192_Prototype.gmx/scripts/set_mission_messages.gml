/* Sets the messages for missions -only callable by obj_hq 
   argument 0 - current mission
   
/* set a default array to avoid invalid access */
switch argument0
{
    case 1:
    {
        wave_messages[1] = "destroy the two trucks heading for the north entrance"
        wave_messages[2] = "take out the trucks entering from the west, and kill escort"
        wave_messages[3] = "destroy the two trucks that are arriving from the north"
        wave_messages[4] = "a vulture patrol skid is entering from the east"
        wave_messages[5] = "mission complete.  return to base, velasquez"
    } break;
    default:
    {
        wave_messages[1] = choose("Give em hell, vel", "Destroy all vultures ships")
        wave_messages[2] = choose("Mission Complete, Vel. Return to base.", "Come on back, vel")
    }; break;
}
