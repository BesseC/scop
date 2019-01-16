#version 410
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

flat out vec4 colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main ()
{
  colour = vec4(vertex_position * 0.4f + 0.4f, 1.0f);
  gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}
