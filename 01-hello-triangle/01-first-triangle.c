#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

static const char* vertShader = "\
#version 330\n\
\n\
layout (location = 0) in vec3 pos;\n\
\n\
void main() {\n\
  gl_Position = vec4(0.8 * pos.x, 0.8 * pos.y, pos.z, 1.0);\n\
}";

static const char* fragShader = "\
#version 330\n\
\n\
out vec4 color;\n\
\n\
void main() {\n\
  color = vec4(1.0, 0.0, 0.0, 1.0);\n\
}";

void createTriangle() {
  GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f
  };

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void addShader(GLuint program, const char* shaderCode, GLenum shaderType) {
  GLuint shader = glCreateShader(shaderType);

  const GLchar* code[1];
  code[0] = shaderCode;

  GLint codeLength[1];
  codeLength[0] = strlen(shaderCode);

  glShaderSource(shader, 1, code, codeLength);
  glCompileShader(shader);

  GLint result = 0;
  GLchar eLog[1024];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

  if (!result) {
    glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
    printf("Error compiling the %d shader: %s\n", shaderType, eLog);
    return;
  }

  glAttachShader(program, shader);
}

void compileShaders() {
  shader = glCreateProgram();

  if (!shader) {
    printf("Error creating shader program.\n");
    return;
  }

  addShader(shader, vertShader, GL_VERTEX_SHADER);
  addShader(shader, fragShader, GL_FRAGMENT_SHADER);
  
  GLint result = 0;
  GLchar eLog[1024];

  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &result);

  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    printf("Error linking program: %s\n", eLog);
    return;
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    printf("Error validating program: %s\n", eLog);
    return;
  }
}

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
  GLFWwindow* mainWindow =
      glfwCreateWindow(WIDTH, HEIGHT, "Hello world!", NULL, NULL);
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

  createTriangle();
  compileShaders();

  // Main loop.
  while (!glfwWindowShouldClose(mainWindow)) {
    // Get and handle user input events.
    glfwPollEvents();

    // Clear the window.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
    
    glfwSwapBuffers(mainWindow);
  }

  return 0;
}