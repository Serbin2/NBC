
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    int n = 0;
    cin >> n;
    cin.ignore();
    string str;
    getline(cin, str);
    istringstream iss(str);
    int max = -1000;
    for (int i = 0; i < n; i++)
    {
        int comp = 0;
        iss >> comp;;
        if (comp > max)
        {
            max = comp;
        }
    }
    cout << max;
    return 0;
}