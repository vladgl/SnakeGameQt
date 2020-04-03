#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QResizeEvent>

#include "fieldgraphicsview.h"
#include "snake.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FixedRatioLayout : public QVBoxLayout
{
    Q_OBJECT
public:
protected:
    bool hasHeightForWidth() const
    {
        return true;
    }
    int heightForWidth(int w) const
    {
        return w;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
/*    void resizeEvent(QResizeEvent* event) override
    {
        if(event->size().width() < event->size().height())
            resize(event->size().height(),event->size().height());
        if(event->size().width() > event->size().height())
            resize(event->size().width(),event->size().width());
    }*/
    bool hasHeightForWidth() const override
    {
        return true;
    }
    int heightForWidth(int w) const override
    {
        return w;
    }
private:
    Ui::MainWindow *ui;

    FieldGraphicsView* v_PlayArea;
};
#endif // MAINWINDOW_H
