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

enum class HAND_TYPE {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

void printHandType(HAND_TYPE type) {
    switch(type) {
        case HAND_TYPE::FIVE_OF_A_KIND:
            std::cout << "Five of a Kind\n";
            break;
        case HAND_TYPE::FOUR_OF_A_KIND:
            std::cout << "Four of a Kind\n";
            break;
        case HAND_TYPE::FULL_HOUSE:
            std::cout << "Full House\n";
            break;
        case HAND_TYPE::THREE_OF_A_KIND:
            std::cout << "Three of a Kind\n";
            break;
        case HAND_TYPE::TWO_PAIR:
            std::cout << "Two Pair\n";
            break;
        case HAND_TYPE::ONE_PAIR:
            std::cout << "One Pair\n";
            break;
        case HAND_TYPE::HIGH_CARD:
            std::cout << "High Card\n";
            break;
    }
}

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

HAND_TYPE getHandType(std::string hand) {
    std::map<char, lld> cardCounts;
    for (std::size_t i=0; i<hand.length(); ++i) {
        char ch = hand[i];
        if (cardCounts.find(ch) == cardCounts.end()) {
            cardCounts.insert({ch, 1});
        } else {
            cardCounts[ch]++;
        }
    }

    int fives=0, fours=0, threes=0, twos=0, ones=0;
    for(auto [ch, count]: cardCounts) {
        if (count == 5) fives++;
        else if (count == 4) fours++;
        else if (count == 3) threes++;
        else if (count == 2) twos++;
        else if (count == 1) ones++;
    }

    if (fives) return HAND_TYPE::FIVE_OF_A_KIND;
    if (fours) return HAND_TYPE::FOUR_OF_A_KIND;
    if (threes==1 && twos==1) return HAND_TYPE::FULL_HOUSE;
    if (threes==1) return HAND_TYPE::THREE_OF_A_KIND;
    if (twos==2) return HAND_TYPE::TWO_PAIR;
    if (twos==1) return HAND_TYPE::ONE_PAIR; 
    return HAND_TYPE::HIGH_CARD;
}

bool compareCards(std::string card1, std::string card2) {
    std::map<char, lld> cardPoints = {
        {'2', 2}, 
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'J', 11},
        {'Q', 12},
        {'K', 13},
        {'A', 14}
    };

    if (getHandType(card1) < getHandType(card2)) return true;
    if (getHandType(card1) > getHandType(card2)) return false;

    for (std::size_t i=0; i<card1.length(); ++i) {
        if (cardPoints[card1[i]] < cardPoints[card2[i]]) return true;
        if (cardPoints[card1[i]] > cardPoints[card2[i]]) return false;
    }

    return true;
}

int main() {
    std::string str("");

    std::map<std::string, lld> handBidsMap{};
    std::vector<std::string> hands;

    while(std::getline(std::cin, str)) {
        std::vector<std::string> temp = split(str, " ");
        std::string hand = temp[0], bid = temp[1];
        handBidsMap.insert({hand, std::stoull(bid)});
        hands.push_back(hand);
    }

    std::for_each(hands.begin(), hands.end(), [](auto s) { std::cout << s << " "; });
    std::cout << "\n";
    std::sort(hands.begin(), hands.end(), compareCards);
    std::cout << "After Sorting\n";
    std::for_each(hands.begin(), hands.end(), [](auto s) { std::cout << s << " "; });
    std::cout << "\n";

    ulld total = 0;
    for (std::size_t i=0; i<hands.size(); ++i) {
        total += ((i+1) * handBidsMap[hands[i]]);
    }

    std::cout << "Total Winnings: " << total << "\n";

    return 0;
}

/**
 * Day 7: Camel Cards
*/