//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


# include "CustomSlider.h"


CustomSlider::CustomSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent), m_firstFrame(0), m_lastFrame(0), m_drag(false)
{
}


CustomSlider::CustomSlider(QWidget *parent)
    : QSlider(parent), m_firstFrame(0), m_lastFrame(0), m_drag(false)
{
}

CustomSlider::~CustomSlider()
{
}

int CustomSlider::firstFrame() const
{
    return m_firstFrame;
}

void CustomSlider::setFirstFrame(int firstFrame)
{
    m_firstFrame = firstFrame;
}

int CustomSlider::lastFrame() const
{
    return m_lastFrame;
}

void CustomSlider::setLastFrame(int lastFrame)
{
    m_lastFrame = lastFrame;
}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    m_drag = true;
    QSlider::mousePressEvent(event);
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (m_drag)
    {

    }
    QSlider::mouseMoveEvent(event);
}

void CustomSlider::mouseReleaseEvent(QMouseEvent *event)
{
    m_drag = false;
    QSlider::mouseReleaseEvent(event);
}
