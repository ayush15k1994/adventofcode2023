#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <numeric>

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

std::vector<std::string> split(std::string input, std::string separator) {
    if (separator.length() > input.length()) return std::vector<std::string>();
    std::vector<std::string> output{};

    std::size_t start = 0, end = 0;
    std::string s_part("");

    while ((end = input.find(separator, start)) != std::string::npos) {
        s_part = input.substr(start, end-start);
        start = end + separator.length();
        if (s_part.length() == 0) continue;
        output.push_back(s_part);
    }

    s_part = input.substr(start);
    output.push_back(s_part);

    return output;
}

static inline void trim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

std::vector<lld> parseNums(std::string s, std::string sep = " ") {
    auto split_nums = split(s, sep);
    std::vector<lld> nums(split_nums.size());
    
    std::transform(split_nums.begin(), split_nums.end(), nums.begin(), [](std::string s){
        return std::stoll(s);
    });

    return nums;
}

lld getNextInPattern(std::vector<lld> nums) {
    std::vector<std::vector<lld>> patterns{};

    bool allZeroes = false;
    patterns.push_back(nums);

    while(!allZeroes) {
        allZeroes = true;
        lld diff;
        std::vector<lld> temp{};
        std::vector<lld> pattern = *(patterns.end()-1);

        for (std::size_t i=1; i<pattern.size(); ++i) {
            diff = pattern[i] - pattern[i-1];
            if (diff != 0) allZeroes = false;
            temp.push_back(diff);
        }
        patterns.push_back(temp);

        // std::for_each(temp.begin(), temp.end(), [](auto &s) { std::cout << s << " "; });
        // std::cout << "\n";
    }

    std::vector<std::vector<lld>>::iterator it = (patterns.end() - 2);
    lld prev = 0;

    while(it != patterns.begin()) {
        prev = *(it->begin()) - prev;
        std::cout << "Prev: " << prev << "\n"; 
        it--;
    }

    prev = *(it->begin()) - prev;
    std::cout << "Prev: " << prev << "\n";

    return prev;
}

int main() {
    std::string str("");

    lld total = 0;
    // std::vector<std::vector<lld>> patterns{};
    while(std::getline(std::cin, str)) {
        std::vector<lld> nums = parseNums(str);
        std::for_each(nums.begin(), nums.end(), [](auto &s) { std::cout << s << " "; });
        std::cout << "\n";

        lld prediction = getNextInPattern(nums);
        total += prediction;
        std::cout << "Prediction: " << prediction << "\n";
    }

    std::cout << "Total: " << total << "\n";

    return 0;
}

/**
 * Day 9: Mirage Maintenance
*/