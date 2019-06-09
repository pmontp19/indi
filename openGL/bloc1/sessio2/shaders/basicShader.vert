#version 330 core

in vec3 vertex;
in vec3 color;
out vec3 fcolor;

void main()  {
    fcolor = color;
    mat4 esc = mat4(1.);
    esc[0][0] = 0.5;
    esc[1][1] = 0.5;
    gl_Position = esc * vec4 (vertex, 1.0);
}
