//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <functional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../events/events.h"


namespace gdl {

    typedef std::tuple<gdl::EventType, gdl::KeyboardKey, std::function<void()>> TKeyboardCallback;
    typedef std::vector<TKeyboardCallback> TKeyboardCallbacks;

    typedef std::function<void(double, double)> TMouseMoveCallback;
    typedef std::tuple<gdl::MouseButton, gdl::EventType, std::function<void(double, double)>> TMouseClickCallback;
    typedef std::tuple<TMouseMoveCallback, std::vector<TMouseClickCallback>> TMouseCallbacks;

    typedef std::tuple<TKeyboardCallbacks, TMouseCallbacks> TCallbacks;


    class KeyboardController {
    public:
        explicit KeyboardController(GLFWwindow *window): window(window) { };
        void addCallback(gdl::EventType eventType, gdl::KeyboardKey key, std::function<void()> callbackHandler);
        void registerCallbacks();
        const TKeyboardCallbacks& getCallbacks();
    private:
        GLFWwindow *window;
        TKeyboardCallbacks callbacks;
    };


    class MouseController {
    public:
        explicit MouseController(GLFWwindow *window): window(window) { };
        void setCursorPos(double x, double y);
        void getCursorPos(double* x, double* y);
        void showCursor();
        void hideCursor();
        void setMoveCallback(std::function<void(double, double)> callbackHandler);
        void addClickCallback(gdl::EventType type, gdl::MouseButton button, std::function<void(double, double)> callbackHandler);
        void registerCallbacks();
        const TMouseCallbacks& getCallbacks();
    private:
        GLFWwindow *window;
        TMouseCallbacks callbacks;
    };


    class WindowController {
    public:
        explicit WindowController(GLFWwindow *window): window(window), keyboard(window), mouse(window) { };
        KeyboardController& keyboardController();
        MouseController& mouseController();
        void registerCallbacks();
    private:
        GLFWwindow *window;
        KeyboardController keyboard;
        MouseController mouse;
        TCallbacks callbacks;
    };

}
