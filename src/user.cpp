#include "../header/user.hpp"
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "../header/base.hpp"
// #include "boost/tokenizer.hpp"
#include "../header/and.hpp"
#include "../header/command.hpp"
#include "../header/connector.hpp"
#include "../header/input.hpp"
#include "../header/or.hpp"
#include "../header/output1.hpp"
#include "../header/output2.hpp"
#include "../header/pipe.hpp"
#include "../header/semi.hpp"

using namespace std;
// using namespace boost;

class Base;

void User::opening() {
  root->execute();
}

Base *User::parsing(string &str) {
  // stack of connectors
  stack<string> op;
  stack<string> pcounter;

  string command = "";
  string temp = "";
  bool quote = false;
  bool comment = false;
  bool parentheses = false;
  bool semicolon = false;

  for (unsigned i = 0; i < str.size(); ++i) {
    if (str.at(i) == '\"') {
      quote = true;
    }

    if (!quote) {
      if (str.at(i) == '(') {
        pcounter.push("(");
      }
    }
  }

  quote = false;

  stringstream ss(str);
  while (ss >> temp) {
    if (!quote && temp.at(0) == '#') {
      break;
    }

    // cout << "TEMP GOES TO BEGINNING OF WHILE LOOP" << endl;
    if (temp.at(0) == '\"') {
      quote = true;
      // temp = temp.substr(1, temp.size() - 1);
      // cout << temp << endl;
    }

    if (temp == "(") {
      op.push(temp);

    } else if (temp.at(0) == '(') {
      string paren = "(";
      int index = 0;

      for (unsigned i = 0; i < temp.size(); ++i) {
        if (temp.at(i) == '(') {
          op.push(paren);
        } else {
          index = i;
          break;
        }
      }

      command = command + temp.substr(index, temp.size() - 1);
      // cout << "Command at front parentheses: " << command << endl;
    }

    if (temp.find(')') != string::npos) {
      parentheses = true;
      int count = 0;

      for (unsigned i = 0; i < temp.size(); ++i) {
        if (temp.at(i) == ')') {
          count++;
        }
      }

      // cout << "command before back parentheses: " << command << endl;

      if (quote) {
        command = command + " " + temp.substr(0, temp.find('\"'));

      } else {
        command = command + " " + temp.substr(0, temp.find(')'));
      }

      // cout << "Command at back parentheses: " << command << endl;
      // argVec.push_back(command);
      // command = "";

      while (!op.empty() && !pcounter.empty() && (op.top() != "(")) {
        if (command != "") {
          argVec.push_back(command);
          command = "";
        }

        // cout << "op.top rn is: " << op.top() << endl;
        argVec.push_back(op.top());
        op.pop();

        if (op.top() == "(" && count != 1) {
          op.pop();
          pcounter.pop();
          count--;
        }
      }

      if ((op.top() == "(") && !(op.empty()) && !pcounter.empty()) {
        // cout << "popping op stack: " << op.top() << endl;
        op.pop();
        pcounter.pop();

        if (!(op.empty())) {
          // cout << "top after popping stack is: " << op.top() << endl;
        }
      }
    }

    if (!quote && (temp == "|" || temp == "<" || temp == ">" || temp == ">>")) {
      if (command != "") {
        argVec.push_back(command);
        command = "";
      }

      while (!op.empty() && (op.top() == "|" || op.top() == "<" || op.top() == ">" || op.top() == ">>")) {
        argVec.push_back(op.top());
        op.pop();
      }
      op.push(temp);

    } else if (!quote && (temp == "&&" || temp == "||" || temp == ";")) {
      // cout << "entering loop of operator" << endl;
      // cout << "command before op check is: " << command << endl;

      if (command != "" && command.at(0) == ' ') {
        command = command.substr(1, command.size() - 1);
      }

      if (command != "") {
        argVec.push_back(command);
        command = "";
      }

      while (!(op.empty()) && (op.top() == "&&" || op.top() == "||" || op.top() == "|" || op.top() == "<" || op.top() == ">" || op.top() == ">>")) {
        // cout << "while loop for op.top == &&/||" << endl;
        argVec.push_back(op.top());
        op.pop();
      }
      op.push(temp);

    } else if (!quote && temp.find(';') != string::npos) {
      semicolon = true;
      temp = temp.substr(0, temp.find(';'));
      // cout << "command before append: " << command << endl;
      if (command != "") {
        command = command + " " + temp;
      } else {
        command = command + temp;
      }
      // cout << "command after appending temp: " << command << endl;
      argVec.push_back(command);
      command = "";

      // if (!op.empty()) {
      //   cout << "op before semi push: " << op.top() << endl;
      // }

      string semi = ";";
      op.push(semi);

      // cout << "op after semi push: " << op.top() << endl;

      while (!op.empty() && op.top() != ";") {
        // cout << "whats up how it do" << endl;
        argVec.push_back(op.top());
        op.pop();
      }

    } else {
      // cout << "entering where it is not an op" << endl;

      if (temp.at(0) != '(' && temp.at(temp.size() - 1) != ')') {
        if (quote) {
          if (temp.at(0) == '\"') {
            temp = temp.substr(1, temp.size() - 1);
          }
          command = command + " " + temp;

          if (command.find('\"') != string::npos) {
            command = command.substr(0, command.find('\"'));
            quote = false;
          }
        } else {
          // cout << "when it enters here command is:" << command << endl;
          if (command == "") {
            command = command + temp;

          } else {
            command = command + " " + temp;
          }
        }
      }
      // cout << "Command: " << command << endl;
    }
  }

  // cout << "command after while loop: " << command << endl;
  if (!parentheses) {
    argVec.push_back(command);
    // cout << argVec.at(0) << endl;
    command = "";
  }

  // cout << "passed last command push back" << endl;

  if (command != "") {
    argVec.push_back(command);
    command = "";
  }

  while (!(op.empty())) {
    // cout << "op is not empty, op.top is: " << op.top() << endl;
    if (op.top() != "(") {
      argVec.push_back(op.top());
      op.pop();
    } else {
      op.pop();
    }
  }

  // for (unsigned i = 0; i < argVec.size(); ++i) {
  //   cout << "-------" << argVec.at(i) << "------" << endl;
  // }

  stack<Base *>
      tree;

  for (auto it : argVec) {
    // cout << it << endl;

    if (!(it == "&&" || it == "||" || it == ";" || it == "|" || it == "<" || it == ">" || it == ">>")) {
      if (it.at(0) == '[' || it.substr(0, 4) == "test") {
        tree.push(new TestCommand(it));
      } else {
        tree.push(new Command(it));
      }
    } else {
      Base *right = tree.top();
      tree.pop();
      Base *left = tree.top();
      tree.pop();

      if (it == "&&") {
        tree.push(new AndConnector(left, right));
      }
      if (it == "||") {
        tree.push(new OrConnector(left, right));
      }
      if (it == ";") {
        tree.push(new SemiConnector(left, right));
      }
      if (it == "|") {
        tree.push(new Pipe(left, right));
      }
      if (it == "<") {
        tree.push(new Input(left, right));
      }
      if (it == ">") {
        // cout << "pushing new output1" << endl;
        tree.push(new Output1(left, right));
      }
      if (it == ">>") {
        tree.push(new Output2(left, right));
      }
    }
  }

  this->root = tree.top();
  return root;
}
