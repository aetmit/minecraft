#version 410 core
layout (location = 0) out vec4 colour;

uniform sampler2D uTexture;

in vec2 vTexCoord;

void main()
{
    vec4 texColour = texture(uTexture, vTexCoord);
    colour = texColour;
} 