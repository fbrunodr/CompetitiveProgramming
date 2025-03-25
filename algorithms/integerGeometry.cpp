#ifndef FBRUNODR_INTEGER_GEOMETRY
#define FBRUNODR_INTEGER_GEOMETRY

#include "../header.hpp"

struct Point{
    int x, y;

    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int sqrMod() const { return x*x + y*y; }

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

    int sqrMod() const { return x*x + y*y; }

    int cross(Vec other) const {
        return x * other.y - y * other.x;
    }

    int dot(Vec other) const {
        return x * other.x + y * other.y;
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
        
        int dot = OA.dot(OB);
        int cross = OA.cross(OB);
        int d = gcd(dot, cross);
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
        int crossP = AB.cross(Vec(A, P));
        if(crossP == 0)
            return false;
        int crossQ = AB.cross(Vec(A, Q));
        if(crossQ == 0)
            return false;
        return std::signbit(crossP) != std::signbit(crossQ);
    }

    bool makeCross(const Segment& other) const {
        return diffSideNotOnLine(other.A, other.B) && other.diffSideNotOnLine(A, B);
    }
};

class Polygon{
    private:
    vec<Point> closeLoop(bool leaveRepeated = false) const {
        auto polygon = points;
        polygon.push_back(polygon.front());
        if(leaveRepeated)
            return polygon;
        int n = unique(polygon.begin(), polygon.end()) - polygon.begin();
        polygon.resize(n);
        return polygon;
    }

    public:
    vec<Point> points;

    Polygon() {}

    Polygon(const vec<Point>& _points) : points(_points) {}

    void push_back(const Point& P){
        points.push_back(P);
    }

    bool isOnPolygon(const Point& P) const {
        for(auto& point : points)
            if(P == point)
                return true;
        auto polygon = closeLoop();
        for(int i = 1; i < polygon.size(); i++){
            auto side = Segment(polygon[i-1], polygon[i]);
            if(side.isBetween(P))
                return true;
        }

        return false;
    }

    bool isInside(const Point& P) const {
        auto polygon = closeLoop();
        if(polygon.size() <= 3) // first is repeated
            return false;
        if(isOnPolygon(P))
            return false;
        Point surelyOutside = P;
        int delta = 1e9 + 5;
        surelyOutside.x += delta;
        surelyOutside.y += delta + 1;
        Segment rayToOutside(P, surelyOutside);
        int crosses = 0;
        for(int i = 1; i < polygon.size(); i++)
            if(rayToOutside.makeCross(Segment(polygon[i-1], polygon[i])))
                crosses++;
        return crosses & 1;
    }

    bool isConvex(){
        auto polygon = closeLoop();
        int n = (int)polygon.size();
        // a point/sz=2 or a line/sz=3 is not convex  
        if (n <= 3) return false;

        auto ccw = [](const Point& A, const Point& O, const Point& B) {
            Vec AO = Vec(A, O);
            Vec AB = Vec(A, B);
            int cross = AO.cross(AB);
            return cross >= 0;
        };

        auto& P = polygon;
        bool firstTurn = ccw(P[0], P[1], P[2]);        // remember one result,
        for (int i = 1; i < n-1; ++i)                  // compare with the others
            if (ccw(P[i], P[i+1], P[(i+2) == n ? 1 : i+2]) != firstTurn)
                return false;                          // different -> concave
        return true;                                   // otherwise -> convex
    }

    // Convex Hull Andrew
    Polygon convexHull(bool leaveNonNecessary = false) const {
        auto polygon = closeLoop(leaveNonNecessary);
        int n = polygon.size(), k = 0;
        vec<Point> H(2*n);
        sort(polygon.begin(), polygon.end());

        auto ccw = [leaveNonNecessary](const Point& A, const Point& O, const Point& B) {
            Vec AO = Vec(A, O);
            Vec AB = Vec(A, B);
            int cross = AO.cross(AB);
            if(leaveNonNecessary)
                return cross >= 0;
            return cross > 0;
        };

        for (int i = 0; i < n; ++i) {
            while ((k >= 2) && !ccw(H[k-2], H[k-1], polygon[i])) --k;
            H[k++] = polygon[i];
        }
        for (int i = n-2, t = k+1; i >= 0; --i) {       // build upper hull
            while ((k >= t) && !ccw(H[k-2], H[k-1], polygon[i])) --k;
            H[k++] = polygon[i];
        }

        H.resize(k);
        if(H.size() > 1)
            H.pop_back();
        return Polygon(H);
    }
};


#endif
