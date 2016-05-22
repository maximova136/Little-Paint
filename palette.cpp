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
    paletteButton *mColorButton;

    butCol1 = new paletteButton(Qt::black);
    butCol1->setCheckable(true);
    butCol1->setChecked(true);
    connect(butCol1,SIGNAL(colorPicked()),this, SLOT(on_butCol1_clicked()));
    addWidget(butCol1);

    butCol2 = new paletteButton(Qt::white);
    butCol2->setCheckable(true);
    butCol2->setChecked(false);
    connect(butCol2,SIGNAL(colorPicked()),this, SLOT(on_butCol2_clicked()));
    addWidget(butCol2);

    addSeparator();
    addSeparator();

    mColorButton = new paletteButton(Qt::red);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::darkRed);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::green);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::darkGreen);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::blue);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::darkBlue);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::cyan);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::darkCyan);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::magenta);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::darkMagenta);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::yellow);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::darkYellow);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);

    mColorButton = new paletteButton(Qt::gray);
    connect(mColorButton,SIGNAL(colorPicked()),this, SLOT(on_colors_clicked()));
    addWidget(mColorButton);
    addSeparator();

    choose = new QToolButton();
    choose->setText("..");
    connect(choose,SIGNAL(clicked()),this, SLOT(on_choose_clicked()));

    addWidget(choose);
    addSeparator();
}


void Palette::on_choose_clicked()
{
    if (firstColActive)
    {
        QColor color = QColorDialog::getColor(col1);
        if (color.isValid())
        {
            butCol1->changeColor(color);
            col1 = color;
        }
    }
    else
    {
        QColor color = QColorDialog::getColor(col2);
        if (color.isValid())
        {
            butCol2->changeColor(color);
            col2 = color;
        }

    }
}


void Palette::on_butCol1_clicked()
{
    qDebug()<<"but1";
    if (!firstColActive)
    {
        butCol1->setChecked(true);
        butCol2->setChecked(false);
        firstColActive = true;
    }
}

void Palette::on_butCol2_clicked()
{
    qDebug()<<"but2";
    if (firstColActive)
    {
        butCol2->setChecked(true);
        butCol1->setChecked(false);
        firstColActive = false;
    }
}

void Palette::on_colors_clicked()
{

    qDebug()<< sender();

    if (firstColActive)
    {
        //butCol1->changeColor();
        //col1 = color;
    }
    else
    {
        //butCol2->changeColor(color);
        //col2 = color;
    }
}
