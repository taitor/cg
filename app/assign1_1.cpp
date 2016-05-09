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

#include "Window.h"
#include "Object.h"
#include "KeyboardDelegate.h"

int main(int argc, const char *argv[]) {
  using namespace std;
  using namespace otita::cg;

  WindowFactory *wFactory = WindowFactory::getInstance();
  Window *window = wFactory->createWindowOrDie(500, 500, "Test");
  WindowFactory::deleteInstance();

  World *world = new World();
  ObjectFactory *oFactory = ObjectFactory::getInstance();
  Circle *circle1 = oFactory->createCircle(1.);
  Circle *circle2 = oFactory->createCircle(1.5);
  world->addObject(circle1);
  world->addObject(circle2);
  ObjectFactory::deleteInstance();

  window->setWorld(world);

  double pos1[2] = {0., 1.};
  double pos2[2] = {0., 0.};
  while (!window->shouldClose()) {
    window->clear();
    circle1->setPosition(pos1);
    circle2->setPosition(pos2);
    window->draw();
    pos1[1] += 0.1;
    pos2[0] += 0.15;
    window->swapBuffers();
  }

  delete world;
  delete window;

  return 0;
}
