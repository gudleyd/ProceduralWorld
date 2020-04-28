attribute vec3 coord3d;
attribute vec3 normal;
attribute float colorIndex;

uniform sampler1D colorRamp;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

varying vec3 f_color;
varying vec3 fragPos;
varying vec3 fragNormal;

void main(void) {
	fragNormal = normal;
	fragPos = vec3(u_Model * vec4(coord3d, 1.0));
	gl_Position = u_Proj * u_View * vec4(fragPos, 1.0);
	f_color = texture(colorRamp, colorIndex).rgb;
	if (colorIndex > 3) f_color = vec3(1.0, 1.0, 0.0);
}
