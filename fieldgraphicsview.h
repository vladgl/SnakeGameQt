#ifndef FIELDGRAPHICSVIEW_H
#define FIELDGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QWidget>
#include <QTimer>
#include <QList>
#include <QKeyEvent>
#include <QTime>
#include <functional>
#include "snake.h"

class FieldGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    FieldGraphicsView(QWidget* parent = nullptr);
public slots:
    void nextEpoch();

protected:

    bool hasHeightForWidth() const override
    {
        return true;
    }
    int heightForWidth(int w) const override
    {
        return w;
    }
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void reDraw();
    QGraphicsRectItem* pushSnakePart(const Point& pos, bool head = false)
    {
        QGraphicsRectItem* rect_itm = new QGraphicsRectItem();
        rect_itm->setRect(QRectF(0, 0,
                         _coef_scale, _coef_scale));
        rect_itm->setPos(pos.x*_coef_scale, pos.y*_coef_scale);
        if(head)
            rect_itm->setBrush(QBrush(QColor(200, 180, 180)));
        else
            rect_itm->setBrush(QBrush(QColor(145, 162, 0)));
        rect_itm->setPen(QPen(Qt::PenStyle::NoPen));
        s_PlayArea->addItem(rect_itm);
        snakeView.push_back(rect_itm);
        return rect_itm;
    }
private:
    enum ViewState { WAT, GAM, WIN, LOS };
    QGraphicsScene*    s_PlayArea;
    QGraphicsRectItem *rect, *itm_food;
    QGraphicsSimpleTextItem *itm_score_text;
    QTimer* timer;
    Snake* snake;

    uint16_t _game_width, _game_height;
    float _coef_margin, _coef_scale, _coef_text_scale;

    QTime delay;
    uint16_t _delay_epoch, _delay_key_press;

    QList<QGraphicsRectItem*> snakeView;

    ViewState _flag_DrawState;
};

#endif // FIELDGRAPHICSVIEW_H
