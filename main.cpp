#include <iostream>
#include <string>

using namespace std;

string add(string x, string y) {
    string result;
    int n = max(x.size(), y.size());
    int carry = 0;

    while (x.size() < n) x.insert(x.begin(), '0');
    while (y.size() < n) y.insert(y.begin(), '0');

    for (int i = n - 1; i >= 0; i--) {
        int xBit = x[i] - '0';
        int yBit = y[i] - '0';

        int sum = xBit + yBit + carry;
        result.insert(result.begin(), (char)(sum % 2 + '0'));
        carry = sum / 2;
    }

    if (carry) {
        result.insert(result.begin(), '1');
    }

    return result;
}

string subtract(string x, string y) {
    string result;
    int n = max(x.size(), y.size());
    int borrow = 0;

    while (x.size() < n) x.insert(x.begin(), '0');
    while (y.size() < n) y.insert(y.begin(), '0');

    for (int i = n - 1; i >= 0; i--) {
        int xBit = x[i] - '0';
        int yBit = y[i] - '0';

        int diff = xBit - yBit - borrow;
        if (diff >= 0) {
            result.insert(result.begin(), (char)(diff + '0'));
            borrow = 0;
        } else {
            result.insert(result.begin(), (char)(diff + 2 + '0'));
            borrow = 1;
        }
    }

    result.erase(0, result.find_first_not_of('0'));
    return result.empty() ? "0" : result;
}

string shiftLeft(string x, int shift) {
    for (int i = 0; i < shift; i++) {
        x.push_back('0');
    }
    return x;
}

int makeEqualLength(string &x, string &y) {
    int n = max(x.size(), y.size());
    while (x.size() < n) x.insert(x.begin(), '0');
    while (y.size() < n) y.insert(y.begin(), '0');
    return n;
}

string karatsuba(string x, string y) {
    int n = makeEqualLength(x, y);

    if (n == 1) {
        return to_string((x[0] - '0') * (y[0] - '0'));
    }

    int fh = n / 2;
    int sh = n - fh;

    string xR = x.substr(fh, sh);
    string xL = x.substr(0, fh);

    string yR = y.substr(fh, sh);
    string yL = y.substr(0, fh);

    string p1 = karatsuba(xR, yR);
    string p2 = karatsuba(xL, yL);
    string p3 = karatsuba(add(xR, xL), add(yR, yL));

    string result = add(shiftLeft(p2, 2 * sh), shiftLeft(subtract(subtract(p3, p2), p1), sh));
    result = add(result, p1);

    result.erase(0, result.find_first_not_of('0'));

    return result.empty() ? "0" : result;
}

int main(int argc, char *argv[]) {

    string result = karatsuba(argv[1], argv[2]);

    cout << "Product: " << result << endl;
    return 0;
}

