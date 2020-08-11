
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"

static GLFWwindow *m_win = NULL;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
            
    //glVertexPointer(2, GL_FLOAT, sizeof(particle), m_par);
    //glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(color), m_col);

    glPointSize(3.0);
    //glDrawArrays(GL_POINTS, 0, PARTICLES);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void graphics_init()
{
    if (!glfwInit())
    {
        fprintf(stderr, "failure init!\n");
        exit(1);
    }

    m_win = glfwCreateWindow(640, 480, "Hamiltonian Neural Network", NULL, NULL);

    if (!m_win)
    {
        fprintf(stderr, "failure window creation!\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_win);
}

void graphics_loop()
{
    if (!m_win)
    {
        fprintf(stderr, "failure window not initialized!\n");
        glfwTerminate();
        exit(1);
    }

    while (!glfwWindowShouldClose(m_win))
    {
        // custom render function
        display();

        glfwSwapBuffers(m_win);
        glfwPollEvents();
    }

    glfwTerminate();
}
