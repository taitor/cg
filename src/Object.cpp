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

#include <OpenGL/gl.h>

#include "Object.h"

namespace otita {

namespace cg {

class GLTriangle : public Triangle {
public:
  GLTriangle(const double (&vertexes)[9]);
  virtual void render();
private:
  double _vertexes[9];
};

class GLObjectFactory : public ObjectFactory {
public:
  virtual Triangle *createTriangle(const double (&vertexes)[9]);
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

GLTriangle::GLTriangle(const double (&vertexes)[9]) {
  for (uint32_t i = 0; i < 9; i++) {
    _vertexes[i] = vertexes[i];
  }
}

void GLTriangle::render() {
  glBegin(GL_TRIANGLES);
  {
    glColor3d(1, 0, 0);
    for (uint32_t i = 0; i < 3; i++) {
      glVertex3d(_vertexes[3 * i], _vertexes[3 * i + 1], _vertexes[3 * i + 2]);
    }
  }
  glEnd();
}

Triangle *GLObjectFactory::createTriangle(const double (&vertexes)[9]) {
  return new GLTriangle(vertexes);
}

} // cg

} // otita
