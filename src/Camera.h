//
//  Camera.h
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

#ifndef _CAMERA_H_
#define _CAMERA_H_

namespace otita {

namespace cg {

class Camera {
public:
  virtual ~Camera() = default;
  virtual void setEye(const double (&eye)[3]) = 0;
  virtual void setCenter(const double (&center)[3]) = 0;
  virtual void setUp(const double (&up)[3]) = 0;
  virtual void lookAt(
      const double (&eye)[3],
      const double (&center)[3],
      const double (&up)[3]
      );
  virtual void look() = 0;
private:
};

class CameraFactory {
public:
  CameraFactory(const CameraFactory &) = delete;
  CameraFactory &operator =(const CameraFactory &) = delete;
  CameraFactory(CameraFactory &&) = delete;
  CameraFactory &operator =(CameraFactory &&) = delete;

  static CameraFactory *getInstance();
  static void deleteInstance();

  virtual Camera *createCamera() = 0;

protected:
  CameraFactory() = default;
  virtual ~CameraFactory() = default;
  static CameraFactory *_instance;
};

} // cg

} // otita

#endif  // _CAMERA_H_
