#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPainter>

class paintArea : public QWidget
{
    Q_OBJECT
public:
    explicit paintArea(QWidget *parent = 0);
    //    bool openImage(const QString &fileName);
    //    bool saveImage(const QString &fileName, const char *fileFormat);
    //    void setPenColor(const QColor &newColor);
    //    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor getPenColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    void setSettings(QString _drawableObj, QColor _penColor,QPen _penStyle, QColor _brushColor,  QBrush _brushStyle);
    void setColors(QColor col1, QColor col2);

signals:

public slots:
    void clearImage();
    //void changeColor();
    void changeColors(QColor, QColor);
    void firstColorActive(bool);
    //void print();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;


private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;



    QColor penColor;
    QColor brushColor;
    QString drawableObj;
    QBrush brushStyle;
    QPen penStyle;
    bool firstColActive;

};

#endif // PAINTAREA_H



