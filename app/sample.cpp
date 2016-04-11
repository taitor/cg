//
//  sample.cpp
//
//  Created by otita on 2016/04/11.
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

#include <GLFW/glfw3.h>


static void error_callback(int error, const char *description) {
  using namespace std;
  cerr << description << endl;
}
  
static void key_callback(GLFWwindow *window,
                         int key,
                         int scancode,
                         int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE &&
      action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, const char *argv[]) {
  GLFWwindow *window;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) exit(EXIT_FAILURE);

  window = glfwCreateWindow(640, 480, "Example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = float(width) / float(height);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1., 1., 1., -1.);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef(glfwGetTime() * 50., 0., 0., 1.);

    glBegin(GL_TRIANGLES);
    glColor3f(1., 0., 0.);
    glVertex3f(-0.6, -0.4, 0.);
    glColor3f(0., 1., 0.);
    glVertex3f(0.6, -0.4, 0.);
    glColor3f(0., 0., 1.);
    glVertex3f(0., 0.6, 0.);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}
