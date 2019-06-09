#version 330 core

out vec4 FragColor;
in vec3 fcolor;

void main() {
    FragColor = vec4(fcolor, 1.0);

    /*FragColor = vec4(0, 0, 0, 1);
    if (int(gl_FragCoord.y) % 20 > 10)
        discard;
    else {
        if (gl_FragCoord.x < 355. && gl_FragCoord.y < 357.)
            FragColor = vec4(1, 1, 0, 1);
        else if (gl_FragCoord.x < 355. && gl_FragCoord.y > 357.)
            FragColor = vec4(1, 0, 0, 1);
        else if (gl_FragCoord.x > 355. && gl_FragCoord.y < 357.)
            FragColor = vec4(0, 0, 1, 1);
        else if (gl_FragCoord.x > 355. && gl_FragCoord.y > 357.)
            FragColor = vec4(0, 1, 0, 1);
    }*/

}
