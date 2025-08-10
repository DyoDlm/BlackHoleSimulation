#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct Engine
{
    GLFWwindow* window;
    const short int WIDTH = 800;
    const short int HEIGHT = 600;

    Engine() {
        if (!glfwInit()) {
            std::cerr << "Erreur lors de l'initialisation de GLFW\n";
            exit(EXIT_FAILURE);
        }

        window = glfwCreateWindow(WIDTH, HEIGHT, "Black Hole Sim", nullptr, nullptr);
        if (!window) {
            std::cerr << "Erreur lors de la création de la fenêtre GLFW\n";
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            std::cerr << "Erreur lors de l'initialisation de GLEW\n";
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glViewport(0, 0, WIDTH, HEIGHT);

        // Projection orthographique (coordonnées en pixels)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void clear() {
        glLoadIdentity();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
    }

    ~Engine() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

#endif
