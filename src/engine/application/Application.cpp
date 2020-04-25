//
// Created by lebedev-ivan on 25.04.2020.
//

#include "Application.h"


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
        double ox, oy;
        Camera camera;
        WindowController windowController(this->mainWindow);
        windowController.mouseController().setMoveCallback([&camera, &ox, &oy](double x, double y) {
        });
        windowController.registerCallbacks();
        TimeManager timeManager;
        gdl::Shader shaderUtil("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");
        shaderUtil.use();
        shaderUtil.setUniform4f("u_Color", 1.0, 0.0, 0.0, 1.0);

        glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 100.0f);
        shaderUtil.setUniformMat4f("u_Proj", proj);

//        camera.move(glm::vec3(0.0f, 50.0f, 0.0f));
//        camera.update();

        gdl::BlockWorld blockWorld;
        glEnable(GL_DEPTH_TEST);
        while (!glfwWindowShouldClose(this->mainWindow)) {
            timeManager.tick();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            camera.move(Left, timeManager);
            camera.update();

            shaderUtil.setUniformMat4f("u_Proj", proj);
            shaderUtil.setUniformMat4f("u_View", camera.getView());
            blockWorld.update(timeManager);
            blockWorld.render();

            glfwSwapBuffers(this->mainWindow);

            glfwPollEvents();
        }
        shaderUtil.stop();
        glfwTerminate();
    }
}