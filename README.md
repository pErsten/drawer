# drawer
This is more sophisticated console application on drawing than my previous one. It is much faster(get rid of annoying "system("cls")"),
it no more uses of stream input/output, but the opportunities of Windows.h library. Returning to the position, where is something drew
doesn`t mean it would disappear, but the cursor will turn into black. Also, to my mind, the most important innovation here is you can draw
with different colors, which are listed in up-left corner, which you can choose by clicking the corresponding symbol beneath the color 
palette.

Controls:
 w,a,s,d - to move cursor;
 space - to draw that pixel, where cursor is now with corresponding color;
 z - clear pixel from color;
 q - exit.
