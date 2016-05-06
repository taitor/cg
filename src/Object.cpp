//
//  Object.cpp
//
//  Created by otita on 2016/04/13.
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

#include <cmath>

#include <OpenGL/gl.h>

#include "Object.h"

namespace otita {

namespace cg {

class GLTriangle : public Triangle {
public:
  GLTriangle(const double (&vertexes)[6]);
  virtual void render();
private:
  double _vertexes[6];
};

class GLCircle : public Circle {
public:
  GLCircle(const double (&center)[2],
           const double radius);
  virtual void render();
private:
  double _center[2];
  double _radius;
};

class GLObjectFactory : public ObjectFactory {
public:
  virtual Triangle *createTriangle(const double (&vertexes)[6]);
  virtual Circle *createCircle(const double (&center)[2],
                               const double radius);
};

World::~World() {
  for (Object *obj : _objects) {
    delete obj;
  }
}

void World::render() {
  using namespace std;
  for (Object *obj : _objects) {
    obj->render();
  }
}

void World::addObject(Object *obj) {
  _objects.push_back(obj);
}

ObjectFactory *ObjectFactory::_instance = nullptr;

ObjectFactory *ObjectFactory::getInstance() {
  if (!_instance) {
    _instance = new GLObjectFactory();
  }
  return _instance;
}

void ObjectFactory::deleteInstance() {
  if (_instance) {
    delete _instance;
    _instance = nullptr;
  }
}

GLTriangle::GLTriangle(const double (&vertexes)[6]) {
  for (uint32_t i = 0; i < 6; i++) {
    _vertexes[i] = vertexes[i];
  }
}

void GLTriangle::render() {
  glBegin(GL_TRIANGLES);
  {
    glColor3d(1, 0, 0);
    for (uint32_t i = 0; i < 3; i++) {
      glVertex3d(_vertexes[2 * i], _vertexes[2 * i + 1], 0.);
    }
  }
  glEnd();
}

GLCircle::GLCircle(const double (&center)[2],
                   const double radius) {
  for (unsigned i = 0; i < 2; i++) {
    _center[i] = center[i];
  }
  _radius = radius;
}

void GLCircle::render() {
  for (double th1 = 0.0; th1 <= 360.; th1 += 1.) {
    double th2 = th1 + 10.0;
    double th1_rad = th1 / 180.0 * M_PI; 
    double th2_rad = th2 / 180.0 * M_PI;
  
    double x1 = _radius * cos(th1_rad);
    double y1 = _radius * sin(th1_rad);
    double x2 = _radius * cos(th2_rad);
    double y2 = _radius * sin(th2_rad);
  
    glBegin(GL_TRIANGLES); 
    {
      glVertex3d(_center[0], _center[1], 0.);
      glVertex3d(_center[0] + x1, _center[1] + y1, 0.);     
      glVertex3d(_center[0] + x2, _center[1] + y2, 0.);
    }
    glEnd();
  }
}

Triangle *GLObjectFactory::createTriangle(const double (&vertexes)[6]) {
  return new GLTriangle(vertexes);
}

Circle *GLObjectFactory::createCircle(const double (&center)[2],
                                      const double radius) {
  return new GLCircle(center, radius);
}

} // cg

} // otita
