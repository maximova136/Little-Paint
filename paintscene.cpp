#include "paintscene.h"
#include <QDebug>

paintScene::paintScene(QObject *parent):QGraphicsScene(parent)
{
    setSettings("Brush",Qt::black,QPen(Qt::SolidLine),Qt::white,QBrush(Qt::SolidPattern));
    newFigure = true;
    firstColActive = true;
//    setMouseTracking(true);

//    parent_figure = new QGraphicsEllipseItem(QRect(0,0,40,40));
//    figureSelected = new QGraphicsItemGroup;

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
         if (newFigure)
         {
             QBrush blueBrush(Qt::blue);
             QPen blackPen(Qt::black);

             //blackPen.setWidth(3);
             QPolygonF point;
             QGraphicsPolygonItem* points;



             //ellipse = addEllipse(QRect(0,0,30,30),blackPen,blueBrush);
             //ellipse->setPos(event->scenePos());

             //figure = new QGraphicsEllipseItem();
             //figure = QGraphicsEllipseItem(QRect(0,0,40,40),blackPen,blueBrush);
                figure = new QGraphicsEllipseItem(QRectF(0,0,40,40));
             // figure = new QGraphicsEllipseItem(QRect(0,0,40,40),parent_figure);
             qDebug()<<figure->parentItem();
             qDebug()<<figure->childItems();

             //figure->setPos(event->scenePos());
             figure->setFlag(QGraphicsItem::ItemIsMovable);
             figure->setFlag(QGraphicsItem::ItemIsSelectable);


             qDebug()<<figure->pos();
             qDebug()<<figure->boundingRect();

             //!!!!!!!!!!! скорректировать для разной толщины контура фигуры. также для прозрачного

             point<<QPointF(figure->pos().x(),figure->pos().y())
                 <<QPointF(figure->pos().x()+figure->boundingRect().width(),figure->pos().y())
                <<QPointF(figure->pos().x()+figure->boundingRect().width(),figure->pos().y()+figure->boundingRect().height())
               <<QPointF(figure->pos().x(),figure->pos().y()+figure->boundingRect().height());
             //addPolygon(point,QPen(Qt::SolidLine),QBrush(Qt::magenta,Qt::BDiagPattern));

             blackPen.setColor(Qt::darkGray);
             blackPen.setStyle(Qt::DashLine);
             points = new QGraphicsPolygonItem(point);
             points->setPen(blackPen);


             //figureSelected = new QGraphicsItemGroup(parent_figure);
             figureSelected = new QGraphicsItemGroup;


             figureSelected->addToGroup(points);
             figureSelected->addToGroup(figure);

             figureSelected->setX(event->scenePos().rx()-figure->boundingRect().width()/2);
             figureSelected->setY(event->scenePos().ry()-figure->boundingRect().height()/2);

             addItem(figureSelected);

         }
         else
         {

             newFigure = true;
             figure = new QGraphicsEllipseItem;

         }


        // ellipse->setFlag(QGraphicsItem::ItemIsMovable);
        // ellipse->setFlag(QGraphicsItem::ItemIsSelectable);

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
        if (newFigure)
        {
            figureSelected->setX(event->scenePos().rx()- figure->boundingRect().width()/2);
            figureSelected->setY(event->scenePos().ry()- figure->boundingRect().height()/2);
        }
        else
        {

        }
    }
    qDebug()<<"mouse moved";
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawableObj == "Brush")
    {


    }
    else if (drawableObj == "Ellipse")
    {
        if (newFigure)
        {
            qDebug()<<figureSelected->childItems();
            //removeItem(figureSelected->childItems());
            addItem(figure);

        //figure->show();
        //removeItem(figure);
        //removeItem(figureSelected);
            newFigure = false;
            figureSelected = new QGraphicsItemGroup;
        }
        else
        {

        }
    }
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
