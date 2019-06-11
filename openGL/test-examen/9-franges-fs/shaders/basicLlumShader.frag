#version 330 core

in vec3 fcolor;
out vec4 FragColor;
uniform float franges;

void main()
{	
	FragColor = vec4(fcolor,1);	
	if (franges > 0.5) {
		if (int(gl_FragCoord.y) % 10 > 5)
			FragColor = vec4(1, 1, 1, 1);
		else {	
			FragColor = vec4(0, 0, 0, 0);
    }
	}
    
}
