/* 
Register object as keyboard listener
Argument0 = unique object id
*/

var keyboard = instance_find(obj_keyboard,0)
var object_id = argument0;

with object_id
        command_stack = ds_stack_create();

ds_list_add(keyboard.target_list, object_id)
