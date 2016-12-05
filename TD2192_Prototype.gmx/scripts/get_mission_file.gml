/* returns the appropriate modified mission file name for the current mission
   arg0 is the current mission */
   
var file_ext, mission_num, fname;

if argument0 < 60 then
    file_ext = ".MS3"
if argument0 < 41 then
    file_ext = ".MS2"
if argument0 < 21 then
    file_ext = ".MS1"

mission_num = argument0-20*floor((argument0-1)/20)
fname = "M"+string(mission_num)+file_ext;

return fname
