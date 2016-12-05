/* argument0 is the ship id */
var mission = instance_find(obj_hq,0);

argument0.ai.mode = AIMODE.inactive
argument0.visible = false

if ds_list_find_index(mission.target_list,argument0) > -1
    ds_list_delete(mission.target_list,ds_list_find_index(mission.target_list,argument0))
