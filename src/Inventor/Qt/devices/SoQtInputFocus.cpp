/**************************************************************************\
 *
 *  This file is part of the Coin family of 3D visualization libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and / or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use this library in software that is incompatible
 *  with the GNU GPL, and / or you would like to take advantage of the
 *  additional benefits with regard to our support services, please
 *  contact Systems in Motion about acquiring a Coin Professional
 *  Edition License.  See <URL:http://www.coin3d.org> for more
 *  information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

// FIXME: this device class has not been implemented yet. 20020625 mortene.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/errors/SoDebugError.h>

#include <soqtdefs.h>
#include <Inventor/Qt/devices/SoQtInputFocus.h>
#include <Inventor/Qt/devices/SoGuiInputFocusP.h>

// *************************************************************************

class SoQtInputFocusP : public SoGuiInputFocusP {
public:
  SoQtInputFocusP(SoQtInputFocus * p) : SoGuiInputFocusP(p) { }
};

// *************************************************************************

SoQtInputFocus::SoQtInputFocus(int mask)
{
  PRIVATE(this) = new SoQtInputFocusP(this);
  PRIVATE(this)->eventmask = mask;
}

SoQtInputFocus::~SoQtInputFocus()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoQtInputFocus::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  SOQT_STUB();
}

void
SoQtInputFocus::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  SOQT_STUB();
}

// *************************************************************************

const SoEvent *
SoQtInputFocus::translateEvent(QEvent *)
{
  SOQT_STUB();
  return NULL;
}

// *************************************************************************
