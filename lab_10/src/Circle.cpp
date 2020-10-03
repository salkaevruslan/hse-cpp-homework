#include "Circle.hpp"
#include <string.h>

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y) {
    id_ = id;
    x_mid_ = x;
    y_mid_ = y;
    radius_ = radius;
    label_ = new char[strlen(label) + 1];
    strcpy(label_, label);
}

Circle::~Circle() {
    delete[] label_;
}

bool Circle::is_inside(int x, int y) const {
    return (x - x_mid_) * (x - x_mid_) + (y - y_mid_) * (y - y_mid_) <= radius_ * radius_;
}

void Circle::zoom(int factor) {
    radius_ *= factor;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id_, x_mid_, y_mid_, radius_, label_);
}


