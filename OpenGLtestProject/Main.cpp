#include <iostream>
#include<thread>
#include<chrono>
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<glm/trigonometric.hpp>
#include<GLFW/glfw3.h>
#include"shaderprogram.hpp"
#include"square.hpp"
#include<vector>

GLfloat rgb(float c) 
{
    return c/255;
}
float length = 0.08;

std::vector<glm::vec3> vertices;

std::vector<unsigned int> indices;

unsigned int VAO;

unsigned int VBO;

unsigned int EBO;

void createCircle(float radius, int vertexCount)
{
    float angle = 360.0f / vertexCount;

    int triangleCount = vertexCount - 2;

    std::vector<glm::vec3> tempVertices;

    for (int i = 0; i < vertexCount; i++)
    {
        glm::vec3 nextPos;
        float nextAngle = angle*i;
        nextPos.x = radius*glm::cos(glm::radians(nextAngle));
        nextPos.y = radius*glm::sin(glm::radians(nextAngle));
        nextPos.z = 0.0f;
        vertices.push_back(nextPos);

    }

    for (int i = 0; i < triangleCount; i++)
    {
        indices.push_back(0);
        indices.push_back(i+1);
        indices.push_back(i+2);
    }
}


// Yýlan Kodlarý:

//void moveSnake(std::vector<Square*> snakeList)
//{
//    for (auto next : snakeList)
//        next->move(1);
//    for(int i = snakeList.size()-1; i > 0; i--)
//    {
//        snakeList[i]->setDirection(snakeList[i - 1]->getDirection());
//    }
//}
//
//void drawSnake(ShaderProgram& program, std::vector<Square*> snakeList)
//{
//    for (auto next : snakeList)
//    {
//        program.setVec3("uMove", next->getPosition());
//        program.setVec4("uColor", next->getColor());
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//    }
//}
//
//void addToSnakeTail(std::vector<Square*> snakeList)
//{
//    int elementCount = snakeList.size();
//
//    if (!elementCount)
//    {
//        snakeList.push_back(new Square(0.0f, 0.0f, length));
//    }
//    else
//    {
//        Square* lastSquare = snakeList[elementCount - 1];
//        glm::vec3 pos = lastSquare->getPosition();
//        Square::DIRECTION dir = lastSquare->getDirection();
//
//        switch (dir)
//        {
//            case Square::DIR_RIGHT:
//                pos += glm::vec3(-length, 0.0f, 0.0f);
//                break;
//            case Square::DIR_LEFT:
//                pos += glm::vec3(length, 0.0f, 0.0f);
//                break;
//            case Square::DIR_UP:
//                pos += glm::vec3(0.0f, -length, 0.0f);
//                break;
//            case Square::DIR_DOWN:
//                pos += glm::vec3(0.0f, length, 0.0f);
//                break;
//        }
//        
//        Square* newSquare = new Square(pos.x, pos.y, length);
//        newSquare->setDirection(dir);
//        snakeList.push_back(newSquare);
//    }
//}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(1)
    {
       
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

    createCircle(0.5, 36);

    ShaderProgram program;

    program.attachShader("simplevs.glsl", GL_VERTEX_SHADER);
    program.attachShader("simplefs.glsl", GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");

    // Generating Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
    

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(rgb(255), rgb(127), rgb(127), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();

        glBindVertexArray(VAO);
        program.setVec3("uMove", glm::vec3(0.0f, 0.0f, 0.0f));
        program.setVec4("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        glDrawElements(GL_TRIANGLES,  indices.size(),GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    
}