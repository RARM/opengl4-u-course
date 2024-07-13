#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {
  // Initialize GLFW.
  if (!glfwInit()) {
    printf("GLFW initialization failed.\n");
    glfwTerminate();
    return 1;
  }

  // OpenGL version 3.3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  // No backward compatibility.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Allow forward compatibility.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create window.
  GLFWwindow *mainWindow = glfwCreateWindow(
    WIDTH, HEIGHT, "Hello world!", NULL, NULL
  );
  if (!mainWindow) {
    printf("GLFW windows creation failed.\n");
    glfwTerminate();
    return 1;
  }

  // Get buffer size information.
  int bufferWidth, bufferHeight;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  // Set context for GLEW to use.
  glfwMakeContextCurrent(mainWindow);

  // Allow modern extensions features.
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    printf("GLEW initialization failed.\n");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }

  // Setup viewport size.
  glViewport(0, 0, bufferWidth, bufferHeight);

  // Main loop.
  while (!glfwWindowShouldClose(mainWindow)) {
    // Get and handle user input events.
    glfwPollEvents();

    // Clear the window.
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(mainWindow);
  }

  return 0;
}