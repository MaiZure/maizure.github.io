if mission_complete == false
{
    /* Start mission */
    if mission_wave == 0 then
        wave_activate(++mission_wave)
    else /* Continue mission */
    {
        if is_wave_clear(mission_wave)
            wave_activate(++mission_wave)
    }
                
    if mission_wave > last_wave then
        mission_complete = true                
}
