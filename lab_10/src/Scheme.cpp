#include "Scheme.hpp"

Scheme::Scheme(int capacity) {
    figures_ = new Figure *[capacity];
    number_of_elements_ = 0;
}

Scheme::~Scheme() {
    for (int index = 0; index < number_of_elements_; ++index) {
        delete figures_[index];
    }
    delete[] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[number_of_elements_] = fg;
    ++number_of_elements_;
}

void Scheme::remove_figure(int id) {
    int index = find_figure_by_id(id);
    if (index < number_of_elements_) {
        delete figures_[index];
        figures_[index] = nullptr;
        int index2 = index + 1;
        while (index2 < number_of_elements_) {
            figures_[index] = figures_[index2];
            figures_[index2] = nullptr;
            index = index2;
            ++index2;
        }
        --number_of_elements_;
    }
}

void Scheme::zoom_figure(int id, int factor) {
    int index = find_figure_by_id(id);
    figures_[index]->zoom(factor);
}

void Scheme::move(int id, int new_x, int new_y) {
    int index = find_figure_by_id(id);
    figures_[index]->move(new_x, new_y);
}

void Scheme::print_all_figures() {
    for (int index = 0; index < number_of_elements_; ++index) {
        figures_[index]->print();
    }
}

int Scheme::find_figure_by_id(int id) {
    int index = 0;
    while (index < number_of_elements_ && figures_[index]->getId() != id)
        ++index;
    return index;
}

Figure *Scheme::is_inside_figure(int x, int y) {
    Figure *result = nullptr;
    int index = 0;
    while (index < number_of_elements_) {
        if (figures_[index]->is_inside(x, y)) {
            result = figures_[index];
            break;
        }
        ++index;
    }
    return result;
}



