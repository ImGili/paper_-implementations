#version 330 core

uniform mat4 uModelViewMatrix;
uniform mat4 uProjectionMatrix;
layout(location=0) in vec3 aPosition;

void main(){
    vec4 position = vec4(aPosition, 1.0);
    gl_Position = uProjectionMatrix * uModelViewMatrix * position;
}