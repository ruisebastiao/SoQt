/**************************************************************************\
 *
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

//  $Id$

#ifndef SOQT_GLAREA_H
#define SOQT_GLAREA_H

#include <qgl.h>

// *************************************************************************

class SoQtGLArea : public QGLWidget {
  typedef QGLWidget inherited;

  Q_OBJECT

public:
  SoQtGLArea( QWidget * const parent, const char * const name = "QtGLArea" );
  ~SoQtGLArea(void);

signals:
  void init_sig(void);
  void reshape_sig(int, int);
  void expose_sig(void);

protected:
  virtual void paintGL(void);
  virtual void resizeGL( int width, int height );
  virtual void initializeGL(void);

}; // class SoQtGLArea

// *************************************************************************

#endif // ! SOQT_GLAREA_H