#version 410 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D textAtlas;
uniform vec4 textColor;

void main() {
    float alpha = texture(textAtlas, TexCoords).a;
    color = vec4(textColor.rgb, textColor.a * alpha);
}
