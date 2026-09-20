#pragma once

#include <engine.hpp>

#define BACKEND_OPENGL 1

class Application {

public:

    Application(int backend);
    int run();

private:

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    engine::GraphicsBackend backend;

};