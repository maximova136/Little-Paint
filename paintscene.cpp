#include "paintscene.h"
#include <QDebug>

paintScene::paintScene(QObject *parent):QGraphicsScene(parent)
{
    setSettings("Brush",Qt::black,QPen(Qt::SolidLine),Qt::white,QBrush(Qt::SolidPattern));
}

paintScene::~paintScene()
{

}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     if (drawableObj == "Brush")
     {
            // При нажатии кнопки мыши отрисовываем эллипс
            addEllipse(event->scenePos().x() - 5, event->scenePos().y() - 5, 10 , 10, QPen(Qt::NoPen), QBrush(Qt::blue));
            // Сохраняем координаты точки нажатия
            previousPoint = event->scenePos();

     }

     qDebug()<<"mouse pressed";

}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawableObj == "Brush")
    {
        // Отрисовываем линии с использованием предыдущей координаты
        //addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(), QPen(Qt::red,10,Qt::SolidLine, Qt::RoundCap));
        addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(), QPen(penStyle));
        // Обновляем данные о предыдущей координате
        previousPoint = event->scenePos();

    }
    qDebug()<<"mouse moved";
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{


    qDebug()<<"mouse released";
}

void paintScene::setSettings(QString _drawableObj, QColor _penColor, QPen _penStyle, QColor _brushColor, QBrush _brushStyle)
{
    drawableObj = _drawableObj;
    penColor = _penColor;
    penStyle = _penStyle;
    brushColor = _brushColor;
    brushStyle = _brushStyle;
}
