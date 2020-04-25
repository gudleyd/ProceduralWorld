//
// Created by lebedev-ivan on 25.04.2020.
//

#include "Controllers.h"


namespace gdl {

    void KeyboardController::addCallback(gdl::EventType eventType, gdl::KeyboardKey key,
                                         std::function<void()> callbackHandler) {
        this->callbacks.emplace_back(eventType, key, std::move(callbackHandler));
    }

    void KeyboardController::registerCallbacks() {
        glfwSetKeyCallback(this->window, [](GLFWwindow *kWindow, int key, int, int action, int) {
            auto &kCallbacks = std::get<0>(*static_cast<TCallbacks *>(glfwGetWindowUserPointer(kWindow)));
            for (auto &f: kCallbacks) {
                if ((int)std::get<0>(f) == action && (int)std::get<1>(f) == key)
                        std::get<2>(f)();
            }
        });
    }

    const TKeyboardCallbacks &KeyboardController::getCallbacks() {
        return this->callbacks;
    }


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

    void MouseController::setMoveCallback(std::function<void(double, double)> callbackHandler) {
        std::get<0>(this->callbacks) = std::move(callbackHandler);
    }

    void MouseController::addClickCallback(gdl::EventType type, gdl::MouseButton button,
                                           std::function<void(double, double)> callbackHandler) {
        std::get<1>(this->callbacks).emplace_back(button, type, std::move(callbackHandler));
    }

    void MouseController::registerCallbacks() {
        glfwSetCursorPosCallback(this->window, [](GLFWwindow *mWindow, double x, double y) {
            auto &data = std::get<1>(*static_cast<TCallbacks *>(glfwGetWindowUserPointer(mWindow)));
            std::get<0>(data)(x, y);
        });
        glfwSetMouseButtonCallback(this->window, [](GLFWwindow *mWindow, int button, int action, int) {
            auto &mCallbacks = std::get<1>(*static_cast<TCallbacks *>(glfwGetWindowUserPointer(mWindow)));
            auto &clickCallbacks = std::get<1>(mCallbacks);
            for (auto &f: clickCallbacks) {
                if ((int)std::get<1>(f) == action && (int)std::get<0>(f) == button) {
                    double x, y;
                    glfwGetCursorPos(mWindow, &x, &y);
                    std::get<2>(f)(x, y);
                }
            }
        });

    }

    const TMouseCallbacks &MouseController::getCallbacks() {
        return this->callbacks;
    }

    KeyboardController &WindowController::keyboardController() {
        return this->keyboard;
    }

    MouseController &WindowController::mouseController() {
        return this->mouse;
    }

    void WindowController::registerCallbacks() {
        this->keyboard.registerCallbacks();
        this->mouse.registerCallbacks();

        std::get<0>(this->callbacks) = this->keyboard.getCallbacks();
        std::get<1>(this->callbacks) = this->mouse.getCallbacks();

        glfwSetWindowUserPointer(this->window, &this->callbacks);
    }
}