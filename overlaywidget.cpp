#include "overlaywidget.h"

OverlayWidget::OverlayWidget(QWidget *parent) : QWidget(parent)
{
    addLogoCheckBox = new QCheckBox("Add Logo");
    eraseLogoCheckBox = new QCheckBox ("Erase Mask");
    textLabel = new QLabel("Text:");
    textLineEdit = new QLineEdit();
    positionXLabel = new QLabel("X:");
    positionYLabel = new QLabel("Y:");
    positionXSpinBox = new QDoubleSpinBox();
    positionXSpinBox->setDecimals(0);
    positionYSpinBox = new QDoubleSpinBox();
    positionYSpinBox->setDecimals(0);

    addTextLayout = new QGridLayout();
    addTextLayout->addWidget(textLabel,0,0);
    addTextLayout->addWidget(textLineEdit,0,1);
    addTextLayout->addWidget(positionXLabel,1,0,Qt::AlignRight);
    addTextLayout->addWidget(positionYLabel,2,0,Qt::AlignRight);
    addTextLayout->addWidget(positionXSpinBox,1,1);
    addTextLayout->addWidget(positionYSpinBox,2,1);

    addTextGroupBox = new QGroupBox();
    addTextGroupBox->setCheckable(true);
    addTextGroupBox->setTitle("Add Text");
    addTextGroupBox->setChecked(false);
    addTextGroupBox->setLayout(addTextLayout);
    mainLayout = new QGridLayout;
    mainLayout->addWidget(addLogoCheckBox,0,0);
    mainLayout->addWidget(eraseLogoCheckBox,0,1);
    mainLayout->addWidget(addTextGroupBox,0,2);
    setLayout(mainLayout);
}

bool OverlayWidget::isAddTextSelected()
{
    return addTextGroupBox->isChecked();
}

const char *OverlayWidget::getAddText()
{
    return textLineEdit->text().toStdString().c_str();
}

