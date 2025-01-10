#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <set>
using namespace std;

struct Rule {
    char nonTerminal;
    string production;
    
    Rule() : nonTerminal('\0'), production("") {}  // Default constructor
    Rule(char nt, string prod) : nonTerminal(nt), production(prod) {}
};

struct LRItem {
    Rule rule;
    int dotPosition;
    set<char> lookAhead;
    
    LRItem() : rule(), dotPosition(0) {}  // Default constructor
    LRItem(Rule r, int pos, set<char> la) 
        : rule(r), dotPosition(pos), lookAhead(la) {}
};

enum class ActionType {
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR,
    NONE  
};

struct Action {
    ActionType type;
    int value;
    
    Action() : type(ActionType::NONE), value(-1) {}
    
    Action(ActionType t, int v) : type(t), value(v) {}
    
    Action(const Action& other) : type(other.type), value(other.value) {}
    
    Action& operator=(const Action& other) {
        if (this != &other) {
            type = other.type;
            value = other.value;
        }
        return *this;
    }
};

class LRParser {
private:
    vector<Rule> grammar;
    map<int, map<char, Action>> actionTable;
    map<int, map<char, int>> gotoTable;
    
public:
    void addRule(char nonTerminal, string production) {
        grammar.push_back(Rule(nonTerminal, production));
    }
    
    void buildTables() {
    actionTable.clear();
    gotoTable.clear();

    // State 0
    actionTable[0]['i'] = Action(ActionType::SHIFT, 5); 
    actionTable[0]['('] = Action(ActionType::SHIFT, 4);  
    gotoTable[0]['E'] = 1;  
    gotoTable[0]['T'] = 2;  
    gotoTable[0]['F'] = 3;  

    // State 1
    actionTable[1]['+'] = Action(ActionType::SHIFT, 6);  
    actionTable[1]['$'] = Action(ActionType::ACCEPT, 0); 

    // State 2
    actionTable[2]['+'] = Action(ActionType::REDUCE, 1); 
    actionTable[2]['*'] = Action(ActionType::SHIFT, 7);  
    actionTable[2][')'] = Action(ActionType::REDUCE, 1); 
    actionTable[2]['$'] = Action(ActionType::REDUCE, 1); 

    // State 3
    actionTable[3]['+'] = Action(ActionType::REDUCE, 3); 
    actionTable[3]['*'] = Action(ActionType::REDUCE, 3); 
    actionTable[3][')'] = Action(ActionType::REDUCE, 3); 
    actionTable[3]['$'] = Action(ActionType::REDUCE, 3);

    // State 4
    actionTable[4]['i'] = Action(ActionType::SHIFT, 5);  
    actionTable[4]['('] = Action(ActionType::SHIFT, 4);  
    gotoTable[4]['E'] = 8;  
    gotoTable[4]['T'] = 2;  
    gotoTable[4]['F'] = 3;  

    // State 5
    actionTable[5]['+'] = Action(ActionType::REDUCE, 5); 
    actionTable[5]['*'] = Action(ActionType::REDUCE, 5); 
    actionTable[5][')'] = Action(ActionType::REDUCE, 5);
    actionTable[5]['$'] = Action(ActionType::REDUCE, 5); 

    // State 6
    actionTable[6]['i'] = Action(ActionType::SHIFT, 5);  
    actionTable[6]['('] = Action(ActionType::SHIFT, 4);  
    gotoTable[6]['T'] = 9; 
    gotoTable[6]['F'] = 3;  

    // State 7
    actionTable[7]['i'] = Action(ActionType::SHIFT, 5);  
    actionTable[7]['('] = Action(ActionType::SHIFT, 4);  
    gotoTable[7]['F'] = 10; 

    // State 8
    actionTable[8]['+'] = Action(ActionType::SHIFT, 6);  
    actionTable[8][')'] = Action(ActionType::SHIFT, 11); 

    // State 9
    actionTable[9]['+'] = Action(ActionType::REDUCE, 0); 
    actionTable[9]['*'] = Action(ActionType::SHIFT, 7);  
    actionTable[9][')'] = Action(ActionType::REDUCE, 0); 
    actionTable[9]['$'] = Action(ActionType::REDUCE, 0); 

    // State 10
    actionTable[10]['+'] = Action(ActionType::REDUCE, 2); 
    actionTable[10]['*'] = Action(ActionType::REDUCE, 2); 
    actionTable[10][')'] = Action(ActionType::REDUCE, 2); 
    actionTable[10]['$'] = Action(ActionType::REDUCE, 2); 

    // State 11
    actionTable[11]['+'] = Action(ActionType::REDUCE, 4); 
    actionTable[11]['*'] = Action(ActionType::REDUCE, 4); 
    actionTable[11][')'] = Action(ActionType::REDUCE, 4); 
    actionTable[11]['$'] = Action(ActionType::REDUCE, 4); 
}

    
    bool parse(const string& input) {
        stack<int> stateStack;
        stack<char> symbolStack;
        int currentState = 0;
        stateStack.push(0);
        
        size_t inputPos = 0;
        while (true) {
            char currentSymbol = (inputPos < input.length()) ? input[inputPos] : '$';
            
            auto stateIter = actionTable.find(currentState);
            if (stateIter == actionTable.end() || 
                stateIter->second.find(currentSymbol) == stateIter->second.end()) {
                cout << "Error: No action defined for state " << currentState 
                     << " and symbol " << currentSymbol << endl;
                return false;
            }
            
            Action action = actionTable[currentState][currentSymbol];
            
            switch (action.type) {
                case ActionType::SHIFT: {
                    stateStack.push(action.value);
                    symbolStack.push(currentSymbol);
                    currentState = action.value;
                    inputPos++;
                    break;
                }
                
                case ActionType::REDUCE: {
                
                    if (action.value >= static_cast<int>(grammar.size())) {
                        cout << "Error: Invalid reduction rule index" << endl;
                        return false;
                    }
                    Rule& rule = grammar[action.value];
                    
                    for (size_t i = 0; i < rule.production.length(); i++) {
                        if (stateStack.empty() || symbolStack.empty()) {
                            cout << "Error: Stack underflow during reduction" << endl;
                            return false;
                        }
                        stateStack.pop();
                        symbolStack.pop();
                    }
                    
                    symbolStack.push(rule.nonTerminal);
                    
                    currentState = stateStack.top();
                    auto gotoStateIter = gotoTable.find(currentState);
                    if (gotoStateIter == gotoTable.end() || 
                        gotoStateIter->second.find(rule.nonTerminal) == gotoStateIter->second.end()) {
                        cout << "Error: No goto defined for state " << currentState 
                             << " and non-terminal " << rule.nonTerminal << endl;
                        return false;
                    }
                    
                    int nextState = gotoTable[currentState][rule.nonTerminal];
                    stateStack.push(nextState);
                    currentState = nextState;
                    break;
                }
                
                case ActionType::ACCEPT:
                    return true;
                    
                case ActionType::ERROR:
                    cout << "Error at position " << inputPos << endl;
                    return false;
                    
                case ActionType::NONE:
                    cout << "Error: Invalid action type" << endl;
                    return false;
            }
        }
    }
    
    void printTables() {
        cout << "ACTION TABLE:" << endl;
        for (const auto& stateEntry : actionTable) {
            cout << "State " << stateEntry.first << ":" << endl;
            for (const auto& symbolEntry : stateEntry.second) {
                cout << "  " << symbolEntry.first << " -> ";
                switch (symbolEntry.second.type) {
                    case ActionType::SHIFT:
                        cout << "shift " << symbolEntry.second.value;
                        break;
                    case ActionType::REDUCE:
                        cout << "reduce " << symbolEntry.second.value;
                        break;
                    case ActionType::ACCEPT:
                        cout << "accept";
                        break;
                    case ActionType::ERROR:
                        cout << "error";
                        break;
                    case ActionType::NONE:
                        cout << "none";
                        break;
                }
                cout << endl;
            }
        }
        
        cout << "\nGOTO TABLE:" << endl;
        for (const auto& stateEntry : gotoTable) {
            cout << "State " << stateEntry.first << ":" << endl;
            for (const auto& symbolEntry : stateEntry.second) {
                cout << "  " << symbolEntry.first << " -> " << symbolEntry.second << endl;
            }
        }
    }
};

int main() {
    LRParser parser;
    
    parser.addRule('E', "E+T");   // E → E+T
    parser.addRule('E', "T");     // E → T
    parser.addRule('T', "T*F");   // T → T*F
    parser.addRule('T', "F");     // T → F
    parser.addRule('F', "(E)");   // F → (E)
    parser.addRule('F', "i");     // F → i
    
    parser.buildTables();
    
    // Print the tables
    parser.printTables();
    
    // Test parsing
    string input = "i+i*i";
    bool success = parser.parse(input);
    cout << "\nParsing " << input << ": " << (success ? "Success" : "Failed") << endl;
    
    return 0;
}
