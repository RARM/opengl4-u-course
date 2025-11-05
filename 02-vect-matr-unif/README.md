# Vectors, Matrices, and Uniform Variables

This section convers the use of vectors, matrices, and uniform variables in OpenGL.

Content:
- [Uniform Variables](#uniform-variables)
- Vectors
- Matrices

## Extra Setup
This tutorial uses another library, GLM (OpenGL Mathematics). That's a library that simplify mathematical operations (e.g., vectors and matrices). To compile the same program with GLM, ensure you have it installed. Then, add it to the compilation command. **Remember that GLM is a C++ library, so you'll have to use `clang++` (or `g++`) instead.**

```shell
clang++ -o 02-2-translate.out 02-2-translate.cpp `pkg-config --cflags --libs glfw3 glew glm`
```

The same command in MacOS requires the `-framework OpenGL` to be added at the end.

## Uniform Variables
Source code: [`02-1-moving.c`](./02-1-moving.c)

<div align="center">
  <img src="https://github.com/user-attachments/assets/c7217af9-e883-42d4-9518-89266d06efbc" width="285" height="228">
</div>

This program builds on the last lesson. The source code uses the custom functions to load the shader programs from other files.

To demonstrate how uniform variables work, there is one variable that now takes care of transforming the vertices translating them through the X axis. Find the most relevant edits below.

Note also that translating object using uniform variables is no the best way to do so. The purpose of this code is just to demonstrate the use of uniform variables in OpenGL.

```c
// 02-1-moving.c
GLuint uniformXMove;
enum direction { LEFT, RIGHT } dir = RIGHT;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;

...

void compileShaders() {
  ...
  uniformXMove = glGetUniformLocation(shader, "xMove");
}

...

int main(int argc, char* argv[]) {
  ...

  // Main loop.
  while (!glfwWindowShouldClose(mainWindow)) {
    // Get and handle user input events.
    glfwPollEvents();

    triOffset += dir == RIGHT ? triIncrement : -triIncrement;
    if (abs(triOffset) >= triMaxOffset) dir = (dir == RIGHT) ? LEFT : RIGHT;

    // Clear the window.
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glUniform1f(uniformXMove, triOffset);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);

    glfwSwapBuffers(mainWindow);
  }

  return 0;
}
```

The vertex shader now uses the `xMove` uniform variable to translate the vertices in the x-axis.
```
#version 330

layout (location = 0) in vec3 pos;
uniform float xMove;

void main() {
  gl_Position = vec4(0.4 * pos.x + xMove, 0.4 * pos.y, pos.z, 1.0);
}
```

## Model
Source code: [`02-2-translate.cpp`](./02-2-translate.cpp)

The second file uses a model, a 4x4 matrix instead. That's a much more adequate way to handle moving and translation.

```cpp
...

GLuint VAO, VBO, shader, uniformModel;

...

void compileShaders() {
  ...

  uniformModel = glGetUniformLocation(shader, "model");
}

int main(int argc, char* argv[]) {
  ...

  // Main loop.
  while (!glfwWindowShouldClose(mainWindow)) {
    ...

    glUseProgram(shader);

    glm::mat4 model{0.1f};
    // model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));

    // glUniform1f(uniformXMove, triOffset);
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    ...
  }

  ...
}
```