//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "GlynWidget.h"
#include <QtGui/QImage>
#include <QtGui/QMouseEvent>
#include <QtCore/QTimeLine>
#include <QtSvg/QSvgRenderer>
#include <QtOpenGL/QGLFramebufferObject>
#include <cmath>


struct GlynWidget::Impl
{
    QPoint anchor;
    float scale;
    float rot_x, rot_y, rot_z;
    GLuint tile_list;
    GLfloat *wave;

    QImage logo;
    QTimeLine *anim;
    QSvgRenderer *svg_renderer;
    QGLFramebufferObject *render_fbo;
    QGLFramebufferObject *texture_fbo;

    void saveGLState();
    void restoreGLState();
};

void GlynWidget::Impl::saveGLState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void GlynWidget::Impl::restoreGLState()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}

GlynWidget::GlynWidget(QWidget *parent) :
    QGLWidget(parent), m_pimpl(new Impl)
{
    setWindowTitle(tr("OpenGL framebuffer objects"));
    makeCurrent();

    if (QGLFramebufferObject::hasOpenGLFramebufferBlit()) {
        QGLFramebufferObjectFormat format;
        format.setSamples(4);
        format.setAttachment(QGLFramebufferObject::CombinedDepthStencil);

        m_pimpl->render_fbo = new QGLFramebufferObject(512, 512, format);
        m_pimpl->texture_fbo = new QGLFramebufferObject(512, 512);
    } else {
        m_pimpl->render_fbo = new QGLFramebufferObject(1024, 1024);
        m_pimpl->texture_fbo = m_pimpl->render_fbo;
    }

    m_pimpl->rot_x = m_pimpl->rot_y = m_pimpl->rot_z = 0.0f;
    m_pimpl->scale = 0.1f;
    m_pimpl->anim = new QTimeLine(750, this);
    m_pimpl->anim->setUpdateInterval(20);
    connect(m_pimpl->anim, SIGNAL(valueChanged(qreal)), SLOT(animate(qreal)));
    connect(m_pimpl->anim, SIGNAL(finished()), SLOT(animFinished()));

    m_pimpl->svg_renderer = new QSvgRenderer(QLatin1String(":/res/bubbles.svg"), this);
    connect(m_pimpl->svg_renderer, SIGNAL(repaintNeeded()), this, SLOT(draw()));

    m_pimpl->logo = QImage(":/res/designer.png");
    m_pimpl->logo = m_pimpl->logo.convertToFormat(QImage::Format_ARGB32);

    m_pimpl->tile_list = glGenLists(1);
    glNewList(m_pimpl->tile_list, GL_COMPILE);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    }
    glEnd();
    glEndList();

    m_pimpl->wave = new GLfloat[m_pimpl->logo.width()*m_pimpl->logo.height()];
    memset(m_pimpl->wave, 0, m_pimpl->logo.width()*m_pimpl->logo.height());
    startTimer(30); // wave timer
}

GlynWidget::~GlynWidget()
{
    delete[] m_pimpl->wave;
    glDeleteLists(m_pimpl->tile_list, 1);
    delete m_pimpl->texture_fbo;
    if (m_pimpl->render_fbo != m_pimpl->texture_fbo)
        delete m_pimpl->render_fbo;
    delete m_pimpl;
}

void GlynWidget::initializeGL()
{
    QGLWidget::initializeGL();
}

void GlynWidget::paintGL()
{
    QGLWidget::paintGL();
}

void GlynWidget::resizeGL(int width, int height)
{
    QGLWidget::resizeGL(width, height);
}

void GlynWidget::paintEvent(QPaintEvent *event)
{
    draw();
    // QGLWidget::paintEvent(event);
}

void GlynWidget::mousePressEvent(QMouseEvent *event)
{
    m_pimpl->anchor = event->pos();
    // QGLWidget::mousePressEvent(event);
}

void GlynWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_pimpl->anim->start();
    // QGLWidget::mouseDoubleClickEvent(event);
}

void GlynWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint diff = event->pos() - m_pimpl->anchor;
    if (event->buttons() & Qt::LeftButton) {
        m_pimpl->rot_x += diff.y()/5.0f;
        m_pimpl->rot_y += diff.x()/5.0f;
    } else if (event->buttons() & Qt::RightButton) {
        m_pimpl->rot_z += diff.x()/5.0f;
    }

    m_pimpl->anchor = event->pos();
    draw();
    // QGLWidget::mouseMoveEvent(event);
}

void GlynWidget::wheelEvent(QWheelEvent *event)
{
    event->delta() > 0 ? m_pimpl->scale += m_pimpl->scale*0.1f : m_pimpl->scale -= m_pimpl->scale*0.1f;
    draw();
    // QGLWidget::wheelEvent(event);
}

void GlynWidget::keyPressEvent(QKeyEvent *event)
{
    QGLWidget::keyPressEvent(event);
}

void GlynWidget::keyReleaseEvent(QKeyEvent *event)
{
    QGLWidget::keyReleaseEvent(event);
}

void GlynWidget::animate(qreal val)
{
    m_pimpl->rot_y = val * 180;
    draw();
}

void GlynWidget::animFinished()
{
    if (m_pimpl->anim->direction() == QTimeLine::Forward)
        m_pimpl->anim->setDirection(QTimeLine::Backward);
    else
        m_pimpl->anim->setDirection(QTimeLine::Forward);
}

void GlynWidget::draw()
{
    QPainter p(this); // used for text overlay

    // save the GL state set for QPainter
    m_pimpl->saveGLState();

    // render the 'bubbles.svg' file into our framebuffer object
    QPainter fbo_painter(m_pimpl->render_fbo);
    m_pimpl->svg_renderer->render(&fbo_painter);
    fbo_painter.end();

    if (m_pimpl->render_fbo != m_pimpl->texture_fbo) {
        QRect rect(0, 0, m_pimpl->render_fbo->width(), m_pimpl->render_fbo->height());
        QGLFramebufferObject::blitFramebuffer(m_pimpl->texture_fbo, rect,
                                              m_pimpl->render_fbo, rect);
    }

    // draw into the GL widget
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 10, 100);
    glTranslatef(0.0f, 0.0f, -15.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, width(), height());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, m_pimpl->texture_fbo->texture());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);

    // draw background
    glPushMatrix();
    glScalef(1.7f, 1.7f, 1.7f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glCallList(m_pimpl->tile_list);
    glPopMatrix();

    const int w = m_pimpl->logo.width();
    const int h = m_pimpl->logo.height();

    glRotatef(m_pimpl->rot_x, 1.0f, 0.0f, 0.0f);
    glRotatef(m_pimpl->rot_y, 0.0f, 1.0f, 0.0f);
    glRotatef(m_pimpl->rot_z, 0.0f, 0.0f, 1.0f);
    glScalef(m_pimpl->scale/w, m_pimpl->scale/w, m_pimpl->scale/w);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    // draw the Qt icon
    glTranslatef(-w+1, -h+1, 0.0f);
    for (int y=h-1; y>=0; --y) {
        uint *p = (uint*) m_pimpl->logo.scanLine(y);
        uint *end = p + w;
        int  x = 0;
        while (p < end) {
            glColor4ub(qRed(*p), qGreen(*p), qBlue(*p), uchar(qAlpha(*p)*.9));
            glTranslatef(0.0f, 0.0f, m_pimpl->wave[y*w+x]);
            if (qAlpha(*p) > 128)
                glCallList(m_pimpl->tile_list);
            glTranslatef(0.0f, 0.0f, -m_pimpl->wave[y*w+x]);
            glTranslatef(2.0f, 0.0f, 0.0f);
            ++x;
            ++p;
        }
        glTranslatef(-w*2.0f, 2.0f, 0.0f);
    }

    // restore the GL state that QPainter expects
    m_pimpl->restoreGLState();

    // draw the overlayed text using QPainter
    p.setPen(QColor(197, 197, 197, 157));
    p.setBrush(QColor(197, 197, 197, 127));
    p.drawRect(QRect(0, 0, width(), 50));
    p.setPen(Qt::black);
    p.setBrush(Qt::NoBrush);
    const QString str1(tr("A simple OpenGL framebuffer object example."));
    const QString str2(tr("Use the mouse wheel to zoom, press buttons and move mouse to rotate, double-click to flip."));
    QFontMetrics fm(p.font());
    p.drawText(width()/2 - fm.width(str1)/2, 20, str1);
    p.drawText(width()/2 - fm.width(str2)/2, 20 + fm.lineSpacing(), str2);
}
