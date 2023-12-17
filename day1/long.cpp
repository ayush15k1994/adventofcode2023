#include <string>
#include <iostream>
#include <regex>

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
        but some digits can be present as words like one, two etc.
*/

int getWordDigit(std::string s, lld start_index) {
    std::string digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (lld i=0; i<9; ++i) {
        if (digits[i].length()+start_index > s.length()) continue;
        if (digits[i].compare(s.substr(start_index, digits[i].length())) == 0) {
            return i+1;
        }
    }

    return -1;
}

lld getCalibrationValue(std::string s) {
    ulld i, num=0;
    for (i=0; i<s.length(); ++i) {
        if (s[i]>='0' && s[i]<='9') {
            num += (s[i] - '0');
            break;
        } else {
            int digit = getWordDigit(s, i);
            if (digit != -1) {
                num += digit;
                break;
            }
        }
    }

    for (i=s.length()-1; i>=0; --i) {
        if (s[i]>='0' && s[i]<='9') {
            num = num*10 + (s[i]-'0');
            break;
        } else {
            int digit = getWordDigit(s, i);
            if (digit != -1) {
                num  = num*10 + digit;
                break;
            }
        }
    }

    return num;
}

int main() {
    std::string str("");
    ulld sum = 0;

    while(std::getline(std::cin, str)) {
        std::cout << "Input: " << str << "\n";
        lld value = getCalibrationValue(str); 
        std::cout << "Value is: " << value << "\n";
        sum += value;
    }

    std::cout << sum << "\n";

    return 0;
}