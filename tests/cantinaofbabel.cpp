// see https://open.kattis.com/problems/cantinaofbabel

#include "../algorithms/GraphCompression.cpp"

int main(){
    using vi = vector<int>;
    int N; cin >> N;

    vector<string> spokenLanguage(N);
    vector<unordered_set<string>> addLanguages(N);

    string garbage; getline(cin, garbage);
    for(int u = 0; u < N; u++){
        string input;
        getline(cin, input);
        stringstream inputStream(input);

        string name; inputStream >> name;
        inputStream >> spokenLanguage[u];

        string addLanguage;
        while(inputStream >> addLanguage)
            addLanguages[u].insert(addLanguage);
    }

    vector<vi> AL(N);

    for(int u = 0; u < N; u++)
        for(int v = 0; v < N; v++){
            if(u == v) continue;
            auto& lang = spokenLanguage[u];
            if( (spokenLanguage[v] == lang) || addLanguages[v].count(lang) )
                AL[u].push_back(v);
        }

    GraphCompressor graphCompressor(AL);

    auto [compressedNode, AL_compressed] = graphCompressor.compress();
    int numSCC = AL_compressed.size();
    vi sizes(numSCC, 0);

    for(int u = 0; u < N; u++)
        sizes[compressedNode[u]]++;

    int bigger = -1;
    for(int i = 0; i < numSCC; i++)
        bigger = max(bigger, sizes[i]);

    cout << N - bigger << endl;

    return 0;
}
