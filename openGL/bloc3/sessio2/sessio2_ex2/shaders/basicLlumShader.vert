#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 posFocus;
uniform vec3 colFocus;
uniform vec3 llumAmbient;

out vec3 fcolor;

out vec3 matamb_fs;
out vec3 matdiff_fs;
out vec3 matspec_fs;
out float matshin_fs; 
out vec4 vertexSCO_fs;
out vec3 normalMatrix_fs;
out vec3 normal_fs;

void main()
{
  // fcolor = matdiff;

  // passar vector normal a SCO
  mat3 normalMatrix = inverse (transpose (mat3 (view * TG)));
  vec3 nomNormal = normalize (normalMatrix * normal);
  
  // passar posicio vertex a SCO esta en SCM 
  vec4 vertexSCO = view * TG * vec4 (vertex, 1.0);  
  
  vertexSCO_fs = vertexSCO;
  normalMatrix_fs = nomNormal; // shaura de normalitzar igualment al FS
  matamb_fs = matamb;
  matdiff_fs = matdiff;
  matspec_fs = matspec;
  matshin_fs = matshin;


  gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
