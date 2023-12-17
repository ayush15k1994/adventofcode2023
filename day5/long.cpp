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

struct SimpleRange {
    lld start;
    lld end;    // end exclusive
    bool processed = false;
    bool transformed = false;

    SimpleRange() {}
    SimpleRange(lld start, lld end) {
        this->start = start;
        this->end = end;
    }

    void show() {
        std::cout << start << " to " << end << "\n";
    }

    void setProcessed() {
        this->processed = true;
    }

    void setTransformed() {
        this->transformed = true;
    }

    bool isProcessed() {
        return processed;
    }

    bool isTransformed() {
        return transformed;
    }
};

struct RangeMap {
    std::string from;
    std::string to;
    lld src_start;
    lld src_end;
    lld dest_start;
    lld dest_end;

    RangeMap() {}

    RangeMap(std::string from, std::string to, lld src, lld dest, lld range) {
        this->from = from;
        this->to = to;
        this->src_start = src;
        this->src_end = src + range;
        this->dest_start = dest;
        this->dest_end = dest + range;
    }

    bool checkRange(SimpleRange& check) {
        if (check.end<=this->src_start || check.start>=this->src_end) return false;
        return true;
    }

    std::vector<SimpleRange> partitionRanges(std::vector<SimpleRange>& check) {
        std::vector<SimpleRange> ranges{};

        std::for_each(check.begin(), check.end(), [&ranges, this](auto &s) {
            if (!this->checkRange(s)) ranges.push_back(s);

            // complete overlap
            if (this->src_start<=s.start && this->src_end>=s.end) {
                // std::cout << "Complete Overlap\n";
                SimpleRange temp = SimpleRange(s.start, s.end);
                ranges.push_back(temp);
            }

            // partial overlap - this completely inside check
            if (this->src_start>s.start && this->src_end<s.end) {
                // std::cout << "partial overlap - this completely inside check\n";
                lld dest_start, dest_end;
                SimpleRange temp;
                // left range
                dest_start = s.start;
                dest_end = this->src_start;
                temp = SimpleRange(dest_start, dest_end);
                ranges.push_back(temp);

                // middle overlap
                dest_start = this->src_start;
                dest_end = this->src_end;
                temp = SimpleRange(dest_start, dest_end);
                ranges.push_back(temp);

                // right range
                dest_start = this->src_end;
                dest_end = s.end;
                temp = SimpleRange(dest_start, dest_end);
                ranges.push_back(temp);
            }

            // partial overlap - this to left of check
            if (this->src_start<=s.start && this->src_end>s.start && this->src_end<s.end) {
                // std::cout << "partial overlap - this to left of check\n";
                lld dest_start, dest_end;
                SimpleRange temp;

                // left overlap
                dest_start = s.start;
                dest_end = this->src_end;
                temp = SimpleRange(dest_start, dest_end);
                ranges.push_back(temp);

                // right range
                dest_start = this->src_end;
                dest_end = s.end;
                temp = SimpleRange(dest_start, dest_end);
                ranges.push_back(temp);
            }

            // partial overlap - this to the right of check
            if (this->src_end>=s.end && this->src_start>s.start && this->src_start<s.end) {
                // std::cout << "partial overlap - this to the right of check\n";
                lld dest_start, dest_end;
                SimpleRange temp;

                // left range
                dest_start = s.start;
                dest_end = this->src_start;
                temp = SimpleRange(dest_start, dest_end);
                ranges.push_back(temp);

                // right overlap
                dest_start = this->src_start;
                dest_end = s.end;
                temp = SimpleRange(dest_start, dest_end);
                ranges.push_back(temp);
            }
        });

        return ranges;
    }

    std::vector<SimpleRange> transformRange(SimpleRange& check) {
        std::vector<SimpleRange> ranges{};
        
        // No overlap
        if (check.isProcessed() || !checkRange(check)) {
            // std::cout << "No overlap\n";
            // ranges.push_back(check);
            return ranges;
        }

        check.setProcessed();
        // complete overlap
        if (this->src_start<=check.start && this->src_end>=check.end) {
            // std::cout << "Complete Overlap\n";
            lld dest_start = this->dest_start + (check.start - this->src_start);
            lld dest_end = this->dest_start + (check.end - this->src_start);
            SimpleRange temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);
            return ranges;
        }

        // partial overlap - this completely inside check
        if (this->src_start>check.start && this->src_end<check.end) {
            // std::cout << "partial overlap - this completely inside check\n";
            lld dest_start, dest_end;
            SimpleRange temp;
            // left range
            dest_start = check.start;
            dest_end = this->src_start;
            temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);

            // middle overlap
            dest_start = this->dest_start;
            dest_end = this->dest_end;
            temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);

            // right range
            dest_start = this->src_end;
            dest_end = check.end;
            temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);

            return ranges;
        }

        // partial overlap - this to left of check
        if (this->src_start<check.start && this->src_end>check.start && this->src_end<check.end) {
            // std::cout << "partial overlap - this to left of check\n";
            lld dest_start, dest_end;
            SimpleRange temp;

            // left overlap
            dest_start = this->dest_start + (check.start - this->src_start);
            dest_end = this->dest_end;
            temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);

            // right range
            dest_start = this->src_end;
            dest_end = check.end;
            temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);

            return ranges;
        }

        // partial overlap - this to the right of check
        if (this->src_end>check.end && this->src_start>check.start && this->src_end<check.end) {
            // std::cout << "partial overlap - this to the right of check\n";
            lld dest_start, dest_end;
            SimpleRange temp;

            // left range
            dest_start = check.start;
            dest_end = this->src_start;
            temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);

            // right overlap
            dest_start = this->src_start;
            dest_end = this->dest_start + (check.end - this->src_start);
            temp = SimpleRange(dest_start, dest_end);
            ranges.push_back(temp);
            
            return ranges;
        }

        return ranges;
    }

    lld getDestValue(lld srcValue) {
        if (srcValue>=this->src_start && srcValue<this->src_end) {
            return this->dest_start + (srcValue - this->src_start);
        }

        return srcValue;
    }

    void show() {
        std::cout << from << " to " << to << ": ";
        std::cout << "[" << this->src_start << ", " << this->src_end << ") -> ";
        std::cout << "[" << this->dest_start << ", " << this->dest_end << ")\n";
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

std::pair<std::string, std::string> getMap(std::string str) {
    lld mapIdx = str.find(" map");
    std::string s_mapEntities = str.substr(0, mapIdx);
    auto entities = split(s_mapEntities, "-to-");

    std::pair<std::string, std::string> p = {entities[0], entities[1]};
    return p;
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
    std::vector<SimpleRange> seedRanges{};
    std::map<std::string, std::vector<RangeMap>> maps{};
    std::pair<std::string, std::string> pr;
    std::vector<std::string> order{};

    RangeMap rMap;
    while(std::getline(std::cin, str)) {
        ++line;

        if (line == 1) {
            lld colon = str.find(":");
            std::string values = str.substr(colon+1);
            trim(values);
            seeds = parseNums(values);
            order.push_back("seed");
        }

        else {
            if (str.length()==0) {    
            }
            else if (*(str.end()-1) == ':') {
                pr = getMap(str);
                maps.insert({pr.second, std::vector<RangeMap>()});
                order.push_back(pr.second);
            } else {
                auto nums = parseNums(str);
                rMap = RangeMap(pr.first, pr.second, nums[1], nums[0], nums[2]);
                maps[pr.second].push_back(rMap);
            }
        }
    }
    for (lld i=0; i<seeds.size(); i+=2) {
        SimpleRange sr(seeds[i], seeds[i]+seeds[i+1]);
        seedRanges.push_back(sr);
    }
    std::sort(seedRanges.begin(), seedRanges.end(), [](auto& r1, auto& r2) {
        if (r1.start <= r2.start) return true;
        return false;
    });

    std::cout << "Seeds: \n";
    std::for_each(seedRanges.begin(), seedRanges.end(), [](auto s) { s.show(); });
    std::cout << "\n";
    
    std::for_each(order.begin(), order.end(), [](auto el) { std::cout << el << " "; });
    std::cout << "\n";

    /*std::for_each(maps.begin(), maps.end(), [](auto kv) {
        std::sort(kv.second.begin(), kv.second.end(), [](auto& el1, auto& el2) {
            if (el1.src_start <= el2.src_start) return true;
            return false;
        });
        std::cout << kv.first << ": " << kv.second.size() << " entries.\n";
        std::for_each(kv.second.begin(), kv.second.end(), [](auto el) {
            el.show();
        });
    });*/


    std::vector<SimpleRange> a{seedRanges}, b{}, c{};
    std::vector<SimpleRange> &refa = a, &refb = b, &temp = a;    
    for (lld i=1; i<order.size(); ++i) {
        std::cout << order[i] << ": \n";

        std::vector<RangeMap> ranges = maps[order[i]];

        std::sort(ranges.begin(), ranges.end(), [](auto &r1, auto &r2){
            if (r1.src_start <= r2.src_start) return true;
            return false;
        });

        refb.clear();

        for (lld j=0; j<ranges.size(); ++j) {
            refa = ranges[j].partitionRanges(refa);
            /* std::cout << "Partition with:: ";
            ranges[j].show();
            std::for_each(refa.begin(), refa.end(), [](auto &s) { s.show(); });
            std::cout << "\n"; */
        }

        for (lld j=0; j<ranges.size(); ++j) {
            // std::for_each(refa.begin(), refa.end(), [](auto s) { s.processed = false; });

            for (lld k=0; k<refa.size(); ++k) {
                if (!refa[k].isProcessed()) 
                {
                    c = ranges[j].transformRange(refa[k]);
                    refb.insert(refb.end(), c.begin(), c.end());
                }
            }
        }

        std::for_each(refa.begin(), refa.end(), [&refb](auto s) {
            if (!s.isProcessed()) refb.push_back(s);
        });

        temp = refa;
        refa = refb;
        refb = temp;

        std::for_each(refa.begin(), refa.end(), [](auto s) { s.show(); });
        std::cout << "\n";
    }

    auto min = refa.begin()->start;
    for (auto it = refa.begin(); it!=refa.end(); it++) {
        if (min > it->start)
            min = it->start;
    }

    std::cout << "Minimum Location: " << min << "\n\n";

    /*auto locations = getLocations(seeds, maps);
    auto location = std::min_element(locations.begin(), locations.end());
    std::cout << "Minimum location: " << *location << "\n";*/

    return 0;
}

/**
 * If you give a seed a fertilizer
*/