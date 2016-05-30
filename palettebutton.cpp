#include "palettebutton.h"

#include <QMouseEvent>
#include <QDebug>

PaletteButton::PaletteButton(const QColor &color)
{
    mColor = color;
    setMinimumSize(QSize(30, 30));
    setMaximumSize(QSize(30, 30));
    QPixmap pixmap(20, 20);
    pixmap.fill(color);
    setIcon(pixmap);
    setStatusTip(color.name());
}

void PaletteButton::mousePressEvent(QMouseEvent *event)
{
    /*if(event->button() == Qt::LeftButton)
        DataSingleton::Instance()->setPrimaryColor(mColor);
    else if(event->button() == Qt::RightButton)
        DataSingleton::Instance()->setSecondaryColor(mColor);
*/
    //emit colorPicked();
    //emit colortryed(mColor);
    emit colorPicked(mColor);
}

void PaletteButton::changeColor(QColor col)
{
    mColor = col;
    QPixmap pixmap(20, 20);
    pixmap.fill(col);
    setIcon(pixmap);
    setStatusTip(col.name());
}


QColor PaletteButton::getColor()
{
    return mColor;
}
