#version 330

layout (location = 0) in vec3 pos;

void main() {
  gl_Position = vec4(0.8 * pos.x, 0.8 * pos.y, pos.z, 1.0);
}