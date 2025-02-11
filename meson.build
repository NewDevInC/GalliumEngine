project('SDL2-Engine', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=gnu++17', 'cpp_args=-mwindows'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_MESON_LIBRARY']

subdir('src')

include = include_directories('src')
executable('SDL2-Demo', './demo/main.cpp', link_with : lib, include_directories : include, dependencies: [glew_dep, glm_dep, sdl2_dep, sdl2_main_dep])
