#pragma once

struct Coords {
    int x;
    int y;

    bool operator == (const Coords& other) const {
        return (x == other.x && y == other.y);
    }
};