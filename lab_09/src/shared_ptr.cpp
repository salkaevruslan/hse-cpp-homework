#include "shared_ptr.hpp"

shared_ptr::shared_ptr(Matrix *obj) {
    if (obj != nullptr)
        storage_ = new Storage(obj);
    else
        storage_ = nullptr;
}

shared_ptr::shared_ptr(const shared_ptr &other) {
    storage_ = other.storage_;
    increase_counter();
}

shared_ptr &shared_ptr::operator=(shared_ptr other) {
    decrease_counter();
    storage_ = other.storage_;
    increase_counter();
    return *this;
}

shared_ptr::~shared_ptr() {
    decrease_counter();
}

bool shared_ptr::isNull() const {
    return (storage_ == nullptr);
}

Matrix *shared_ptr::ptr() const {
    if (isNull())
        return nullptr;
    else
        return storage_->getObject();
}

void shared_ptr::reset(Matrix *obj) {
    decrease_counter();
    if (obj != nullptr)
        storage_ = new Storage(obj);
    else
        storage_ = nullptr;
}

Matrix *shared_ptr::operator->() const {
    return ptr();
}

Matrix &shared_ptr::operator*() const {
    return *ptr();
}

shared_ptr::Storage::Storage(Matrix *mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ++ref_count_;
}

void shared_ptr::Storage::decr() {
    --ref_count_;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix *shared_ptr::Storage::getObject() const {
    return data_;
}

void shared_ptr::decrease_counter() {
    if (!isNull()) {
        storage_->decr();
        if (storage_->getCounter() == 0)
            delete storage_;
    }
}

void shared_ptr::increase_counter() {
    if (!isNull())
        storage_->incr();
}
