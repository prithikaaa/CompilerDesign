map<char, vector<string>> grammar;
map<char, set<char>> firstSet, followSet;
set<char> visited;

void findFirst(char symbol) {
    if (firstSet.find(symbol) != firstSet.end()) return;

    set<char> result;
    for (const string& production : grammar[symbol]) {
        if (production == "#") { 
            result.insert('#');  
            continue;
        }
        for (char c : production) {
            if (islower(c)) { 
                result.insert(c);
                break;
            } else if (c == symbol) { 
                continue;
            } else {
                findFirst(c); 
                result.insert(firstSet[c].begin(), firstSet[c].end());
                if (firstSet[c].find('#') == firstSet[c].end()) break; 
            }
        }
    }
    firstSet[symbol] = result;
}

void findFollow(char symbol) {
    if (visited.find(symbol) != visited.end()) return;
    visited.insert(symbol);

    if (symbol == 'S') followSet[symbol].insert('$');

    for (auto& rule : grammar) {
        char lhs = rule.first;
        for (const string& production : rule.second) {
            for (size_t i = 0; i < production.size(); ++i) {
                if (production[i] == symbol) {
                    if (i + 1 < production.size()) {
                        char next = production[i + 1];
                        if (islower(next)) {
                            followSet[symbol].insert(next);
                        } else {
                            followSet[symbol].insert(firstSet[next].begin(), firstSet[next].end());
                            followSet[symbol].erase('#'); 
                            if (firstSet[next].find('#') != firstSet[next].end() && lhs != symbol) {
                                findFollow(lhs);
                                followSet[symbol].insert(followSet[lhs].begin(), followSet[lhs].end());
                            }
                        }
                    } else if (lhs != symbol) {
                        findFollow(lhs);
                        followSet[symbol].insert(followSet[lhs].begin(), followSet[lhs].end());
                    }
                }
            }
        }
    }
}

int main() {
    int numRules;
    cout << "Enter number of rules: ";
    cin >> numRules;

    cout << "Enter grammar rules (e.g., S->AB or A->a|# for epsilon):" << endl;
    for (int i = 0; i < numRules; ++i) {
        string rule;
        cin >> rule;
        char lhs = rule[0];
        string rhs = rule.substr(3);
        string production;
        for (char c : rhs) {
            if (c == '|') {
                grammar[lhs].push_back(production);
                production.clear();
            } else {
                production += c;
            }
        }
        grammar[lhs].push_back(production);
    }

   
    for (auto& rule : grammar) {
        findFirst(rule.first);
    }

    for (auto& rule : grammar) {
        findFollow(rule.first);
    }

    cout << "\nFirst Sets:\n";
    for (auto& rule : firstSet) {
        cout << "First(" << rule.first << ") = { ";
        for (char c : rule.second) {
            if (c == '#') {
                cout << "ε "; 
            } else {
                cout << c << " ";
            }
        }
        cout << "}\n";
    }

    cout << "\nFollow Sets:\n";
    for (auto& rule : followSet) {
        cout << "Follow(" << rule.first << ") = { ";
        for (char c : rule.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }

    return 0;
}
