//
// Created by NewDevInC on 11.12.2024.
//


#include "OBJ.hpp"

glMesh *importObj(const char *file) {

    std::vector<vertex> vertices;
    std::vector<GLuint> indices;
    char *name = (char *) (malloc(128));

    FILE *source = fopen(file, "r");

    int read = '\0';
    while ((read = fgetc(source)) != EOF) {
        if (read == 'o') {
            fgetc(source); //skips a white-line
            fscanf(source, "%s \n", name);
        }
        if (read == 'v') {
            //Temporary storage of the read data
            vertex readVertex = {};

            char secondIdentifier = fgetc(source);
            //note to clang-tidy, please shut the fuck up,
            //I know it's an int to char conversion we are dealing WITH ASCII

            fgetc(source); //skips a white-line

            //In case we are reading vn for vertex normal
            if (secondIdentifier == 'n') {
                fscanf(source, "%f %f %f\n", &readVertex.normal.x, &readVertex.normal.y, &readVertex.normal.z);
            } else if (secondIdentifier == 't') {
                fscanf(source, "%f %f\n", &readVertex.texUV.x, &readVertex.texUV.y);
            } else {
                fscanf(source, "%f %f %f\n", &readVertex.position.x, &readVertex.position.y, &readVertex.position.z);
            }
            vertices.push_back(readVertex);

        }else if (read == 'f') {
            fgetc(source); //skips a white-line
            GLuint vertexIndex[3], uvIndex[3], normalIndex[3];

            fscanf(source, " %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            /* Explanation for the %*d:
             * Wavefront OBJ for indices has defined vertexIndices/faceIndices/normalIndices,
             * we really don't need these because we are indexing based on our struct vertex
             */
            indices.push_back(vertexIndex[0]-1);
            indices.push_back(vertexIndex[1]-1);
            indices.push_back(vertexIndex[2]-1);
        }
    }

    return new glMesh(vertices, indices, name);

}
