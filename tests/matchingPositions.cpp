#include "../algorithms/stringUtils.cpp"

int32_t main(){
    string pattern = "hello";
    string text = "hello world! hello is a word with four letters. Say hello too, please!";
    for(int position : matching_positions(text, pattern, (char)5))
        cout << position << ' ';
    cout << endl;

    vi pattern_numbers{1, 1, 1};
    vi sequence{1, 1, 1, 1, 1, 1};
    for(int position : matching_positions(sequence, pattern_numbers, (int)1e9))
        cout << position << ' ';
    cout << endl;
    return 0;
}