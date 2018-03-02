
    float inner = 0;
    float outter = 0;
    for(int i = 0; i < 9; i++)
    {
		vec4 m = texture(screenTexture, aTexCoord.st + offsets[i]);
		outter += 1 - m.a;
		inner += m.a;
    }

    outter /= 9;
    inner /= 9;
    vec4 tempColor = vec4(1, 0, 0, 1);
    vec4 col = texture(screenTexture, aTexCoord);
    float out_alpha = max(col.a, inner);
    float in_alpha = min(out_alpha, outter);

    col.rgb = col.rgb + in_alpha * tempColor.a * tempColor.rgb;
    color = col;