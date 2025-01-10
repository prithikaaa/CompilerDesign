set<char> computeFirst(char nonTerminal, map<char, vector<string>>& grammar, map<char, set<char>>& firstSets) {
    if (!firstSets[nonTerminal].empty()) return firstSets[nonTerminal];
    
    set<char> first;
    
    for (string production : grammar[nonTerminal]) {

        if (isupper(production[0]) == 0) {
            first.insert(production[0]);
        }
        
        else {
            set<char> subFirst = computeFirst(production[0], grammar, firstSets);
            first.insert(subFirst.begin(), subFirst.end());
        }
    }
    firstSets[nonTerminal] = first;
    return first;
}

set<char> computeFollow(char nonTerminal, map<char, vector<string>>& grammar, map<char, set<char>>& followSets, char startSymbol) {
    if (!followSets[nonTerminal].empty()) return followSets[nonTerminal];
    
    set<char> follow;
    
    if (nonTerminal == startSymbol) {
        follow.insert('$');
    }

    for (auto& rule : grammar) {
        for (string production : rule.second) {
            for (int i = 0; i < production.length(); i++) {
                if (production[i] == nonTerminal) {
                  
                    if (i + 1 == production.length()) {
                        if (rule.first != nonTerminal) {
                            set<char> subFollow = computeFollow(rule.first, grammar, followSets, startSymbol);
                            follow.insert(subFollow.begin(), subFollow.end());
                        }
                    }
                  
                    else {
                        if (isupper(production[i + 1]) == 0) {
                            follow.insert(production[i + 1]);
                        } else {
                            set<char> subFirst = computeFirst(production[i + 1], grammar, followSets);
                            follow.insert(subFirst.begin(), subFirst.end());
                            follow.erase('ε'); 
                            if (subFirst.find('ε') != subFirst.end()) {
                                set<char> subFollow = computeFollow(rule.first, grammar, followSets, startSymbol);
                                follow.insert(subFollow.begin(), subFollow.end());
                            }
                        }
                    }
                }
            }
        }
    }
    followSets[nonTerminal] = follow;
    return follow;
}

bool isLL1(map<char, vector<string>>& grammar, char startSymbol) {
    map<char, set<char>> firstSets;
    map<char, set<char>> followSets;

    for (auto& rule : grammar) {
        computeFirst(rule.first, grammar, firstSets);
    }
    for (auto& rule : grammar) {
        computeFollow(rule.first, grammar, followSets, startSymbol);
    }

    for (auto& rule : grammar) {
        set<char> firstSet;
        for (string production : rule.second) {
            set<char> currFirst = computeFirst(production[0], grammar, firstSets);
            
            for (char c : currFirst) {
                if (firstSet.find(c) != firstSet.end()) {
                    return false; 
                }
                firstSet.insert(c);
            }
            
            if (currFirst.find('ε') != currFirst.end()) {
                set<char> followSet = computeFollow(rule.first, grammar, followSets, startSymbol);
                for (char c : followSet) {
                    if (firstSet.find(c) != firstSet.end()) {
                        return false; 
                    }
                }
            }
        }
    }
    return true; 
}

int main() {
    map<char, vector<string>> grammar;
    char startSymbol;
    int numRules;
    cout << "Enter the number of grammar rules: ";
    cin >> numRules;

    for (int i = 0; i < numRules; i++) {
        char nonTerminal;
        cout << "Enter the non-terminal (e.g., 'A', 'B'): ";
        cin >> nonTerminal;
        int numProductions;
        cout << "Enter the number of productions for " << nonTerminal << ": ";
        cin >> numProductions;
        vector<string> productions;
        for (int j = 0; j < numProductions; j++) {
            string production;
            cout << "Enter production " << j + 1 << " for " << nonTerminal << ": ";
            cin >> production;
            productions.push_back(production);
        }
        grammar[nonTerminal] = productions;
    }

    cout << "Enter the start symbol: ";
    cin >> startSymbol;

    if (isLL1(grammar, startSymbol)) {
        cout << "The grammar is LL(1)." << endl;
    } else {
        cout << "The grammar is not LL(1)." << endl;
    }

    return 0;
}
