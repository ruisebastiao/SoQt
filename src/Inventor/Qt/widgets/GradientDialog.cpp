/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <qlayout.h>
#include <qfiledialog.h>
#include <qcombobox.h>
#include <qimage.h>
#include <qpushbutton.h>

#include "SoQtGradientDialog.h"
#include "gradientp/GradientEditor.h"
#include "gradientp/Gradient.h"

#include <Inventor/Qt/widgets/moc_SoQtGradientDialog.icc>


SoQtGradientDialog::SoQtGradientDialog(Gradient * grad, QWidget * parent, bool modal, const char* name)
: QDialog(parent, name, modal)
{
  this->gradEdit = new GradientEditor(grad, this, "gradEdit");

  QVBoxLayout * topLayout = new QVBoxLayout(this);
  topLayout->addWidget(this->gradEdit);

  QHBoxLayout * buttonLayout = new QHBoxLayout();
  topLayout->addLayout(buttonLayout);

  buttonLayout->setAlignment(Qt::AlignLeft);

  QPushButton * loadButton = new QPushButton(this, "loadButton");
  loadButton->setText("Load");
  buttonLayout->addWidget(loadButton, 0, 1);

  QPushButton * saveButton = new QPushButton(this, "saveButton");
  saveButton->setText("Save");
  buttonLayout->addWidget(saveButton, 0, 1);

  this->gradientList = new QComboBox(this, "gradientList");
 // this->addGradient(grad);

  buttonLayout->addWidget(gradientList, 0, 1);

  connect(loadButton, SIGNAL(clicked()), this, SLOT(loadGradient()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveGradient()));

  connect(this->gradientList, SIGNAL(activated(int)), this, SLOT(chooseGradient(int)));
  
  connect(this->gradEdit, SIGNAL(accepted()), this, SLOT(accept()));
  connect(this->gradEdit, SIGNAL(rejected()), this, SLOT(reject()));
}

SoQtGradientDialog::~SoQtGradientDialog()
{
}

void SoQtGradientDialog::addGradient(Gradient * grad)
{
  this->gradients.append(grad);
  this->gradientList->insertItem(this->makePixmap(grad), "description");
}

void SoQtGradientDialog::loadGradient()
{
  QString filename = QFileDialog::getOpenFileName();
  const char * string = filename.ascii();  
  Gradient * grad = new Gradient(string);
  this->gradients.append(grad);
  this->gradEdit->setGradient(grad);
  gradientList->insertItem(this->makePixmap(grad), "description");
}

void SoQtGradientDialog::saveGradient()
{
  QString filename = QFileDialog::getSaveFileName();
  this->gradEdit->getGradient()->save(filename.ascii());
}

void SoQtGradientDialog::chooseGradient(int i)
{
  this->gradEdit->setGradient(this->gradients[i]);
  this->gradEdit->updateAll();
}

Gradient * SoQtGradientDialog::getGradient() const
{
  return this->gradEdit->getGradient();
}

QPixmap SoQtGradientDialog::makePixmap(const Gradient * grad)
{
  int width = 60;
  int height = 16;
  QImage img(width, height, 32);

  SbColor4f * colorArray = new SbColor4f[width];
  grad->getColorArray(colorArray, width);

  for (int i = 0; i < width; i++) {
    uint32_t pixel = colorArray[i].getPackedValue()>>8;
    for (int j = 0; j < height; j++) {
      img.setPixel(i, j, pixel);
    }
  }
  QPixmap pm;
  pm.convertFromImage(img,  Qt::OrderedAlphaDither);
  return pm;
}
