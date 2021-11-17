#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cassert>
#include <utility>
#include <vector>

class Position;
class Vector{
private:
    int x_, y_;
public:
    Vector(int x,int y):x_(x), y_(y){}
    explicit Vector(const Position &position);
    Vector(const Vector &v) = default;;
    Vector(Vector&& v) noexcept :x_(v.x_), y_(v.y_){};
    Vector& operator =(Vector&& v) noexcept {
        x_ = v.x_;
        y_ = v.y_;
        return *this;
    }
    Vector& operator =(const Vector& v)= default;
    int x() const{ return x_; }
    int y() const{ return y_; }
    Vector& operator +=(const Vector&);
    Vector reflection() const;
    bool operator ==(const Vector&) const;
};


class Position{
private:
    int x_, y_;
public:
    Position(int x,int y):x_(x), y_(y){}
    explicit Position(const Vector& v);
    Position(const Position &p) = default;;
    Position(Position&& p) noexcept :x_(p.x_), y_(p.y_){};
    Position& operator =(Position&& p) noexcept {
        x_ = p.x_;
        y_ = p.y_;
        return *this;
    }
    Position& operator =(const Position& p)= default;
    int x() const{ return x_; }
    int y() const{ return y_; }
    Position& operator +=(const Vector&);
    Position reflection() const;
    bool operator ==(const Position&) const;
    static const Position& origin(){
        static Position origin_(0,0);
        return origin_;
    };
};

class Rectangle{
private:
    int height_, width_;
    Position pos_;
public:
    Rectangle(int width, int height, Position low): width_(width), height_(height), pos_(std::move(low)){
        assert(width > 0 && height > 0);
    }
    Rectangle(int width, int height): Rectangle(width, height, Position::origin()){}
    Rectangle(const Rectangle &r) = default;
    Rectangle(Rectangle&& r) noexcept:width_(r.width_), height_(r.height_), pos_(std::move(r.pos_)){};
    Rectangle& operator =(Rectangle&& r) noexcept {
        height_ = r.height_;
        width_ = r.width_;
        pos_ = std::move(r.pos_);
        return *this;
    }
    Rectangle& operator =(const Rectangle& r)= default;
    int height() const { return height_;};
    int width() const { return width_;};
    const Position& pos() const { return pos_;};
    Rectangle& operator +=(const Vector&);
    Rectangle reflection() const;
    bool operator ==(const Rectangle&) const;
    int area() const { return height_* width_;};
};

class Rectangles {
private:
    size_t size_;
    std::vector<Rectangle> recs_;
public:
    Rectangles() :recs_({}), size_(0) {};
    Rectangles(const std::initializer_list<Rectangle> &arr):recs_(arr), size_(arr.size()){
    };
    Rectangles(const Rectangles& recs): size_(recs.size()) {
        for (int i = 0; i < recs.size(); i++)
            recs_.emplace_back(recs[i]);
    };
    Rectangles(Rectangles&& recs) noexcept : size_(recs.size_), recs_(std::move(recs.recs_)) {}
    Rectangles& operator =(Rectangles&& r) noexcept {
        size_ = r.size_;
        recs_ = std::move(r.recs_);
        return *this;
    }

    size_t size() const { return size_; };

    Rectangles& operator =(const Rectangles&) = default;
    Rectangles& operator +=(const Vector&);
    bool operator ==(const Rectangles&) const;
    const Rectangle& operator[](size_t) const;
    Rectangle& operator[](size_t);

};

Position operator +(const Position&, const Vector&);
Position operator +(const Vector&,const Position&);
Vector operator+(const Vector&, const Vector&);
Rectangle operator +(const Rectangle&, const Vector&);
Rectangle operator +(const Vector&, const Rectangle&);
Rectangles operator +(Rectangles, const Vector&);
Rectangles operator +(const Vector&, Rectangles);


Rectangle merge_horizontally(const Rectangle&, const Rectangle&);
Rectangle merge_vertically(const Rectangle&, const Rectangle&);
Rectangle merge_all(const Rectangles&);

#endif //GEOMETRY_H