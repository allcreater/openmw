#version 120

void main()
{
    gl_Position = vec4(gl_Vertex.xyz, 1);
    gl_TexCoord[0].st = gl_Vertex.xy*0.5 + 0.5;
}
