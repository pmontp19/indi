#version 330 core

in vec3 fcolor;
out vec4 FragColor;

uniform vec3 posFocus;
uniform vec3 colFocus;
uniform vec3 llumAmbient;

in vec3 fmatamb;
in vec3 fmatdiff;
in float fmatshin;
in vec3 fmatspec;
in vec4 fvertexSCO;
in vec3 fnormalMatrix;


vec3 Lambert (vec3 NormSCO, vec3 L)
{
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats

    // Inicialitzem color a component ambient
    vec3 colRes = llumAmbient * fmatamb;

    // Afegim component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colRes + colFocus * fmatdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Phong (vec3 NormSCO, vec3 L, vec4 vertSCO)
{
    // Els vectors estan normalitzats

    // Inicialitzem color a Lambert
    vec3 colRes = Lambert (NormSCO, L);

    // Calculem R i V
    if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
      return colRes;  // no hi ha component especular

    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular

    float shine = pow(max(0.0, dot(R, V)), fmatshin);
    return (colRes + fmatspec * colFocus * shine);
}

void main()
{	
    vec4 focusSCO = vec4(posFocus, 1.0);
    vec4 vecL = focusSCO - fvertexSCO;
    vec3 vecLxyz = normalize(vecL.xyz);

    vec3 normalSCO = normalize(fnormalMatrix);
    vec3 fc = Phong(normalSCO, vecLxyz, fvertexSCO);
    FragColor = vec4(fc,1.0);
}
