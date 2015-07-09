#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_color;
varying vec2 v_texCoord;
uniform vec2 u_Resolution;
uniform float u_Time;
uniform float u_Intensity;
uniform float u_fuckU;
//uniform sampler2D CC_Texture0;

void main()
{
    vec2 blablabla = u_Resolution;
    vec2 position = gl_FragCoord.xy/u_Resolution.xy;
    //    vec2 position = gl_FragCoord.xy/vec2(1536.0, 2048.0);
    
    position += u_Time;
    float pi = 3.14159265359;
    float wave = sin(2.*pi*position.x);
    wave = (wave+1.) * 0.2;
    vec4 normalColor = texture2D(CC_Texture0, v_texCoord) * v_color;
    wave = wave * normalColor.a;
    vec4 finalColor = vec4(normalColor.r+wave, normalColor.g+wave, normalColor.b+wave, normalColor.a);
    
    gl_FragColor = finalColor;
}