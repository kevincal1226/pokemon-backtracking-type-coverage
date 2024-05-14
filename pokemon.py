import copy

class PokemonTypes:
    def __init__(self, remove_unused_types: bool = True):
        self.best_paths =  [["normal", "fighting", "flying", "poison", "ground", "rock", "bug", "ghost", "steel", "fire", "water", "grass", "electric", "psychic", "ice", "dragon", "dark", "fairy"]]
        self.monotypes = ["normal", "fighting", "flying", "poison", "ground", "rock", "bug", "ghost", "steel", "fire", "water", "grass", "electric", "psychic", "ice", "dragon", "dark", "fairy", None]
        self.all_types: list[list[str]] = []
        for i in range (len(self.monotypes) - 1):
            for j in range(i + 1, len(self.monotypes)):
                self.all_types.append([self.monotypes[i], self.monotypes[j]])
        self.monotypes.remove(None)
        self.unused_types = [
            ["normal", "ice"],
            ["normal", "bug"],
            ["normal", "rock"],
            ["normal", "steel"],
            ["fire", "fairy"],
            ["poison", "ice"],
            ["ground", "fairy"],
            ["bug", "dragon"],
            ["rock", "ghost"]
        ]
        if (remove_unused_types):
            for pair in self.unused_types:
                self.all_types.remove(pair)
        self.resistances: dict[str: list[str]] = {
        "normal": ["rock", "steel"],
        "fighting": ["flying", "poison", "bug", "psychic", "fairy"],
        "flying": ["rock", "steel", "electric"],
        "poison": ["poison", "ground", "rock", "ghost"],
        "ground": ["bug", "grass"],
        "rock": ["fighting", "ground", "steel"],
        "bug": ["fighting", "flying", "poison", "ghost", "steel", "fire", "fairy"],
        "ghost": ["dark"],
        "steel": ["steel", "fire", "water", "electric"],
        "fire": ["rock", "fire", "water", "dragon"],
        "water": ["water", "grass", "dragon"],
        "grass": ["flying", "poison", "bug", "steel", "fire", "grass", "dragon"],
        "electric": ["grass", "electric", "dragon"],
        "psychic": ["steel", "psychic"],
        "ice": ["steel", "fire", "water", "ice"],
        "dragon": ["steel"],
        "dark": ["fighting", "dark", "fairy"],
        "fairy": ["poison", "steel", "fire"]
        }
        self.immunities: dict[str: list[str]] = {
            "normal": ["ghost"],
            "fighting": ["ghost"],
            "poison": [],
            "ground": ["flying"],
            "flying": [],
            "psychic": ["dark"],
            "bug": [],
            "rock": [],
            "ghost": ["normal"],
            "dragon": ["fairy"],
            "dark": [],
            "steel": [],
            "fire": [],
            "water": [],
            "grass": [],
            "electric": ["ground"],
            "ice": [],
            "fairy": []
        }
        self.effective: dict[str: list[str]] = {
        "normal": [],
        "fighting": ["normal", "rock", "steel", "ice", "dark"],
        "flying": ["fighting", "bug", "grass"],
        "poison": ["grass", "fairy"],
        "ground": ["fire", "electric", "poison", "rock", "steel"],
        "rock": ["fire", "ice", "flying", "bug"],
        "bug": ["grass", "psychic", "dark"],
        "ghost": ["ghost", "psychic"],
        "steel": ["ice", "rock", "fairy"],
        "fire": ["bug", "steel", "grass", "ice"],
        "water": ["ground", "rock", "fire"],
        "grass": ["ground", "rock", "water"],
        "electric": ["flying", "water"],
        "psychic": ["fighting", "poison"],
        "ice": ["flying", "ground", "grass", "dragon"],
        "dragon": ["dragon"],
        "dark": ["ghost", "psychic"],
        "fairy": ["fighting", "dragon", "dark"]
        }
    
    def super_effective(self, attacking: str, defending: str) -> bool:
        return defending in self.effective[attacking]
    
    def resists_or_immune(self, attacking: str, defending: str) -> bool:
        return defending in self.resistances[attacking] or defending in self.immunities[attacking]
    
    def is_super_effective_against(self, attacking: str, defending: list[list[str]]):
        if defending[1] is None:
            return self.super_effective(attacking, defending[0])
        if (self.super_effective(attacking, defending[0])):
            return not self.resists_or_immune(attacking, defending[1])
        if (self.super_effective(attacking, defending[1])):
            return not self.resists_or_immune(attacking, defending[0])
        return False
            
    
    def find_all_super_effective(self, current_path: list[str], not_effective_against: list[list[str]], previous: int):
        if (len(not_effective_against) == 0):
            if (len(current_path) < len(self.best_paths[0])):
                self.best_paths.clear()
                self.best_paths.append(copy.deepcopy(current_path))
            elif (len(current_path) == len(self.best_paths[0])):
                self.best_paths.append(copy.deepcopy(current_path))
            return
        
        if (len(current_path) > len(self.best_paths[0])):
            return
        
        for idx in range(previous + 1, len(self.monotypes)):
            i = self.monotypes[idx]
            new_list: list[list[str]] = []
            for defending_type in not_effective_against:
                if not self.is_super_effective_against(i, defending_type):
                    new_list.append(defending_type)
            if len(not_effective_against) == len(new_list):
                continue
            current_path.append(i)
            self.find_all_super_effective(current_path, new_list, idx)
            current_path.remove(i)
        
    def print_best_paths(self):
        for p in self.best_paths:
            print(*p, sep=', ')

def main():        
    types = PokemonTypes(True)
    types.find_all_super_effective([], copy.deepcopy(types.all_types), 0)
    types.print_best_paths()
    
if __name__ == "__main__":
    main()