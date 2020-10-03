#include "Figure.hpp"

Figure::Figure(int id, int x, int y) {
    id_ = id;
    x_mid_ = x;
    y_mid_ = y;
}

void Figure::move(int new_x, int new_y) {
    x_mid_ = new_x;
    y_mid_ = new_y;
}

int Figure::getId() {
    return id_;
}

