#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    width_ = width;
    height_ = height;
}

bool Rectangle::is_inside(int x, int y) const {
    return (x <= x_mid_ + width_ / 2) && (x >= x_mid_ - width_ / 2) &&
           (y <= y_mid_ + height_ / 2) && (y >= y_mid_ - height_ / 2);
}

void Rectangle::zoom(int factor) {
    width_ *= factor;
    height_ *= factor;
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id_, x_mid_, y_mid_, width_, height_);
}
