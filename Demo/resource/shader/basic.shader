#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;
out vec4 fragmentColor;

void main()
{
    fragmentColor = vertexColor; 
    gl_Position = position;
}

#shader fragment
#version 330 core

in vec4 fragmentColor;
layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = fragmentColor;
}