//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __CUSTOMSLIDER_INC__
# define __CUSTOMSLIDER_INC__


# include <QtGui/QSlider>


class CustomSlider : public QSlider {

    Q_OBJECT

    Q_PROPERTY(int firstFrame READ firstFrame WRITE setFirstFrame);
    Q_PROPERTY(int lastFrame READ lastFrame WRITE setLastFrame);

public:
    explicit CustomSlider(Qt::Orientation orientation, QWidget *parent = 0);
    explicit CustomSlider(QWidget *parent = 0);
    virtual ~CustomSlider();

    int firstFrame() const;
    int lastFrame() const;

public slots:
    void setFirstFrame(int firstFrame);
    void setLastFrame(int lastFrame);

private:

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:

    int m_firstFrame, m_lastFrame;
    bool m_drag;

};


#endif // __CUSTOMSLIDER_INC__
