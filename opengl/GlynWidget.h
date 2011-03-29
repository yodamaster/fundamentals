//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_OPENGL_GLYNWIDGET_INC__
# define __GLYNOS_OPENGL_GLYNWIDGET_INC__


#include <QtOpenGL/QGLWidget>


class GlynWidget : public QGLWidget
{
    Q_OBJECT

public:

    GlynWidget(QWidget *parent = 0);

    virtual ~GlynWidget();

private:

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int width, int height);

    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent(QKeyEvent *event);

    virtual void keyReleaseEvent(QKeyEvent *event);

private slots:

    void animate(qreal);
    void animFinished();
    void draw();

private:

    struct Impl;
    Impl *m_pimpl;

};


#endif // __GLYNOS_OPENGL_GLYNWIDGET_INC__
