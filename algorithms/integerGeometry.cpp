#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Point{
    int x, y;

    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    i64 sqrMod() const { return (i64)x*x + (i64)y*y; }

    bool operator == (const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator != (const Point& other) const {
        return !this->operator==(other);
    }

    // Points are ordered from left to right
    // if tied, from bottom to top
    bool operator < (const Point& other) const {
        if(operator==(other))
            return false;
        if(x == other.x)
            return y < other.y;
        return x < other.x;
    }

    bool operator > (const Point& other) const {
        return !operator==(other) && !operator<(other);
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

    // vectors are sorted according to their angle
    bool operator < (Vec other) const {
        if(operator==(other))
            return false;
        if(x == 0 && y == 0) // (0,0) has priority
            return true;
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

class Segment{
    Point A, B;
    Vec AB;

    public:
    Segment(Point _A, Point _B) : A(_A), B(_B) {
        if(A == B)
            exit(3708);
        AB = Vec(A, B);
    }

    bool isCollinear(const Point& P) const {
        return AB.cross(Vec(A, P)) == 0;
    }

    bool isBetween(const Point& P) const {
        if(P == A)
            return false;
        if(P == B)
            return false;

        if(!isCollinear(P))
            return false;
        
        Vec AP = Vec(A, P);
        return AB.dot(AP) > 0 && AP.sqrMod() < AB.sqrMod();
    }

    bool isBetweenOrOn(const Point& P) const {
        return (P == A) || (P == B) || isBetween(P);
    }

    bool isParallel(const Segment& other) const {
        return AB.cross(other.AB) == 0;
    }

    bool isOnSameLine(const Segment& other) const {
        return isParallel(other) && isCollinear(other.A);
    }

    // remember lines are infinity
    bool doLinesCross(const Segment& other) const {
        return !isParallel(other);
    }

    bool diffSideNotOnLine(const Point& P, const Point& Q) const {
        i64 crossP = AB.cross(Vec(A, P));
        if(crossP == 0)
            return false;
        i64 crossQ = AB.cross(Vec(A, Q));
        if(crossQ == 0)
            return false;
        return signbit(crossP) != signbit(crossQ);
    }

    bool makeCross(const Segment& other) const {
        return diffSideNotOnLine(other.A, other.B) && other.diffSideNotOnLine(A, B);
    }
};

class Polygon{
    vector<Point> points;

    public:
    Polygon() {}

    Polygon(const vector<Point>& _points) : points(_points) {}

    void push_back(const Point& P){
        points.push_back(P);
    }

    bool isOnPolygon(const Point& P) const {
        for(auto& point : points)
            if(P == point)
                return true;
        auto aux = points;
        aux.push_back(aux.front());
        for(int i = 1; i < aux.size(); i++){
            if(aux[i-1] == aux[i]) continue;
            auto side = Segment(aux[i-1], aux[i]);
            if(side.isBetween(P))
                return true;
        }

        return false;
    }

    bool isInside(const Point& P) const {
        if(points.size() < 3)
            false;
        if(isOnPolygon(P))
            return false;
        Point surelyOutside = P;
        int delta = 1e9 + 5;
        surelyOutside.x += delta;
        surelyOutside.y += delta + 1;
        Segment rayToOutside(P, surelyOutside);
        auto aux = points;
        aux.push_back(aux.front());
        int crosses = 0;
        for(int i = 1; i < aux.size(); i++){
            if(aux[i-1] == aux[i])
                continue;
            if(rayToOutside.makeCross(Segment(aux[i-1], aux[i])))
                crosses++;
        }
        return crosses & 1;
    }
};
