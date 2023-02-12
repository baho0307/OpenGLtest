#include <iostream>

#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<GLFW/glfw3.h>
#include"shaderprogram.hpp"

GLfloat rgb(float c) 
{
    return c/255;
}
float length = 0.08;
glm::vec3 pos = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
glm::vec4 color2 = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
glm::vec4 color3 = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

float vertices[] = {
     -length / 2,  length / 2, 0.0f,
     -length / 2, -length / 2, 0.0f,
      length / 2, -length / 2, 0.0f,

     -length / 2,  length / 2, 0.0f,
      length / 2, -length / 2, 0.0f,
      length / 2,  length / 2, 0.0f,
};

unsigned int programID;
unsigned int VBO;
unsigned int VAO;

float xVal = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwTerminate();

        if (key == GLFW_KEY_LEFT)
            pos.x -= length;

        if (key == GLFW_KEY_RIGHT)
            pos.x += length;

        if (key == GLFW_KEY_DOWN)
            pos.y -= length;

        if (key == GLFW_KEY_UP)
            pos.y += length;
    }
}

int main(int argc, char** argv)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Test", NULL, NULL);


    if (window == NULL)
    {
        std::cout << "Pencere Olusturulamadi" << std::endl;

        glfwTerminate();

        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    programID = glCreateProgram();

    ShaderProgram program;

    program.attachShader("simplevs.glsl", GL_VERTEX_SHADER);
    program.attachShader("simplefs.glsl", GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(rgb(0), rgb(0), rgb(0), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();

        program.setVec3("uMove", pos);
        program.setVec4("uColor", color);
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        program.setVec3("uMove", pos + glm::vec3(-length,0.0f, 0.0f));
        program.setVec4("uColor", color2);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        program.setVec3("uMove", pos + glm::vec3(0.0f, -length, 0.0f));
        program.setVec4("uColor", color3);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    system("exit");
}