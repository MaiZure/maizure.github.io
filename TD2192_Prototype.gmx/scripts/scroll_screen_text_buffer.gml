with obj_dialogue
{
    for (var i=10;i>0;i--)
    {
        display_text_buffer[i] = display_text_buffer[i-1]
        display_color_buffer[i] = display_color_buffer[i-1]
    }
    display_text_buffer[0] = ""
}
