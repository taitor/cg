//
//  Camera.cpp
//
//  Created by otita on 2016/04/15.
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

#include <cstdint>
#include <cmath>

#include <OpenGL/gl.h>

#include "Camera.h"

namespace otita {

namespace cg {

class GLCamera : public Camera {
public:
  GLCamera();
  virtual void setEye(const double (&eye)[3]);
  virtual void setCenter(const double (&center)[3]);
  virtual void setUp(const double (&up)[3]);
  virtual void look();
private:
  double _eye[3];
  double _center[3];
  double _up[3];
};

class GLCameraFactory : public CameraFactory {
public:
  virtual Camera *createCamera();
};

void Camera::lookAt(
    const double (&eye)[3],
    const double (&center)[3],
    const double (&up)[3]
    ) {
  setEye(eye);
  setCenter(center);
  setUp(up);
}

CameraFactory *CameraFactory::_instance = nullptr;

CameraFactory *CameraFactory::getInstance() {
  if (!_instance) {
    _instance = new GLCameraFactory();
  }
  return _instance;
}

void CameraFactory::deleteInstance() {
  if (_instance) {
    delete _instance;
    _instance = nullptr;
  }
}

GLCamera::GLCamera() {
  setEye({0., 0., 0.8});
  setCenter({0., 0., 0.});
  setUp({0., 1., 0.});
}

void GLCamera::setEye(const double (&eye)[3]) {
  for (uint32_t i = 0; i < 3; i++) {
    _eye[i] = eye[i];
  }
}

void GLCamera::setCenter(const double (&center)[3]) {
  for (uint32_t i = 0; i < 3; i++) {
    _center[i] = center[i];
  }
}

void GLCamera::setUp(const double (&up)[3]) {
  for (uint32_t i = 0; i < 3; i++) {
    _up[i] = up[i];
  }
}

void GLCamera::look() {
  double f[3] = {_center[0] - _eye[0],
                 _center[1] - _eye[1],
                 _center[2] - _eye[2]};
  {
    double len = sqrt(f[0] * f[0] +
                      f[1] * f[1] +
                      f[2] * f[2]);
    for (uint32_t i = 0; i < 3; i++) {
      f[i] /= len;
    }
  }
  double UP[3] = {_up[0], _up[1], _up[2]};
  {
    double len = sqrt(_up[0] * _up[0] + 
                      _up[1] * _up[1] + 
                      _up[2] * _up[2]);
    for (uint32_t i = 0; i < 3; i++) {
      UP[i] /= len;
    }
  }
  double s[3] = {f[1] * UP[2] - f[2] * UP[1],
                 f[2] * UP[0] - f[0] * UP[2],
                 f[0] * UP[1] - f[1] * UP[0]};
  double u[3] = {s[1] * f[2] - s[2] * f[1],
                 s[2] * f[0] - s[0] * f[2],
                 s[0] * f[1] - s[1] * f[0]};
  double M[16] = {   s[0],    s[1],    s[2],     0.,
                     u[0],    u[1],    u[2],     0.,
                    -f[0],   -f[1],   -f[2],     0.,
                  _eye[0], _eye[1], _eye[2],     1.};

  glLoadIdentity();
  glMultMatrixd(M);
}

Camera *GLCameraFactory::createCamera() {
  return new GLCamera();
}

} // cg

} // otita
