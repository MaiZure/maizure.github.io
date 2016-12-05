/* 
Deregister object as keyboard listener 
Argument0 = Unique object id
*/

var keyboard = instance_find(obj_keyboard,0)
var object_id = argument0;

ds_list_delete(keyboard.target_list,ds_list_find_index(keyboard.target_list,object_id))

with object_id
    ds_stack_destroy(command_stack)
