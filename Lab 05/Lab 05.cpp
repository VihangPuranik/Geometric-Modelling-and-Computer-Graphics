// Lab 05.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void cursorEnterCallback(GLFWwindow* window, int entered);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void drawCircle(GLfloat x, GLfloat y);

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetCursorEnterCallback(window, cursorEnterCallback);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    glfwSetScrollCallback(window, scrollCallback);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render OpenGL here

        double x, y;
        glfwGetCursorPos(window, &x, &y);
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

        if (state == GLFW_PRESS)
        {
            std::cout << "Left Mouse Button Pressed" << std::endl;

            GLfloat twicePi = 0.12566f;

            GLfloat radius = 50;

            GLfloat circleVerticesX[52];
            GLfloat circleVerticesY[52];
            GLfloat circleVerticesZ[52];

            circleVerticesX[0] = x;
            circleVerticesY[0] = 800 - y;
            circleVerticesZ[0] = 0;

            for (int i = 1; i < 52; i++)
            {
                circleVerticesX[i] = x + (radius * cos(i * twicePi));
                circleVerticesY[i] = 800 - y + (radius * sin(i * twicePi));
                circleVerticesZ[i] = 0;
            }

            GLfloat allCircleVertices[(52) * 3];

            for (int i = 0; i < 52; i++)
            {
                allCircleVertices[i * 3] = circleVerticesX[i];
                allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
                allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
            }

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 52);
            glDisableClientState(GL_VERTEX_ARRAY);
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << xpos << " : " << ypos << std::endl;
}

void cursorEnterCallback(GLFWwindow* window, int entered)
{
    if (entered)
    {
        std::cout << "Entered Window" << std::endl;
    }
    else
    {
        std::cout << "Left window" << std::endl;
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        std::cout << "Left button pressed" << std::endl;

        void drawCircle(GLfloat xpos, GLfloat ypos);
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << xoffset << " : " << yoffset << std::endl;
}