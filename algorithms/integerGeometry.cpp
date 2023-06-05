#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Point{
    int x, y;

    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    i64 sqrMod() const { return (i64)x*x + (i64)y*y; }

    bool operator == (Point other) const {
        return x == other.x && y == other.y;
    }

    bool operator != (Point other) const {
        return !this->operator==(other);
    }
};

struct Vec{
    int x, y;

    Vec() {}
    
    Vec(int _x, int _y) : x(_x), y(_y) {}

    Vec(Point A, Point B){
        x = B.x - A.x;
        y = B.y - A.y;
    }

    i64 sqrMod() const { return (i64)x*x + (i64)y*y; }

    i64 cross(Vec other) const {
        return (i64)x * other.y - (i64)y * other.x;
    }

    i64 dot(Vec other) const {
        return (i64)x * other.x + (i64)y * other.y;
    }

    bool operator == (Vec other) const {
        return x == other.x && y == other.y;
    }

    bool operator != (Vec other) const {
        return !this->operator==(other);
    }

    // for sorting acording to angle
    bool operator < (Vec other) const {
        if(top() != other.top())
            return top();
        auto css = cross(other);
        if(css == 0)
            return sqrMod() < other.sqrMod();
        return css > 0;
    }

    bool operator > (Vec other) const {
        return !operator==(other) && !operator<(other);
    }

    private:
    bool top() const {
        return y > 0 || (y == 0 && x > 0);
    }
};

class Angle{
    // cosLike, sinLike
    Vec tan2;

    public:
    Angle() {}

    Angle(Vec OA, Vec OB){
        if(OA.x == 0 && OA.y == 0)
            exit(4278);
        if(OB.x == 0 && OB.y == 0)
            exit(4278);
        
        i64 dot = OA.dot(OB);
        i64 cross = OA.cross(OB);
        i64 d = gcd(dot, cross);
        dot /= d;
        cross /= d;

        if(dot > INT_MAX || cross > INT_MAX)
            exit(7140);

        tan2 = Vec(dot, cross);
    }

    Angle(Point A, Point O, Point B) : Angle(Vec(O,A), Vec(O,B)) {}

    bool operator == (Angle other) const {
        return tan2 == other.tan2;
    }

    bool operator != (Angle other) const {
        return !operator==(other);
    }

    bool operator < (Angle other) const {
        return tan2 < other.tan2;
    }

    bool operator > (Angle other) const {
        return !operator==(other) && !operator<(other);
    }
};
