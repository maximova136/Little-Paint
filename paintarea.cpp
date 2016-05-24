#include "paintarea.h"
#include <QtWidgets>
#include <QDebug>
paintArea::paintArea(QWidget *parent) : QWidget(parent)
{
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;

    setSettings("Brush",Qt::black,QPen(Qt::SolidLine),Qt::white,QBrush(Qt::SolidPattern));
    //newFigure = true;
    firstColActive = true;
//    penColor = Qt::black;
//    penStyle = QPen(Qt::SolidLine);

    //qDebug()<<"set settings"<<drawableObj;
}


void paintArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

/*void paintArea::changeColor()
{
    //setSettings(drawableObj,palette->getCol1(),Qt::DotLine,palette->getCol2(),Qt::BDiagPattern);
}*/

void paintArea::changeColors(QColor col1, QColor col2)
{
    setColors(col1,col2);
    //penColor = col1;
    //brushColor = col2;
    qDebug()<<"slot";
}
void paintArea::firstColorActive(bool first)
{
    if (first)
        firstColActive = true;
    else
        firstColActive = false;
}


void paintArea::setColors(QColor col1, QColor col2)
{
    penColor = col1;
    brushColor = col2;
}

void paintArea::mousePressEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush")
    {
        //if (event->button() == Qt::LeftButton)
        {
            lastPoint = event->pos();
            scribbling = true;
        }
    }
    else if (drawableObj == "Ellipse")
    {

    }
    else if (drawableObj == "Fill")
    {
        QPointF point = event->pos();
        QColor oldColor, newColor;

        if (firstColActive)
        {
            newColor = penColor;
        }
        else
        {
            newColor = brushColor;
        }
        qDebug()<<oldColor;
        qDebug()<<newColor;
    }

    qDebug()<<"mouse pressed";
}

void paintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush")
    {
        //if ((event->buttons() & Qt::LeftButton) && scribbling)
        if (scribbling)
            drawLineTo(event->pos());

    }
}

void paintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush")
    {
        //if (event->button() == Qt::LeftButton && scribbling) {
        if (scribbling)
        {
            drawLineTo(event->pos());
            scribbling = false;
        }
    }

}

void paintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
 }

void paintArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void paintArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    if (firstColActive)
    {
        painter.setPen(QPen(penColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        qDebug()<<"here";
    }
    else
    {
        painter.setPen(QPen(brushColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        qDebug()<<"there";

    }

    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void paintArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}


void paintArea::setSettings(QString _drawableObj, QColor _penColor, QPen _penStyle, QColor _brushColor, QBrush _brushStyle)
{
    drawableObj = _drawableObj;
    //penColor = _penColor;
    penStyle = _penStyle;
    //brushColor = _brushColor;
    setColors(_penColor,_brushColor);
    brushStyle = _brushStyle;
    qDebug()<<"set settings"<<drawableObj;
}
