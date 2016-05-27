#include "paintarea.h"
#include <QtWidgets>
#include <QDebug>
PaintArea::PaintArea(QWidget *parent) : QWidget(parent) {
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    shiftOn = false;
    drawCurve = false;

    setSettings("Brush",Qt::black,myPenWidth,Qt::white);
    
    firstColActive = true;
    image = QImage(QSize(600,350),QImage::Format_ARGB32_Premultiplied);
    // Here is possible to create transparent canvas
 //   image.fill(Qt::white);
//    QPainter painter(&image);
//    painter.fillRect(0,0,600,350,Qt::transparent);
//    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    eraserTransparency = 0;
    capCount = 0;
    copyImage = image;
    update();
}

void PaintArea::shiftActive(bool active) {
    if (active)
        shiftOn = true;
    else
        shiftOn = false;
}

void PaintArea::clearImage() {
    image.fill(qRgb(255, 255, 255));
    copyImage = image;
    modified = true;
    update();
}

void PaintArea::saveImage() {
    QString path = QDir::currentPath() + "/image.png";
    QString selectionFilter = tr("PNG (*.png)");
    QString fileFullName = QFileDialog::getSaveFileName(
            this,
            tr("Save Picture"),
            path,
            tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" ),
            &selectionFilter);

    if (!fileFullName.isEmpty()) {

        qDebug()<<fileFullName <<path ;
        int indexOfLastDot = fileFullName.lastIndexOf(".");
        QStringRef format (&fileFullName, indexOfLastDot+1,fileFullName.length()-indexOfLastDot-1);
        image.save(fileFullName,format.toUtf8().toUpper().constData(),100);
        qDebug()<<format;
    }
}

void PaintArea::changeColors(QColor col1, QColor col2) {
    setColors(col1,col2);
    qDebug()<<"slot";
}

void PaintArea::changeWidth(int width) {
    myPenWidth = width;
    setPen(myPenWidth);
}

void PaintArea::changePenStyle(QString style) {
    if (style == "Solid Line") {
        penStyle = Qt::SolidLine;
    } else if (style == "Dash Line") {
        penStyle = Qt::DashLine;
    } else if (style == "Dot Line") {
        penStyle = Qt::DotLine;
    } else if (style == "Dash Dot Line") {
        penStyle = Qt::DashDotLine;
    } else if (style == "Dash Dot Dot Line") {
        penStyle = Qt::DashDotDotLine;
    } else if (style == "No Line") {
        penStyle = Qt::NoPen;
    }
    setPen(penStyle);
    qDebug()<<style;
}

void PaintArea::changeBrushStyle(QString style)
{
    if (style == "No Brush") {
        brushStyle = Qt::NoBrush;
    } else if(style == "Solid") {
        brushStyle = Qt::SolidPattern;
    } else if(style == "Hor") {
        brushStyle = Qt::HorPattern;
    } else if(style == "Ver") {
        brushStyle = Qt::VerPattern;
    } else if(style == "Cross") {
        brushStyle = Qt::CrossPattern;
    } else if(style == "DiagCross") {
        brushStyle = Qt::DiagCrossPattern;
    } else if(style == "BDiag") {
        brushStyle = Qt::BDiagPattern;
    } else if(style == "FDiag") {
        brushStyle = Qt::FDiagPattern;
    } else if(style == "Dense") {
        brushStyle = Qt::Dense3Pattern;
    }
    qDebug()<<style;
}

void PaintArea::changeTransparency(int value) {
    eraserTransparency = value*10;
}

void PaintArea::firstColorActive(bool first) {
    if (first)
        firstColActive = true;
    else
        firstColActive = false;
}

void PaintArea::setPen( int wid) {
    pen.setWidth(wid);
}

void PaintArea::setPen(Qt::PenStyle _style) {
    pen.setStyle(_style);
}

void PaintArea::setColors(QColor col1, QColor col2) {
    penColor = col1;
    brushColor = col2;
}

void PaintArea::mousePressEvent(QMouseEvent *event) {
    if (drawableObj == "Brush")
    {
        lastPoint = event->pos();
        scribbling = true;

    } else if ((drawableObj == "Ellipse") || (drawableObj == "Rectangle") ||
               (drawableObj == "Triangle") || (drawableObj == "Line"))
    {
        copyImage = image;
        lastPoint = event->pos();
        scribbling = true;
        if (event->button()!=0) {
            button = event->button();
        }
    } else if (drawableObj == "Curve")
    {
        if (!drawCurve) {
            copyImage = image;
            lastPoint = event->pos();
            scribbling = true;
            if (event->button()!=0) {
                button = event->button();
            }
        } else {
            copyImage = image;
            c2 = event->pos();
        }

    } else if (drawableObj == "Fill")
    {
        QColor newColor;
        button = event->button();
        if (button == Qt::LeftButton) {
            newColor = penColor;
        } else if (button == Qt::RightButton) {
            newColor = brushColor;
        }
        qDebug()<<event->pos();

        if (event->pos().x()< image.width() && event->pos().y() < image.height()) {
             fillTool(event->pos().x(),event->pos().y(), image.pixel(event->pos()),newColor.rgb());
             update();
        }
    } else if (drawableObj == "Pipette") {
        scribbling = true;
        emit pipetteColor(QColor(image.pixel(event->pos())));
    } else if (drawableObj == "Eraser") {
        lastPoint = event->pos();
        scribbling = true;
//        capCount++;
        penCapStyle = Qt::SquareCap;
    }
    qDebug()<<"mouse pressed";
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush") {
        if (event->button()==Qt::LeftButton)
            button = Qt::LeftButton;
        else if (event->button() == Qt::RightButton)
            button =  Qt::RightButton;
        if (scribbling)
            brushTool(event->pos());
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
    else if (drawableObj == "Curve")
    {
        copyImage = image;
        if (event->button()==Qt::LeftButton)
            button = Qt::LeftButton;
        else if (event->button() == Qt::RightButton)
            button =  Qt::RightButton;

        if (scribbling) {
            if (!drawCurve){
                drawLine(event->pos());
            } else {
                c1 = event->pos();
                paint(event->pos());
            }
        }
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
    else if (drawableObj == "Pipette")
    {
        if (scribbling)
            emit pipetteColor(QColor(image.pixel(event->pos())));
    } else if (drawableObj == "Eraser") {
        if (capCount < 3){
            capCount++;
        } else {
            penCapStyle = Qt::RoundCap;
        }
        if (scribbling)
            brushTool(event->pos());
    }

}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (drawableObj == "Brush") {
        if (scribbling) {
            brushTool(event->pos());
            scribbling = false;
        }
    }
    else if ((drawableObj == "Ellipse")||(drawableObj == "Rectangle")||(drawableObj == "Triangle")) {
        if (scribbling) {
            paint(event->pos());
            scribbling = false;
            image = copyImage;
        }
    } else if (drawableObj == "Curve") {
        if (drawCurve)
        {
            if (scribbling) {
                paint(event->pos());
                drawCurve = false;
                scribbling = false;
                image = copyImage;
            }
        } else {
            drawCurve = true;
            cEndPoint = event->pos();
        }
    } else if (drawableObj == "Line") {
        if (scribbling) {
            scribbling = false;
            image = copyImage;
        }
    } else if (drawableObj == "Pipette") {
        if (scribbling) {
            emit pipetteColor(QColor(image.pixel(event->pos())));
            scribbling = false;
        }
    } else if (drawableObj == "Eraser") {
        if (scribbling) {
            capCount = 0;
            penCapStyle = Qt::SquareCap;
            brushTool(event->pos());
            scribbling = false;
        }
    }
    qDebug()<<"mouse released";
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRect dirtyRect = event->rect(); 

    if ((drawableObj!="Line") && (drawableObj!="Ellipse") && (drawableObj!="Rectangle")
            && (drawableObj!="Triangle") && (drawableObj != "Curve")) {
        painter.drawImage(dirtyRect, image, dirtyRect);
    } else {
        painter.drawImage(dirtyRect,copyImage,dirtyRect);
    }
    qDebug()<<"painEvent";
}

void PaintArea::resizeEvent(QResizeEvent *event)
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

void PaintArea::paint(const QPoint &endPoint)
{
     copyImage = image;

     QPainter painter(&copyImage);

     painter.setRenderHint(QPainter::Antialiasing, true);

     if (button == Qt::LeftButton) {
         painter.setPen(QPen(penColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
         painter.setBrush(QBrush(brushColor,brushStyle));
     } else {
         painter.setPen(QPen(brushColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
         painter.setBrush(QBrush(penColor,brushStyle));
     }

     if (lastPoint!=endPoint) {
         if (drawableObj == "Ellipse") {
             if (shiftOn) {
                 painter.drawEllipse(QRect(lastPoint,QSize(endPoint.y()-lastPoint.y(),endPoint.y()-lastPoint.y())));
             } else {
                 painter.drawEllipse(QRect(lastPoint, endPoint));
             }
         }
         else if (drawableObj == "Rectangle") {
             if (shiftOn) {
                 painter.drawRect(QRect(lastPoint,QSize(endPoint.y()-lastPoint.y(),endPoint.y()-lastPoint.y())));
             } else {
                 painter.drawRect(QRect(lastPoint,endPoint));
             }
         }
         else if (drawableObj == "Triangle") {
            if (shiftOn) {
                int width = endPoint.y() - lastPoint.y();
                QPolygonF triangle;
                triangle << QPointF(lastPoint.x(),endPoint.y())
                         <<QPointF(lastPoint.x()+width/2,lastPoint.y())
                        <<QPointF(lastPoint.x()+width,endPoint.y());
                painter.drawPolygon(triangle);
            } else {
                QPolygonF triangle;
                triangle << QPointF(lastPoint.x(),endPoint.y())
                         <<QPointF((lastPoint.x()+endPoint.x())/2,lastPoint.y())
                        <<endPoint;
                painter.drawPolygon(triangle);
            }
         }
         else if (drawableObj == "Curve")
         {
             QPainterPath myPath;
             myPath.moveTo(lastPoint);
             myPath.cubicTo(c1, c2, cEndPoint);

             painter.drawPath(myPath);
         }
     }
     modified = true;
     painter.end();
     //int rad = (myPenWidth / 2) + 2;
     //update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
     update();
}

void PaintArea::drawLine(const QPoint &endPoint) {
    copyImage = image;
    QPainter painter(&copyImage);

    painter.setRenderHint(QPainter::Antialiasing, true);

    if (button == Qt::LeftButton){
        painter.setPen(QPen(penColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter.setPen(QPen(brushColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
    }

    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
}

void PaintArea::brushTool(const QPoint &endPoint){

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (drawableObj != "Eraser") {
        if (button == Qt::LeftButton) {
            painter.setPen(QPen(penColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
        } else {
            painter.setPen(QPen(brushColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
        }
    } else {
        painter.setPen(QPen(Qt::white,pen.width(),Qt::SolidLine,penCapStyle, Qt::BevelJoin));
        //painter.setPen(QPen(QBrush(qRgba(255,0,0,100)),pen.width(),pen.style(),Qt::SquareCap, Qt::MiterJoin));
        //painter.setBrush(Qt::NoBrush);
        //painter.setBackgroundMode(QPainter::CompositionMode_SourceIn);
        //painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
        //image.setPixel(endPoint,qRgba(255,0,0,255));
    }
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void PaintArea::resizeImage(QImage *image, const QSize &newSize)
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


void PaintArea::setSettings(QString _drawableObj, QColor _penColor, int width, QColor _brushColor, Qt::PenStyle _penStyle, Qt::BrushStyle _brushStyle)
{
    drawableObj = _drawableObj;
    penColor = _penColor;
    brushColor = _brushColor;
    pen = QPen(_penColor,width,_penStyle);
    brush = QBrush(_brushColor,_brushStyle);
    penStyle = _penStyle;
    brushStyle = _brushStyle;
    qDebug()<<"set settings2"<<drawableObj;
    qDebug()<<_penColor<<width<<_brushColor<<_penStyle<<_brushStyle;
    if ((drawableObj == "Fill") || (drawableObj == "Text") || (drawableObj == "Pipette")) {
        emit signalBlockSettings(true,true,true);
    } else if ((drawableObj == "Brush") || (drawableObj == "Eraser")) {
        emit signalBlockSettings(true,true,false);
    } else if (drawableObj == "Line") {
        emit signalBlockSettings(false,true,false);
    } else {
        emit signalBlockSettings(false,false,false);
    }
}


void PaintArea::fillTool(int x, int y, QRgb oldColor, QRgb newColor)
{
    if (oldColor == newColor) return;
    QStack<QPoint> stk;
    QPoint pt;

    int y1;
    bool spanLeft, spanRight;

    stk.push(QPoint(x, y));

    while (!stk.empty()) {
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
