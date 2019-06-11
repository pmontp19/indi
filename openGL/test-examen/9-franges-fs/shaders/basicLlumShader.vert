#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

vec3 wmatamb;
vec3 wmatdiff;
vec3 wmatspec;
float wmatshin;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem dels focus de llum
vec3 colFocus = vec3(0, 0.8, 0.8); // cyan
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
vec3 posFocus = vec3(0, 1, 0);    // en SCO

out vec3 fcolor;
in int esVaca;
uniform float franges;

vec3 Lambert (vec3 NormSCO, vec3 L) 
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * wmatamb;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * wmatdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO) 
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if (dot(NormSCO,L) < 0)
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: normalize (2.0*dot(NormSCO,L)*NormSCO - L);
    vec3 V = normalize(-vertSCO.xyz);

    if ((dot(R, V) < 0) || (wmatshin == 0))
      return colRes;  // no hi ha component especular
    
    // Afegim la component especular
    float shine = pow(max(0.0, dot(R, V)), wmatshin);
    return (colRes + wmatspec * colFocus * shine); 
}

void main()
{	
  if (esVaca == 1) {
    wmatamb = vec3(0.5,0.5,0.5);
    wmatdiff = vec3(0.8,0.8,0.8);
    wmatspec = vec3(0.8,0.8,0.8);
    wmatshin = 100;  
  } else {
    wmatamb = matamb;
    wmatdiff = matdiff;
    wmatspec = matspec;
    wmatshin = matshin;  
  }

  // Passar vector normal a SCO 
  mat3 normalMatrix = inverse (transpose (mat3 (view * TG)));
  vec3 normalVec = normalize (normalMatrix * normal);

  // Passar posicio a SCO ve en SCM
  vec4 vertexSCO = view * TG * vec4 (vertex, 1.0);  
  
  vec4 vecL = vec4 (posFocus, 1.0) - vertexSCO;
  vec3 vecLxyz = normalize(vecL.xyz);

  fcolor = Phong(normalVec, vecLxyz, vertexSCO);

  gl_Position = proj * view * TG * vec4 (vertex, 1.0);
}
