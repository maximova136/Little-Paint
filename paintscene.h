#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class paintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();

private:
    QPointF previousPoint;      // Eiidacirnu ddlauaoule ni?ec
    QColor penColor; //adricou
    QColor brushColor; //crecaer
    QString drawableObj;
    QBrush brushStyle;
    QPen penStyle;
    bool firstColActive;

    QGraphicsItem* figure;
    QGraphicsItemGroup* figureSelected;
    //QPen pen
    //QBrush brush
    // QBrush brushStyl -----> Qt::Brushstyle ????
    bool newFigure;

private:
    // Ae? dcniaric? cndieucole niaunc? eurc
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
public:
    void setSettings(QString _drawableObj, QColor _penColor,QPen _penStyle, QColor _brushColor,  QBrush _brushStyle);
};

#endif // PAINTSCENE_H
