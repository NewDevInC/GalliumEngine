#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the current position from the Vertex Shader
in vec3 currentPosition;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;

// Gets the color of the light from the main function
uniform vec3 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPosition;
// Gets the position of the camera from the main function
uniform vec3 camPosition;


void main()
{

    vec3 ambient = 0.25f * lightColor;

    // Diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPosition - currentPosition);
    vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * lightColor;

    // Specular lighting
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPosition - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    vec3 specular = specAmount * specularLight * lightColor;

    vec3 finalColor = (0.8f, 0.1f, 0.8f, 1.0f) * (diffuse + ambient + specular);

    FragColor =  vec4(finalColor, 1.0f);


    //TODO: Add texutres
    //FragColor = texture(tex0, texCoord);
}