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

enum class Direction {
    NORTH, SOUTH, EAST, WEST
};

struct Pipe {
    char symbol;
    Direction from;
    Direction to;

    Pipe() {}

    Pipe(char s, Direction from, Direction to) {
        this->symbol = s;
        this->from = from;
        this->to = to;
    }

    bool isConnect(Direction dir1, Direction dir2) {
        if (
            (dir1==this->from && dir2==this->to) || 
            (dir2==this->from && dir1==this->to)
        ) {
            return true;
        }

        return false;
    }

    void show(char terminator = '\n') {
        std::cout << symbol << terminator;
    }

    Pipe operator= (Pipe& other) {
        this->symbol = other.symbol;
        this->from = other.from;
        this->to = other.to;
        return *this;
    }
};

Direction oppDir(Direction dir) {
    switch(dir) {
        case Direction::NORTH: return Direction::SOUTH; 
        case Direction::SOUTH: return Direction::NORTH; 
        case Direction::EAST: return Direction::WEST; 
        case Direction::WEST: return Direction::EAST; 
        default: return Direction::NORTH;
    }
}

Direction getDirection(std::pair<lld, lld> index1, std::pair<lld, lld> index2) {
    // index2 is in which direction from index1
    lld diffx=index2.first-index1.first, diffy=index2.second-index1.second;

    if (diffx==0 && diffy==-1) return Direction::NORTH;
    if (diffx==0 && diffy==1) return Direction::SOUTH;
    if (diffx==-1 && diffy==0) return Direction::WEST;
    if (diffx==1 && diffy==0) return Direction::EAST;

    return Direction::NORTH;
}

std::pair<lld, lld> getDeltas(Direction dir) {
    switch (dir) {
        case Direction::NORTH: return {-1, 0};
        case Direction::SOUTH: return {1, 0};
        case Direction::EAST: return {0, 1};
        case Direction::WEST: return {0, -1};
    }

    return {-1, -1};
}

bool canConnect(Pipe pipe1, Pipe pipe2, Direction dir) {
    // can pipe1 connect to pipe2, if pipe2 is in <dir> direction of pipe1
    Direction oppositeDir = oppDir(dir);
    if (pipe1.from==dir && pipe2.to==oppositeDir) return true;
    if (pipe1.from==dir && pipe2.from==oppositeDir) return true;
    if (pipe1.to==dir && pipe2.from==oppositeDir) return true;
    if (pipe1.to==dir && pipe2.to==oppositeDir) return true;
    return false;
}

Pipe getStartPipeType(std::vector<std::string>& maze, std::pair<lld, lld> start, std::map<char, Pipe>& pipeTypes) {
    std::size_t rows = maze.size(), cols = maze[0].length();
    std::size_t row, col;
    char symbol;
    std::vector<Direction> dirs{};

    // NORTH
    row = start.first-1, col = start.second;
    symbol = maze[row][col];
    if (row>=0 && symbol!='.') {
        Pipe pipe = pipeTypes[symbol];
        if (pipe.from==Direction::SOUTH || pipe.to==Direction::SOUTH) dirs.push_back(Direction::NORTH);
    }

    // SOUTH
    row = start.first+1, col = start.second;
    symbol = maze[row][col];
    if (row<rows && symbol!='.') {
        Pipe pipe = pipeTypes[symbol];
        if (pipe.from==Direction::NORTH || pipe.to==Direction::NORTH) dirs.push_back(Direction::SOUTH);
    }

    // EAST
    row = start.first, col = start.second+1;
    symbol = maze[row][col];
    if (col<cols && symbol!='.') {
        Pipe pipe = pipeTypes[symbol];
        if (pipe.from==Direction::WEST || pipe.to==Direction::WEST) dirs.push_back(Direction::EAST);
    }

    // WEST
    row = start.first, col = start.second-1;
    symbol = maze[row][col];
    if (col>=0 && symbol!='.') {
        Pipe pipe = pipeTypes[symbol];
        if (pipe.from==Direction::EAST || pipe.to==Direction::EAST) dirs.push_back(Direction::WEST);
    }

    auto it = std::find_if(pipeTypes.begin(), pipeTypes.end(), [&dirs](auto kv) {
        return (kv.second.from==dirs[0] && kv.second.to==dirs[1]) || (kv.second.from==dirs[1] && kv.second.to==dirs[0]);
    });

    std::cout << "Start type: " << it->first << "\n";

    return it->second;
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

bool isGreater(lld num, lld cmp) {
    if (cmp == -1) return true;
    if (num >= cmp) return true;
    return false;
}

bool findLoop(std::vector<std::string>& maze, std::pair<lld, lld>& pos, std::vector<std::vector<lld>>& dists, Direction prevDir, lld currentDist, std::map<char, Pipe>& pipeTypes) {
    if (dists[pos.first][pos.second] >= 0) return true;
    if (maze[pos.first][pos.second] == '.') return false;

    Pipe thisPipe = pipeTypes[maze[pos.first][pos.second]];
    Direction nextDir = (prevDir==thisPipe.from) ? thisPipe.to : thisPipe.from;
    std::pair<lld, lld> nextDeltas = getDeltas(nextDir);
    std::pair<lld, lld> nextPos = {pos.first+nextDeltas.first, pos.second+nextDeltas.second};
    dists[pos.first][pos.second] = currentDist;

    return findLoop(maze, nextPos, dists, oppDir(nextDir), currentDist+1, pipeTypes);
}

int main() {
    std::string str("");
    std::vector<std::string> maze;

    lld line = 0; 
    std::pair<lld, lld> start = {-1, -1};

    std::map<char, Pipe> pipeTypes = {
        {'|', Pipe('|', Direction::NORTH, Direction::SOUTH)},
        {'-', Pipe('-', Direction::EAST, Direction::WEST)},
        {'L', Pipe('L', Direction::NORTH, Direction::EAST)},
        {'J', Pipe('J', Direction::NORTH, Direction::WEST)},
        {'7', Pipe('7', Direction::SOUTH, Direction::WEST)},
        {'F', Pipe('F', Direction::SOUTH, Direction::EAST)}
    };

    while(std::getline(std::cin, str)) {
        // std::cout << str << "\n";
        maze.push_back(str);

        lld startPos = str.find('S');
        if (startPos != -1) start = {line, startPos};
        ++line; 
    }

    std::cout << "\nStarting Position: " << start.first  << ", " << start.second << "\n";
    Pipe startPipe = getStartPipeType(maze, start, pipeTypes);
    maze[start.first][start.second] = startPipe.symbol;
    std::vector<std::vector<lld>> distances(maze.size(), std::vector<lld>(maze[0].length(), -1));
    std::vector<std::vector<lld>> distances2(maze.size(), std::vector<lld>(maze[0].length(), -1));

    /*std::for_each(distances.begin(), distances.end(), [](auto &dist) {
        std::for_each(dist.begin(), dist.end(), [](auto &d) {
            std::cout << d << " ";
        });
        std::cout << "\n";
    });

    std::cout << "\n"; */

    distances[start.first][start.second] = 0;
    std::pair<lld, lld> nextDelta = getDeltas(startPipe.from);
    std::pair<lld, lld> pos = {start.first+nextDelta.first, start.second+nextDelta.second};
    findLoop(maze, pos, distances, oppDir(startPipe.from), 1, pipeTypes);

    lld maxDist = -1;
    std::for_each(distances.begin(), distances.end(), [&maxDist](auto &dist) {
        std::for_each(dist.begin(), dist.end(), [&maxDist](auto &d) {
            //std::cout << d << " ";
            if (d>maxDist) maxDist = d;
        });
        //std::cout << "\n";
    });

    std::cout << "\n";
    std::cout << "Maximum Distance: " << maxDist << "\n";
    std::cout << "Maximum Distance from source: " << std::ceil(maxDist/2.0) << "\n";

    return 0;
}

/**
 * Day 10: Pipe Maze
*/