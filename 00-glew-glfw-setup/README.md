# Setup GLEW and GLFW

Relevant sites:
- The OpenGL Extension Wrangler Library: https://glew.sourceforge.net/
- GLFW: https://www.glfw.org/

Setting up GLEW and GLFW for Windows requires downloading the binaries and header files, plus configuring them in the desired IDE (e.g., Visual Studio Community). However, the environment for this repository is a Debian system. Therefore, it was as simple as installing the two libraries through the package manager.
```
sudo apt update
sudo apt install libglew-dev libglfw3-dev
```

That made the header files available for the source code.
```c
#include <GL/glew.h>
#include <GLFW/glfw3.h>
```

Finally, compilation only required linking the proper libraries in the compiler (they were installed through the package manager).
```
gcc -o main.out main.c -lGLEW -glfw -lGL
```

The source code for this section ([`main.c`](./main.cpp)) shows how to setup GLEW and GLFW to work with OpenGL in C. It shows a simple window with a red background.