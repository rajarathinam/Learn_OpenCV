#ifndef VIDEOLABEL_H
#define VIDEOLABEL_H

#include <QLabel>
#include <QEvent>
#include <QHoverEvent>
#include <QDebug>
#include <QVBoxLayout>

class VideoLabel : public QWidget
{
  Q_OBJECT
public:
  VideoLabel(QWidget *parent=0);
  void setPixmap(QPixmap pix);
  void setMovie(QMovie*);
protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:
      void mousedoubleclicked();
protected:
    void resizeEvent(QResizeEvent *);

private slots:

private slots:
  void showContextMenu(const QPoint point);
  void resizeImage();

private:
  QLabel *label;
  QGridLayout *mainLayout;


};

#endif // VIDEOLABEL_H
