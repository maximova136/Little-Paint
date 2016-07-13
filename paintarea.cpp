#include "paintarea.h"
#include <QtWidgets>
#include <QDebug>
PaintArea::PaintArea(QWidget *parent) : QWidget(parent) {
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    shiftOn = false;
    ctrlOn = false;
    selectionOn = false;
    drawCurve = false;
    wasMovedSelection = false;
    mIsResize = false;

    topleft_x = 0;
    topleft_y = 0;
    scaleIsOn = false;
    setSettings("Brush",Qt::black,myPenWidth,Qt::white);
    eraserPix = QPixmap(1,1);

    
    firstColActive = true;
    image = QImage(QSize(400,250),QImage::Format_ARGB32_Premultiplied);
    // Here it is possible to create transparent canvas
    image.fill(Qt::white);
//    QPainter painter(&image);
//    painter.fillRect(0,0,600,350,Qt::transparent);
//    painter.setCompositionMode(QPainter::CompositionMode_Clear);
    setMouseTracking(true);
    copyImage = image;
    update();
}

void PaintArea::slotShiftOn(bool active) {
    if (active)
        shiftOn = true;
    else
        shiftOn = false;
}

void PaintArea::slotCtrlOn(bool active) {
    if (active)
        ctrlOn = true;
    else
        ctrlOn = false;
}


void PaintArea::slotChangeSize() {
    QLineEdit w, h;

}

void PaintArea::clearImage() {
    image.fill(qRgb(255, 255, 255));
    update();
    copyImage = image;
    modified = true;
    scribbling = false;
    selectionOn = false;
    wasMovedSelection = false;
    drawCurve = false;
    update();
}

void PaintArea::saveImage() {
    QString path = QDir::homePath()+"/Pictures" + "/image.png";
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
        if (!image.save(fileFullName,format.toUtf8().toUpper().constData(),100)) {
            QMessageBox::warning(this, tr("Error saving file"), tr("Can't save file \"%1\".").arg(fileFullName));
        }
        qDebug()<<format;
    }
}

void PaintArea::openImage() {
    QString path = QDir::homePath()+"/Pictures";
    QString selectionFilter = tr("PNG (*.png)");
    QString fileFullName = QFileDialog::getOpenFileName(
                               this,
                               tr("Open Image"),
                               path,
                               tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;BMP (*.bmp)" ),
                               &selectionFilter
                               );
    if (!fileFullName.isEmpty()) {

        qDebug()<<fileFullName <<path ;
        int indexOfLastDot = fileFullName.lastIndexOf(".");
        QStringRef format (&fileFullName, indexOfLastDot+1,fileFullName.length()-indexOfLastDot-1);
        if (!image.load(fileFullName,format.toUtf8().toUpper().constData())) {
            QMessageBox::warning(this, tr("Error opening file"), tr("Can't open file \"%1\".").arg(fileFullName));
        } else {
            qDebug()<<image.size()<< size() << pos () ;
            QSize screenSize = QApplication::desktop()->screenGeometry().size();
            if (image.height() > (screenSize.height() - 130)) {
                image = image.scaledToHeight(screenSize.height() - 130,Qt::SmoothTransformation);
            }
            if (image.width() > (screenSize.width() - 200)) {
                image = image.scaledToWidth(screenSize.width() - 200,Qt::SmoothTransformation);
            }
            copyImage = image;
            qDebug()<<image.size()<< size();

            update();
        }
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

void PaintArea::firstColorActive(bool first) {
    if (first)
        firstColActive = true;
    else
        firstColActive = false;
}

void PaintArea::setPen(int wid) {

    if (drawableObj == "Eraser") {
        if (pen.width() != wid) {
            eraserPix = QPixmap(wid,wid);
            QPainter painter(&eraserPix);
            painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
            painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
            painter.drawRect(0,0,wid-1,wid-1);
            painter.end();
        }
        setCursor(QCursor(eraserPix));
    }
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

    if(event->button() == Qt::LeftButton &&
            event->pos().x() < image.rect().right() + 6 &&
            event->pos().x() > image.rect().right() &&
            event->pos().y() > image.rect().bottom() &&
            event->pos().y() < image.rect().bottom() + 6)
    {
        mIsResize = true;
    }
    else
    {
        if (drawableObj == "Brush") {
            lastPoint = event->pos();
            scribbling = true;
            if (event->button()!=0) {
                button = event->button();
            }
        } else if ((drawableObj == "Ellipse") || (drawableObj == "Rectangle") ||
                   (drawableObj == "Triangle") || (drawableObj == "Line")) {
            copyImage = image;
            lastPoint = event->pos();
            scribbling = true;
            if (event->button()!=0) {
                button = event->button();
            }
        } else if (drawableObj == "Curve") {
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
        } else if (drawableObj == "Fill") {
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
            capCount++;
            penCapStyle = Qt::SquareCap;
        } else if (drawableObj == "Selection") {
            qDebug()<<"press selection"<<selectionOn;
            wasMovedSelection = false;
            if (!selectionOn)
            {
                qDebug()<<"no selection";
                copyImage = image;
                lastPoint = event->pos();
                scribbling = true;
                if (event->button()!=0) {
                    button = event->button();
                }
            }
            else
            {
                qDebug()<<"selection ";
                selection.setCoords(lastPoint.x(),lastPoint.y(), cEndPoint.x(),cEndPoint.y());
                qDebug()<<selection <<event->pos();
                if ((selection.size().width() < 0) || (selection.size().height()<0)){
                    selection.setCoords(cEndPoint.x(),cEndPoint.y(),lastPoint.x(),lastPoint.y());
                }
                qDebug()<<selection <<event->pos();
                if (QRegion(selection).contains(event->pos()))
                {
                    bufImage = image.copy(selection);
                    qDebug()<<"contains";
                    lastPoint = event->pos();
                } else {
                    qDebug()<<"don't contains";
                    scribbling = false;
                    selectionOn = false;
                    copyImage = image;
                    update();
                }
            }
        }
    }
    qDebug()<<"mouse pressed";
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (mIsResize)
    {
        if (QRect(this->rect().left(),this->rect().top(),this->rect().width()-6, this->rect().height()-6).contains(event->pos()))
                resizeImage(QSize(event->x(),event->y()));
    }
    else if (event->buttons() != 0)
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
        } else if (drawableObj == "Selection") {
            qDebug()<<"move selection"<<selectionOn;
            wasMovedSelection = true;
            if (scribbling) {
                qDebug()<<"scribble";
                copyImage = image;
                paint(event->pos());
                update();
            } else {
                qDebug()<<"no scribble";
            }
        }
    }
    else if (event->pos().x() < image.rect().right() + 6 &&
            event->pos().x() > image.rect().right() &&
            event->pos().y() > image.rect().bottom() &&
            event->pos().y() < image.rect().bottom() + 6)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (event->pos().x() < image.rect().right() &&
             event->pos().y() < image.rect().bottom())
    {
        setCurrentCursor();
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
    qDebug()<<"mouse moved";
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (mIsResize)
    {
        mIsResize = false;
    }
    else
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
            if (drawCurve) {
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
                penCapStyle = Qt::RoundCap;
                scribbling = false;
            }
        } else if (drawableObj == "Selection") {
            qDebug()<<"RELEASE selection"<<selectionOn;
            if (wasMovedSelection)
            {
                cEndPoint = event->pos();
                qDebug()<<"was moved";
                if (!selectionOn) {
                    qDebug()<<"no selection ";
                    if (scribbling) {
                        qDebug()<<"scribble";
                        qDebug() << event->pos();
                        cEndPoint = event->pos();
                        selectionOn = true;
                    } else {
                        qDebug()<<"not scribble";
                    }
                } else {
                    qDebug()<<"selection ";
                    if (scribbling) {
                        qDebug()<<"scribble";
                        paint(event->pos());
                        scribbling = false;
                        image = copyImage;
                        selectionOn = false;
                    }
                    else {
                        qDebug()<<"not scribble";
                        copyImage = image;
                        update(0,0,image.width(),image.height());
                    }
                }
            }
            else {
                qDebug()<<"was not moved";
            }
        }
        if(mIsResize)
        {
            mIsResize = false;
        }
    }
    qDebug()<<"mouse released";
}
/*
void PaintArea::wheelEvent(QWheelEvent *event)
{
    qDebug()<< event->pos()
           << event->pixelDelta()
           << event->angleDelta();
    if (event->angleDelta().y() > 0) {
        copyImage = image.scaled(copyImage.width()*1.1,copyImage.height()*1.1,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
//        topleft_x -= 2;
//        topleft_y -= 2;
//        topleft_x *= 0.1;
//        topleft_y *= 0.1;
        topleft_x = event->pos().x()*0.1;
        topleft_y = event->pos().y()*0.1;
        scaleIsOn = true;

    } else {
        copyImage = image.scaled(copyImage.width()*0.9,copyImage.height()*0.9,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
//        topleft_x += 2;
//        topleft_y += 2;
//        topleft_x /= 0.1;
//        topleft_y /= 0.1;
        topleft_x = event->pos().x()*(-0.1);
        topleft_y = event->pos().y()*(-0.1);
        if (copyImage.size() == image.size()) {
            qDebug()<<"size == size";
            scaleIsOn = false;
        }
    }
    update();
}
*/

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
//    QRect dirtyRect = event->rect();
    QRect targetRect = event->rect();
    QRect sourceRect = event->rect();

    if ((drawableObj!="Line") && (drawableObj!="Ellipse") && (drawableObj!="Rectangle")
            && (drawableObj!="Triangle") && (drawableObj != "Curve")
            && (drawableObj != "Selection")) {
//        sourceRect.setX(sourceRect.x() + topleft_x);
//        sourceRect.setY(sourceRect.y() + topleft_y);
        painter.drawImage(targetRect, image, sourceRect);
        qDebug()<<"painEvent1";
    } else {
        sourceRect.setX(sourceRect.x() + topleft_x);
        sourceRect.setY(sourceRect.y() + topleft_y);
        painter.drawImage(targetRect,copyImage,sourceRect);
        qDebug()<<"painEvent2";
    }
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    painter.drawRect(image.rect().x(),image.rect().y(),image.width()-1,image.height()-1);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(QRect(image.rect().right(),
                            image.rect().bottom(), 6, 6));
    qDebug()<<targetRect<<sourceRect<<image.rect().x()<<image.rect().y();
    painter.end();
}

void PaintArea::resizeEvent(QResizeEvent *event)
{
    /*if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        //resizeImage(&image, QSize(image.width(),image.height()));
        update();
    }*/

    QWidget::resizeEvent(event);
    update();
}

void PaintArea::paint(const QPoint &endPoint)
{
    if (!scaleIsOn)
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

     if (lastPoint != endPoint) {
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
         else if (drawableObj == "Selection") {
             qDebug()<<"paint selection"<<selectionOn;
             if (!selectionOn) {
                 painter.setPen(QPen(Qt::black, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
                 painter.setBrush(QBrush(Qt::transparent));
                 if (shiftOn) {
                     painter.drawRect(QRect(lastPoint,QSize(endPoint.y()-lastPoint.y(),endPoint.y()-lastPoint.y())));
                 } else {
                     painter.drawRect(QRect(lastPoint,endPoint));
                 }
             } else {
                 if (!ctrlOn)
                     painter.fillRect(selection,brushColor);
                 painter.drawImage(QPoint(endPoint.x()-bufImage.width()/2,endPoint.y()-bufImage.height()/2),bufImage);
             }
         }
     }
     modified = true;
     painter.end();
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
        qDebug()<<"i'm brush";
        if (button == Qt::LeftButton) {
            painter.setPen(QPen(penColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
        } else {
            painter.setPen(QPen(brushColor, pen.width(), pen.style(), Qt::RoundCap, Qt::RoundJoin));
        }
    } else {
        qDebug()<<"i'm eraser";
        painter.setPen(QPen(Qt::white,pen.width(),Qt::SolidLine,penCapStyle, Qt::BevelJoin));
    }
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void PaintArea::resizeImage(const QSize &newSize)
{
    if (image.size() == newSize)
        return;
    QImage newImage(newSize, QImage::Format_ARGB32_Premultiplied);
    newImage.fill(Qt::white);
    QPainter painter(&newImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(QPoint(0, 0), image);
    image = newImage;
    update();
}


void PaintArea::setSettings(QString _drawableObj, QColor _penColor, int width, QColor _brushColor, Qt::PenStyle _penStyle, Qt::BrushStyle _brushStyle)
{
    drawableObj = _drawableObj;
    penColor = _penColor;
    brushColor = _brushColor;
    if (drawableObj == "Brush") {
        pen = QPen(_penColor,width,Qt::SolidLine);
        penStyle = Qt::SolidLine;
        emit signalChangePenStyle("Solid Line");
    } else {
        pen = QPen(_penColor,width,_penStyle);
        penStyle = _penStyle;
    }
    brush = QBrush(_brushColor,_brushStyle);
    brushStyle = _brushStyle;
    qDebug()<<"set settings2"<<drawableObj;
    qDebug()<<_penColor<<width<<_brushColor<<_penStyle<<_brushStyle;
    myPenWidth = width;

    if ((drawableObj == "Fill") || (drawableObj == "Pipette")) {
        emit signalBlockSettings(true,true,true);
    } else if ((drawableObj == "Brush") || (drawableObj == "Eraser")) {
        emit signalBlockSettings(true,true,false);
    } else if (drawableObj == "Line") {
        emit signalBlockSettings(false,true,false);
    } else if (drawableObj == "Selection") {
        emit signalBlockSettings(true,true,true);
    } else {
        emit signalBlockSettings(false,false,false);
    }
}

void PaintArea::setCurrentCursor()
{
    if (drawableObj == "Fill") {
        setCursor(QCursor(QPixmap("media/cursor_fill.png")));
    } else if (drawableObj == "Pipette") {
        setCursor(QCursor(QPixmap("media/cursor_pipette.png")));
    } else if ((drawableObj == "Line") || (drawableObj == "Curve") || (drawableObj == "Ellipse") || (drawableObj == "Rectangle") || (drawableObj == "Triangle") || (drawableObj == "Selection")) {
        setCursor(Qt::CrossCursor);
    } else if (drawableObj == "Eraser") {
        changeWidth(myPenWidth);
    } else if (drawableObj == "Brush") {
        setCursor(QCursor(QPixmap("media/cursor_pencil.png")));
    } else {
        setCursor(Qt::ArrowCursor);
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
