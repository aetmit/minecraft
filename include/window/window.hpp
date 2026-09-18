#ifndef WINDOW_WINDOW_HPP
#define WINDOW_WINDOW_HPP

#include <string>


#include <glad/glad.h>
// tell glfw not to include system opengl headers
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace engine {

class Window {

public:
    ~Window();

    Window(int width, int height, std::string name);

    void pollEvents();

    void swapBuffers();

    bool shouldClose() const;

private:
    GLFWwindow *getWindow() const;

    GLFWwindow *window;

};

} // namespace engine

#endif // WINDOW_WINDOW_HPP