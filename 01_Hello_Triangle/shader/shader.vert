#version 430 core

layout (location = 0) in vec2 aPosition;


out vec4 color;

void main() {
  color = vec4(aPosition * 0.5 + 0.5, 0.0, 1.0);
  gl_Position = vec4(aPosition, 0.0, 1.0);
}
