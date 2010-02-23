/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2009 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOQT_GLAREA_H
#define SOQT_GLAREA_H

#include <qgl.h>

#include <Inventor/Qt/SoQtBasic.h>


typedef void GLAreaKeyHandler(QKeyEvent * ke, void * userdata);

// *************************************************************************

class SoQtGLArea : public QGLWidget {
  typedef QGLWidget inherited;
  Q_OBJECT

public:
  SoQtGLArea(QGLFormat * const format, QWidget * const parent,
             const QGLWidget * sharewidget,
             const char * const name = "QtGLArea");
  ~SoQtGLArea();

  void registerQKeyEventHandler(GLAreaKeyHandler * cb, void * userdata)
  {
    this->keycb = cb;
    this->keycbuserdata = userdata;
  }

signals:
  void init_sig(void);
  void reshape_sig(int, int);
  void expose_sig(void);

protected:
  virtual void paintGL(void);
  virtual void resizeGL(int width, int height);
  virtual void initializeGL(void);

  virtual void focusInEvent(QFocusEvent * e);
  virtual void focusOutEvent(QFocusEvent * e);
  virtual bool event(QEvent * e);

private:
  GLAreaKeyHandler * keycb;
  void * keycbuserdata;
};

// *************************************************************************

#endif // ! SOQT_GLAREA_H
