#ifndef DATA
#include <string>
#include <unordered_map>
#include <vector>

const std::vector<std::string> monotypes = {"normal", "fighting", "flying", "poison", "ground", "rock", "bug", "ghost", "steel", "fire", "water", "grass", "electric", "psychic", "ice", "dragon", "dark", "fairy"};

const std::vector<std::pair<std::string, std::string>> unusedTypes = {            
    {"normal", "ice"},
    {"normal", "bug"},
    {"normal", "rock"},
    {"normal", "steel"},
    {"fire", "fairy"},
    {"poison", "ice"},
    {"ground", "fairy"},
    {"bug", "dragon"},
    {"rock", "ghost"}
};

const std::unordered_map<std::string, std::vector<std::string>> resistances = {
    {"normal", {"rock", "steel"}},
    {"fighting", {"flying", "poison", "bug", "psychic", "fairy"}},
    {"flying", {"rock", "steel", "electric"}},
    {"poison", {"poison", "ground", "rock", "ghost"}},
    {"ground", {"bug", "grass"}},
    {"rock", {"fighting", "ground", "steel"}},
    {"bug", {"fighting", "flying", "poison", "ghost", "steel", "fire", "fairy"}},
    {"ghost", {"dark"}},
    {"steel", {"steel", "fire", "water", "electric"}},
    {"fire", {"rock", "fire", "water", "dragon"}},
    {"water", {"water", "grass", "dragon"}},
    {"grass", {"flying", "poison", "bug", "steel", "fire", "grass", "dragon"}},
    {"electric", {"grass", "electric", "dragon"}},
    {"psychic", {"steel", "psychic"}},
    {"ice", {"steel", "fire", "water", "ice"}},
    {"dragon", {"steel"}},
    {"dark", {"fighting", "dark", "fairy"}},
    {"fairy", {"poison", "steel", "fire"}}
};
const std::unordered_map<std::string, std::vector<std::string>> immunities = {
    {"normal", {"ghost"}},
    {"fighting", {"ghost"}},
    {"poison", {}},
    {"ground", {"flying"}},
    {"flying", {}},
    {"psychic", {"dark"}},
    {"bug", {}},
    {"rock", {}},
    {"ghost", {"normal"}},
    {"dragon", {"fairy"}},
    {"dark", {}},
    {"steel", {}},
    {"fire", {}},
    {"water", {}},
    {"grass", {}},
    {"electric", {"ground"}},
    {"ice", {}},
    {"fairy", {}}
};
const std::unordered_map<std::string, std::vector<std::string>> effective = {
    {"normal", {}},
    {"fighting", {"normal", "rock", "steel", "ice", "dark"}},
    {"flying", {"fighting", "bug", "grass"}},
    {"poison", {"grass", "fairy"}},
    {"ground", {"fire", "electric", "poison", "rock", "steel"}},
    {"rock", {"fire", "ice", "flying", "bug"}},
    {"bug", {"grass", "psychic", "dark"}},
    {"ghost", {"ghost", "psychic"}},
    {"steel", {"ice", "rock", "fairy"}},
    {"fire", {"bug", "steel", "grass", "ice"}},
    {"water", {"ground", "rock", "fire"}},
    {"grass", {"ground", "rock", "water"}},
    {"electric", {"flying", "water"}},
    {"psychic", {"fighting", "poison"}},
    {"ice", {"flying", "ground", "grass", "dragon"}},
    {"dragon", {"dragon"}},
    {"dark", {"ghost", "psychic"}},
    {"fairy", {"fighting", "dragon", "dark"}}
};
#endif