#version 330 core

layout(location = 0) in vec2 pos;

uniform vec4 rgba;

out vec4 squareColor;

void main() {
    gl_Position = vec4(pos, 1.0f, 1.0f);
    squareColor = rgba;
};