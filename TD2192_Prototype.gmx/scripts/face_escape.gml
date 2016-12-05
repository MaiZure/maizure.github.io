/* Ensures proper values of faces when text reading of binary files */
var output = argument0

if output == $4E then output = $0D
if output == $41 then output = $0A 
if output == $42 then output = $0E 
if output == $20 then output = $09 

return --output /* aligns matching face to start counting at 0 (input assumes 1)
