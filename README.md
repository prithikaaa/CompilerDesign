# Compiler Design Mini Projects

This repository contains mini projects developed using concepts from **Compiler Design**, a core subject in Computer Science fundamentals. These projects are implemented in **C++** and cover various phases of compiler construction, including lexical analysis, syntax analysis, semantic analysis, and code generation.

## Table of Contents
- [Overview](#overview)
- [Projects](#projects)
  - [1. Balance Parenthesis](#1-balance-parenthesis)
  - [2. First & Follow Set Generator](#2-first--follow-set-generator)
  - [3. Infix to Postfix Converter](#3-infix-to-postfix-converter)
  - [4. LL(1) Parser](#4-ll1-parser)
  - [5. LR Parser](#5-lr-parser)
  - [6. Left Recursion Elimination](#6-left-recursion-elimination)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Overview
The mini projects demonstrate key components involved in compiler design. The goal is to provide a hands-on understanding of how a source program gets translated into machine code. Each project focuses on specific concepts and phases of compilation.

## Projects

### 1. Balance Parenthesis
Checks whether the parentheses in a given expression are balanced.

**Concepts Used:**
- Stack Data Structure

### 2. First & Follow Set Generator
Generates First and Follow sets for a given grammar, aiding in parser construction.

**Concepts Used:**
- Grammar Analysis
- Recursive Computation

### 3. Infix to Postfix Converter
Converts infix expressions to postfix notation to simplify evaluation.

**Concepts Used:**
- Stack-Based Algorithm
- Operator Precedence

### 4. LL(1) Parser
Implements an LL(1) parser to parse context-free grammars.

**Concepts Used:**
- Predictive Parsing
- Parsing Table Construction

### 5. LR Parser
Implements an LR parser for syntax analysis of programming languages.

**Concepts Used:**
- Shift-Reduce Parsing
- Parsing Table Generation

### 6. Left Recursion Elimination
Eliminates left recursion from a given grammar to make it suitable for top-down parsing.

**Concepts Used:**
- Grammar Transformation

## Setup and Installation
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/compiler-design-projects.git
   ```
2. **Navigate to the Project Directory:**
   ```bash
   cd compiler-design-projects
   ```
3. **Compile the Programs:**
   ```bash
   g++ -o balance_parenthesis "Balance Parenthesis.cpp"
   g++ -o first_follow "First&Follow.cpp"
   g++ -o infix_to_postfix "Infix to Postfix.cpp"
   g++ -o ll1_parser "LL1 Parser.cpp"
   g++ -o lr_parser "LR Parser.cpp"
   g++ -o left_recursion "Left Recursion.cpp"
   ```
4. **Run the Programs:**
   ```bash
   ./balance_parenthesis
   ./first_follow
   ./infix_to_postfix
   ./ll1_parser
   ./lr_parser
   ./left_recursion
   ```

## Usage
Each project folder contains a `README.md` with detailed usage instructions. Example:
```bash
./balance_parenthesis input.txt
```

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests for improvements and new features.


