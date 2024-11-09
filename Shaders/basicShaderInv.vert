#version 400 core
uniform vec2 posit;
in vec3 pos;
out vec3 position;

void main()
{
    gl_Position = vec4(point, 1.0f);
    vec3 point = vec3(posit, 0.0f) - pos;
    position = point;
}