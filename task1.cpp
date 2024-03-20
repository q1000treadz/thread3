#include <iostream>
#include <string> 
#include <fstream> 
#include <unordered_map> 
#include<algorithm>
using namespace std;

char tolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    if (in <= 'Я' && in >= 'А')
        return in - ('Я' - 'я');
    return in;
}
bool cmp(pair<string, int>& a, pair<string, int>& b)
{
    return a.second > b.second;
}
void sortMap(unordered_map<string, int>& M)
{
    vector<pair<string, int> > A;
    for (auto& it : M) {
        A.push_back(it);
    }

    sort(A.begin(), A.end(), cmp);

    for (auto& it : A) {
        if (it.second > 5) {
            cout << it.first << ' '
                << it.second << endl;
        }
    }
}
int main() {
    setlocale(LC_ALL, "rus");
    string all = "";
    ifstream file("data.txt");
    unordered_map<string, int> word_map;
    string word;
    string s ="";
    #pragma omp parallel for
    while (file >> word) {
    #pragma omp critical 
        {
            for (int i = 0; i < word.size(); i++) {
                char t = tolower(word[i]);
                if (t >= 'а' && t <= 'я' || t >= 'a' && t <= 'z') {
                    s += t;
                }
            }
            word_map[s]++;
            s = "";
        }
    }
    cout << "Все слова, который встречаются более 5 раз: " << endl;
    sortMap(word_map);
    file.close(); 

    return 0;
}