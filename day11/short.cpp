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
    std::string str("");
    
    ulld line = 0;
    std::vector<std::string> grid{};
    std::vector<ulld> emptyRows{}, emptyCols{};
    std::vector<std::vector<ulld>> galaxies{};

    while(std::getline(std::cin, str)) {
        std::cout << str << "\n";
        grid.push_back(str);
        if (str.find('#') == std::string::npos) emptyRows.push_back(line);
        else {
            size_t pos = str.find('#', 0);
            while(pos != std::string::npos) {
                galaxies.push_back({line, pos});
                pos = pos+1;
                pos = str.find('#', pos);
            }
        } 
        line++;
    }

    for (size_t j=0; j<grid[0].length(); ++j) {
        bool isEmpty = true;
        for (size_t i=0; i<grid.size(); ++i) {
            if (grid[i][j] == '#') isEmpty = false;
        }
        if (isEmpty) emptyCols.push_back(j);
    }

    std::cout << "Empty Rows: ";
    std::for_each(emptyRows.begin(), emptyRows.end(), [](auto &r) { std::cout << r << " "; });
    std::cout << "\n";

    std::cout << "Empty Cols: ";
    std::for_each(emptyCols.begin(), emptyCols.end(), [](auto &r) { std::cout << r << " "; });
    std::cout << "\n";

    std::cout << "Galaxies: " << galaxies.size() << "\n";
    std::for_each(galaxies.begin(), galaxies.end(), [&emptyRows, &emptyCols](auto &p) {
        std::cout << "(" << p[0] << ", " << p[1] << ")\n";
        ulld x = p[0], y = p[1];
        std::for_each(emptyRows.begin(), emptyRows.end(), [&p, &x](auto &r) {
            if (r<x) p[0]+=1;
        });

        std::for_each(emptyCols.begin(), emptyCols.end(), [&p, &y](auto &c) {
            if (c<y) p[1]+=1;
        }); 
        std::cout << "(" << p[0] << ", " << p[1] << ")\n"; 
    });

    ulld sum = 0;
    for (size_t i=0; i<galaxies.size(); ++i) {
        for (size_t j=i+1; j<galaxies.size(); ++j) {
            auto pos1 = galaxies[i], pos2 = galaxies[j];
            
            lld diffx = pos2[0]-pos1[0];
            if (diffx < 0) diffx = -diffx;
            lld diffy = pos2[1]-pos1[1];
            if (diffy < 0) diffy = -diffy;

            lld dist = diffx + diffy;

            //std::cout << "Distance between " << i << " and " << j << ": " << dist << "\n";
            sum += dist;
        }
    }

    std::cout << "Distance sum: " << sum << "\n";

    return 0;
}

/**
 * Day 11: Cosmic Expansion
*/