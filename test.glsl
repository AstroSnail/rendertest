#version 110

varying vec2 vposition;

void main (void) {
	gl_FragColor = vec4(0.5 * vposition.x + 0.5, 0.5 * vposition.y + 0.5, 0.5, 1.0);
}
