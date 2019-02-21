
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

out vec3 normal;
out vec3 fragmentPosition;
out vec3 aColor;

void main()
{
    // Calculate the normal
    normal = mat3(transpose(inverse(model))) * normals;
    
    // If Gouraud shading is active calculate the shading else return aColor vec3 of negative values
    if (gouraudActive == 1) {
        // Ambient
        vec3 ambient = vertexAmbientCoefficient * vertexLightColor;

        // Diffuse
        vec3 lightDirection = normalize(vertexLightPosition - position);
        float diffuseStrength = max(dot(normalize(normal), lightDirection), 0.0f);
        vec3 diffuse = vertexDiffuseCoefficient * diffuseStrength * vertexLightColor;

        // Specular
        vec3 viewDirection = normalize(vertexViewPosition - position);
        vec3 reflectedLightDirection = reflect(-lightDirection, normalize(normal));
        float specularStrength = pow(max(dot(reflectedLightDirection, viewDirection), 0.0f), 32);
        vec3 specular = vertexSpecularCoefficient * specularStrength * vertexLightColor;

        aColor = (ambient + diffuse + specular) * vertexObjectColor;
    } else {
        aColor = vec3(-1, -1, -1);
    }

    fragmentPosition = vec3(model * vec4(position, 1.0f));
    
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
}