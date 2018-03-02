attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

#ifdef GL_ES
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
#endif

uniform float locationY;

void main()
{
    //gl_Position = CC_MVPMatrix * vec4(a_position.x +   sin(radians(a_position.y - 40) * 1.2) * 60 * clamp(abs(locationY - a_position.y), 0, 600) / 600  , a_position.y, a_position.z, a_position.w);
    gl_Position = CC_PMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
}