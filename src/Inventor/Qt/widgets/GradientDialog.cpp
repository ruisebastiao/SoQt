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
#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

#include <qlayout.h>
#include <qimage.h>
#include <qcanvas.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qvaluelist.h>
#include <qfiledialog.h>
#include <qpushbutton.h>

#include "gradientp/GradientView.h"
#include "gradientp/SoQtGradientDialogP.h"
#include "SoQtGradientDialog.h"

#include <Inventor/Qt/widgets/moc_SoQtGradientDialogP.icc>

SoQtGradientDialogP::SoQtGradientDialogP(SoQtGradientDialog * publ)
{
  PUBLIC(this) = publ;
  this->updateContinuously = FALSE;
}

void
SoQtGradientDialogP::contupdateClicked()
{
  this->updateContinuously = this->contupdate->isChecked();
}

void
SoQtGradientDialogP::callGradientUpdate()
{  
  if (this->changeCallBack) {
    this->changeCallBack(this->gradView->getGradient(), this->changeCallBackData);
  }
}

void
SoQtGradientDialogP::gradientCallBack(const Gradient & g, void * userData)
{
  SoQtGradientDialogP * thisp = (SoQtGradientDialogP *)userData;
  if (thisp->updateContinuously) {
    if (thisp->changeCallBack) { thisp->changeCallBack(g, thisp->changeCallBackData); }
  }
}

void
SoQtGradientDialogP::resetGradient()
{
  this->gradView->setGradient(this->gradientcopy);
  this->saveCurrent();
}

void 
SoQtGradientDialogP::loadGradient()
{
  if (this->fileDialog->exec()) {
    QString filename = this->fileDialog->selectedFile();
    if (!filename.isEmpty()) {
      this->saveCurrent();
      Gradient grad(filename);
      QString path = this->fileDialog->dirPath();
      QString description = filename.remove(0, path.length() + 1);
      PUBLIC(this)->addGradient(grad, description);
    }
  }
}

void 
SoQtGradientDialogP::saveGradient()
{
  if (this->fileDialog->exec()) {
    QString filename = this->fileDialog->selectedFile();
    if (!filename.isEmpty()) {
      Gradient grad = this->gradView->getGradient();
      grad.save(filename);
    
      QString path = this->fileDialog->dirPath();
      QString description = filename.remove(0, path.length() + 1);
      this->gradientList->changeItem(grad.getImage(60, 16, 32), description, this->old_index);
    }
  }
}

void 
SoQtGradientDialogP::chooseGradient(int i)
{
  this->saveCurrent();
  this->gradView->setGradient(this->gradients[i]);
  this->gradientcopy = this->gradients[i];
  this->old_index = i;
}

void SoQtGradientDialogP::saveCurrent()
{
  const Gradient & grad = this->gradView->getGradient();
  QString description = this->gradientList->text(this->old_index);
  this->gradientList->changeItem(grad.getImage(60, 16, 32), description, this->old_index);
  this->gradients[old_index] = grad;
}

SoQtGradientDialog::SoQtGradientDialog(const Gradient & grad,
                                       QWidget * parent, 
                                       bool modal, 
                                       const char* name)  
: QDialog(parent, name, modal)
{
  PRIVATE(this) = new SoQtGradientDialogP(this);

  PRIVATE(this)->fileDialog = new QFileDialog("gradients/",
                                      "*.grad",
                                      this);
  PRIVATE(this)->fileDialog->setFilter("*.grad"); 

  
  QCanvas * canvas = new QCanvas(450,75);
  PRIVATE(this)->gradView = new GradientView(canvas, grad, this, "GradientView");
  PRIVATE(this)->gradView->setFrameStyle(QFrame::Sunken);
  PRIVATE(this)->gradView->setMinimumHeight(75);

  PRIVATE(this)->gradientList = new QComboBox(this, "gradientList");
  PRIVATE(this)->old_index = 0;
  this->addGradient(grad, "no filename specified");
  PRIVATE(this)->gradientList->hide();

  QGridLayout * topLayout = new QGridLayout(this, 3, 2);
  topLayout->setSpacing(5);
  topLayout->setMargin(10);
  topLayout->addMultiCellWidget(PRIVATE(this)->gradView, 0, 0, 0, 2);

  QHBoxLayout * buttonLayout = new QHBoxLayout();
  topLayout->addLayout(buttonLayout, 2, 0);

  QVBoxLayout * loadsaveLayout = new QVBoxLayout();
  buttonLayout->addLayout(loadsaveLayout);

  QHBoxLayout * contupdateLayout = new QHBoxLayout();
  contupdateLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  topLayout->addLayout(contupdateLayout, 1, 2);

  QHBoxLayout * applyresetLayout = new QHBoxLayout();
  applyresetLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  topLayout->addLayout(applyresetLayout, 2, 2);

  loadsaveLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
  loadsaveLayout->addWidget(PRIVATE(this)->gradientList, 0, 1);

  QPushButton * loadButton = new QPushButton(this, "loadButton");
  loadButton->setText("Load");
  loadsaveLayout->addWidget(loadButton, 0, 1);

  QPushButton * saveButton = new QPushButton(this, "saveButton");
  saveButton->setText("Save");
  loadsaveLayout->addWidget(saveButton, 0, 1);

  PRIVATE(this)->contupdate = new QCheckBox(this);
  PRIVATE(this)->contupdate->setChecked(FALSE);

  PRIVATE(this)->contupdateLabel = new QLabel(this);
  PRIVATE(this)->contupdateLabel->setText("Continuous update ");
  PRIVATE(this)->contupdateLabel->setBuddy(PRIVATE(this)->contupdate);
  
  contupdateLayout->addWidget(PRIVATE(this)->contupdateLabel);
  contupdateLayout->addWidget(PRIVATE(this)->contupdate);

  PRIVATE(this)->applyButton = new QPushButton(this);
  PRIVATE(this)->applyButton->setText("Apply");
  applyresetLayout->addWidget(PRIVATE(this)->applyButton);

  QPushButton * resetButton = new QPushButton(this);
  resetButton->setText("Reset");
  applyresetLayout->addWidget(resetButton);

  QPushButton * doneButton = new QPushButton(this);
  doneButton->setText("Done");
  applyresetLayout->addWidget(doneButton);

  connect(loadButton, SIGNAL(clicked()), PRIVATE(this), SLOT(loadGradient()));
  connect(saveButton, SIGNAL(clicked()), PRIVATE(this), SLOT(saveGradient()));
  connect(PRIVATE(this)->applyButton, SIGNAL(clicked()), PRIVATE(this), SLOT(callGradientUpdate()));
  connect(resetButton, SIGNAL(clicked()), PRIVATE(this), SLOT(resetGradient()));
  connect(doneButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(PRIVATE(this)->gradientList, SIGNAL(activated(int)), PRIVATE(this), SLOT(chooseGradient(int)));
  connect(PRIVATE(this)->contupdate, SIGNAL(clicked()), PRIVATE(this), SLOT(contupdateClicked()));
}

SoQtGradientDialog::~SoQtGradientDialog()
{
  delete this->pimpl;
}

void 
SoQtGradientDialog::resizeEvent(QResizeEvent * e)
{
  this->resize(e->size());
  PRIVATE(this)->gradView->resize(e->size().width()-20, 75);

  this->repaint();
}

void SoQtGradientDialog::addGradient(const Gradient & grad, QString description)
{
  PRIVATE(this)->gradientcopy = grad;

  if (PRIVATE(this)->changeCallBack) {
    PRIVATE(this)->gradientcopy.setChangeCallback(PRIVATE(this)->gradientCallBack,
                                                  PRIVATE(this));
  }

  PRIVATE(this)->gradients.append(PRIVATE(this)->gradientcopy);
  PRIVATE(this)->gradientList->insertItem(PRIVATE(this)->gradientcopy.getImage(60, 16, 32), description);
  PRIVATE(this)->old_index = PRIVATE(this)->gradientList->count() - 1;
  
  PRIVATE(this)->gradientList->setCurrentItem(PRIVATE(this)->old_index);
  PRIVATE(this)->gradView->setGradient(PRIVATE(this)->gradientcopy);
  PRIVATE(this)->gradientList->show();
}

const Gradient & SoQtGradientDialog::getGradient() const
{
  return PRIVATE(this)->gradView->getGradient();
}

void SoQtGradientDialog::setDataLimits(float min, float max)
{
  PRIVATE(this)->gradView->setDataLimits(min, max);
}

void SoQtGradientDialog::setChangeCallback(Gradient::ChangeCB * cb, void * userdata)
{
  PRIVATE(this)->changeCallBack = cb;
  PRIVATE(this)->changeCallBackData = userdata;
  PRIVATE(this)->gradView->setChangeCallback(PRIVATE(this)->gradientCallBack, PRIVATE(this));
}

void 
SoQtGradientDialog::setContinuousNotification(SbBool yes)
{
  PRIVATE(this)->contupdate->setChecked(yes);
  PRIVATE(this)->updateContinuously = yes;
}

SbBool 
SoQtGradientDialog::getContinuousNotification(void) const
{
  return PRIVATE(this)->updateContinuously; 
}

void 
SoQtGradientDialog::alwaysContinuousUpdates(SbBool yes)
{
  PRIVATE(this)->updateContinuously = yes;
  if (yes) { 
    PRIVATE(this)->contupdate->hide(); 
    PRIVATE(this)->contupdateLabel->hide();
    PRIVATE(this)->applyButton->hide();
    
  }
  else {
    PRIVATE(this)->contupdate->show();
    PRIVATE(this)->contupdateLabel->show();
    PRIVATE(this)->applyButton->show();
  }
}

#undef PRIVATE
#undef PUBLIC
