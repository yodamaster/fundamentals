//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "MyGlWidget.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>


MyGlWidget::MyGlWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

MyGlWidget::~MyGlWidget()
{
    gluDeleteQuadric(m_scene);
}

void MyGlWidget::initializeGL()
{
	glDisable(GL_TEXTURE_2D);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  	glClearDepth(1.0);
  	glDepthFunc(GL_LESS);
  	glEnable(GL_DEPTH_TEST);
  	glShadeModel(GL_SMOOTH);

  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();

  	gluPerspective(45.0f,(GLfloat)640/(GLfloat)480,0.1f,100.0f);

  	glMatrixMode(GL_MODELVIEW);

    m_scene = gluNewQuadric();
    gluQuadricNormals(m_scene, GLU_SMOOTH);
}

void MyGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-5.f);
    gluSphere(m_scene,1.3f,32,32);
}

void MyGlWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
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
