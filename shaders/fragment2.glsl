#version 410
flat in vec4 colour_f;
smooth in vec4 colour_s;

out vec4 frag_colour;
uniform bool flatmode;

void main ()
{
    if (flatmode)
        frag_colour = colour_f;
    else
        frag_colour = colour_s;
}
