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

std::vector<std::vector<int>> deltas = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1} , {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};

bool isSymbol(char c) {
    if (c>='A' && c<='Z') return false;
    if (c>='a' && c<='z') return false;
    if (c>='0' && c<='9') return false;
    if (c=='.') return false;
    return true;
}

bool isNum(char c) {
    if (c>='0' && c<='9') return true;
    return false;
}

lld getPartNumber(auto& schematic, auto& visited, lld i, lld j) {
    lld x=j, minx, maxx;
    
    while(x>=0 && isNum(schematic[i][x])) {
        if (visited[i][x]) return -1;
        x--;
    }
    minx = x+1; 

    x = j+1;
    while(x<schematic[i].size() && isNum(schematic[i][x])) {
        if (visited[i][x]) return -1;
        x++;
    }
    maxx = x-1;

    lld num = 0;
    for (x=minx; x<=maxx; ++x) {
        num = num*10 + (int)(schematic[i][x] - '0');
    }

    return num;
}

int main() {

    std::string str("");

    std::vector<std::string> schematic{};
    while(std::getline(std::cin, str)) {
        schematic.push_back(str);
    }

    std::vector<std::vector<int>> visited(schematic.size(), std::vector(schematic[0].size(), 0));

    lld i, j;
    lld total = 0;

    for (i=0; i<schematic.size(); ++i) {
        for (j=0; j<schematic[i].size(); ++j) {
            char c = schematic[i][j];

            if (isSymbol(c)) {
                for (int k=0; k<deltas.size(); ++k) {
                    lld row = i + deltas[k][0];
                    lld col = j + deltas[k][1];

                    if (row<0 || row>=schematic.size()) continue;
                    if (col<0 || col>=schematic[row].size()) continue;

                    if (!visited[row][col] && isNum(schematic[row][col])) {
                        lld num = getPartNumber(schematic, visited, row, col);
                        if (num > 0) total += num; 
                        visited[row][col] = 1;
                    }
                }
            }
        }
    }

    std::cout << total << "\n";

    return 0;
}

/**
 * Gear Ratios:
 * 
 * In engine schematic, any number adjacent to a symbol (even diagonally) is a part number
 * Periods do not count as a symbol
 * 
*/