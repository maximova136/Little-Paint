#include "palette.h"

Palette::Palette(QToolBar *toolBar) : QToolBar(tr("Colors"))
{
    col1 = Qt::black;
    col2 = Qt::white;
    mToolBar = toolBar;
    setMovable(false);
    initializeItems();
    firstColActive = true;

}

void Palette::initializeItems()
{
    addSeparator();
    PaletteButton *mColorButton;

    butCol1 = new PaletteButton(Qt::black);
    butCol1->setCheckable(true);
    butCol1->setChecked(true);
    connect(butCol1,SIGNAL(colorPicked(QColor)),this, SLOT(on_butCol1_clicked(QColor)));
    addWidget(butCol1);

    butCol2 = new PaletteButton(Qt::white);
    butCol2->setCheckable(true);
    butCol2->setChecked(false);
    connect(butCol2,SIGNAL(colorPicked(QColor)),this, SLOT(on_butCol2_clicked(QColor)));
    addWidget(butCol2);

    addSeparator();
    addSeparator();


    mColorButton = new PaletteButton(Qt::red);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkRed);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::green);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkGreen);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::blue);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkBlue);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::cyan);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkCyan);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::magenta);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkMagenta);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::yellow);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::darkYellow);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::gray);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::white);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    mColorButton = new PaletteButton(Qt::black);
    connect(mColorButton, SIGNAL(colorPicked(QColor)),this,SLOT(on_colors_clicked(QColor)));
    addWidget(mColorButton);

    addSeparator();

    choose = new QToolButton();
    choose->setText("..");
    connect(choose,SIGNAL(clicked()),this, SLOT(on_choose_clicked()));

    addWidget(choose);
    addSeparator();
}


void Palette::on_choose_clicked() {
    if (firstColActive) {
        QColor color = QColorDialog::getColor(col1);
        if (color.isValid()) {
            butCol1->changeColor(color);
            col1 = color;
            emit colorsChanged(col1,col2);
        }
    }
    else {
        QColor color = QColorDialog::getColor(col2);
        if (color.isValid()) {
            butCol2->changeColor(color);
            col2 = color;
            emit colorsChanged(col1,col2);
        }
    }
}

void Palette::on_butCol1_clicked(QColor) {
    qDebug()<<"but1";
    if (!firstColActive) {
        butCol1->setChecked(true);
        butCol2->setChecked(false);
        firstColActive = true;
        emit firstColorIsActive(true);
    }
}

void Palette::on_butCol2_clicked(QColor) {
    qDebug()<<"but2";
    if (firstColActive) {
        butCol2->setChecked(true);
        butCol1->setChecked(false);
        firstColActive = false;
        emit firstColorIsActive(false);
    }
}

void Palette::on_colors_clicked(QColor color) {
    //qDebug()<< sender();
    if (firstColActive) {
        butCol1->changeColor(color);
        col1 = color;
    } else {
        butCol2->changeColor(color);
        col2 = color;
    }
    emit colorsChanged(col1,col2);
}

bool Palette::isFirstColActive()
{
    return firstColActive;
}


QColor Palette::getCol1()
{
    return col1;
}

QColor Palette::getCol2()
{
    return col2;
}

