#version 330

// Entrées standards de Raylib
in vec2 fragTexCoord;
in vec4 fragColor;

// Texture envoyée par Raylib (ton menuCanvas)
uniform sampler2D texture0;

// Variables dynamiques passées depuis le C++
uniform float iTime;
uniform vec2 iResolution;

out vec4 finalColor;

// --- FONCTIONS DU SHADER ORIGINAL DE PATU ---

// Émule la distorsion de l'écran cathodique (effet bombé)
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
    // 1. Appliquer la courbure de l'écran aux coordonnées UV
    vec2 uv = curve(fragTexCoord);
    vec4 col;
    
    // Vérifier si le pixel courbé dépasse les limites physiques de l'écran (bords noirs)
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
    {
        col = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        // 2. Échantillonnage de la couleur du menu (avec de légères aberrations chromatiques)
        col.r = texture(texture0, vec2(uv.x + 0.002, uv.y)).r;
        col.g = texture(texture0, vec2(uv.x + 0.000, uv.y)).g;
        col.b = texture(texture0, vec2(uv.x - 0.002, uv.y)).b;
        col.a = texture(texture0, uv).a;

        // Si le pixel d'origine était transparent, on n'applique pas les effets lumineux
        if (col.a > 0.0)
        {
            // 3. Effet de Scintillement (Flicker) basé sur le temps
            float flicker = 0.95 + 0.05 * sin(iTime * 100.0) * sin(iTime * 20.0);
            col.rgb *= flicker;

            // 4. Lignes de balayage (Scanlines) horizontales et verticales complexes
            float scanlineH = sin(uv.y * iResolution.y * 2.5) * 0.12;
            float scanlineV = sin(uv.x * iResolution.x * 2.5) * 0.04;
            col.rgb -= scanlineH;
            col.rgb -= scanlineV;

            // 5. Teinte globale style écran à phosphore vert (Pip-Boy)
            // On convertit en niveaux de gris et on injecte le vert iconique
            float gray = dot(col.rgb, vec3(0.299, 0.587, 0.114));
            col.rgb = vec3(gray * 0.3, gray * 1.2, gray * 0.4);
            
            // Un léger boost pour l'effet de rémanence / lueur (Glow)
            col.rgb += vec3(0.0, 0.05, 0.0);
        }
    }

    finalColor = col * fragColor;
}
