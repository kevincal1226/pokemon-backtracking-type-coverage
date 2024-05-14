#include <iostream>
#include <algorithm>
#include "data.hpp"

bool operator==(const std::pair<std::string, std::string>& lhs, const std::pair<std::string, std::string>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

bool isSuperEffective(const std::string& attacking, const std::string& defending) {
    auto it = effective.find(attacking);
    return std::find(it->second.begin(), it->second.end(), defending) != it->second.end();
}

bool isResistedOrImmune(const std::string& attacking, const std::string& defending) {
    auto res = resistances.find(attacking);
    auto imm = immunities.find(attacking);
    return std::find(res->second.begin(), res->second.end(), defending) != res->second.end() || std::find(imm->second.begin(), imm->second.end(), defending) != imm->second.end();
}

struct SuperEffective {
    bool operator()(const std::string& attacking, const std::pair<std::string, std::string>& defending) {
        if (isSuperEffective(attacking, defending.first)) {
            return !isResistedOrImmune(attacking, defending.second);
        }
        if (isSuperEffective(attacking, defending.second)) {
            return !isResistedOrImmune(attacking, defending.first);
        }
        return false;
    }
};

struct NotResisted {
    bool operator()(const std::string& attacking, const std::pair<std::string, std::string>& defending) {
        return !isResistedOrImmune(attacking, defending.first) && !isResistedOrImmune(attacking, defending.second);
    }
};

class TypeInformation {
public:
    TypeInformation() {
        for (size_t i = 0; i < monotypes.size(); ++i) {
            for (size_t j = i; j < monotypes.size(); ++j) {
                std::pair<std::string, std::string> temp = {monotypes[i], monotypes[j]};
                if (std::find(unusedTypes.begin(), unusedTypes.end(), temp) != unusedTypes.end()) {
                    continue;
                }
                notCovered.emplace_back(std::move(temp));
            }
        }
        best.emplace_back();
        for (size_t i = 0; i < 20; ++i) {
            best.front().emplace_back("");
        }
    }

    template <typename Functor>
    void genCombs(std::vector<std::string>& currentPath, size_t previousIndex, Functor func) {
        if (notCovered.empty()) {
            if (currentPath.size() < best[0].size()) {
                best.clear();
                auto copy = currentPath;
                best.emplace_back(copy);
            }
            else if (currentPath.size() == best[0].size()) {
                auto copy = currentPath;
                best.emplace_back(copy);
            }
            return;
        }
        if (currentPath.size() >= best[0].size()) {
            return;
        }

        for (size_t i = previousIndex + 1; i < monotypes.size(); ++i) {
            std::string attacking = monotypes[i];
            std::vector<std::pair<std::string, std::string>> toRemove;
            for (size_t j = 0; j < notCovered.size(); ++j) {
                if (func(attacking, notCovered[j])) {
                    toRemove.emplace_back(notCovered[j]);
                    std::swap(notCovered[j], notCovered.back());
                    notCovered.pop_back();
                    --j;
                }
            }
            if (toRemove.empty()) {
                continue;
            }
            currentPath.emplace_back(attacking);
            genCombs(currentPath, i, func);
            currentPath.pop_back();
            for (const auto& pair : toRemove) {
                notCovered.emplace_back(pair);
            }

        }
        
        //automatically clear the path for the user once the function ends
        if (previousIndex == std::string::npos) {
            currentPath.clear();
        }
    }     

    std::vector<std::vector<std::string>> getPaths() {
        return best;
    }

    void printPaths() {
        std::cout << best.size() << " Results Found:\n";
        for (auto& v : best) {
            for (auto& s : v) {
                std::cout << s << " ";
            }
            std::cout << '\n';
        }    
        std::cout << '\n';    
    }

    void reset() {
        if (!notCovered.empty()) {
            notCovered.clear();
        }
        best = {{}};
        for (size_t i = 0; i < 20; ++i) {
            best.front().emplace_back("");
        }  
        for (size_t i = 0; i < monotypes.size(); ++i) {
            for (size_t j = i; j < monotypes.size(); ++j) {
                std::pair<std::string, std::string> temp = {monotypes[i], monotypes[j]};
                if (std::find(unusedTypes.begin(), unusedTypes.end(), temp) != unusedTypes.end()) {
                    continue;
                }
                notCovered.emplace_back(std::move(temp));
            }
        }
    }

private:
    std::vector<std::vector<std::string>> best;
    std::vector<std::pair<std::string, std::string>> notCovered;
};

int main() {
    TypeInformation types;
    SuperEffective se;
    NotResisted nr;
    std::vector<std::string> path;
    types.genCombs(path, -1, se);
    types.printPaths();
    types.reset();
    types.genCombs(path, -1, nr);
    types.printPaths();
    return 0;
}