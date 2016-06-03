#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QWidget>
#include <vector>

#include "palette.h"
#include "paintarea.h"

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
    void on_allButtons_clicked();
    void blockSettings(bool penBoxBlocked, bool brushBoxBlocked, bool sliderBlocked);

public slots:

signals:
    void clicked(int x);
    void ShiftOn(bool);
    void CtrlOn(bool);

private:
    Ui::MainWindow *ui;
    QScrollArea* view;
    PaintArea *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    std::vector <QPushButton*> allButtons;
    Palette *palette;
    QToolBar *mToolbar;
    QSlider *slider;
    QLabel* sliderLabel;
    QComboBox *penPattern;
    QComboBox *brushPattern;

    QVBoxLayout *createToolsGroup();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
