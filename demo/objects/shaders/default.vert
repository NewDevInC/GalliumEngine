#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 atribPos;

// Normals
layout (location = 1) in vec3 atribNormal;

// Texture Coordinates
layout (location = 2) in vec2 atribTex;


// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// For use in the fragment shader
out vec3 Normal;

// Outputs our current world position
out vec3 currentPosition;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
// Imports the model matrix from the main function
uniform mat4 worldMatrix;


void main()
{
    // Postion of our model in relative to world origin
    currentPosition = vec3(worldMatrix * vec4(atribPos, 1.0f));
    // Outputs the positions/coordinates of all vertices
    gl_Position = camMatrix * worldMatrix * vec4(atribPos, 1.0f);
    // Assigns the texture coordinates from our Vertex data
    texCoord = atribTex;
    // Assigns the normal from our Vertex data
    Normal = atribNormal;
}