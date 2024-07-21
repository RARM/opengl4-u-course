# Vectors, Matrices, and Uniform Variables

This section convers the use of vectors, matrices, and uniform variables in OpenGL.

Content:
- [Uniform Variables](#uniform-variables)
- Vectors
- Matrices

## Uniform Variables
Source code: [`02-1-moving.c`](./02-1-moving.c)

<div align="center">
  <img src="https://github.com/user-attachments/assets/c7217af9-e883-42d4-9518-89266d06efbc" width="285" height="228">
</div>

This program builds on the last lesson. The source code uses the custom functions to load the shader programs from other files.

To demonstrate how uniform variables work, there is one variable that now takes care of transforming the vertices translating them through the X axis. Find the most relevant edits below.

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