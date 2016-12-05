/* Go to the next briefing action */
var briefing = instance_find(obj_briefing,0);
if instance_exists(briefing)
{
    var current_mission = briefing.gamedata.current_mission;
    
    /* brief_phase should always points to next state */
    briefing.brief_state = briefing.brief[current_mission, briefing.brief_phase]
    briefing.brief_phase+=1
}
