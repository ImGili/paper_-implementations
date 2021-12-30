#version 330 core
out vec4 fragColor;

uniform vec3 line_color;
uniform float line_mode;
uniform vec3 mesh_color;

void main(){
    if(line_mode == 1.0f)
    {
        fragColor = vec4(line_color, 1.0f);
    }
    else
    {
        fragColor = vec4(mesh_color, 1.0);
    }
}