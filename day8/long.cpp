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

bool areAllEnds(std::vector<std::string>& positions) {
    for(auto position: positions) {
        if (position[position.length() - 1] != 'Z') return false;
    }
    return true;
}

int main() {
    std::string str(""), directions;

    std::map<std::string, std::pair<std::string, std::string>> dirMap;
    std::vector<std::string> starts{};
    std::vector<ulld> stepCounts{};

    std::getline(std::cin, directions);
    while(std::getline(std::cin, str)) {
        if (str.length()==0) continue;
        std::vector<std::string> temp = split(str, " = ");
        std::vector<std::string> temp2 = split(temp[1].substr(1, temp[1].length()-2), ", "); 
        std::string left = temp2[0], right = temp2[1];

        dirMap[temp[0]] = {left, right};
        if (temp[0][temp[0].length() - 1] == 'A') starts.push_back(temp[0]);
    }

    std::for_each(starts.begin(), starts.end(), [](auto &s) { std::cout << s << "\n"; });

    ulld i=0, size=directions.length();
    ulld steps = 0;
    std::for_each(starts.begin(), starts.end(), [](auto &s) { std::cout << s << " "; });
    std::cout << "\n";

    for (auto &s: starts) {
        steps = 0;
        i=0;
        while (s[s.length()-1] != 'Z') {
            if (directions[i]=='R') {
                s = dirMap[s].second;
            } else if (directions[i]=='L') {
                s = dirMap[s].first;
            }
            // std::cout << s << "\n";
            steps++;
            i = (i+1) % size;
        }
        stepCounts.push_back(steps);
        std::cout << steps << "\n";
    }

    std::for_each(stepCounts.begin(), stepCounts.end(), [](auto &s) { std::cout << s << " "; });
    std::cout << "\n";

    ulld finalStepCount = 1;
    for (auto &s: stepCounts) {
        finalStepCount = std::lcm(finalStepCount, s);
    }

    std::cout << finalStepCount << "\n";

    // find LCM of all the steps for getting final count

    return 0;
}

/**
 * Day 7: Camel Cards
*/