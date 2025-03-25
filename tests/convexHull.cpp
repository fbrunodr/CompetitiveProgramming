// see https://open.kattis.com/problems/convexhull
// latest submission: https://open.kattis.com/submissions/16966319

#include "../algorithms/integerGeometry.hpp"

int32_t main(){
    fastIO();

    int n; cin >> n;

    while(n){
        Polygon polygon;
        for(int i = 0; i < n; i++){
            int x, y; cin >> x >> y;
            polygon.push_back(Point(x, y));
        }

        polygon = polygon.convexHull();
        cout << polygon.points.size() << '\n';
        for(auto& point : polygon.points)
            cout << point.x << ' ' << point.y << '\n';

        cin >> n;
    }

    return 0;
}
