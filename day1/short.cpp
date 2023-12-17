#include <string>
#include <iostream>

typedef long int ld;
typedef unsigned long int uld;
typedef long long int lld;
typedef unsigned long long int ulld;
typedef int const cd;
typedef long int const cld;
typedef long long int const clld;
typedef int *pd;
typedef long int *pld;
typedef long long int *plld;
typedef int const *pcd;
typedef int *const cpd;

/*
    Day 1 - Trebuchet
    Part I:
        Input: amended calibration document
        each line contains a specific calibration value
        calibration value = first digit in string *10 + last digit in string
*/

lld getCalibrationValue(std::string s) {
    ulld i, num=0;
    for (i=0; i<s.length(); ++i) {
        if (s[i]>='0' && s[i]<='9') {
            num += (s[i] - '0');
            break;
        }
    }

    for (i=s.length()-1; i>=0; --i) {
        if (s[i]>='0' && s[i]<='9') {
            num = num*10 + (s[i]-'0');
            break;
        }
    }

    return num;
}

int main() {
    std::string str("");
    ulld sum = 0;

    while(std::getline(std::cin, str)) {
        sum += getCalibrationValue(str);
    }

    std::cout << sum << "\n";

    return 0;
}