#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

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

lld maxR=12, maxG=13, maxB=14;

std::vector<std::string> split(std::string input, std::string separator) {
    if (separator.length() > input.length()) return std::vector<std::string>();
    std::vector<std::string> output{};

    std::size_t start = 0, end = 0;
    std::string s_part("");

    while ((end = input.find(separator, start)) != std::string::npos) {
        s_part = input.substr(start, end-start);
        output.push_back(s_part);
        start = end + separator.length();
    }

    s_part = input.substr(start);
    output.push_back(s_part);

    return output;
}

std::map<std::string, int> getMapFromRound(std::string round) {
    std::map<std::string, int> roundMap = {
        {"b", 0}, {"g", 0}, {"r", 0}  
    };

    int r=0, g=0, b=0;

    std::vector<std::string> balls = split(round, ", ");
    std::for_each(balls.begin(), balls.end(), [&r, &g, &b](std::string s) {
        auto s_colors = split(s, " ");
        if (s_colors.size() != 2) return;

        if (s_colors[1].compare("green") == 0) {
            g = std::stoi(s_colors[0]);
        } else if (s_colors[1].compare("red") == 0) {
            r = std::stoi(s_colors[0]);
        } else if (s_colors[1].compare("blue") == 0) {
            b = std::stoi(s_colors[0]);
        }
    });

    roundMap["r"] = r;
    roundMap["g"] = g;
    roundMap["b"] = b;

    return roundMap;
}

bool parseGame(std::string game) {
    std::map<std::string, int> ballMap = {
        {"b", 0}, {"g", 0}, {"r", 0}  
    };

    lld r=0, g=0, b=0;
    bool isPossible = true;
    
    std::size_t colon = game.find(":");
    std::string s_game_num = game.substr(5, colon-5);
    int game_num = std::stoi(s_game_num);

    std::string s_rounds = game.substr(colon+2);
    
    auto rounds = split(s_rounds, "; ");
    std::for_each(rounds.begin(), rounds.end(), [game_num, &isPossible, &r, &g, &b](std::string round) {
        auto roundMap = getMapFromRound(round);
        r = roundMap["r"];
        g = roundMap["g"];
        b = roundMap["b"];

        if (r>maxR || g>maxG || b>maxB) {
            std::cout << game_num << ": impossible\n";
            isPossible = false;
        } 
    });

    ballMap["r"] = r;
    ballMap["g"] = g;
    ballMap["b"] = b;

    return isPossible;
}

int main() {

    std::string str("");

    lld total = 0;

    while(std::getline(std::cin, str)) {
        bool isPossible = parseGame(str);
        if (isPossible) {
            std::size_t colon = str.find(":");
            std::string s_game_num = str.substr(5, colon-5);
            int game_num = std::stoi(s_game_num);
            total += game_num;
        }
    }

    std::cout << total << "\n";

    return 0;
}

/**
 * A bag containing cubes which red, green or blue in colour
 * each time a secret number of cubes of each color are hidden in bag
 * figure out information about number of cubes
 * 
 * eg. Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
 * Total revealed = 9 blue, 5 red, 4 green
 * 
 * which games are possible if bag contians only 12 red, 13 green and 14 blue cubes
 * 
*/