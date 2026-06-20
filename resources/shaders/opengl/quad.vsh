#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 fragTexCoord;

uniform mat4 uViewProjection;
uniform mat4 uTransform;

void main()
{
    fragTexCoord = inTexCoord;
    gl_Position  = uViewProjection * uTransform * vec4(inPosition, 1.0);
}
