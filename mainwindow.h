#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QWidget>
#include <vector>

#include "paintscene.h"

enum BUTTON {ELLIPSE=0, RECTANGLE, TRIANGLE, LINE, CURVE, POLYGON};
class QGroupBox;
namespace Ui {
    class MainWindow;
    }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    //void on_Buttons_clicked(int);
    void on_allButtons_clicked();

signals:
    void clicked(int x);

private:
    Ui::MainWindow *ui;
    //QGraphicsScene *scene;
    paintScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    std::vector <QPushButton*> allButtons;


    QVBoxLayout *createToolsGroup();
    void setSettings();

   // void mousePressEvent(QGraphicsSceneMouseEvent *event);
   // void mouseMoveEvent(QGraphicsSceneMouseEvent * event);


};

#endif // MAINWINDOW_H
