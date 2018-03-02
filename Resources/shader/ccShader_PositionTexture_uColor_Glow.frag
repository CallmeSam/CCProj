#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	//内发光参数  range = 6   offset = 1 / 30 color = 0, 0, 1, 1
	int range = 6;
	const float offset = 1.0 / 80.0;  

	float inner = 0;
    	float outter = 0;
    	int count = 0;
	for(int i = -range; i <= range; i++)
	{
		for(int j = -range; j <= range; j++)
		{
			vec4 m = texture2D(CC_Texture0, v_texCoord + vec2(i * offset, j * offset));
			outter += 1 - m.a;
			inner += m.a;
			count += 1;
		}
	}

	outter /= count;
	inner /= count;
	vec4 tempColor = vec4(0.0, 1.0, 0.0, 1);
	vec4 col = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
	float out_alpha = max(col.a, inner);
	float in_alpha = min(out_alpha, outter);

	//col.rgb = col.rgb + in_alpha * tempColor.a * tempColor.rgb;
	col.rgb = col.rgb + (1-col.a)  * tempColor.a * tempColor.rgb;
	col.a = out_alpha;

	gl_FragColor = col;
}