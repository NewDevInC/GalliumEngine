glew_dep = dependency('glew')
glm_dep = dependency('glm')
sdl2_dep = dependency('sdl2')
sdl2_main_dep = dependency('sdl2main')


lib_sources = files('rheniumRenderer.cpp', 'GL/VBO.cpp', 'GL/VAO.cpp', 'GL/EBO.cpp', 'GL/glShader.cpp', 'GL/camera.cpp', 'GL/glMesh.cpp', 'import/OBJ.cpp')

lib = shared_library('SDL2-Engine', lib_sources,
                     install : true,
                     cpp_args : lib_args,
                     dependencies : [glew_dep, glm_dep, sdl2_dep]
)