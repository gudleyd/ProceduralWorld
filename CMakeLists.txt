cmake_minimum_required(VERSION 3.16)
project(ProceduralWorld)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(ProceduralWorld main.cpp src/engine/application/Application.cpp src/engine/application/Application.h src/engine/shader/Shader.cpp src/engine/shader/Shader.h src/engine/block-world/BlockWorld.cpp src/engine/block-world/BlockWorld.h src/engine/entities/Entity.h src/engine/time-manager/TimeManager.cpp src/engine/time-manager/TimeManager.h src/engine/utils/Utils.cpp src/engine/utils/Utils.h src/engine/camera/Camera.cpp src/engine/camera/Camera.h src/engine/controllers/Controllers.cpp src/engine/controllers/Controllers.h src/engine/events/events.h)

if(UNIX)
    target_link_libraries(ProceduralWorld -lglut -lGL -lGLU -lglfw -lGLEW)
endif()