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

int main() {
    std::string str(""), directions;

    std::map<std::string, std::pair<std::string, std::string>> dirMap;

    std::getline(std::cin, directions);
    while(std::getline(std::cin, str)) {
        if (str.length()==0) continue;
        std::vector<std::string> temp = split(str, " = ");
        std::vector<std::string> temp2 = split(temp[1].substr(1, temp[1].length()-2), ", "); 
        std::string left = temp2[0], right = temp2[1];

        dirMap[temp[0]] = {left, right};
    }

    ulld i=0, size=directions.length();
    ulld steps = 0;
    std::string src = "AAA";
    std::cout << src << "\n";
    while (src != "ZZZ") {
        if (directions[i]=='R') {
            src = dirMap[src].second;
        } else if (directions[i]=='L') {
            src = dirMap[src].first;
        }
        std::cout << src << "\n";
        steps++;
        i = (i+1) % size;
    } 

    std::cout << "Steps: " << steps << "\n";

    return 0;
}

/**
 * Day 7: Camel Cards
*/