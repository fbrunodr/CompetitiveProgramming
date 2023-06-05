// see https://open.kattis.com/problems/convexhull

#include "../algorithms/integerGeometry.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

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
