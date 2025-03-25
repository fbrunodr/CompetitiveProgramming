// see https://open.kattis.com/problems/pointinpolygon
// latest submission: https://open.kattis.com/submissions/16969473

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

        int queries; cin >> queries;
        while(queries--){
            int x, y; cin >> x >> y;
            Point P(x, y);

            if(polygon.isOnPolygon(P))
                cout << "on\n";
            else if(polygon.isInside(P))
                cout << "in\n";
            else
                cout <<"out\n";
        }

        cin >> n;
    }

    return 0;
}
