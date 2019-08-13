#version 410
layout(location = 0) in vec3 vertex_position;

# define PI 3.14159265359

flat out vec4 colour_f;
smooth out vec4    colour_s;
out    vec2 texture_coordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec2    cylinder_mapping()
{
    float    u;
    float    v;

    u = 0.5 + atan(vertex_position.z, vertex_position.x) / PI * 0.5;
    v = vertex_position.y / 10.0;
    return (vec2(u, v) * 15);
}

void main ()
{
    colour_s = vec4(vertex_position * 0.4f + 0.4f, 1.0f);
    colour_f = colour_s;
    gl_Position = projection * view * model * vec4(vertex_position, 1.0);
    texture_coordinates = cylinder_mapping();
}
