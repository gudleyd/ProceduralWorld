varying vec3 f_color;

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;

void main(void) {
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * u_LightColor;

	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(u_LightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_LightColor;


	gl_FragColor = vec4((ambient + diffuse), 1.0f) * vec4(f_color.r, f_color.g, f_color.b, 1.0);
}
