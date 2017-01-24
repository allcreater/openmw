#version 120

varying vec2 uv;
varying float depth;

varying vec4 passColor;
varying vec3 passViewPos;
varying vec3 passNormal;

void main(void)
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    depth = gl_Position.z;

    vec4 viewPos = (gl_ModelViewMatrix * gl_Vertex);
    gl_ClipVertex = viewPos;

    passColor = gl_Color;
    passNormal = gl_Normal.xyz;
    passViewPos = viewPos.xyz;

    uv = gl_MultiTexCoord0.xy;
}
