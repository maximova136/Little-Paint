#include "paintarea.h"
#include <QtWidgets>
#include <QDebug>
paintArea::paintArea(QWidget *parent) : QWidget(parent)
{
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    shiftOn = false;

    setSettings("Brush",Qt::black,myPenWidth,Qt::white);
    
    firstColActive = true;
//    image = QImage(QSize(600,400),QImage::Format_RGB32);
    image = QImage(QSize(400,250),QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);
    //image = image.scaled(300,200,Qt::KeepAspectRatio);
    copyImage = image;
    update();
}

void paintArea::shiftActive(bool active)
{
    if (active)
        shiftOn = true;
    else
        shiftOn = false;
}


void paintArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    copyImage = image;
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
    myPenWidth = width;
    setPen(myPenWidth);
}

void paintArea::changePenStyle(QString style)
{
    if (style == "Solid Line")
    {
        penStyle = Qt::SolidLine;
    }
    else if (style == "Dash Line")
    {
        penStyle = Qt::DashLine;
    }
    else if (style == "Dot Line")
    {
        penStyle = Qt::DotLine;
    }
    else if (style == "Dash Dot Line")
    {
        penStyle = Qt::DashDotLine;
    }
    else if (style == "Dash Dot Dot Line")
    {
        penStyle = Qt::DashDotDotLine;
    }
    else if (style == "No Line")
    {
        penStyle = Qt::NoPen;
    }
    setPen(penStyle);
    qDebug()<<style;
}

void paintArea::changeBrushStyle(QString style)
{
    if (style == "No Brush")
    {
        brushStyle = Qt::NoBrush;
    }
    else if(style == "Solid")
    {
        brushStyle = Qt::SolidPattern;
    }
    else if(style == "Hor")
    {
        brushStyle = Qt::HorPattern;
    }
    else if(style == "Ver")
    {
        brushStyle = Qt::VerPattern;
    }
    else if(style == "Cross")
    {
        brushStyle = Qt::CrossPattern;
    }
    else if(style == "DiagCross")
    {
        brushStyle = Qt::DiagCrossPattern;
    }
    else if(style == "BDiag")
    {
        brushStyle = Qt::BDiagPattern;
    }
    else if(style == "FDiag")
    {
        brushStyle = Qt::FDiagPattern;
    }
    else if(style == "Dense")
    {
        brushStyle = Qt::Dense3Pattern;
    }
//    else if(style == "Gradient")
//    {
//        QLinearGradient linGradient(0,0,10,10);
//        linGradient.setColorAt(0,penColor);
//        linGradient.setColorAt(1,brushColor);
//        brushStyle = linGradient;
//    }

    qDebug()<<style;
}

void paintArea::firstColorActive(bool first)
{
    if (first)
        firstColActive = true;
    else
        firstColActive = false;
}

void paintArea::setPen( int wid)
{
   // pen = QPen(QBrush(penColor),wid);
    //pen = QPen(penColor, wid, penStyle);
    pen.setWidth(wid);
}

void paintArea::setPen(Qt::PenStyle _style)
{
    pen.setStyle(_style);
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
    else if ((drawableObj == "Ellipse")||(drawableObj == "Rectangle")||
             (drawableObj == "Triangle")||(drawableObj == "Line"))
    {
        copyImage = image;
        lastPoint = event->pos();
        scribbling = true;
        if (event->button()!=0)
        {
            button = event->button();
        }
    }
    else if (drawableObj == "Fill")
    {
        //QPointF point = event->pos();
        QColor newColor;
        button = event->button();
        if (button == Qt::LeftButton)
        {
            newColor = penColor;
        }
        else if (button == Qt::RightButton)
        {
            newColor = brushColor;
        }
        qDebug()<<event->pos();

        if (event->pos().x()< image.width() && event->pos().y() < image.height())
        {
             fillToolWork(event->pos().x(),event->pos().y(), image.pixel(event->pos()),newColor.rgb());
             update();
        }

    }

    qDebug()<<"mouse pressed";
}

void paintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush")
    {
        if (event->button()==Qt::LeftButton)
            button = Qt::LeftButton;
        else if (event->button() == Qt::RightButton)
            button =  Qt::RightButton;
        if (scribbling)
            drawLineTo(event->pos());

    }
    else if ((drawableObj == "Ellipse")||(drawableObj == "Rectangle")||(drawableObj == "Triangle"))
    {
        copyImage = image;
        if (event->button()==Qt::LeftButton)
            button = Qt::LeftButton;
        else if (event->button() == Qt::RightButton)
            button =  Qt::RightButton;
        if (scribbling)
            paint(event->pos());
        update();
    }
    else if (drawableObj == "Line")
    {
        copyImage = image;

        if (event->button()==Qt::LeftButton)
            button = Qt::LeftButton;
        else if (event->button() == Qt::RightButton)
            button =  Qt::RightButton;
        if (scribbling)
            drawLine(event->pos());
        update();
    }
}

void paintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush")
    {
        if (scribbling)
        {
            drawLineTo(event->pos());
            scribbling = false;
        }

    }
    else if ((drawableObj == "Ellipse")||(drawableObj == "Rectangle")||(drawableObj == "Triangle"))
    {
        if (scribbling)
        {
            paint(event->pos());
            scribbling = false;
            image = copyImage;
        }
    }
    else if (drawableObj == "Line")
    {
        if (scribbling)
        {
            scribbling = false;
            image = copyImage;
        }
    }

    qDebug()<<"mouse released";

}

void paintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //copyImage = image;
    QRect dirtyRect = event->rect();
    if ((drawableObj!="Line")&&(drawableObj!="Ellipse")&&(drawableObj!="Rectangle")&&(drawableObj!="Triangle"))
    {
        painter.drawImage(dirtyRect, image, dirtyRect);
    }
    else
    {
        painter.drawImage(dirtyRect,copyImage,dirtyRect);
    }
    qDebug()<<"painEvent";

 }

void paintArea::resizeEvent(QResizeEvent *event)
{
//    if (width() > image.width() || height() > image.height()) {
//        int newWidth = qMax(width() + 128, image.width());
//        int newHeight = qMax(height() + 128, image.height());
//        resizeImage(&image, QSize(newWidth, newHeight));
//        //resizeImage(&image, QSize(image.width(),image.height()));
//        update();
//    }
    QWidget::resizeEvent(event);
    update();
}

void paintArea::paint(const QPoint &endPoint)
{
     copyImage = image;

     QPainter painter(&copyImage);

     painter.setRenderHint(QPainter::Antialiasing, true);

     if (button == Qt::LeftButton)
     {
         painter.setPen(QPen(penColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
         painter.setBrush(QBrush(brushColor,brushStyle));
     }
     else
     {
         painter.setPen(QPen(brushColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
         painter.setBrush(QBrush(penColor,brushStyle));

     }

     if (lastPoint!=endPoint)
     {
         if (drawableObj == "Ellipse")
         {
             if (shiftOn)
             {
                 painter.drawEllipse(QRect(lastPoint,QSize(endPoint.y()-lastPoint.y(),endPoint.y()-lastPoint.y())));
             }
             else
             {
                 painter.drawEllipse(QRect(lastPoint, endPoint));
             }

         }
         else if (drawableObj == "Rectangle")
         {
             if (shiftOn)
             {
                 painter.drawRect(QRect(lastPoint,QSize(endPoint.y()-lastPoint.y(),endPoint.y()-lastPoint.y())));
             }
             else
             {
                 painter.drawRect(QRect(lastPoint,endPoint));
             }

         }
         else if (drawableObj == "Triangle")
         {
            if (shiftOn)
            {
                int width = endPoint.y() - lastPoint.y();
                QPolygonF triangle;
                triangle << QPointF(lastPoint.x(),endPoint.y())
                         <<QPointF(lastPoint.x()+width/2,lastPoint.y())
                        <<QPointF(lastPoint.x()+width,endPoint.y());
                painter.drawPolygon(triangle);
            }
            else
            {
                QPolygonF triangle;
                triangle << QPointF(lastPoint.x(),endPoint.y())
                         <<QPointF((lastPoint.x()+endPoint.x())/2,lastPoint.y())
                        <<endPoint;
                painter.drawPolygon(triangle);
            }
         }
     }
     modified = true;
     painter.end();
     //int rad = (myPenWidth / 2) + 2;
     //update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
     update();
}

void paintArea::drawLine(const QPoint &endPoint)
{
    copyImage = image;

    QPainter painter(&copyImage);

     painter.setRenderHint(QPainter::Antialiasing, true);

     if (button == Qt::LeftButton)
     {
         painter.setPen(QPen(penColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
     }
     else
     {
         painter.setPen(QPen(brushColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
     }

     painter.drawLine(lastPoint, endPoint);
     modified = true;

     int rad = (myPenWidth / 2) + 2;

     update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
}


void paintArea::drawLineTo(const QPoint &endPoint)
{
   //QPainter painter(imageLabel);
   QPainter painter(&image);

    painter.setRenderHint(QPainter::Antialiasing, true);
    if (button == Qt::LeftButton)
    {
        painter.setPen(QPen(penColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(brushColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
    }

    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
    //qDebug()<<penStyle<<pen.style();
    //imageLabel->setPixmap(QPixmap::fromImage(image));
    //imageLabel->update();

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

    image = copyImage;
    qDebug()<<"set settings"<<drawableObj;
}

void paintArea::setSettings(QString _drawableObj, QColor _penColor, int width, QColor _brushColor, Qt::PenStyle _penStyle, Qt::BrushStyle _brushStyle)
{
    drawableObj = _drawableObj;
    penColor = _penColor;
    brushColor = _brushColor;
    pen = QPen(_penColor,width,_penStyle);
    brush = QBrush(_brushColor,_brushStyle);
    penStyle = _penStyle;
    brushStyle = _brushStyle;
    qDebug()<<"set settings"<<drawableObj;
    qDebug()<<_penColor<<width<<_brushColor<<_penStyle<<_brushStyle;

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
