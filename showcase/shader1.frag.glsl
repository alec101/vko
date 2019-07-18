#version 450
#extension GL_ARB_separate_shader_objects : enable

// in / out

layout(location= 0) in vec4 color;
layout(location= 0) out vec4 finalColor;

void main() {
  //finalColor= vec4(1.0, 1.0, 1.0, 1.0);
  finalColor= color;
}

