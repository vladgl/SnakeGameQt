#include "fieldgraphicsview.h"

/** Color scheme: https://colorscheme.ru/#3i409w0w0w0w0"*/
FieldGraphicsView::FieldGraphicsView(QWidget* parent) :
    QGraphicsView(parent)
{
    QSizePolicy size_policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    size_policy.setHeightForWidth(true);
    this->setSizePolicy(size_policy);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumSize(QSize(128, 128));

    _delay_epoch = 100;
    _delay_key_press = 0;

    _game_width = 50;
    _game_height = 50;

    _coef_margin = 1.05f;
    _coef_scale = 10.0f;

    /** Create **/
    timer = new QTimer();
    snake = new Snake(_game_width, _game_height, 9, 0);

    s_PlayArea = new QGraphicsScene();
    rect = new QGraphicsRectItem();
    itm_food = new QGraphicsRectItem();

    /** Setup **/
    this->setBackgroundBrush(QBrush(QColor(0, 99, 99)));
    s_PlayArea->setBackgroundBrush(QBrush(QColor(0, 99, 99)));

    QPen pen(QColor(166, 75, 0));
    pen.setWidth(1);
    rect->setPen(pen);

    itm_food->setPen(Qt::PenStyle::NoPen);
    itm_food->setBrush(QBrush(QColor(90, 1, 109)));

    s_PlayArea->setSceneRect(0, 0,
                             _game_width*_coef_scale,
                             _game_height*_coef_scale);
    QRectF rSz(0, 0,
               s_PlayArea->width(),
               s_PlayArea->height());
    rect->setRect(rSz);
    rect->setPos(0, 0);

    itm_food->setRect(0, 0, _coef_scale, _coef_scale);
    itm_food->setPos(snake->getFood().x * _coef_scale,
                     snake->getFood().y * _coef_scale);

    /** Connect **/
    connect(timer, &QTimer::timeout, this, &FieldGraphicsView::nextEpoch);

    /** Place **/
    s_PlayArea->addItem(rect);
    s_PlayArea->addItem(itm_food);

    pushSnakePart(snake->at(0), true);

    this->setScene(s_PlayArea);

    /** Start **/
    _flag_DrawState = GAM;
    timer->start(_delay_epoch);
    delay.start();
}

void FieldGraphicsView::nextEpoch()
{
    if(!snake->nextStep())
    {
        if(!snake->isWin())
        {
            snake->resetGame();
            for(auto el : snakeView)
                delete el;
            snakeView.clear();
            pushSnakePart(snake->at(0), true);
        }
        else _flag_DrawState = ViewState::WIN;
    }
    reDraw();
}


void FieldGraphicsView::reDraw()
{
    switch(_flag_DrawState)
    {
    case ViewState::GAM:
        itm_food->setPos(snake->getFood().x*_coef_scale,
                         snake->getFood().y*_coef_scale);
        for(size_t i = 0; i<snakeView.size(); ++i)
        {
            snakeView[i]->setPos(snake->at(i).x*_coef_scale, snake->at(i).y*_coef_scale);
        }

        if(snakeView.size() < snake->size())
        {
            for(size_t i = snakeView.size(); i < snake->size(); ++i)
                pushSnakePart(snake->at(i));
        }
        break;
    case ViewState::WIN:
        itm_food->hide();

        if(snakeView.size() == 0)
            _flag_DrawState = ViewState::WAT;
        else
        {
            delete snakeView[snakeView.size() - 1];
            snakeView.erase(snakeView.begin() + snakeView.size() - 1);
        }
        break;

    case ViewState::WAT:

        break;

    }
}

void FieldGraphicsView::keyPressEvent(QKeyEvent *event)
{

    if(delay.elapsed() > _delay_key_press)
    {
        switch(event->key())
        {
        case Qt::Key::Key_Up:
        case Qt::Key::Key_W:
            snake->setDirection(Snake::BOT);
            break;
        case Qt::Key::Key_Down:
        case Qt::Key::Key_S:
            snake->setDirection(Snake::TOP);
            break;
        case Qt::Key::Key_Left:
        case Qt::Key::Key_A:
            snake->setDirection(Snake::LFT);
            break;
        case Qt::Key::Key_Right:
        case Qt::Key::Key_D:
            snake->setDirection(Snake::RHT);
            break;
        case Qt::Key::Key_Space:
            snake->genTail();
            break;
        default:
            break;
        }
        delay.restart();
    }
}

void FieldGraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    QRectF rc = QRectF(0, 0,
                       rect->rect().width()*_coef_margin,
                       rect->rect().height()*_coef_margin);
    this->fitInView(rc, Qt::KeepAspectRatio);
}
