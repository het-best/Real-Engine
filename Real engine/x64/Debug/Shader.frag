#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 uResolution;
uniform vec2 uMouse;
uniform float uTime;

vec4 line(vec2 cords, vec4 backColor) {
    vec3 color = vec3(0.9, 0.9, 0.9);
	color.r = backColor.r;
	color.g = backColor.g;
	color.b = backColor.b;

    float pct = smoothstep(0.01, 0.0, abs(cords.y - cords.x));
    color = (1.0-pct)*color+pct*vec3(0.0,0.0,0.0);
	return vec4(color, 1.0);
}

void main() {
	vec2 cords = gl_FragCoord.xy;
    cords.x = cords.x / uResolution.x;
    cords.y = cords.y / uResolution.y;

	
    vec3 cil = 0.5 + 0.5*cos(uTime * 4.5 + cords.xyx + vec3(0, 2, 4));
    vec4 gradient = vec4(cil, 1.0);
    gradient.g = cords.x;
    gradient.b = cords.y;

    vec4 firstColor = vec4(0.9, 0.9, 0.9, 1.0);
    vec4 middleColor = gradient;

    vec4 color = mix(firstColor, middleColor, cords.y / 0.4);
	
    if(line(cords, color) != color) {
	    color = line(cords, color);
    }
	gl_FragColor = color;
}