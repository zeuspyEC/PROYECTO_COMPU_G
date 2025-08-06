#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 FragColor;
uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos, 0.0, 1.0);
    FragColor = aColor;
}
