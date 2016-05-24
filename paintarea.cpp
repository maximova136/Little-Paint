#include "paintarea.h"
#include <QtWidgets>
#include <QDebug>
paintArea::paintArea(QWidget *parent) : QWidget(parent)
{
    modified = false;
    scribbling = false;
    myPenWidth = 1;

    setSettings("Brush",Qt::black,QPen(Qt::SolidLine),Qt::white,QBrush(Qt::SolidPattern));

    firstColActive = true;
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

void paintArea::changeWidth(int width)
{
    setPen(width);
}

void paintArea::setPen( int wid)
{
    pen = QPen(QBrush(penColor),wid);
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
        lastPoint = event->pos();
        scribbling = true;
        if (event->button()!=0)
        {
            button = event->button();
        }
    }
    else if (drawableObj == "Ellipse")
    {

    }
    else if (drawableObj == "Fill")
    {
        QPointF point = event->pos();
        QColor oldColor, newColor;
        button = event->button();
        if (button == Qt::LeftButton)
        {
            newColor = penColor;
        }
        else if (button == Qt::RightButton)
        {
            newColor = brushColor;
        }
        qDebug()<<image.width();
        qDebug()<<image.height();
        qDebug()<<event->pos();
        //fillTool(event->pos(),newColor.rgb());
        fillToolWork(event->pos().x(),event->pos().y(), image.pixel(event->pos()),newColor.rgb());
        update();

    }
    qDebug()<<"mouse pressed";
}

void paintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush")
    {
        //if ((event->buttons() & Qt::LeftButton) && scribbling)
        if (event->button()==Qt::LeftButton)
            button = Qt::LeftButton;
        else if (event->button() == Qt::RightButton)
            button =  Qt::RightButton;
        if (scribbling)
            drawLineTo(event->pos());
            //drawLineTo(event->pos(),event->button());

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
            //drawLineTo(event->pos(),event->button());
            scribbling = false;
        }

    }
    qDebug()<<"mouse released";

}

void paintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
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
    painter.setRenderHint(QPainter::Antialiasing, true);
    if (button == Qt::LeftButton)
    {
        painter.setPen(QPen(penColor, pen.width(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(brushColor, pen.width(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void paintArea::drawLineTo(const QPoint &endPoint, const Qt::MouseButton &button)
{
    //qDebug()<<button;
    QPainter painter(&image);
    if ((firstColActive)||(button==Qt::LeftButton))
    {
        painter.setPen(QPen(penColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        qDebug()<<"here2";
    }
    else if (!(firstColActive)||(button == Qt::RightButton))
    {
        painter.setPen(QPen(brushColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        qDebug()<<"there2";

    }
    else
    {
        qDebug()<<"hmm2";
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
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}


void paintArea::setSettings(QString _drawableObj, QColor _penColor, QPen _pen, QColor _brushColor, QBrush _brush)
{
    drawableObj = _drawableObj;

    pen = _pen;
    setColors(_penColor,_brushColor);
    brush = _brush;
    qDebug()<<"set settings"<<drawableObj;
}

void paintArea::fillTool(QPoint pixel, QRgb Col)
{
    QRgb c = image.pixel(pixel);
    //qDebug()<<pixel << c << Col;
    if (c == Col)
        return;
    image.setPixel(pixel,Col);

    if ((pixel.x() < image.width() - 1)&&((image.pixel(pixel.x()+1,pixel.y()) == c)))
    {
            fillTool(QPoint(pixel.x()+1,pixel.y()),Col);
    }

    if (((pixel.y() < image.height()-1)&&(image.pixel(pixel.x(),pixel.y()+1) == c)))
    {
        fillTool(QPoint(pixel.x(),pixel.y()+1),Col);
    }

    if ((pixel.x() > 0)&& (image.pixel(pixel.x()-1,pixel.y()) == c))
        {
            fillTool(QPoint(pixel.x()-1,pixel.y()),Col);
        }


    if ((pixel.y() > 0)&&(image.pixel(pixel.x(),pixel.y()-1) == c))
        {
            fillTool(QPoint(pixel.x(),pixel.y()-1),Col);
        }

}

void paintArea::fillToolWork(int x, int y, QRgb oldColor, QRgb newColor)
{
    // void PaintWidget::Fill2(QRgb oldColor, QRgb newColor, int x, int y)

    if (oldColor == newColor) return;

    QStack<QPoint> stk;
    QPoint pt;

    int y1;
    bool spanLeft, spanRight;

    stk.push(QPoint(x, y));

    while (!stk.empty()) {
        //qDebug()<<"filling";
        pt = stk.pop();
        x = pt.x();
        y = pt.y();
        y1 = y;
        while (y1 >= 0 && image.pixel(x, y1) == oldColor) y1--;
        y1++;

        spanLeft = spanRight = false;
        while (y1 < image.height() && image.pixel(x, y1) == oldColor) {
            image.setPixel(x, y1, newColor);
            if (!spanLeft && x > 0 && image.pixel(x-1, y1) == oldColor) {
                stk.push(QPoint(x-1, y1));
                spanLeft = true;
            } else if(spanLeft && x > 0 && image.pixel(x-1, y1) != oldColor) {
                spanLeft = false;
            }
            if (!spanRight && x < (image.width() - 1) && image.pixel(x+1, y1) == oldColor) {
                stk.push(QPoint(x+1, y1));
                spanRight = true;
            } else if(spanRight && (x < image.width() - 1) && image.pixel(x+1, y1) != oldColor) {
                spanRight = false;
            }
            y1++;

        }

    }

}
