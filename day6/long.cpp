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

static inline void removeChar(std::string &s, char replaceCh) {
    lld pos;
    while((pos = s.find(replaceCh)) != -1) {
        s.replace(pos, 1, "");
    }
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
    std::string str("");

    std::string s_times, s_distances;
    std::getline(std::cin, s_times);
    std::getline(std::cin, s_distances);

    s_times = s_times.substr(s_times.find(":") + 1);
    removeChar(s_times, ' ');
    s_distances = s_distances.substr(s_distances.find(":") + 1);
    removeChar(s_distances, ' ');
    trim(s_distances);

    std::cout << s_times << ", " << s_distances << "\n"; 

    ulld time = std::stoull(s_times);
    ulld distance = std::stoull(s_distances);

    ulld total=0, min=0, max=0;

    ulld det = time*time - 4.0*distance;
    if (det >= 0) {
        total = 0;        
        min = std::ceil((time - sqrt(1.0 * det)) / 2.0);
        max = std::floor((time + sqrt(1.0 * det)) / 2.0);
        
        total = max - min + 1;
        if (max * (time-max) <= distance) total--;
        if (min * (time-min) <= distance) total--;
    }

    std::cout << min << ", " << max << " - " << total << "\n";

    return 0;
}

/**
 * Day 6: Wait for It
*/