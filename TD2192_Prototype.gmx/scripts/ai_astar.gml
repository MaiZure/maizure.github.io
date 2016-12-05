///Only run this within the obj_ship_ai object
//Argument0 = Start_map_x
//Argument1 = Start_map_y
//Argument2 = End_map_x
//Argument3 = End_map_y
//Argument4 = Number of steps to solve for

var start_x = argument0;
var start_y = argument1;
var goal_x = argument2;
var goal_y = argument3;
var max_steps = argument4;

var current_node, current_node_cost;
var current_x, current_y;
var next_node, next_node_cost;
var next_x, next_y;

var goal_found = false
var finished = false;

ds_priority_clear(astar_frontier_pq)
ds_list_clear(astar_closed_list)
ds_map_clear(astar_relation_map)
ds_map_clear(astar_cost_map)
ds_stack_clear(astar_path_stack)

start_node = map_pos_to_id(argument0,argument1)
goal_node = map_pos_to_id(argument2,argument3)


//Add start node - priority is heuristic only
ds_priority_add(astar_frontier_pq,start_node,mh_dist(start_x,start_y,goal_x,goal_y))
ds_map_add(astar_relation_map,start_node,0)
ds_map_add(astar_cost_map,start_node,0)

while !finished
{
    current_node_best = ds_priority_find_priority(astar_frontier_pq, ds_priority_find_min(astar_frontier_pq)); 
    current_node = ds_priority_delete_min(astar_frontier_pq);
    current_node_cost = ds_map_find_value(astar_cost_map, current_node); 
    current_x = id_to_map_x(current_node)
    current_y = id_to_map_y(current_node)
    ds_list_add(astar_closed_list,current_node)
    
    
    if current_node == goal_node || current_node_cost == max_steps then 
        goal_found = true
    else
    {
        /* Add all 4 grid directions to the queue */
        for (var i=0;i<4;i++)
        {
            switch i
            {
                case 0: next_x = current_x-1; next_y = current_y; break; /*Left*/
                case 1: next_x = current_x+1; next_y = current_y; break; /*Right*/
                case 2: next_x = current_x; next_y = current_y-1; break; /*Up*/
                case 3: next_x = current_x; next_y = current_y+1; break; /*Down*/
            }
            
            if ds_grid_get(map.collision_map,next_x,next_y) == 0
            {
                var next_node = map_pos_to_id(next_x,next_y);
                var next_node_cost = current_node_cost + mh_dist(next_x,next_y,goal_x,goal_y)
                var in_closed = ds_list_find_index(astar_closed_list,next_node)
                var in_pq = ds_priority_find_priority(astar_frontier_pq,next_node)
                
                if in_closed < 0 && (is_undefined(in_pq) || in_pq <= 0)
                {
                    ds_priority_add(astar_frontier_pq,next_node,next_node_cost)
                    ds_map_add(astar_relation_map,next_node,current_node)
                    ds_map_add(astar_cost_map,next_node,current_node_cost+1)
                }
            }
        }
    }
    
    if goal_found == true || ds_priority_empty(astar_frontier_pq)
        finished = true
}

var rollup = false

while !rollup
{
    ds_stack_push(astar_path_stack,current_node)
    current_node = ds_map_find_value(astar_relation_map,current_node)
    if current_node == 0 then rollup = true
}

/* This is our usage output */
if !ds_stack_empty(astar_path_stack)
{
    var first_step = ds_stack_pop(astar_path_stack)
    ai_next_x = id_to_map_x(first_step)
    ai_next_y = id_to_map_y(first_step)
}

