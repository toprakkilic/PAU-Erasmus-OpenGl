#version 430 core

uniform mat4 uProj;
uniform mat4 uView;
uniform mat4 uModel;

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec3 vColor;

out float vDistance;


void main() {
  vColor = aColor;

  gl_Position = uProj * uView * uModel * vec4(aPosition, 1.0);
  
  vDistance = length((uView * uModel * vec4(aPosition, 1.0)).z);
}
