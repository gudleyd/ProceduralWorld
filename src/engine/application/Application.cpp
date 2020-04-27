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
    }

    void Application::run() {

        TimeManager timeManager;
        WindowController windowController(this->mainWindow);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LESS);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        Scene scene;
        auto bw1 = std::make_shared<BlockWorld>();
        scene.addObject(bw1);
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