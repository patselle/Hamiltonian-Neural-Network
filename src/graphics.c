
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"
#include "opts.h"

static GLFWwindow *m_win = NULL;

static particle *m_p = NULL;
static size_t m_c = 0;
static vec3f m_center;

static int m_width = 640;
static int m_height = 480;
static int m_logicalWidth = 500;

static int m_showDebug = 0;

typedef struct
{
    unsigned char r,g,b,a;
} color;

static color *m_colors = NULL;

static void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float logicalWidthHalf = m_logicalWidth / 2.0f;
    float ratio = (float)m_height / m_width;
    float logicalHeightHalf = logicalWidthHalf * ratio;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-logicalWidthHalf, logicalWidthHalf, -logicalHeightHalf, logicalHeightHalf, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(m_center.x, m_center.y, m_center.z);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
            
    glVertexPointer(2, GL_FLOAT, sizeof(particle), m_p);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(color), m_colors);

    glPointSize(2.0);
    glDrawArrays(GL_POINTS, 0, m_c);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    if (m_showDebug)
    {
        glBegin(GL_LINES);
        glColor3f(0, 0, 1);
        glVertex2f(-m_center.x + 5, -m_center.y);
        glVertex2f(-m_center.x - 5, -m_center.y);
        glVertex2f(-m_center.x, -m_center.y + 5);
        glVertex2f(-m_center.x, -m_center.y - 5);
        glEnd();
    }
}

static void key_pressed(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
    {
        m_showDebug = 1 - m_showDebug;
    }
}

static void mass_to_color(particle const * const p, unsigned int const c)
{
    off_t i;
    
    color max = { 255, 0, 0, 255 };
    color min = { 255, 255, 255, 255 };

    // get min and max mass

    float mass_min = p[0].mass, mass_max = p[0].mass;

    for (i = 1; i < c; i++)
    {
        if (p[i].mass < mass_min)
        {
            mass_min = p[i].mass;
        }
        else if (p[i].mass > mass_max)
        {
            mass_max = p[i].mass;
        }
    }

    // apply colors

    for (i = 0; i < c; i++)
    {
        m_colors[i].r =  min.r + (max.r - min.r) * (p[i].mass - mass_min) / (mass_max - mass_min);
        m_colors[i].g =  min.g + (max.g - min.g) * (p[i].mass - mass_min) / (mass_max - mass_min);
        m_colors[i].b =  min.b + (max.b - min.b) * (p[i].mass - mass_min) / (mass_max - mass_min);
        m_colors[i].r =  255;
    }
}

void graphics_init(particle const * const p, opts_t const * const opts)
{
    if ((opts->flags & OPT_NO_GUI) > 0) 
        return;

    m_c = opts->particle_count;
    m_p = p;

    // initialize colors

    m_colors = (color*) malloc(sizeof(color) * m_c);

    if ((opts->flags & OPT_STATIC_COLOR) > 0)
    {
        memset(m_colors, 255, sizeof(color) * m_c);
    }
    else
    {
        mass_to_color(p, m_c);
    }

    if (!glfwInit())
    {
        fprintf(stderr, "failure init!\n");
        exit(1);
    }

    m_win = glfwCreateWindow(m_width, m_height, "Hamiltonian Neural Network", NULL, NULL);

    if (!m_win)
    {
        fprintf(stderr, "failure window creation!\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_win);
    glfwSetKeyCallback(m_win, key_pressed);
}

void graphics_loop()
{
    if (!m_win)
    {
        // if window is not initialized (--no-gui), loop over stdin
    
        while (1)
        {
            getchar();
        }
    }

    while (!glfwWindowShouldClose(m_win))
    {
        glfwPollEvents();

        // custom render function
        display();

        glfwSwapBuffers(m_win);
    }

    glfwTerminate();
}

void compute_center(vec3f * const center, particle const * const p, unsigned int const c)
{
    off_t i;

    memset(center, 0, sizeof(vec3f));

    for (i = 0; i < c; i++)
    {
        vec3f_add(center, center, &p[i].position);
    }

    vec3f_scalar(center, center, -1.0 / c);
}

void graphics_update()
{
    vec3f center;

    // compute center locally
    compute_center(&center, m_p, m_c);

    memcpy(&m_center, &center, sizeof(vec3f));
}
