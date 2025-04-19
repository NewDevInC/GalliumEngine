//
// Created by NewDevInC on 11.12.2024.
//


#include "OBJ.hpp"

glMesh *importObj(const char *file) {

    std::vector<vertex> vertices;
    std::vector<GLuint> indices;
    
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> texUVs;
    std::vector<glm::vec3> positions;
    
    char *name = (char *) (malloc(128));

    FILE *source = fopen(file, "r");
#ifdef DEBUG
    FILE *debug = fopen("readVertex.txt", "a");
#endif
    int read = '\0';
    while ((read = fgetc(source)) != EOF) {
        if (read == 'o') {
            fgetc(source); //skips a white-line
            fscanf(source, "%s \n", name);
        }
        
        if (read == 'v') {
            
            char secondIdentifier = fgetc(source);
            //note to clang-tidy, please shut the fuck up,
            //I know it's an int to char conversion we are dealing WITH ASCII

            //In case we are reading vn for vertex normal
            if (secondIdentifier == 'n') {
                glm::vec3 normal;
                fscanf(source, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);
                
            } else if (secondIdentifier == 't') {
                glm::vec3 texUV;
                fscanf(source, "%f %f\n", &texUV.x, &texUV.y);
                texUVs.push_back(texUV);

            } else {
                glm::vec3 readVertex = {};
                ungetc(secondIdentifier, source);
                fscanf(source, "%f %f %f\n", &readVertex.x, &readVertex.y, &readVertex.z);
                positions.push_back(readVertex);
#ifdef DEBUG
                fprintf(debug, "readVertex:{\n\t trueIndex: %d\n\t position: %f | %f | %f\n}\n", positions.size(), readVertex.x, readVertex.y, readVertex.z);
#endif
            }

        }else if (read == 'f') {
            fgetc(source); //skips a white-line
            GLuint vertexIndex[3], uvIndex[3], normalIndex[3];

            fscanf(source, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            /* Explanation for the %*d:
             * Wavefront OBJ for indices has defined vertexIndices/faceIndices/normalIndices,
             * we really don't need these because we are indexing based on our struct vertex
             */

            for (int i = 0; i < 3; i++) {
                vertex completedVertex = {};

                completedVertex.position = positions[vertexIndex[i] - 1];
                completedVertex.normal = normals[normalIndex[i] - 1];
                completedVertex.texUV = texUVs[uvIndex[i] - 1];

                vertices.push_back(completedVertex);

#ifdef DEBUG

                fprintf(debug, "readVertex:{\n\t Index: %d\n\t position: %f | %f | %f\n\t normals: %f | %f | %f\n\t UV: %f | %f\n}\n", vertexIndex[i], completedVertex.position.x, completedVertex.position.y,
                completedVertex.position.y, completedVertex.normal.x, completedVertex.normal.y, completedVertex.normal.y, completedVertex.texUV.x, completedVertex.texUV.y);
#endif
                indices.push_back(indices.size());
            }


        }
    }
#ifdef DEBUG
    fclose(debug);
#endif
    fclose(source);

    return new glMesh(vertices, indices, name);

}
