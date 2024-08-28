#include <iostream>
using namespace std;

int makeEqualLength(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1; // If len1 >= len2
}

string karatsuba(string x, string y){
    int n = makeEqualLength(x, y);

    if (n == 0) return "0";

    int fh = n/2;
    int sh = (n-fh);

    string xL = x.substr(0, fh);
    string xR = x.substr(fh, sh);

    string yL = y.substr(0, fh);
    string yR = y.substr(fh, sh);

    cout << xL << " " << xR << " " << yL << " " << yR << endl;
    return "1";
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