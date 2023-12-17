#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>

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

struct RangeMap {
    std::string from;
    std::string to;
    std::vector<lld> dest_start {};
    std::vector<lld> src_start{};
    std::vector<lld> range_length{};

    void addValues(lld src, lld dest, lld range) {
        dest_start.push_back(dest);
        src_start.push_back(src);
        range_length.push_back(range);
    }

    lld getDestValue(lld srcValue) {
        for (lld i=0; i<src_start.size(); ++i) {
            if (srcValue>=src_start[i] && srcValue<src_start[i]+range_length[i]) {
                return dest_start[i] + (srcValue - src_start[i]);
            }
        }

        return srcValue;
    }

    void show() {
        std::cout << from << " to " << to << ": \n";
        for (lld i=0; i<src_start.size(); ++i) {
            std::cout << src_start[i] << " " << dest_start[i] << " " << range_length[i] << "\n";
        }
    }
};

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

static inline void trim(std::string s) {
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

RangeMap getMap(std::string str) {
    lld mapIdx = str.find(" map");
    std::string s_mapEntities = str.substr(0, mapIdx);
    auto entities = split(s_mapEntities, "-");

    RangeMap rMap;
    rMap.from = entities[0];
    rMap.to = entities[2];

    return rMap;
}

std::vector<lld> getLocations(std::vector<lld>& seeds, std::vector<RangeMap>& rMap) {
    std::vector<lld> temp(seeds.size(), -1);

    for (lld i=0; i<seeds.size(); ++i) {
        lld src = seeds[i];
        std::string from="seed", to="";
        while(from != "location") {
            auto it = std::find_if(rMap.begin(), rMap.end(), [from](auto m) { return m.from == from; });
            if (it != rMap.end()) {
                to = it->to;
                src = it->getDestValue(src);
                from = to;
            }
        }

        temp[i] = src;
    }

    return temp;
}

int main() {
    std::string str("");

    lld line = 0;

    std::vector<lld> seeds{};
    std::vector<RangeMap> maps{};
    RangeMap rMap;
    while(std::getline(std::cin, str)) {
        ++line;

        if (line == 1) {
            lld colon = str.find(":");
            std::string values = str.substr(colon+1);
            trim(values);
            seeds = parseNums(values);
        }

        else {
            if (str.length()==0) {
                if (line>2) maps.push_back(rMap);
            }
            else if (*(str.end()-1) == ':') {
                rMap = getMap(str);
            } else {
                auto nums = parseNums(str);
                rMap.addValues(nums[1], nums[0], nums[2]);
            }
        }
    }
    maps.push_back(rMap);

    std::for_each(seeds.begin(), seeds.end(), [](auto s) { std::cout<<s<<" "; });
    std::cout << "\n";

    auto locations = getLocations(seeds, maps);
    auto location = std::min_element(locations.begin(), locations.end());
    std::cout << "Minimum location: " << *location << "\n";

    return 0;
}

/**
 * If you give a seed a fertilizer
*/