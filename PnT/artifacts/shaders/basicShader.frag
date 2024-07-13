#version 400 core
out vec4 color;
in vec3 position;
void main()
{
  color = vec4(position.xz * 2, 1.0f, 1.0f);
}