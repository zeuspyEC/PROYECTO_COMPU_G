#version 330 core
out vec4 FragColor;
in vec3 FragColor;

void main()
{
    FragColor = vec4(FragColor, 1.0);
}
