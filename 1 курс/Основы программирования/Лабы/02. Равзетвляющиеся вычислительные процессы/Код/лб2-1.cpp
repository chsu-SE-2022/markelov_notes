#include <iostream>
using namespace std;

int main() {
    int h, m, s;
    cout << "Enter hours: "; cin >> h;
    cout << "Enter minutes: "; cin >> m;
    cout << "Enter seconds: "; cin >> s;
    if (h < 24 && m < 60 && s < 60 && h >= 0 && m >= 0 && s >= 0) {
        if (s >= 30) m++;
        if (m == 60) {
            h++;
            m = 0;
        }
        if (h == 24) h = 0;
        if (m >= 10) cout << h << ":" << m << endl;
        else cout << h << ":0" << m << endl;
        if (m >= 30) h++;
        cout << h << endl;
    }
    else cout << "Error!" << endl;

    system("pause");
    return 0;
    }