#include <iostream>

using namespace std;

int main() {

    int n[10];

    for (int  i = 0; i < 10; i++)
        cin >> n[i];

    for (int i = 0; i < 10; i++) {
        if ((n[i] % 2) == 0) cout << n[i] << endl;
    }

    return 0;
}

