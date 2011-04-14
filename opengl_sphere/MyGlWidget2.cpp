//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "MyGlWidget.h"
#include <QtGui/QImage>
#include <QtGui/QMouseEvent>
#include <QtCore/QTimeLine>
#include <QtSvg/QSvgRenderer>
#include <QtOpenGL/QGLFramebufferObject>
#include <QtGui/QAction>
#include <cmath>


MyGlWidget::MyGlWidget(QWidget *parent) :
    QGLWidget(parent)
{
    QAction *quit = new QAction(tr("Quit"), this);
    quit->setShortcut(Qt::Key_Q);
    connect(quit, SIGNAL(triggered()), SLOT(close()));
}

MyGlWidget::~MyGlWidget()
{
}

void MyGlWidget::initializeGL()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0, 0, 0, 0);
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(100,500);
    glVertex2f(500,100);
    glEnd();
}

void MyGlWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyGlWidget::paintEvent(QPaintEvent *event)
{
    QGLWidget::paintEvent(event);
}

void MyGlWidget::mousePressEvent(QMouseEvent *event)
{
    QGLWidget::mousePressEvent(event);
}

void MyGlWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGLWidget::mouseDoubleClickEvent(event);
}

void MyGlWidget::mouseMoveEvent(QMouseEvent *event)
{
    QGLWidget::mouseMoveEvent(event);
}

void MyGlWidget::wheelEvent(QWheelEvent *event)
{
    QGLWidget::wheelEvent(event);
}

void MyGlWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}

void MyGlWidget::keyReleaseEvent(QKeyEvent *event)
{
    QGLWidget::keyReleaseEvent(event);
}
