#include "../dataStructures/OrderStatisticsTree.cpp"

int main(){
    using vi = vector<int>;

    vi A{3, 5, 5, 5, 6, 9, 10, 11, 12, 13, 17, 17, 19, 19, 19, 19, 20};

    FenwickTreeOST ost1(20);
    OST ost2;

    for(auto& a_i : A){
        ost1.insert(a_i);
        ost2.insert(a_i);
    }

    for(int i = 1; i <= 20; i++)
        if(ost1.orderOfKey(i) != ost2.order_of_key(i)){
            cout << "Fail" << endl;
            exit(1);
        }

    for(int i = 0; i < 11; i++)
        if(ost1.findByOrder(i) != *ost2.find_by_order(i)){
            cout << "Fails" << endl;
            exit(1);
        }

    FenwickTreeOST ost3(20, true);
    for(auto& a_i : A)
        ost3.insert(a_i);

    for(int i = 1; i <= 20; i++){
        int trueOrder = lower_bound(A.begin(), A.end(), i) - A.begin();
        if(ost3.orderOfKey(i) != trueOrder){
            cout << "Fail" << endl;
            exit(1);
        }
    }

    for(int i = 0; i < A.size(); i++)
        if(ost3.findByOrder(i) != A[i]){
            cout << "Fail" << endl;
            exit(1);
        }

    unordered_map<int, int> freq;
    for(auto& a_i : A)
        freq[a_i]++;

    FenwickTreeOST ost4(20, true);
    for(auto& [val, count] : freq)
        ost4.insertMany(val, count);

    for(int i = 1; i <= 20; i++){
        int trueOrder = lower_bound(A.begin(), A.end(), i) - A.begin();
        if(ost4.orderOfKey(i) != trueOrder){
            cout << "Fail" << endl;
            exit(1);
        }
    }

    for(int i = 0; i < A.size(); i++)
        if(ost4.findByOrder(i) != A[i]){
            cout << "Fail" << endl;
            exit(1);
        }

    // erase 4 random elements
    int toErase = 4;
    while(toErase--){
        int i = rand() % A.size();
        ost4.remove(A[i]);
        A.erase(A.begin() + i);
    }

    for(int i = 1; i <= 20; i++){
        int trueOrder = lower_bound(A.begin(), A.end(), i) - A.begin();
        if(ost4.orderOfKey(i) != trueOrder){
            cout << "Fail" << endl;
            exit(1);
        }
    }

    for(int i = 0; i < A.size(); i++)
        if(ost4.findByOrder(i) != A[i]){
            cout << "Fail" << endl;
            exit(1);
        }

    return 0;
}
