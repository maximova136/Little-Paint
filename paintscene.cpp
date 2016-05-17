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
     else if (drawableObj == "Ellipse")
     {
         QBrush blueBrush(Qt::blue);
         QPen blackPen(Qt::black);
         //QGraphicsItem* ellipse;
         blackPen.setWidth(3);


         //ellipse = addEllipse(QRect(0,0,30,30),blackPen,blueBrush);
         //ellipse->setPos(event->scenePos());

         figure = addEllipse(QRect(0,0,40,40),blackPen,blueBrush);
         figure->setPos(event->scenePos());
         figure->setFlag(QGraphicsItem::ItemIsMovable);
         figure->setFlag(QGraphicsItem::ItemIsSelectable);



        // ellipse->setFlag(QGraphicsItem::ItemIsMovable);
        // ellipse->setFlag(QGraphicsItem::ItemIsSelectable);

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
    else if (drawableObj == "Ellipse")
    {
        figure->setX(event->scenePos().rx());
        figure->setY(event->scenePos().ry());
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
    qDebug()<<"set settings"<<drawableObj;
}
