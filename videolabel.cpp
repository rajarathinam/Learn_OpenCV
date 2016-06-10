#include <QMenu>
#include<QMessageBox>
#include "videolabel.h"

VideoLabel::VideoLabel(QWidget *parent):QWidget(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);

    //Initializations
    label = new QLabel(this);
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(label);

    label->setText("Load Image or Video............");
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint)));

}

void VideoLabel::showContextMenu(const QPoint point)
{
    // for most widgets
    QPoint globalPos = this->mapToGlobal(point);
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction("Grayscale");
    // ...
    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        // something was chosen, do stuff
    }
    else
    {
        // nothing was chosen
    }
}

void VideoLabel::setPixmap(QPixmap pix)
{
    label->setPixmap(pix.scaled(size(),Qt::KeepAspectRatio));
    label->adjustSize();
}

void VideoLabel::setMovie(QMovie *movie)
{
  label->setMovie(movie);

}
void VideoLabel::hoverEnter(QHoverEvent *event)
{
    QPoint pos = event->pos();
    QString temp_pos("x = %1 : y = %2");
    temp_pos.arg(QString::number(pos.x()),QString::number(pos.y()));
    setToolTip(temp_pos);
}

void VideoLabel::hoverLeave(QHoverEvent *event)
{
    QPoint pos = event->pos();
    QString temp_pos("x = %1 : y = %2");
    temp_pos.arg(QString::number(pos.x()),QString::number(pos.y()));
    setToolTip(temp_pos);
}

void VideoLabel::hoverMove(QHoverEvent *event)
{
    QPoint pos = event->pos();
    QString temp_pos("x = %1 : y = %2");
    temp_pos.arg(QString::number(pos.x()),QString::number(pos.y()));
    setToolTip(temp_pos);
    //repaint();
}

bool VideoLabel::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return true;
}

void VideoLabel::mouseDoubleClickEvent(QMouseEvent *event)
{   Q_UNUSED(event);
    emit mousedoubleclicked();
}
void VideoLabel::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    resizeImage();
}
void VideoLabel::resizeImage() {

    if(!label->pixmap()->isNull())
    {
    QSize pixSize = label->pixmap()->size();
    pixSize.scale(size(), Qt::KeepAspectRatio);
    label->setFixedSize(pixSize);
    }
}

