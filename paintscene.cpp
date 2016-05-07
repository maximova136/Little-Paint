#include "paintscene.h"
#include <QDebug>

paintScene::paintScene(QObject *parent):QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(event->scenePos().x() - 5, event->scenePos().y() - 5, 10 , 10, QPen(Qt::NoPen), QBrush(Qt::blue));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
    qDebug()<<"mouse pressed";
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Отрисовываем линии с использованием предыдущей координаты
    addLine(previousPoint.x(), previousPoint.y(), event->scenePos().x(), event->scenePos().y(), QPen(Qt::red,10,Qt::SolidLine, Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
    qDebug()<<"mouse moved";
}
