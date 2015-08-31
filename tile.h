#ifndef TILE_H
#define TILE_H


class Tile
{
public:
    Tile();
    Tile(const Tile& t);
    Tile(int value, bool status);

    int value() const;
    bool status() const;

private:
    int _value;
    bool _status;
};

#endif // TILE_H
