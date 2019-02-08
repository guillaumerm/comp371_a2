#version 330 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

in vec3 norm;
in vec3 fragmentPosition;

void main()
{
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = lightColor * ambientStrength;

    // Diffuse
    vec3 normal = normalize(norm);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    float diffuseStrength = max(dot(lightDirection, normal), 0.0f);
    vec3 diffuse = lightColor * diffuseStrength;

    // Specular
    vec3 viewDirection = normalize(viewPosition - fragmentPosition);
    vec3 reflectedLightDirection = reflect(-lightDirection, normal);
    float specularStrength = pow(max(dot(reflectedLightDirection, viewDirection), 0.0f), 32);
    vec3 specular = lightColor * specularStrength;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    color = vec4(result, 1.0f);
} 