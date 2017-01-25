#version 120

uniform sampler2DRect bufferColor;
uniform sampler2DRect bufferNormalShininess;
uniform sampler2DRect bufferDepth;

#include "lighting.glsl"

vec3 getFragPos(in vec3 screenCoord)
{
    vec4 pos = gl_ProjectionMatrixInverse * vec4(screenCoord*2.0-1.0, 1.0);
    return pos.xyz/pos.w;
}

void main()
{
    vec4 color = texture2DRect(bufferColor, gl_FragCoord.xy);
    vec4 normalShine = texture2DRect(bufferNormalShininess, gl_FragCoord.xy);
    float depth = texture2DRect(bufferDepth, gl_FragCoord.xy).r;

    vec3 fragmentPos = getFragPos (vec3(gl_TexCoord[0].st, depth));

    //vec3 lightDir = gl_LightSource[0].position.xyz - (fragmentPos * gl_LightSource[0].position.w);
    //float NdL = max(dot(normalShine.xyz, lightDir), 0.0);

    gl_FragData[0] = color;// * NdL + color * gl_LightSource[0].ambient;
    //gl_FragColor = color * doLighting(fragmentPos, normalShine.rgb, vec4(1,1,1,1));
    //gl_FragColor.rgb += getSpecular(normalShine.rgb, normalize(fragmentPos), normalShine.a, color.rgb);
//fog
    //float fogValue = clamp((depth - gl_Fog.start) * gl_Fog.scale, 0.0, 1.0);
    //gl_FragColor.rgb = mix(gl_FragData[0].rgb, gl_Fog.color.rgb, fogValue);
}
