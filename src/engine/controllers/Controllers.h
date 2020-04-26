//
// Created by lebedev-ivan on 25.04.2020.
//

#pragma once

#include <functional>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../events/Events.h"
#include "../camera/Camera.h"
#include "../scene/Scene.h"
#include "../renderer/Renderer.h"

namespace gdl {

    typedef std::function<void(double, double)> TMouseMoveCallback;
    typedef std::tuple<gdl::MouseButton, gdl::EventType, std::function<void(double, double)>> TMouseClickCallback;
    typedef std::tuple<TMouseMoveCallback, std::vector<TMouseClickCallback>> TMouseCallbacks;


    class MouseController {
    public:
        explicit MouseController(GLFWwindow *window): window(window), focused(true) { };

        void setCursorPos(double x, double y);
        void getCursorPos(double* x, double* y);

        void showCursor();
        void hideCursor();

        void focus();
        void loseFocus();
        bool isFocused() const;

        void setMoveCallback(std::function<void(double, double)> callbackHandler);
        void addClickCallback(gdl::EventType type, gdl::MouseButton button, std::function<void(double, double)> callbackHandler);
        const TMouseCallbacks& getCallbacks();

    private:
        GLFWwindow *window;
        bool focused;
        TMouseCallbacks callbacks;
    };


    class WindowController {
    public:
        explicit WindowController(GLFWwindow *window);

        void update(const TimeManager&);
        void render(Scene*);

        bool shouldClose();
        void clear();

        MouseController& mouseController();

        Camera& getCamera();
        const glm::mat4& getProjection();


        TMouseCallbacks& getMouseCallbacks();
        void registerCallbacks();

    private:
        GLFWwindow *window;
        int width, height;
        double lastMouseX, lastMouseY;
        glm::mat4 proj;

        MouseController mouse;
        TMouseCallbacks callbacks;

        Renderer renderer;
        Camera camera;

        void handleInput(const TimeManager&);
    };

}
