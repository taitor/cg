//
//  Window.h
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

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <cstdint>

namespace otita {

namespace cg {

class World;
class Camera;
class KeyboardDelegate;

class Window {
public:
  Window();
  virtual ~Window() {}
  virtual bool shouldClose() const = 0;
  void draw() const;
  virtual void clear() = 0;
  virtual void swapBuffers() = 0;
  void setWorld(World *world);
  virtual void setKeyboardDelegate(
      KeyboardDelegate *keyboardDelegate
      );
protected:
  World *_world;
  Camera *_camera;
  KeyboardDelegate *_keyboardDelegate;
};

class WindowFactory {
public:
  WindowFactory(const WindowFactory &) = delete;
  WindowFactory &operator =(const WindowFactory &) = delete;
  WindowFactory(WindowFactory &&) = delete;
  WindowFactory &operator =(WindowFactory &&) = delete;

  static WindowFactory *getInstance();
  static void deleteInstance();

  virtual Window *createWindowOrDie(
      uint32_t width,
      uint32_t height,
      const char title[]
      ) = 0;

protected:
  WindowFactory() = default;
  virtual ~WindowFactory() = default;
  static WindowFactory *_instance;
};

} // cg

} // otita

#endif  // _WINDOW_H_
