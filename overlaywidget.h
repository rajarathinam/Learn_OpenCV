#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QDoubleSpinBox>



class OverlayWidget : public QWidget
{
  Q_OBJECT
public:
  explicit OverlayWidget(QWidget *parent = 0);
    bool isAddTextSelected();
    const char* getAddText();


signals:

public slots:
  private:
  QCheckBox *addLogoCheckBox;
  QCheckBox *eraseLogoCheckBox;
  QCheckBox *addTextCheckBox;

  QLabel *textLabel;
  QLabel *positionXLabel;
  QLabel *positionYLabel;

  QDoubleSpinBox *positionXSpinBox;
  QDoubleSpinBox *positionYSpinBox;

  QLineEdit *textLineEdit;

  QGroupBox  *addTextGroupBox;
  QGridLayout *addTextLayout;
  QGridLayout *mainLayout;
};

#endif // OVERLAYWIDGET_H
