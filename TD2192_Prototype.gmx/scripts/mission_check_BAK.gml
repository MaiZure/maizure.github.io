if mission_complete == false
{
    switch argument0 /* Current mission */
    {
        /* add new missions here as they are scripted */
        case 1:
        //case 2:
        //case 3:
        {
            if mission_wave == 0 then
                wave_activate(++mission_wave)
            else
            {
                if is_wave_clear(mission_wave)
                    wave_activate(++mission_wave)
            }
                        
            if mission_wave > last_wave then
                mission_complete = true                
        } break;
        
        default: /* default mission objectives */
        {   
            if mission_wave == 0 then
            {
                default_activate()
                mission_wave++
            }
                
            if is_wave_clear(mission_wave)
            {
                mission_complete = true
                hud_message(wave_messages[2])
            }
        } break;
    }
}
