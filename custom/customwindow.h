#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QtGui/QWidget>
#include <QGridLayout>
#include <QSizeGrip>
#include <QPixmap>

#include "windowtitlebar.h"

class CustomWindow : public QWidget
{
Q_OBJECT

public:
  CustomWindow(QWidget *parent = 0);
  ~CustomWindow();
  
  void setWindowTitle(const QString &title);
  
signals:
  void WindowTitleChanged();
  
protected:
  void showEvent  (QShowEvent   *event);
  void paintEvent (QPaintEvent  *event);
  void resizeEvent(QResizeEvent *event);

private:
  QGridLayout     m_MainLayout;
  WindowTitleBar  m_TitleBar  ;
  QSizeGrip       m_SizeGrip  ;
  QPixmap        *m_Cache     ;
  
  void CenterOnScreen();
};

#endif
