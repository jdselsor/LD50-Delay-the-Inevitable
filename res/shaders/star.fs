const float repeats = 30.0;
const float layers = 21.0;
const vec3 white = vec3 (255.0, 255.0, 255.0) / 255.0;

uniform vec3 iResolution;
uniform vec3 iTime;

float N21(vec2 p){
    p = fract(p*vec2(233.34, 851.73));
    p+= dot(p, p+23.45);
    return fract(p.x*p.y);
}

vec2 N22 (vec2 p){
	float n = N21(p);
    return vec2 (n, N21(p+n));
}

mat2 scale(vec2 _scale){
    return mat2(_scale.x,0.0,
                0.0,_scale.y);
}

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = N21(i);
    float b = N21(i + vec2(1.0, 0.0));
    float c = N21(i + vec2(0.0, 1.0));
    float d = N21(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

float perlin2(vec2 uv, int octaves, float pscale){
    float col = 1.;
    float initScale = 4.;  
    for ( int l; l < octaves; l++){
        float val = noise(uv*initScale);
        if (col <= 0.01){
            col = 0.;
            break;
        }
        val -= 0.01;
        val *= 0.5;
        col *= val;
        initScale *= pscale;
    }
 	return col;
}

vec3 stars(vec2 uv, float offset){
    
    float timeScale = -(iTime + offset) / layers;
    
    float trans = fract(timeScale);
    
    float newRnd = floor(timeScale);
    
    vec3 col = vec3(0.);
   
    
    // translate uv then scale for center
    uv -= vec2(0.5);
    uv = scale( vec2(trans) ) * uv;
    uv += vec2(0.5);
    
    // create square aspect ratio
    uv.x *= iResolution.x / iResolution.y;
    
    // create boxes
    uv *= repeats;
    
    // get position
    vec2 ipos = floor(uv);
    
    // return uv as 0 to 1
    uv = fract(uv);
    
    // calculate random xy and size
    vec2 rndXY = N22(newRnd + ipos*(offset+1.))*0.9+0.05;
    float rndSize = N21(ipos)*200.+400.;
    
    
    vec2 j = (rndXY - uv)*rndSize;
    float sparkle = 1./dot(j,j);
    
    col = white * vec3(sparkle);
    
    return col;
       
}

void main (void) 
{
    vec2 uv = gl_FragCoord.xy / iResolution;
    vec3 col = vec3(0.0);

    for (float i = 0.0; i < layers; i++) {
        col += stars(uv, i);
    }

    gl_FragColor = vec4(col, 1.0);
}