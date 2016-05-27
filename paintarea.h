#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPainter>
#include <QtWidgets>
class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);
    //    bool openImage(const QString &fileName);
    //    bool saveImage(const QString &fileName, const char *fileFormat);
    //    void setPenColor(const QColor &newColor);
    //    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor getPenColor() const { return penColor; }
    int penWidth() const { return myPenWidth; }
    Qt::PenStyle getPenStyle() {return penStyle;}
    Qt::BrushStyle getBrushStyle() const {return brushStyle;}
    void setSettings(QString _drawableObj, QColor _penColor,QPen _penStyle, QColor _brushColor,  QBrush _brushStyle);
    void setSettings(QString _drawableObj, QColor _penColor,  int width, QColor _brushColor, Qt::PenStyle _penStyle = Qt::SolidLine, Qt::BrushStyle _brushStyle = Qt::SolidPattern);
    void setColors(QColor col1, QColor col2);
    void setPen(int wid);
    void setPen(Qt::PenStyle _style = Qt::SolidLine);

signals:
    void pipetteColor(QColor color);

public slots:
    void clearImage();
    void changeColors(QColor, QColor);
    void changeWidth(int);
    void changePenStyle(QString);
    void changeBrushStyle(QString);
    void firstColorActive(bool);
    void shiftActive(bool);


protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void paint(const QPoint &endPoint);


private:
    void brushTool(const QPoint &endPoint);
    void drawLine(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void fillTool(int x, int y, QRgb oldColor, QRgb newColor);

    bool modified;
    bool scribbling;
    bool shiftOn;

    bool drawCurve;

    int myPenWidth;
    QImage image;
    QImage copyImage;

    QPoint lastPoint;
    QPoint c1,c2,cEndPoint;

    QColor penColor;
    Qt::PenStyle penStyle;
    QColor brushColor;
    Qt::BrushStyle brushStyle;
    QString drawableObj;

    QBrush brush;
    QPen pen;
    bool firstColActive;
    Qt::MouseButton button;

};

#endif // PAINTAREA_H



