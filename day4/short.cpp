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

std::vector<lld> parseNumList(std::string list) {
    std::vector<lld> nums{};

    auto split_list = split(list, " ");
    std::for_each(split_list.begin(), split_list.end(), [&nums](std::string s) {
        nums.push_back(std::stol(s));
    });

    return nums;
}

static inline void trim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

int main() {
    std::string str("");

    lld total = 0;

    while(std::getline(std::cin, str)) {
        lld colon = -1, bar = -1;
        colon = str.find(":");
        bar = str.find("|");

        std::string s_card_nums, s_winning_nums, s_my_nums;
        s_card_nums = str.substr(0, colon);
        trim(s_card_nums);
        s_winning_nums = str.substr(colon+2, bar-colon-3);
        trim(s_winning_nums);
        s_my_nums = str.substr(bar+2);
        trim(s_my_nums);

        auto winning_nums = parseNumList(s_winning_nums);
        auto my_nums = parseNumList(s_my_nums);

        std::sort(winning_nums.begin(), winning_nums.end());
        std::sort(my_nums.begin(), my_nums.end());

        std::vector<lld> my_wins(winning_nums.size());

        auto it = std::set_intersection(
            winning_nums.begin(), winning_nums.end(),
            my_nums.begin(), my_nums.end(),
            my_wins.begin()
        );
        my_wins.resize(it - my_wins.begin());

        lld score = 0;
        std::for_each(my_wins.begin(), my_wins.end(), [&score](auto n) {
            if (score == 0) score = 1;
            else score *= 2;
        });
        total += score;

        std::cout << s_card_nums << ": " << score << "\n";
    }

    std::cout << "Total: " << total << "\n";

    return 0;
}

/**
 * Gear Ratios:
 * 
 * In engine schematic, any number adjacent to a symbol (even diagonally) is a part number
 * Periods do not count as a symbol
 * 
*/