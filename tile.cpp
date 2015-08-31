#include "tile.h"

Tile::Tile()
{

}

Tile::Tile(const Tile &t) : _value(t.value()), _status(t.status())
{

}

Tile::Tile(int value, bool status) : _value(value), _status(status)
{

}

int Tile::value() const
{
    return _value;
}
bool Tile::status() const
{
    return _status;
}

