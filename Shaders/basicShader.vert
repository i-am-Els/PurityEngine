#version 400 core
in vec3 pos;
out vec3 position;

void main()
{
    gl_Position = vec4(pos, 1.0f);
    position = pos;
}