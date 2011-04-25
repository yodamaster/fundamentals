//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __MYGLWIDGET_INC__
# define __MYGLWIDGET_INC__


#include <QtOpenGL/QGLWidget>


class MyGlWidget : public QGLWidget
{
    Q_OBJECT

public:

    MyGlWidget(QWidget *parent = 0);

    virtual ~MyGlWidget();

private:

    virtual void initializeGL();

    virtual void paintGL();

    virtual void resizeGL(int width, int height);

private:

    GLUquadricObj *m_scene;

};


#endif // __MYGLWIDGET_INC__
