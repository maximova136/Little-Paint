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
    void on_choose_clicked();
    void on_butCol1_clicked(QColor);
    void on_butCol2_clicked(QColor);
    void on_colors_clicked(QColor);

private:
    QColor col1, col2;
    bool firstColActive;
    std::vector <QPushButton*> colors;


    QToolButton* choose;
    paletteButton *butCol1, *butCol2;

    QToolBar *mToolBar;

    void initializeItems();

};

#endif // PALETTE_H
