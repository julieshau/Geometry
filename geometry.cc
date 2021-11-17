#include "geometry.h"

Position::Position(const Vector& v):x_(v.x()), y_(v.y()){}

Position operator +(const Position& p, const Vector& v){
    return std::move(Position(p) += v);
}

Position operator +(const Vector& v,const Position& p){
    return p + v;
}

Position& Position::operator+= (const Vector& v){
    x_ += v.x();
    y_ += v.y();
    return *this;
}

bool Position::operator ==(const Position& right) const{
    return (x_ == right.x() && y_ == right.y());
}

Position Position::reflection() const {
    return {y_, x_};
}

Vector::Vector(const Position &position):x_(position.x()), y_(position.y()){}

bool Vector::operator==(const Vector& right) const{
    return (x_ == right.x_ && y_ == right.y_);
}

Vector& Vector::operator +=(const Vector& v){
    x_ += v.x_;
    y_ += v.y_;
    return *this;
}

Vector operator+(const Vector& left, const Vector& right){
    return std::move(Vector(left) += right);
}

Vector Vector::reflection() const {
    return {y_, x_};
}

Rectangle& Rectangle::operator+=(const Vector & v) {
    pos_+= v;
    return *this;
}

Rectangle Rectangle::reflection() const {
    return {height_, width_, pos_.reflection()};
}

bool Rectangle::operator==(const Rectangle& right) const{
    return (width_ == right.width_ && height_ == right.height_ && pos_ == right.pos_);
}

Rectangle operator +(const Rectangle& r, const Vector& v){
    return std::move(Rectangle(r) += v);
}

Rectangle operator +(const Vector& v, const Rectangle& r){
    return r + v;
}

const Rectangle& Rectangles::operator[](size_t it) const{
    assert(it < size_);
    return recs_[it];
}

Rectangle& Rectangles::operator[](size_t it){
    assert(it < size_);
    return recs_[it];
}

Rectangles& Rectangles::operator +=(const Vector& v) {
    for (int i = 0; i < size_; i++)
        recs_[i] += v;
    return *this;
}

bool Rectangles::operator==(const Rectangles& rhs) const{
    return recs_ == rhs.recs_;
}

Rectangles operator+(Rectangles rect, const Vector& v)
{
    rect += v;
    return rect;
}

Rectangles operator+(const Vector& v, Rectangles rect) {
    return std::move(rect) + v;
}

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2){
    assert(rect1.height() == rect2.height() && rect1.pos().x() + rect1.width() == rect2.pos().x() && rect1.pos().y() == rect2.pos().y());
    return {rect1.width()+rect2.width(), rect1.height(), rect1.pos()};
}

Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2){
    assert(rect1.width() == rect2.width() && rect1.pos().y() + rect1.height() == rect2.pos().y() && rect1.pos().x() == rect2.pos().x());
    return {rect1.width(), rect1.height() + rect2.height(), rect1.pos()};
}

Rectangle merge_all(const Rectangles& r) {
    assert(r.size() != 0);
    if (r.size() == 1) return r[0];
    Rectangle ret = r[0];
    for (int i = 1; i < r.size(); i++)
    {
        if (ret.height() == r[i].height() && ret.pos().x() + ret.width() == r[i].pos().x()) {
            ret = merge_vertically(ret, r[i]);
        }
        else {
            ret = merge_horizontally(ret, r[i]);
        }
    }
    return ret;
}

