#shader vertex
#version 330 core

layout(location = 0) in vec2 position; 
layout(location = 1) in vec3 v_color; 
// attribute vec2 coord2d;
// attribute vec3 v_color;
varying vec3 f_color;
void main(void) {
  gl_Position = vec4(position, 0.0, 1.0);
  f_color = v_color;
}

#shader fragment
#version 330 core

varying vec3 f_color;
void main(void) {
  gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, 1.0);
}