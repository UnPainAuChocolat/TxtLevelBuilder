#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

uniform float iTime;
uniform vec2 iResolution;

out vec4 finalColor;


vec2 curve(vec2 uv)
{
    uv = (uv - 0.5) * 2.0;
    uv.x *= 1.0 + pow((abs(uv.y) / 5.0), 2.0);
    uv.y *= 1.0 + pow((abs(uv.x) / 4.0), 2.0);
    uv = (uv / 2.0) + 0.5;
    uv = uv * 0.92 + 0.04;
    return uv;
}

void main()
{
    vec2 uv = curve(fragTexCoord);
    vec4 col;
    
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
    {
        col = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        col.r = texture(texture0, vec2(uv.x + 0.002, uv.y)).r;
        col.g = texture(texture0, vec2(uv.x + 0.000, uv.y)).g;
        col.b = texture(texture0, vec2(uv.x - 0.002, uv.y)).b;
        col.a = texture(texture0, uv).a;

        if (col.a > 0.0)
        {
            float flicker = 0.95 + 0.05 * sin(iTime * 100.0) * sin(iTime * 20.0);
            col.rgb *= flicker;

            float scanlineH = sin(uv.y * iResolution.y * 2.5) * 0.12;
            float scanlineV = sin(uv.x * iResolution.x * 2.5) * 0.04;
            col.rgb -= scanlineH;
            col.rgb -= scanlineV;

            float gray = dot(col.rgb, vec3(0.299, 0.587, 0.114));
            col.rgb = vec3(gray * 0.3, gray * 1.2, gray * 0.4);
            
            col.rgb += vec3(0.0, 0.05, 0.0);
        }
    }

    finalColor = col * fragColor;
}
