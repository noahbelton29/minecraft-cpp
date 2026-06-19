#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inVertexColor;

out vec3 fragColor;

uniform mat4 uProjection;

void main()
{
    fragColor = inVertexColor;
    gl_Position = uProjection * vec4(inPosition, 1.0);
}
