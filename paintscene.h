#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class paintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();

private:
    QPointF previousPoint;      // ���������� ���������� �����
    QColor penColor; //�������
    QColor brushColor; //�������
    QString drawableObj;
    QBrush brushStyle;
    QPen penStyle;
    //QPen pen
    //QBrush brush
    // QBrush brushStyl -----> Qt::Brushstyle ????


private:
    // ��� ��������� ���������� ������� ����
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
public:
    void setSettings(QString _drawableObj, QColor _penColor,QPen _penStyle, QColor _brushColor,  QBrush _brushStyle);
};

#endif // PAINTSCENE_H
