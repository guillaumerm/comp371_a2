#version 330 core

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform float ambientCoefficient;
uniform float diffuseCoefficient;
uniform float specularCoefficient;

uniform vec3 activeChannels;
uniform vec3 colorScale;

uniform int normalAsObjectColor;
uniform int lightActive;

in vec3 aColor;
in vec3 normal;
in vec3 fragmentPosition;

vec3 calculateColor(){
    vec3 tempObjectColor = objectColor;

    // If the normal is the Object color else normal Phong shading
    if(normalAsObjectColor == 1) {
        tempObjectColor = normal;
    }

    // Ambient
    vec3 ambient = ambientCoefficient * lightColor;

    // If light is active
    if(lightActive == 1){
        // Diffuse
        vec3 lightDirection = normalize(lightPosition - fragmentPosition);
        float diffuseStrength = max(dot(normalize(normal), lightDirection), 0.0f);
        vec3 diffuse = diffuseCoefficient * diffuseStrength * lightColor;

        // Specular
        vec3 viewDirection = normalize(viewPosition - fragmentPosition);
        vec3 reflectedLightDirection = reflect(-lightDirection, normalize(normal));
        float specularStrength = pow(max(dot(reflectedLightDirection, viewDirection), 0.0f), 32);
        vec3 specular = specularCoefficient * specularStrength * lightColor;

        return (ambient + diffuse + specular) * tempObjectColor;
    } else {
        return ambient * tempObjectColor;
    }
}

void main()
{
    vec3 result;
    
    // If aColor is different of vec3(-1,-1,-1) then Gouraud shading is active
    if(aColor != vec3(-1, -1, -1)) {
        result = aColor;
    } else {
        result = calculateColor();
    }

    // Times the active channels and the color scale
    color = vec4(result * activeChannels * colorScale, 1.0f);
}

