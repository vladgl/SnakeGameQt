#include "snake.h"
#include <algorithm>
#include <set>
#include <QDebug>
Snake::Snake(uint16_t fw, uint16_t fh, uint16_t x, uint16_t y,
             std::vector<int16_t> chanks_x,
             std::vector<int16_t> chanks_y,
             std::vector<int16_t> chank_indexes) :
    _fw(fw), _fh(fh), _init_x(x), _init_y(y),
    _chank_indexes(chank_indexes), _chanks_x(chanks_x), _chanks_y(chanks_y)

{
    _count = _fw*_fh;
    _init_x = (_fw + _init_x) % _fw;
    _init_y = (_fh + _init_y) % _fh;
    _pos_x.push_back(_init_x);
    _pos_y.push_back(_init_y);
    _direction = TOP;
    _flag_GenTail = true;
    _flag_ChangeDir = false;
    _flag_Win = false;
    genFood();
    std::srand(std::time(nullptr));
}

void Snake::resetGame()
{
    _pos_x.clear();
    _pos_y.clear();
    _pos_x.push_back(_init_x);
    _pos_y.push_back(_init_y);
    _flag_GenTail = true;
    _flag_ChangeDir = false;
    _flag_Win = false;
    genFood();
}

void Snake::genFood()
{
    // simple food generetion
    bool not_in = true;
    for(size_t i = 0; i < 3; ++i)
    {
        not_in = true;
        _food_x = std::rand() % _fw;
        _food_y = std::rand() % _fh;
        for(size_t i = 0; i < _pos_x.size(); ++i)
        {
            if(_pos_x[i] == _food_x && _pos_y[i] == _food_y)
            {
                not_in = false;
                break;
            }
        }
        for(size_t i = 0; i<_chanks_x.size(); ++i)
        {
            if(_chanks_x[i] == _food_x && _chanks_y[i] == _food_y)
            {
                not_in = false;
                break;
            }
        }
        if(not_in)
            return;
    }
    // in bad case
    std::vector<Point> empty_space;
    std::set<size_t> remove_id;
    for(uint16_t j = 0; j < _fh; ++j)
    {
        for(uint16_t i = 0; i < _fw; ++i)
        {
            empty_space.push_back(Point(i, j));
        }
    }
    for(size_t i = 0; i < _pos_x.size(); ++i)
    {
        remove_id.insert(_pos_x[i] + _pos_y[i]*_fw);
    }
    for(size_t i = 0; i < _chanks_x.size(); ++i)
    {
        remove_id.insert(_chanks_x[i] + _chanks_y[i]*_fw);
    }
    for(auto it = remove_id.rbegin(); it != remove_id.rend(); ++it)
    {
        empty_space.erase(empty_space.begin() + (*it));
    }

    if(empty_space.size() != 0)
    {
        uint16_t index = rand() % empty_space.size();
        _food_x = empty_space[index].x;
        _food_y = empty_space[index].y;
    }
}


bool Snake::nextStep()
{
    if(_flag_ChangeDir)
    {
        if((_direction ^ _new_direction) % 2)
            _direction = _new_direction;
        _flag_ChangeDir = false;
    }
    if(_flag_GenTail)
    {
        _tail_x = _pos_x[_pos_x.size()-1];
        _tail_y = _pos_y[_pos_y.size()-1];
    }
    for(size_t i = _pos_x.size() - 1; i >= 1; --i)
    {
        _pos_x[i] = _pos_x[i-1];
        _pos_y[i] = _pos_y[i-1];
    }

    if(_flag_GenTail)
    {
        _pos_x.push_back(_tail_x);
        _pos_y.push_back(_tail_y);
        _flag_GenTail = false;
    }
    switch(_direction)
    {
    case TOP:
        _pos_y[0] = _pos_y[0] + 1;
        if(_pos_y[0] >= _fh)
            return false;
        break;
    case BOT:
        _pos_y[0] = _pos_y[0] - 1;
        if(_pos_y[0] < 0)
            return false;
        break;
    case LFT:
        _pos_x[0] = _pos_x[0] - 1;
        if(_pos_x[0] < 0)
            return false;
        break;
    case RHT:
        _pos_x[0] = _pos_x[0] + 1;
        if(_pos_x[0] >= _fw)
            return false;
        break;
    }

    //collision
    for(size_t i = 1; i < _pos_x.size(); ++i)
    {
        if(_pos_x[0] == _pos_x[i] && _pos_y[0] == _pos_y[i])
            return false;
    }


    for(size_t i = 0; i < _chanks_x.size(); ++i)
    {
        if(_pos_x[0] == _chanks_x[i] && _pos_y[0] == _chanks_y[i])
            return false;
    }



    //snake ate food
    if(_pos_x[0] == _food_x && _pos_y[0] == _food_y)
    {
        genTail();
        genFood();
    }

    //win
    if(_pos_x.size() == _count)
    {
        _flag_Win = true;
        return false;
    }


    return true;
}
