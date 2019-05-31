#version 410
flat in vec4 colour_f;
smooth in vec4 colour_s;
in vec2 texture_coordinates;

uniform bool flatmode;
uniform sampler2D   ltexture;

out vec4 frag_colour;

void main ()
{
    if (flatmode)
    frag_colour = colour_f;
    else
    frag_colour = texture(ltexture, texture_coordinates);
}
