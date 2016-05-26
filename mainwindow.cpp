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
    slider->setMaximumWidth(25);
    slider->setMinimumHeight(30);
    slider->setTickPosition(QSlider::TicksLeft);

    connect(slider, SIGNAL(valueChanged(int)),label,SLOT(setNum(int)));
    connect(slider, SIGNAL(valueChanged(int)),scene, SLOT(changeWidth(int)));

    penPattern = new QComboBox();
    QPixmap pix (50,50);
    pix.fill(Qt::white);
    QPainter painter(&pix);
    painter.setPen(QPen(Qt::black,4,Qt::SolidLine));
    painter.drawLine(0,pix.width()/2,pix.width()-1,pix.width()/2);
    penPattern->addItem(QIcon(pix),QString("Solid Line"));
    painter.end();


    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setPen(QPen(Qt::black,4,Qt::DashLine));
    painter.drawLine(0,pix.width()/2,pix.width()-1,pix.width()/2);
    penPattern->addItem(QIcon(pix),QString("Dash Line"));
    painter.end();


    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setPen(QPen(Qt::black,4,Qt::DotLine));
    painter.drawLine(0,pix.width()/2,pix.width()-1,pix.width()/2);
    penPattern->addItem(QIcon(pix),QString("Dot Line"));
    painter.end();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setPen(QPen(Qt::black,4,Qt::DashDotLine));
    painter.drawLine(0,pix.width()/2,pix.width()-1,pix.width()/2);
    penPattern->addItem(QIcon(pix),QString("Dash Dot Line"));
    painter.end();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setPen(QPen(Qt::black,4,Qt::DashDotDotLine));
    painter.drawLine(0,pix.width()/2,pix.width()-1,pix.width()/2);
    penPattern->addItem(QIcon(pix),QString("Dash Dot Dot Line"));
    painter.end();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setPen(QPen(Qt::black,4,Qt::NoPen));
    painter.drawLine(0,pix.width()/2,pix.width()-1,pix.width()/2);
    penPattern->addItem(QIcon(pix),QString("No Line"));
    painter.end();

    penPattern->setMaximumWidth(40);
    //penPattern->setFixedWidth(40);

    connect(penPattern,SIGNAL(activated(QString)),scene,SLOT(changePenStyle(QString)));
//    penPattern->setDisabled(true);
//    penPattern->blockSignals(true);

    brushPattern = new QComboBox();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("Solid"));
    painter.end();

    pix.fill(Qt::white);
    brushPattern->addItem(QIcon(pix),QString("No Brush"));

    painter.begin(&pix);
    painter.setBrush(Qt::HorPattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("Hor"));
    painter.end();



    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setBrush(Qt::VerPattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("Ver"));
    painter.end();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setBrush(Qt::CrossPattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("Cross"));
    painter.end();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setBrush(Qt::BDiagPattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("BDiag"));
    painter.end();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setBrush(Qt::FDiagPattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("FDiag"));
    painter.end();

    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setBrush(Qt::DiagCrossPattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("DiagCross"));
    painter.end();


    pix.fill(Qt::white);
    painter.begin(&pix);
    painter.setBrush(Qt::Dense3Pattern);
    painter.drawRect(0,0,pix.width(),pix.width());
    brushPattern->addItem(QIcon(pix),QString("Dense"));
    painter.end();

//    pix.fill(Qt::white);
//    painter.begin(&pix);
//    QLinearGradient linGradient(0,0,pix.width(),pix.width());
//    linGradient.setColorAt(0,Qt::white);
//    linGradient.setColorAt(1,Qt::black);
//    painter.setBrush(linGradient);
//    painter.drawRect(0,0,pix.width(),pix.width());
//    brushPattern->addItem(QIcon(pix),QString("Gradient"));
//    painter.end();

    brushPattern->setMinimumWidth(40);
    brushPattern->setMaximumWidth(40);
    brushPattern->setFixedWidth(40);

    connect(brushPattern,SIGNAL(activated(QString)),scene,SLOT(changeBrushStyle(QString)));



    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(createToolsGroup());
    QHBoxLayout *hboxSlider = new QHBoxLayout;
    hboxSlider->addWidget(slider);
    hboxSlider->addWidget(label);
    vbox->addLayout(hboxSlider);
    vbox->addWidget(penPattern);
    vbox->addWidget(brushPattern);
    vbox->addSpacing(30);
    //vbox->addStretch(30);
    hbox->addLayout(vbox);


    palette = new Palette(mToolbar);
    addToolBar(Qt::BottomToolBarArea, palette);


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


    hbox->addWidget(scene);
    //view = new QScrollArea();
    //view->setWidget(scene->imageLabel);
    //hbox->addWidget(view);
    ui->centralWidget->setLayout(hbox);


    connect(palette, SIGNAL(colorsChanged(QColor,QColor)),scene, SLOT(changeColors(QColor,QColor)));
    connect(palette, SIGNAL(firstColorIsActive(bool)),scene, SLOT(firstColorActive(bool)));

    connect(this,SIGNAL(ShiftOn(bool)),scene,SLOT(shiftActive(bool)));

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
        allButtons[i]->setMinimumHeight(20);
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
        if (event->key() == Qt::Key_Shift)
        {
            emit ShiftOn(true);
        }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Shift)
    {
        emit ShiftOn(false);
    }
}
