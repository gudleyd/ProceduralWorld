//
// Created by lebedev-ivan on 25.04.2020.
//

#include "Application.h"

#include <memory>


namespace gdl {

    Application::Application() {
        if (!glfwInit())
            throw std::runtime_error("Cannot init glfw");

        this->mainWindow = glfwCreateWindow(800, 600, "Hello, world", nullptr, nullptr);
        if (!this->mainWindow) {
            glfwTerminate();
            throw std::runtime_error("Cannot open the window");
        }

        glfwMakeContextCurrent(this->mainWindow);

        if (glewInit() != GLEW_OK)
            throw std::runtime_error("Cannot init glew");

        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    void Application::run() {

        TimeManager timeManager;
        WindowController windowController(this->mainWindow);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LESS);
        glEnable(GL_MULTISAMPLE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        Scene scene;
        scene.addObject(std::make_shared<BlockWorld>());
        while (!windowController.shouldClose()) {
            timeManager.tick();
            windowController.clear();

            scene.update(timeManager, this->mainWindow);

            windowController.update(timeManager);
            windowController.render(&scene);

            glfwPollEvents();
        }
        glfwTerminate();
    }
}