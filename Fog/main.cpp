
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Drawable Object
struct Object {
  GLuint program;
  GLuint vao;
  GLsizei count;
};

std::string readFile(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("failed to open file!");
  }

  std::string content;
  content.assign(std::istreambuf_iterator<char>(file),
                 std::istreambuf_iterator<char>()
                );

  return content;
}

Object initObj() {
  Object obj {};

  // create and compile vertex shader
  const std::string vertexString = readFile("shader/shader.vert");
  const GLchar* vertexText = vertexString.c_str();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexText, nullptr);
  glCompileShader(vertexShader);
  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    GLchar infoLog[1024];
    glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
  }

  // create and compile fragment shader
  const std::string fragmentString = readFile("shader/shader.frag");
  const GLchar* fragmentText = fragmentString.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentText, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    GLchar infoLog[1024];
    glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
  }

  // create and link shader program
  obj.program = glCreateProgram();
  glAttachShader(obj.program, vertexShader);
  glAttachShader(obj.program, fragmentShader);
  glLinkProgram(obj.program);
  glGetProgramiv(obj.program, GL_LINK_STATUS, &status);
  if (!status) {
    GLchar infoLog[1024];
    glGetProgramInfoLog(obj.program, 1024, nullptr, infoLog);
  }
  glValidateProgram(obj.program);
  glGetProgramiv(obj.program, GL_VALIDATE_STATUS, &status);
  if (!status) {
    GLchar infoLog[1024];
    glGetProgramInfoLog(obj.program, 1024, nullptr, infoLog);
  }
  
  struct Position {
  	GLfloat x;
  	GLfloat y;
  	GLfloat z;
  };

  // create vertex buffer
  struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
  };

  std::vector<Vertex> vertices =
    {
	  // top
      {{ -1.0f, -1.0f, 1.0f}, {0.8f, 0.8f, 0.0f}},
      {{  1.0f, -1.0f, 1.0f}, {0.8f, 0.8f, 0.0f}},
      {{  1.0f,  1.0f, 1.0f}, {0.8f, 0.8f, 0.0f}},
      {{ -1.0f, -1.0f, 1.0f}, {0.8f, 0.8f, 0.0f}},
      {{  1.0f,  1.0f, 1.0f}, {0.8f, 0.8f, 0.0f}},
      {{ -1.0f,  1.0f, 1.0f}, {0.8f, 0.8f, 0.0f}},
      // bottom
      {{ -1.0f, -1.0f, -1.0f}, {0.2f, 0.8f, 0.5f}},
      {{  1.0f, -1.0f, -1.0f}, {0.2f, 0.8f, 0.5f}},
      {{  1.0f,  1.0f, -1.0f}, {0.2f, 0.8f, 0.5f}},
      {{ -1.0f, -1.0f, -1.0f}, {0.2f, 0.8f, 0.5f}},
      {{  1.0f,  1.0f, -1.0f}, {0.2f, 0.8f, 0.5f}},
      {{ -1.0f,  1.0f, -1.0f}, {0.2f, 0.8f, 0.5f}},
	  // right
      {{ -1.0f,  1.0f, -1.0f}, {0.8f, 0.3f, 0.4f}},
      {{  1.0f,  1.0f, -1.0f}, {0.8f, 0.3f, 0.4f}},
      {{  1.0f,  1.0f,  1.0f}, {0.8f, 0.3f, 0.4f}},
      {{ -1.0f,  1.0f, -1.0f}, {0.8f, 0.3f, 0.4f}},
      {{  1.0f,  1.0f,  1.0f}, {0.8f, 0.3f, 0.4f}},
      {{ -1.0f,  1.0f,  1.0f}, {0.8f, 0.3f, 0.4f}},
      // left
      {{ -1.0f, -1.0f, -1.0f}, {0.3f, 0.8f, 0.6f}},
      {{  1.0f, -1.0f, -1.0f}, {0.3f, 0.8f, 0.6f}},
      {{  1.0f, -1.0f,  1.0f}, {0.3f, 0.8f, 0.6f}},
      {{ -1.0f, -1.0f, -1.0f}, {0.3f, 0.8f, 0.6f}},
      {{  1.0f, -1.0f,  1.0f}, {0.3f, 0.8f, 0.6f}},
      {{ -1.0f, -1.0f,  1.0f}, {0.3f, 0.8f, 0.6f}},
	   // front
      {{ -1.0f, -1.0f, -1.0f}, {0.1f, 0.2f, 0.8f}},
      {{ -1.0f, -1.0f,  1.0f}, {0.1f, 0.2f, 0.8f}},
      {{ -1.0f,  1.0f,  1.0f}, {0.1f, 0.2f, 0.8f}},
      {{ -1.0f, -1.0f, -1.0f}, {0.1f, 0.2f, 0.8f}},
      {{ -1.0f,  1.0f,  1.0f}, {0.1f, 0.2f, 0.8f}},
      {{ -1.0f,  1.0f, -1.0f}, {0.1f, 0.2f, 0.8f}},
      // back
      {{  1.0f, -1.0f, -1.0f}, {0.2f, 0.5f, 0.8f}},
      {{  1.0f, -1.0f,  1.0f}, {0.2f, 0.5f, 0.8f}},
      {{  1.0f,  1.0f,  1.0f}, {0.2f, 0.5f, 0.8f}},
      {{  1.0f, -1.0f, -1.0f}, {0.2f, 0.5f, 0.8f}},
      {{  1.0f,  1.0f,  1.0f}, {0.2f, 0.5f, 0.8f}},
      {{  1.0f,  1.0f, -1.0f}, {0.2f, 0.5f, 0.8f}},
    };
  obj.count = vertices.size();

  // create vertex buffer object
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // create vertex array object
  glGenVertexArrays(1, &(obj.vao));
  glBindVertexArray(obj.vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    offsetof(Vertex, position)
  );
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (const void*)offsetof(Vertex, color)
  );
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return obj;
}

void draw(Object obj) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(obj.program);
  
  GLint modelLocation = glGetUniformLocation(obj.program, "uModel");
  GLint viewLocation = glGetUniformLocation(obj.program, "uView");
  GLint projLocation = glGetUniformLocation(obj.program, "uProj");
  double time = glfwGetTime();
  
  glm::mat4 view = glm::lookAt(glm::vec3(10.0f, 3.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 15.0f, 15.0f));
  glm::mat4 proj = glm::perspective(glm::radians(100.0f), 1.0f, 0.1f, 100.0f);

  
  glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(projLocation, 1, GL_FALSE, &proj[0][0]);
  
  glBindVertexArray(obj.vao);

  for (int i = -5; i < 6; i++){
    for (int j = -5; j < 6; j++){
      for (int k = -5; k < 6; k++){
        glm::mat4 model1 = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f * i, 3.0f * j, 3.0f * k));
        //model1 = glm::rotate(model1, (float)time, glm::vec3(1.0f, 0.0f, 0.0f));
        model1 = glm::scale(model1, glm::vec3(0.4f, 0.4f, 0.4f));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model1[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, obj.count);
      }
    }
  }
}

void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(600, 600, "Toprak", nullptr, nullptr);
  if (!window) {
    std::cout << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwMakeContextCurrent(window);
  glewInit();

  Object obj = initObj();
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glViewport(0, 0, 600, 600);
  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window)) {
    draw(obj);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

