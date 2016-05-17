#ifndef PALETTEBUTTON_H
#define PALETTEBUTTON_H

#include <QToolButton>

class paletteButton : public QToolButton
{
    Q_OBJECT
public:
    paletteButton(const QColor &color);

signals:
    void colorPicked();

private:
    QColor mColor;

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // PALETTEBUTTON_H
