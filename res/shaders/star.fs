uniform vec3 iResolution;

void main (void) 
{
    vec2 st = gl_FragCoord.xy / iResolution;
    gl_FragColor = vec4 (st.x, st.y, 0.0, 1.0);
}