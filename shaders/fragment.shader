#version 330 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform float ambientCoefficient;
uniform float diffuseCoefficient;
uniform float specularCoefficient;

uniform int normalAsObjectColor;

in vec3 normal;
in vec3 fragmentPosition;

void main()
{
    // Ambient
    vec3 ambient = ambientCoefficient * lightColor;

    // Diffuse
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    float diffuseStrength = max(dot(normalize(normal), lightDirection), 0.0f);
    vec3 diffuse = diffuseCoefficient * diffuseStrength * lightColor;

    // Specular
    vec3 viewDirection = normalize(viewPosition - fragmentPosition);
    vec3 reflectedLightDirection = reflect(-lightDirection, normalize(normal));
    float specularStrength = pow(max(dot(reflectedLightDirection, viewDirection), 0.0f), 32);
    vec3 specular = specularCoefficient * specularStrength * lightColor;

    vec3 result = (ambient + diffuse + specular);
    if(normalAsObjectColor == 1){
        result *= normal;
    }else {
        result *= objectColor;
    }

    color = vec4(result, 1.0f);
} 