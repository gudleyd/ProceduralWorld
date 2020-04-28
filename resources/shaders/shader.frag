varying vec3 f_color;

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_LightDirection;
uniform vec3 u_ViewPos;

void main(void) {
	vec3 ambientColor = vec3(0.5, 0.5, 0.5) * f_color;

	float cosTheta = clamp(dot(fragNormal, u_LightDirection), 0, 1);
	vec3 diffuseColor = f_color * u_LightColor * 0.5 * cosTheta;

	vec3 viewDir = normalize(u_ViewPos - fragPos);
	vec3 halfwayDir = normalize(u_LightDirection + viewDir);
	float spec = pow(max(dot(fragNormal, halfwayDir), 0.0), 16.0);
	vec3 specularColor = u_LightColor * spec * 0.1;

	gl_FragColor = vec4(specularColor + ambientColor + diffuseColor, 1.0f);
}
