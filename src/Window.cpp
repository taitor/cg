//
//  Window.cpp
//
//  Created by otita on 2016/04/12.
//
/*
The MIT License (MIT)

Copyright (c) 2016 otita.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <iostream>
#include <cstdlib>

#include <GLFW/glfw3.h>

#include "Window.h"
#include "Object.h"

namespace otita {

namespace cg {

class GLWindow : public Window {
public:
  GLWindow(uint32_t width,
           uint32_t height,
           const char title[]);
  virtual ~GLWindow();
  virtual bool shouldClose() const;
  virtual void clear();
  virtual void swapBuffers();
private:
  GLFWwindow *_window;
};

class GLWindowFactory : public WindowFactory {
public:
  GLWindowFactory() {}
  virtual Window *createWindowOrDie(
      uint32_t width,
      uint32_t height,
      const char title[]
      );
};

void Window::draw() const {
  if (_world) _world->render();
}

void Window::setWorld(World *world) {
  _world = world;
}

WindowFactory *WindowFactory::getInstance() {
  return new GLWindowFactory();
}

GLWindow::GLWindow(
    uint32_t width,
    uint32_t height,
    const char title[]
    ) {
  using namespace std;

  if (!glfwInit()) exit(EXIT_FAILURE);

  _window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (!_window) {
    cerr << "cannot create window" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);
}

GLWindow::~GLWindow() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

bool GLWindow::shouldClose() const {
  return glfwWindowShouldClose(_window);
}

void GLWindow::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  float ratio;
  int width, height;
  glfwGetFramebufferSize(_window, &width, &height);
  ratio = float(width) / float(height);

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-ratio, ratio, -1., 1., 1., -1.);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  glRotatef(glfwGetTime() * 50., 0., 0., 1.);
}

void GLWindow::swapBuffers() {
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

Window *GLWindowFactory::createWindowOrDie(
    uint32_t width,
    uint32_t height,
    const char title[]
    ) {
  return new GLWindow(width, height, title);
}

} // cg

} // otita
