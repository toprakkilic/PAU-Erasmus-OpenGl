#version 430 core

in vec3 vColor;

out vec4 fragColor;

in float vDistance;

void main() {
  float a = smoothstep(10.0, 25.0, vDistance);

  vec3 color = mix(vColor, vec3(0.5 , 0.5, 0.5), a); 
  fragColor = vec4(color, 1.0);
}
