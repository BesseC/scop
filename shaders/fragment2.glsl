#version 410
flat in vec4 colour_f;
smooth in vec4 colour_s;
in vec2 texture_coordinates;

uniform bool flatmode;
uniform bool textmode;
uniform sampler2D   ltexture;
uniform bool graymode;

out vec4 frag_colour;

void main ()
{
    float	grey;

    if (flatmode)
        frag_colour = colour_f;
    else 
        frag_colour = colour_s;
    if (textmode)
        frag_colour = texture(ltexture, texture_coordinates);
    if (graymode)
    {
		grey = (0.2125 * frag_colour.x + 0.7154 * frag_colour.y + 0.0721 * frag_colour.z) / 3.0f;
		frag_colour = vec4(grey, grey, grey, 1.0f);
    }
}
