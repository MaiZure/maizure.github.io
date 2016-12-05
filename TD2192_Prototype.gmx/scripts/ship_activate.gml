/* argument0 is the ship id */
var mission = instance_find(obj_hq,0);

argument0.ai.mode = AIMODE.move
argument0.visible = true

if argument0.alignment == ALIGNMENT.enemy
    ds_list_add(mission.target_list,argument0)

