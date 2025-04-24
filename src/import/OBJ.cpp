//
// Created by NewDevInC on 11.12.2024.
//


#include "OBJ.hpp"


std::unique_ptr<gameEntity> importObj(const char *file) {

    // Not the most memory optimal solution. I can't figure out a better one, since glMesh expects that all the data
    // inside vertices is filled. Otherwise, the VBO will be incorrect.

    std::map<std::string, std::vector<vertex>*> verticesDictionary;
    std::map<std::string, std::vector<GLuint>*> indicesDictionary;

    std::vector<std::string> meshNames;
    
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> texUVs;
    std::vector<glm::vec3> positions;

    std::vector<glMesh> readMeshes;
    std::vector<glMaterial> materials;
    std::vector<const char*> usedMaterial;

    std::unique_ptr<gameEntity> assembledEntity(new gameEntity());

    FILE *source = fopen(file, "r");
    char read = '\0';
    char* name = (char *)malloc(128);
    while ((read = fgetc(source)) != EOF) {

        if(read == '#'){
            //Comments, We don't need them
            while((read = fgetc(source) != '\n'));
        }

        if(read == 'o'){
            fscanf(source, " %s\n", name);

            meshNames.emplace_back(name);

            verticesDictionary[name] = new std::vector<vertex>;
            indicesDictionary[name] = new std::vector<GLuint>;

        }
        if(read == 'm'){
            char* materialDestination = (char *) (malloc(128));
            memset((void*)materialDestination, '\0', 128);
            fscanf(source, "%*s %s\n", materialDestination);

            char* pwd;
            getPWD(file, pwd);

            materials = readMaterials(strcat(pwd, materialDestination));

        }

        if (read == 'v') {

            char secondIdentifier = fgetc(source);
            //note to clang-tidy, please shut up,
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
            }

        } else if(read == 'u') {
            // Get the name of the material that this mesh will be using
            char* materialName = (char *)malloc(128);
            fscanf(source, "%*s %s", materialName);
            usedMaterial.push_back(materialName);

        } else if (read == 'f') {
            GLuint vertexIndex[3], uvIndex[3], normalIndex[3];

            fscanf(source, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            for (int i = 0; i < 3; i++) {
                vertex completedVertex = {};

                completedVertex.position = positions[vertexIndex[i] - 1];
                completedVertex.normal = normals[normalIndex[i] - 1];
                completedVertex.texUV = texUVs[uvIndex[i] - 1];

                verticesDictionary[name]->push_back(completedVertex);
                indicesDictionary[name]->push_back(indicesDictionary[name]->size());
            }
        }
    }

    for(auto &key : meshNames){
        auto readMesh = glMesh(*verticesDictionary[key], *indicesDictionary[key]);
        readMeshes.push_back(readMesh);

        // Since we have pointers to vectors, we need to manually clear the held data, then delete the pointer.
        verticesDictionary[key]->clear();
        indicesDictionary[key]->clear();

        delete verticesDictionary[key];
        delete indicesDictionary[key];
    }

    meshNames.clear();

    normals.clear();
    texUVs.clear();
    positions.clear();

    fclose(source);

    for(auto mesh : readMeshes){
        assembledEntity->addMesh(mesh);
    }
    for(auto material : materials){
        assembledEntity->addMaterial(material);
    }

    assembledEntity->correlateMeshMaterial(usedMaterial);

    readMeshes.clear();

    return assembledEntity;

}

std::vector<glMaterial> readMaterials(const char* file) {

    std::vector<glMaterial> returnedVector;

    // First we need to know how many materials there are.

    FILE *source = fopen(file, "r");
    char read = '\0';
    
    while ((read = fgetc(source)) != EOF) {

        if(read == '#'){
            //Comments, We don't need them
            while((read = fgetc(source) != '\n'));
        }

        if(read == 'n'){
            ungetc(read, source);

            char* name = (char *)malloc(128);

            fscanf(source, "%*s %s", name);
            
            auto readMaterial = glMaterial(name);

            returnedVector.push_back(readMaterial);
        }

        auto currentMaterial = returnedVector.empty() ? 0 : returnedVector.size() - 1;

        if (read == 'N') {

            char secondIdentifier = fgetc(source);
            //note to clang-tidy, You are still not funny

            if (secondIdentifier == 's') {
                fscanf(source, " %f\n", &(returnedVector[currentMaterial].shine));
            } else if (secondIdentifier == 'i') {
                // Not yet implemented. I don't intend to do refraction.
            }
        } else if (read == 'K') {

            char secondIdentifier = fgetc(source);

            if (secondIdentifier == 'a') {
                fscanf(source, " %f %f %f\n", &returnedVector[currentMaterial].ambient.x, &returnedVector[currentMaterial].ambient.y, &returnedVector[currentMaterial].ambient.z);
            } else if (secondIdentifier == 'd') {
                fscanf(source, " %f %f %f\n", &returnedVector[currentMaterial].diffuse.x, &returnedVector[currentMaterial].diffuse.y, &returnedVector[currentMaterial].diffuse.z);
            } else if (secondIdentifier == 's') {
                fscanf(source, " %f %f %f\n", &returnedVector[currentMaterial].specular.x, &returnedVector[currentMaterial].specular.y, &returnedVector[currentMaterial].specular.z);
            } else if (secondIdentifier == 'e') {
                fscanf(source, " %f %f %f\n", &returnedVector[currentMaterial].emission.x, &returnedVector[currentMaterial].emission.y, &returnedVector[currentMaterial].emission.z);
            }


        } else if (read == 'm') {
            ungetc(read, source);

            char whichMap[32] = {};
            char textureName[128] = {};

            fscanf(source, "%*s_%s %s\n", whichMap, textureName);

            const char *type = "";
            if (strcmp(whichMap, "Kd") == 0) {
                type = "diffuse";
            }
            if (strcmp(whichMap, "Ks") == 0) {
                type = "specular";
            }

            // For simplicity, all textures will be held in demo/objects/textures

            char *pwd;
            getPWD(file, pwd);

            // The cast is required due to C++ safety concerns.
            // However, C is life, C is love.
            auto readTexture = texture(strcat(pwd, strcat((char*)"textures/", textureName)), type, returnedVector[currentMaterial].textures.size());

            returnedVector[currentMaterial].textures.push_back(readTexture);

            returnedVector[currentMaterial].hasTexture = true;

            free(pwd);

        } else if (read == 'd') fscanf(source, " %f\n", &returnedVector[currentMaterial].transparency);
        else if(read == 'i') fscanf(source, " %*s %*d\n");


    }

    fclose(source);

    return returnedVector;
}
