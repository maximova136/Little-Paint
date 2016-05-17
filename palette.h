#ifndef PALETTE_H
#define PALETTE_H

#include <QWidget>
//#include <QtGui>
//#include <QtCore>
#include <QtWidgets>
#include "palettebutton.h"

class Palette : public QToolBar
{
    Q_OBJECT
public:
    Palette(QToolBar* toolBar);
    void setColors(QColor col1_, QColor col2_);
    QColor getCol1();
    QColor getCol2();

signals:

public slots:

private:
    QColor col1, col2;

    std::vector <QPushButton*> colors;

    paletteButton *mColorButton;
    QToolBar *mToolBar;

    void initializeItems();

};

#endif // PALETTE_H
