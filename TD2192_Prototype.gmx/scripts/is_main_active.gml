///Checks various conditions that would make main inactive.
//Not quite as robust as dedicating an inactive state which includes an
//interface for activation and deactivation

if !instance_exists(obj_mainmenu) return false;
if instance_exists(obj_mainpopup) return false;
if instance_exists(obj_loadsave) return false;

return true
