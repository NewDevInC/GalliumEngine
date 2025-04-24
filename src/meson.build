glew_dep = dependency('glew')
glm_dep = dependency('glm')
sdl2_dep = dependency('sdl2')
sdl2_main_dep = dependency('sdl2main')
libpng = dependency('libpng')

lib_dep = [glew_dep, glm_dep, sdl2_dep, libpng]

lib_sources = files('rheniumRenderer.cpp', 'GL/VBO.cpp', 'GL/VAO.cpp', 'GL/EBO.cpp', 'GL/glShader.cpp', 'GL/texture.cpp',
                    'GL/glMaterial.cpp', 'GL/camera.cpp', 'GL/glMesh.cpp', 'import/OBJ.cpp',
                    'genericEntity.cpp', 'lightEntity.cpp', 'gameEntity.cpp')

lib = shared_library('GalliumEngine', lib_sources,
                     install : true,
                     dependencies : lib_dep
)