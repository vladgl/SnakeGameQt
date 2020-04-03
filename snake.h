#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <type_traits>
#include <random>
#include <ctime>


struct Point
{
    Point(uint16_t px, uint16_t py) :
        x(px), y(py)
    {

    }
    uint16_t x;
    uint16_t y;
};


class Snake
{
public:
    Snake() = delete;
    Snake(uint16_t fw, uint16_t fh, uint16_t x, uint16_t y);

    bool nextStep();

    enum Direction
    {
        TOP = 0x0000010,
        BOT = 0x0000100,
        LFT = 0x0001001,
        RHT = 0x0010001
    };

    size_t size()
    {
        return _pos_x.size();
    }

    Point operator[](size_t index)
    {
        return Point(_pos_x[index], _pos_y[index]);
    }
    Point at(size_t index)
    {
        return Point(_pos_x[index], _pos_y[index]);
    }

    Point getFood()
    {
        return Point(_food_x, _food_y);
    }

    void genFood();

    void setDirection(Direction new_direction)
    {
        _new_direction = new_direction;
        _flag_ChangeDir = true;
    }

    void genTail()
    {
        _flag_GenTail = true;
    }

    void setSeed(time_t seed)
    {
        std::srand(seed);
    }

    bool isWin()
    {
        return _flag_Win;
    }

    void resetGame();
    bool checkCollision(uint16_t x, uint16_t y);
private:
    //!size of the field
    uint16_t _fw, _fh, _count, _tail_x, _tail_y, _food_x, _food_y;
    //!direction
    Direction _direction, _new_direction;
    //! positions (DOP)
    std::vector<uint16_t> _pos_x;
    std::vector<uint16_t> _pos_y;

    bool _flag_GenTail, _flag_ChangeDir, _flag_Win;
};

#endif // SNAKE_H
