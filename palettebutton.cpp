#include "palettebutton.h"

#include <QMouseEvent>
#include <QDebug>

paletteButton::paletteButton(const QColor &color)
{
    mColor = color;
    setMinimumSize(QSize(30, 30));
    setMaximumSize(QSize(30, 30));
    QPixmap pixmap(20, 20);
    pixmap.fill(color);
    setIcon(pixmap);
    setStatusTip(color.name());


}

void paletteButton::mousePressEvent(QMouseEvent *event)
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

void paletteButton::changeColor(QColor col)
{
    mColor = col;
    QPixmap pixmap(20, 20);
    pixmap.fill(col);
    setIcon(pixmap);
    setStatusTip(col.name());
}


QColor paletteButton::getColor()
{
    return mColor;
}
