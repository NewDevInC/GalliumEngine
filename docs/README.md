# GalliumEngine

GalliumEngine is a SDL2/OpenGL engine that I've made with the goal
of it someday being a widely usable C++ library for game development.

The project started as proof of completed work for my senior year of high school.

# Usage

The engine is split into two parts:

    1. Demo application (./demo/*)
    2. Engine source    (./src*)

```
.
├── docs/ -> documentation  (You are here.)
|
├── demo/ -> Demo app showing off some basic features.
│   ├── objects/
│   │   ├── shaders/
│   │   │   └── [GLSL shaders]
│   │   └── [3D objects] (Currently only .obj/mtl)
|   |
│   └── main.cpp -> example program.
|
└── src/ -> GalliumEngine root
    ├── GL/ -> OpenGL handling
    ├── import/ -> File importing
    └── [engineSpecificFiles]
```

both have their own documentation, with more indepth definitions and examples. 

Visit the [wiki](./SDL2-Engine.wiki/Home.md) page for more information.

# Contribution

If you wish to create a fork of this repo, you are more than welcome to!

Keep in mind to inform others that your application uses your modified implementation!

There are two branches in total ***(might be expanded to be three)***:

    1. main (used for releases | most support and documentation)
    2. indev (used for experimental implementations of approved features | development only support and inprogress documentation)

If you wish to suggest a feature, open an **[issue](https://github.com/NewDevInC/GalliumEngine/issues/new)** 
with the enhancement label.

# License
The **GalliumEngine** is supplied under the MIT license; however, a full list of [licenses](LICENSE)
is listed under [LICENSE](LICENSE).

