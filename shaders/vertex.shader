
#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;

//Used the logic from learnopengl.com
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

uniform vec3 vertexObjectColor;
uniform vec3 vertexLightColor;
uniform vec3 vertexLightPosition;
uniform vec3 vertexViewPosition;

uniform float vertexAmbientCoefficient;
uniform float vertexDiffuseCoefficient;
uniform float vertexSpecularCoefficient;

uniform int gouraudActive;
uniform int vertexLightActive;
uniform int vertexNormalAsObjectColor;

out vec3 normal;
out vec3 fragmentPosition;
out vec3 aColor;

vec3 calculateColor(){
    vec3 tempObjectColor = vertexObjectColor;

    // If the normal is the Object color else normal Phong shading
    if(vertexNormalAsObjectColor == 1) {
        tempObjectColor = normal;
    }

    // Ambient
    vec3 ambient = vertexAmbientCoefficient * vertexLightColor;

    // If light is active
    if(vertexLightActive == 1){
        // Diffuse
        vec3 lightDirection = normalize(vertexLightPosition - fragmentPosition);
        float diffuseStrength = max(dot(normalize(normal), lightDirection), 0.0f);
        vec3 diffuse = vertexDiffuseCoefficient * diffuseStrength * vertexLightColor;

        // Specular
        vec3 viewDirection = normalize(vertexViewPosition - fragmentPosition);
        vec3 reflectedLightDirection = reflect(-lightDirection, normalize(normal));
        float specularStrength = pow(max(dot(reflectedLightDirection, viewDirection), 0.0f), 32);
        vec3 specular = vertexSpecularCoefficient * specularStrength * vertexLightColor;

        return (ambient + diffuse + specular) * tempObjectColor;
    } else {
        return ambient * tempObjectColor;
    }
}

void main()
{
    // Calculate the normal
    normal = mat3(transpose(inverse(model))) * normals;
    fragmentPosition = vec3(model * vec4(position, 1.0f));
    
    // If Gouraud shading is active calculate the shading else return aColor vec3 of negative values
    if (gouraudActive == 1) {
        aColor = calculateColor();
    } else {
        aColor = vec3(-1, -1, -1);
    }
    
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
}