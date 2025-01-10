struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

bool isBalanced(const string& str, int& index, TreeNode*& node) {
    if (index >= str.length()) {
        return true;
    }

    if (str[index] == '(') {
        node = new TreeNode("(");
        index++;

        node->left = new TreeNode("S");
        if (!isBalanced(str, index, node->left)) {
            return false;
        }

        if (index >= str.length() || str[index] != ')') {
            return false;
        }

        node->right = new TreeNode(")");
        index++;

        node->right->right = new TreeNode("S");
        return isBalanced(str, index, node->right->right);
    }

    node = new TreeNode("ε");
    return true;
}
void printParseTree(TreeNode* node, int level = 0) {
    if (node == nullptr) return;

    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }

    cout << node->value << endl;

    printParseTree(node->left, level + 1);
    printParseTree(node->right, level + 1);
}

int main() {
    string input;
    cout << "Enter a string of parentheses: ";
    cin >> input;

    TreeNode* parseTree = nullptr;
    int index = 0;

    if (isBalanced(input, index, parseTree) && index == input.length()) {
        cout << "The string belongs to the grammar." << endl;
        cout << "Parse Tree:" << endl;
        printParseTree(parseTree);
    } else {
        cout << "The string does NOT belong to the grammar." << endl;
    }

    return 0;
}
