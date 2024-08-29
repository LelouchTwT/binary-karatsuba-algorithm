#include <iostream>
#include <valarray>

using namespace std;

string add(string x, string y) {
    string result;
    int n = (int) x.size();
    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        int xBit = x[i] - '0';
        int yBit = y[i] - '0';

        int sum = (xBit ^ yBit ^ carry);

        result.insert(result.begin(), (char) (sum + '0'));

        carry = (xBit & yBit) | (xBit & carry) | (yBit & carry);
    }

    if (carry) {
        result.insert(result.begin(), '1');
    }

    return result;
}

int makeEqualLength(string &x, string &y) {
    int n = (int) max(x.size(), y.size());

    while (x.size() < n) x.insert(x.begin(), '0');
    while (y.size() < n) y.insert(y.begin(), '0');

    return n;
}

string karatsuba(string x, string y) {
    int n = makeEqualLength(x, y);

    if (n == 0) return "0";

    int fh = n / 2;
    int sh = (n - fh);

    string xR = x.substr(fh, sh);
    string xL = x.substr(0, fh);

    string yR = y.substr(fh, sh);
    string yL = y.substr(0, fh);

    string p1 = karatsuba(xR,yR);
    string p2 = karatsuba(xL,yL);
    string p3 = karatsuba(add(xR, xL), add(yR,yL));

    return p1;
}

int main(int argc, char *argv[]) {
    if (argc > 3) {
        cout << "Too many arguments" << endl;
        return 1;
    } else if (argc < 3) {
        cout << "Too few arguments" << endl;
        return 1;
    }
    karatsuba(argv[1], argv[2]);
    return 0;
}