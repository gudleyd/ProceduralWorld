//
// Created by lebedev-ivan on 25.04.2020.
//

#include <iostream>
#include "Controllers.h"


namespace gdl {

    void MouseController::getCursorPos(double *x, double *y) {
        glfwGetCursorPos(this->window, x, y);
    }

    void MouseController::setCursorPos(double x, double y) {
        glfwSetCursorPos(this->window, x, y);
    }

    void MouseController::hideCursor() {
        glfwSetInputMode(this->window, GLFW_CURSOR, (int) gdl::CursorState::Hidden);
    }

    void MouseController::showCursor() {
        glfwSetInputMode(this->window, GLFW_CURSOR, (int) gdl::CursorState::Visible);
    }

    void MouseController::focus() {
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        this->focused = true;
    }

    void MouseController::loseFocus() {
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        this->focused = false;
    }

    bool MouseController::isFocused() const {
        return this->focused;
    }

    void MouseController::setMoveCallback(std::function<void(double, double)> callbackHandler) {
        std::get<0>(this->callbacks) = std::move(callbackHandler);
    }

    void MouseController::addClickCallback(gdl::EventType type, gdl::MouseButton button,
                                           std::function<void(double, double)> callbackHandler) {
        std::get<1>(this->callbacks).emplace_back(button, type, std::move(callbackHandler));
    }

    const TMouseCallbacks &MouseController::getCallbacks() {
        return this->callbacks;
    }

    WindowController::WindowController(GLFWwindow *window): window(window), mouse(window), renderer(this) {
        glfwGetWindowSize(this->window, &this->width, &this->height);
        this->proj = glm::perspective(this->getCamera().getFov(), 1.0f * width / height, 0.1f, 100.0f);
        this->camera = Camera();
        this->camera.setSpeed(5.0f);
        glfwSetFramebufferSizeCallback(this->window, [] (GLFWwindow* rWindow, int w, int h) {
            auto windowController = static_cast<WindowController*>(glfwGetWindowUserPointer(rWindow));
            glViewport(0, 0, w, h);
            windowController->width = w;
            windowController->height = h;
            windowController->proj = glm::perspective(windowController->getCamera().getFov(), 1.0f * w / h, 0.1f, 100.0f);
        });

        this->mouseController().setMoveCallback([this](double x, double y) {
            this->camera.mouseRotation(x - lastMouseX, lastMouseY - y);
            this->camera.update();
            lastMouseX = x;
            lastMouseY = y;
        });
        this->mouseController().focus();
        glfwSetCursorPosCallback(this->window, [](GLFWwindow *mWindow, double x, double y) {
            auto windowController = static_cast<WindowController*>(glfwGetWindowUserPointer(mWindow));
            if (windowController->mouseController().isFocused()) {
                auto& data = windowController->getMouseCallbacks();
                std::get<0>(data)(x, y);
            }
        });
        glfwSetMouseButtonCallback(this->window, [](GLFWwindow *mWindow, int button, int action, int) {
            auto windowController = static_cast<WindowController*>(glfwGetWindowUserPointer(mWindow));
            if (windowController->mouseController().isFocused()) {
                auto& clickCallbacks = std::get<1>(windowController->getMouseCallbacks());
                for (auto &f: clickCallbacks) {
                    if ((int) std::get<1>(f) == action && (int) std::get<0>(f) == button) {
                        double x, y;
                        glfwGetCursorPos(mWindow, &x, &y);
                        std::get<2>(f)(x, y);
                    }
                }
            } else {
                if (action == (int)gdl::EventType::Press && button == (int)gdl::MouseButton::Left) {
                    windowController->mouseController().focus();
                }
            }
        });
        this->registerCallbacks();
    }

    void WindowController::handleInput(const TimeManager& tm) {
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::Escape)) {
            this->mouseController().loseFocus();
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::W)) {
            this->camera.move(Forward, tm);
            this->camera.update();
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::S)) {
            this->camera.move(Backward, tm);
            this->camera.update();
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::A)) {
            this->camera.move(Left, tm);
            this->camera.update();
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::D)) {
            this->camera.move(Right, tm);
            this->camera.update();
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::LeftShift)) {
            this->camera.setSpeed(15.0f);
        } else {
            this->camera.setSpeed(5.0f);
        }
        if (KeyboardEventManager::shared().isPressed(KeyboardKey::P)) {
            std::cout << "Camera: \n\tposition: " << this->camera.getPos().x << " "
            << this->camera.getPos().y << " "
            << this->camera.getPos().z
            << "\n\t\tpitch: " << this->camera.getPitch()
            << "\n\t\tyaw: " << this->camera.getYaw()
            << std::endl;
        }
    }

    void WindowController::update(const TimeManager& tm) {
        this->handleInput(tm);
    }

    void WindowController::render(Scene* scene) {
        glViewport(0, 0, width, height);
        this->camera.getShader().use();
        glm::mat4 model = glm::mat4(1.0f);
        this->camera.getShader().setUniformMat4f("u_Proj", this->getProjection());
        this->camera.getShader().setUniformMat4f("u_Model", model);
        this->renderer.render(&this->camera, scene);
        glfwSwapBuffers(this->window);
    }

    void WindowController::prepareInput() {
        KeyboardEventManager::shared().setCurrentWindow(this->window);
    }

    bool WindowController::shouldClose() {
        return glfwWindowShouldClose(this->window);
    }

    void WindowController::clear() {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    MouseController& WindowController::mouseController() {
        return this->mouse;
    }

    Camera& WindowController::getCamera() {
        return this->camera;
    }

    const glm::mat4& WindowController::getProjection() {
        return this->proj;
    }

    TMouseCallbacks& WindowController::getMouseCallbacks() {
        return this->callbacks;
    }

    void WindowController::registerCallbacks() {
        this->callbacks = this->mouse.getCallbacks();

        glfwSetWindowUserPointer(this->window, this);
    }
}