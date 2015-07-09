

attribute vec4 a_color;
attribute vec4 a_position;
attribute vec2 a_texCoord;

varying vec4 v_color;
varying vec2 v_texCoord;

void main()
{
    gl_Position = CC_PMatrix * a_position;
    v_color = a_color;
    v_texCoord = a_texCoord;
}