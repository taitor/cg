//
//  assign1_1.cpp
//
//  Created by otita on 2016/05/02.
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
#include <chrono>
#include <thread>
#include <random>

#include "Window.h"
#include "Object.h"
#include "KeyboardDelegate.h"

void setInitialPosition(double (&p0)[2], double (&p1)[2]) {
  using namespace std;
  static mt19937 mt(0);
  uniform_int_distribution<> dis(0, 100);
  for (uint32_t i = 0; i < 2; i++) {
    p0[i] = -10.;
    p1[i] = -9.9 + 0.1 * double(dis(mt)) / 100;
  }
}

int main(int argc, const char *argv[]) {
  using namespace std;
  using namespace std::chrono_literals;
  using namespace otita::cg;

  WindowFactory *wFactory = WindowFactory::getInstance();
  Window *window = wFactory->createWindowOrDie(500, 500, "assignment 1-1");
  WindowFactory::deleteInstance();

  World *world = new World();
  ObjectFactory *oFactory = ObjectFactory::getInstance();
  Circle *circle1 = oFactory->createCircle(0.5);
  world->addObject(circle1);
  ObjectFactory::deleteInstance();

  window->setWorld(world);

  double p0[2];
  double p1[2];
  setInitialPosition(p0, p1);
  double a[2] = {0., -9.7};
  double t = 0.016;
  while (!window->shouldClose()) {
    auto t0 = chrono::system_clock::now();

    window->clear();
    circle1->setPosition(p1);
    bool out = false;
    for (uint32_t i = 0; i < 2; i++) {
      if (p1[i] < -10 || p1[i] > 10) {
        out = true;
        break;
      }
    }

    if (out) {
      setInitialPosition(p0, p1);
    }
    else {
      for (uint32_t i = 0; i < 2; i++) {
        double p = p1[i];
        p1[i] = p1[i] + (p1[i] - p0[i]) + t * t * a[i];
        p0[i] = p;
      }
    }
    window->draw();
    window->swapBuffers();

    auto t1 = chrono::system_clock::now();
    auto dt = t1 - t0;
    auto wait = 16ms;
    if (dt < wait) {
      this_thread::sleep_for(wait);
    }
  }

  delete world;
  delete window;

  return 0;
}
