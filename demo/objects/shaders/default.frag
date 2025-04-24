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

uniform bool hasTexture;

uniform vec3 materialAmbient;

uniform vec3 materialDiffuse;

uniform vec3 materialSpecular;

uniform float materialShine;


// Gets the color of the light from the main function
uniform vec3 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPosition;
// Gets the position of the camera from the main function
uniform vec3 camPosition;


void main()
{

    vec3 ambient = materialAmbient * lightColor;

    // Diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPosition - currentPosition);
    vec3 diffuse = (max(dot(normal, lightDirection), 0.0f) * materialDiffuse) * lightColor;

    // Specular lighting
    vec3 viewDirection = normalize(camPosition - currentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), materialShine);
    vec3 specular = specAmount * materialSpecular * lightColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0f);

    if(hasTexture){
        FragColor = texture(tex0, texCoord) * vec4(diffuse + ambient + specular, 1.0f);
    }

}