#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <vector>
#include <iostream>
#include <QDebug>
#include <QtCore>
#include <QScrollArea>
//#include "paintarea.h"
//#include "palette.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ///scene = new paintScene();
    ///scene->setSceneRect(0,0, ui->graphicsView->width()-40, ui->graphicsView->height()-30);
    ///ui->graphicsView->setScene(scene);

    scene = new paintArea();

    QPushButton *ellipseButton = new QPushButton(tr("&Ellipse"));
    ellipseButton->setObjectName(tr("Ellipse"));

    QPushButton *rectangleButton = new QPushButton(tr("&Rectangle"));
    rectangleButton->setObjectName(tr("Rectangle"));
    QPushButton *triangleButton = new QPushButton(tr("&Triangle"));
    triangleButton->setObjectName(tr("Triangle"));
    QPushButton *lineButton = new QPushButton(tr("&Line"));
    lineButton->setObjectName(tr("Line"));
    QPushButton *curveButton = new QPushButton(tr("&Curve"));
    curveButton->setObjectName(tr("Curve"));
    //QPushButton *polygonButton = new QPushButton(tr("&Polygon"));
    //polygonButton->setObjectName(tr("Polygon"));

    QPushButton *brushButton = new QPushButton(tr("&Brush"));
    brushButton->setObjectName(tr("Brush"));
    QPushButton *textButton = new QPushButton(tr("&Text"));
    textButton->setObjectName(tr("Text"));
    QPushButton *fillButton = new QPushButton(tr("&Fill"));
    fillButton->setObjectName(tr("Fill"));

    allButtons.clear();
    allButtons.push_back(brushButton);
    allButtons.push_back(ellipseButton);
    allButtons.push_back(rectangleButton);
    allButtons.push_back(triangleButton);
    allButtons.push_back(lineButton);
    allButtons.push_back(curveButton);
    //allButtons.push_back(polygonButton);
    allButtons.push_back(fillButton);
    allButtons.push_back(textButton);

    slider = new QSlider(Qt::Vertical);
    label = new QLabel("1");
    label->setMaximumWidth(15);
    slider->setRange(1,8);
    slider->setValue(1);
    slider->setTickInterval(1);
    slider->setMaximumWidth(30);
    slider->setTickPosition(QSlider::TicksLeft);

    connect(slider, SIGNAL(valueChanged(int)),label,SLOT(setNum(int)));
    connect(slider, SIGNAL(valueChanged(int)),scene, SLOT(changeWidth(int)));
    //connect(slider,SIGNAL(valueChanged(int)),this,SLOT(penWidthChanged(int)));

    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(createToolsGroup());
    QHBoxLayout *hboxSlider = new QHBoxLayout;
    hboxSlider->addWidget(slider);
    hboxSlider->addWidget(label);
    vbox->addLayout(hboxSlider);
    vbox->addStretch(30);
    hbox->addLayout(vbox);
    //hbox->addLayout(createToolsGroup());
    ///hbox->addWidget(ui->graphicsView);


    /*QWidget* scrollWidget = new QWidget();
    QVBoxLayout* lay = new QVBoxLayout();
    lay->addWidget(scene);
//    hbox->addLayout(lay);
    scrollWidget->setLayout(lay);
    view = new QScrollArea();

    //scene->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //view->setWidget(scene);
    //view->setGeometry(QRect(110, 80, 120, 80));

    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    view->setWidget(scrollWidget);

    hbox->addWidget(scene);
    hbox->addWidget(view);
    view->show();
    view->resize(600,400);
*/
    //hbox->addLayout(view);
    palette = new Palette(mToolbar);
    addToolBar(Qt::BottomToolBarArea, palette);


    /*QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(ui->menuBar);
    vbox->addWidget(ui->mainToolBar);
    vbox->addLayout(hbox);*/

    for (unsigned int i = 0; i < allButtons.size(); i++)
    {
        connect(allButtons[i],SIGNAL(clicked()),this, SLOT(on_allButtons_clicked()));
        allButtons[i]->setCheckable(true);
    }

    allButtons[0]->setChecked(true);
    QGraphicsDropShadowEffect* pShadow = new QGraphicsDropShadowEffect;
    pShadow->setXOffset(2);
    pShadow->setYOffset(2);
    allButtons[0]->setGraphicsEffect(pShadow);


    //hbox->addWidget(scene->scrollArea);
    hbox->addWidget(scene);
    //view = new QScrollArea();
    //view->setWidget(scene->imageLabel);
    //hbox->addWidget(view);
    ui->centralWidget->setLayout(hbox);

    //scene->setSettings("Brush",palette->getCol1(),slider->value(),palette->getCol2(),scene->penStyle,scene->brushStyle);


    connect(palette, SIGNAL(colorsChanged(QColor,QColor)),scene, SLOT(changeColors(QColor,QColor)));
    connect(palette, SIGNAL(firstColorIsActive(bool)),scene, SLOT(firstColorActive(bool)));

    connect(ui->actionClear, SIGNAL(triggered()), scene, SLOT(clearImage()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_allButtons_clicked()
{
    QPushButton *currentButton = (QPushButton*) sender();
    qDebug()<<currentButton->objectName();

    for (unsigned int i = 0; i < allButtons.size(); i++)
    {
        allButtons[i]->setChecked(false);
        allButtons[i]->setGraphicsEffect(0);
    }
    currentButton->setChecked(true);
    QGraphicsDropShadowEffect* pShadow = new QGraphicsDropShadowEffect;
    pShadow->setXOffset(2);
    pShadow->setYOffset(2);
    currentButton->setGraphicsEffect(pShadow);
   // scene->setSettings(currentButton->objectName(),palette->getCol1(),Qt::DotLine,palette->getCol2(),Qt::BDiagPattern);
    scene->setSettings(currentButton->objectName(),palette->getCol1(),slider->value(),palette->getCol2(),scene->getPenStyle(),scene->getBrushStyle());

}


QVBoxLayout *MainWindow::createToolsGroup()
{
    QVBoxLayout *vbox = new QVBoxLayout;

    for (unsigned int i = 0; i < allButtons.size();i++)
    {
        allButtons[i]->setMaximumWidth(50);
        vbox->addWidget(allButtons[i]);
        vbox->addStretch(-1);
    }
    vbox->addSpacing(15);

    return vbox;
}


void MainWindow::penWidthChanged(int width)
{
    qDebug()<<width;
    //QPixmap myPix(QSize(10,10) );
    QPixmap myPix(10,10);
    QPainter painter(&myPix);

    //QPainter p(this);
    //p.setBrush(QPixmap("/media/data/shot0015.jpg"));
    //p.drawEllipse(rect());

    painter.setBrush(Qt::black);
    //painter.setPen(Qt::black);

    //painter.drawEllipse(5,5,width,width);
    painter.drawArc(QRect(0,0,5,5),0,360*16);



   // label = new QLabel(width, this);
    //label = new QLabel(QString(width),this);
    //label->setText(QString::);
    qDebug()<<label->text();
    //qDebug()<<myPix;
    label->setPixmap(myPix);
    //label->setPicture(myPix.toImage());

}
