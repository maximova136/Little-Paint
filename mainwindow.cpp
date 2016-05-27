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
    scene = new PaintArea();

    QPushButton *ellipseButton = new QPushButton();
    ellipseButton->setObjectName(tr("Ellipse"));
    ellipseButton->setIcon(QIcon("media/ellipse.png"));
    ellipseButton->setIconSize(QSize(25,25));
    ellipseButton->setToolTip(ellipseButton->objectName());

    QPushButton *rectangleButton = new QPushButton();
    rectangleButton->setObjectName(tr("Rectangle"));
    rectangleButton->setIcon(QIcon("media/rectangle.png"));
    rectangleButton->setIconSize(QSize(25,25));
    rectangleButton->setToolTip(ellipseButton->objectName());

    QPushButton *triangleButton = new QPushButton();
    triangleButton->setObjectName(tr("Triangle"));
    triangleButton->setIcon(QIcon("media/triangle.png"));
    triangleButton->setIconSize(QSize(24,18));
    triangleButton->setToolTip(ellipseButton->objectName());

    QPushButton *lineButton = new QPushButton();
    lineButton->setObjectName(tr("Line"));
    lineButton->setIcon(QIcon("media/line.png"));
    lineButton->setIconSize(QSize(25,25));
    lineButton->setToolTip(ellipseButton->objectName());

    QPushButton *curveButton = new QPushButton();
    curveButton->setObjectName(tr("Curve"));
    curveButton->setIcon(QIcon("media/curve.png"));
    curveButton->setIconSize(QSize(15,15));
    curveButton->setToolTip(ellipseButton->objectName());

    QPushButton *brushButton = new QPushButton();
    brushButton->setObjectName(tr("Brush"));
    brushButton->setIcon(QIcon("media/pencil.png"));
    brushButton->setIconSize(QSize(23,23));
    brushButton->setToolTip(ellipseButton->objectName());

    QPushButton *textButton = new QPushButton();
    textButton->setObjectName(tr("Text"));
    textButton->setIcon(QIcon("media/text.png"));
    textButton->setIconSize(QSize(25,25));
    textButton->setToolTip(ellipseButton->objectName());

    QPushButton *fillButton = new QPushButton();
    fillButton->setObjectName(tr("Fill"));
    fillButton->setIcon(QIcon("media/fill.png"));
    fillButton->setIconSize(QSize(25,25));
    fillButton->setToolTip(ellipseButton->objectName());

    QPushButton *eraserButton = new QPushButton();
    eraserButton->setObjectName(tr("Eraser"));
    eraserButton->setIcon(QIcon("media/eraser.png"));
    eraserButton->setIconSize(QSize(25,25));
    eraserButton->setToolTip(ellipseButton->objectName());

    QPushButton *pipetteButton = new QPushButton();
    pipetteButton->setObjectName("Pipette");
    pipetteButton->setIcon(QIcon("media/pipette.png"));
    pipetteButton->setIconSize(QSize(20,20));
    pipetteButton->setToolTip(ellipseButton->objectName());

    allButtons.clear();
    allButtons.push_back(brushButton);
    allButtons.push_back(ellipseButton);
    allButtons.push_back(rectangleButton);
    allButtons.push_back(triangleButton);
    allButtons.push_back(fillButton);
    allButtons.push_back(pipetteButton);
    allButtons.push_back(lineButton);
    allButtons.push_back(curveButton);
    allButtons.push_back(textButton);
    allButtons.push_back(eraserButton);

    slider = new QSlider(Qt::Vertical);
    label = new QLabel("1");
    label->setMaximumWidth(15);
    slider->setRange(1,8);
    slider->setValue(1);
    slider->setTickInterval(1);
    slider->setMaximumWidth(25);
    slider->setMinimumHeight(50);
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

    penPattern->setToolTip("Type of Drawable Line");
    penPattern->setFixedWidth(100);

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

    //brushPattern->setMinimumWidth(40);
//    brushPattern->setMaximumWidth(40);
    brushPattern->setFixedWidth(100);
    brushPattern->setToolTip("Pattern of Filling");

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
    connect(scene, SIGNAL(pipetteColor(QColor)), palette, SLOT(on_colors_clicked(QColor)));

    for (unsigned int i = 0; i < allButtons.size(); i++) {
        connect(allButtons[i],SIGNAL(clicked()),this, SLOT(on_allButtons_clicked()));
        allButtons[i]->setCheckable(true);
    }

    allButtons[0]->setChecked(true);
    QGraphicsDropShadowEffect* pShadow = new QGraphicsDropShadowEffect;
    pShadow->setXOffset(2);
    pShadow->setYOffset(2);
    allButtons[0]->setGraphicsEffect(pShadow);


    hbox->addWidget(scene);
    ui->centralWidget->setLayout(hbox);

    connect(palette, SIGNAL(colorsChanged(QColor,QColor)),scene, SLOT(changeColors(QColor,QColor)));
    connect(palette, SIGNAL(firstColorIsActive(bool)),scene, SLOT(firstColorActive(bool)));

    connect(this,SIGNAL(ShiftOn(bool)),scene,SLOT(shiftActive(bool)));

    connect(ui->actionClear, SIGNAL(triggered()), scene, SLOT(clearImage()));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_allButtons_clicked() {
    QPushButton *currentButton = (QPushButton*) sender();
    qDebug()<<currentButton->objectName();

    for (unsigned int i = 0; i < allButtons.size(); i++) {
        allButtons[i]->setChecked(false);
        allButtons[i]->setGraphicsEffect(0);
    }
    currentButton->setChecked(true);
    QGraphicsDropShadowEffect* pShadow = new QGraphicsDropShadowEffect;
    pShadow->setXOffset(2);
    pShadow->setYOffset(2);
    currentButton->setGraphicsEffect(pShadow);
    scene->setSettings(currentButton->objectName(),palette->getCol1(),slider->value(),
                       palette->getCol2(),scene->getPenStyle(),scene->getBrushStyle());
}


QVBoxLayout *MainWindow::createToolsGroup() {
    QVBoxLayout *vbox = new QVBoxLayout;

    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox1 = new QVBoxLayout;
    QVBoxLayout *vbox2 = new QVBoxLayout;

    for (unsigned int i = 0; i < allButtons.size()/2;i++) {
        allButtons[i]->setFixedSize(30,30);
        vbox1->addWidget(allButtons[i]);
        vbox1->addStretch(3);
    }
    hbox->addLayout(vbox1);
    for (unsigned int i = allButtons.size()/2; i < allButtons.size();i++) {
        allButtons[i]->setFixedSize(30,30);
        vbox2->addWidget(allButtons[i]);
        vbox2->addStretch(3);
    }
    hbox->addLayout(vbox2);
    hbox->setMargin(2);
    hbox->setSpacing(-30);
    hbox->setStretch(0,-1);
    vbox->addLayout(hbox);
    vbox->addSpacing(15);
    return vbox;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Shift) {
            emit ShiftOn(true);
        }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_Shift) {
        emit ShiftOn(false);
    }
}
