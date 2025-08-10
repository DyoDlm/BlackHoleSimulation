#include "Dev.hpp"
#include "BlackHole.hpp"

GLFWwindow    *init()
{
    if (!glfwInit()) {
        std::cerr << "Erreur GLFW\n";
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Black Hole Simulation", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur création fenêtre\n";
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Erreur GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return nullptr;
    }

    // Configurer viewport + projection orthographique 2D
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return (window);
}

Ray    *initRays()
{
    Ray         *rays = new Ray[NUM_RAYS];

    for (int i = 1; i < NUM_RAYS; i++)
    {
        Ray ray(glm::vec2(0, i * 20), glm::vec2(1, 0));
        rays[i] = ray;
    }
    return (rays);
}

int main() {
    GLFWwindow  *window = init();

    if (window == nullptr)
        return (-1);
    // Créer un trou noir centré
    BlackHole   hole(glm::vec2(400.0f, 300.0f), 1e13);
    Ray         *rays = initRays();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        hole.draw();

        for (int i = 0; i < NUM_RAYS; i++)
        {
            geodesic(rays[i], hole.r_s);
            rays[i].draw();
            rays[i].step(hole.position, hole.r_s);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Exit simulation" << std::endl;
    delete []rays;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
