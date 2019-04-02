#include "../header/command.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include "../header/base.hpp"
#include "../header/user.hpp"

using namespace std;

int MAX_SIZE = 1000;

class Base;
class User;
class Command;
class Connector;
class Input;

bool Command::execute() {
  // execvp - provide array of pointers to null-term strings that rep argument list for new program
  // MUST terminate by NULL

  stringstream ss(command);
  string temp;
  vector<char *> wordVec;
  // cout << command << endl;

  // while (ss >> temp) {
  //   wordVec.push_back((char *)temp.c_str());
  // }

  if (command == "exit") {
    exit(0);
  }

  char *input;
  input = strtok((char *)this->command.c_str(), " ");
  while (input != NULL) {
    wordVec.push_back(input);
    input = strtok(NULL, " ");
  }

  char **argVec = new char *[wordVec.size() + 1];

  for (unsigned i = 0; i < wordVec.size(); ++i) {
    argVec[i] = wordVec[i];
    // cout << wordVec.at(i) << endl;
  }

  argVec[wordVec.size()] = NULL;

  // fork - create a child process (2 duplicate)
  pid_t pid = fork();

  if (pid == -1) {
    perror("fork");
    exit(1);
  }
  // child process
  if (pid == 0) {
    if (execvp(argVec[0], argVec) == -1) {
      perror("exec");
      exit(1);
    }
  }
  //parent process //commenting htis part out for testing
  int status;
  if (pid > 0) {
    waitpid(pid, &status, 0);
    if (status > 0) {
      //this is bad !
      return false;
    } else if (WEXITSTATUS(status) == 0) {
      return true;
    } else if (WEXITSTATUS(status) == 1) {
      return false;
    }
  }
  return false;
}

bool TestCommand::execute() {
  struct stat info;
  string command2;
  string newFile;

  string e = "-e";  //	checks if the file/directory exists
  string f = "-f";  //	checks if the file/directory exists and is a regular file
  string d = "-d";  //checks if the file/directory exists and is a directory
  string testz = "test";
  string dash = "-";

  size_t Find_e = command.find(e);
  size_t Find_f = command.find(f);
  size_t Find_d = command.find(d);
  size_t Find_testz = command.find(testz);
  size_t Find_dash = command.find(dash);

  if (Find_dash != string::npos) {                                                     //if found a dash
    if (Find_f == string::npos && Find_d == string::npos && Find_e == string::npos) {  //only gets here if found a dash and
      cout << "(False)" << endl;
      cout << "What came after the dash was not a valid input, try again" << endl;
      return false;
    }
    if (command.at(Find_dash + 2) != ' ') {  //if what comes 2 after the dash isnt  " "
      cout << "(False)" << endl;
      cout << "invalid dash input" << endl;
      return false;
    }
  }

  if (Find_f == string::npos && Find_d == string::npos && Find_e == string::npos) {  //where we find do not find a "-f", "-d", or "-e"

    //cout << "in if statement where no f d or e" << endl;

    //this one seems to work perfectly

    if (command.at(0) == '[' && command.at(command.size() - 1) == ']') {
      command2 = command.substr(1, command.size() - 2);
      stringstream streams(command2);
      streams >> newFile;  // fill newfile
      command2 = newFile;  //update command
    } else {
      command2 = command.substr(5);  //online says do 5 but not sure why
    }
    //}

    if (stat(command2.c_str(), &info) == 0) {
      cout << "(True)" << endl;
      return true;
    } else {
      cout << "(False)" << endl;
      return false;
    }
  }

  // ----------------------TELL ME WHY MY LIFE SUCKS --------------------------------

  if (Find_e != string::npos) {  //if you found a "-e"
    if (Find_e != string::npos) {
      command2 = command.substr(Find_e + 3);
      if (command2.back() == ']' && command2.at(command2.size() - 2) == ' ') {
        stringstream streams(command2);
        streams >> newFile;
        command2 = newFile;
      }
    } else {
      if (command.at(0) == '[' && command.at(command.size() - 1) == ']') {
        command2 = command.substr(1, command.size() - 2);
        stringstream streams(command2);
        streams >> newFile;
        command2 = newFile;
      } else {
        command2 = command.substr(5);
      }
    }

    if (stat(command2.c_str(), &info) == 0) {
      cout << "(True)" << endl;
      return true;
    } else {
      cout << "(False)" << endl;
      return false;
    }
  }

  else if (Find_f != string::npos) {  //if you found a "-f"
    if (Find_f != string::npos) {
      command2 = command.substr(Find_f + 3);
      if (command2.back() == ']' && command2.at(command2.size() - 2) == ' ') {
        stringstream streams(command2);
        streams >> newFile;
        command2 = newFile;
      }
    } else {
      if (command.at(0) == '[' && command.at(command.size() - 1) == ']') {
        command2 = command.substr(1, command.size() - 2);
        stringstream streams(command2);
        streams >> newFile;
        command2 = newFile;
      } else {
        command2 = command.substr(5);
      }
    }

    if (stat(command2.c_str(), &info) == 0) {
      // https://stackoverflow.com/questions/40163270/what-is-s-isreg-and-what-does-it-do
      // how to use S_ISREG
      if (S_ISREG(info.st_mode)) {
        cout << "(True)" << endl;
        return true;
      } else {
        cout << "(False)" << endl;
      }
    } else {
      cout << "(False)" << endl;
      return false;
    }
  }

  else if (Find_d != string::npos) {  //if you found a "-d"
    if (Find_d != string::npos) {
      command2 = command.substr(Find_d + 3);
      if (command2.back() == ']' && command2.at(command2.size() - 2) == ' ') {
        stringstream streams(command2);
        streams >> newFile;
        command2 = newFile;
      }
    } else {
      if (command.at(0) == '[' && command.at(command.size() - 1) == ']') {
        command2 = command.substr(1, command.size() - 2);
        stringstream streams(command2);
        streams >> newFile;
        command2 = newFile;
      } else {
        command2 = command.substr(5);
      }
    }

    if (stat(command2.c_str(), &info) != 0) {
      cout << "(False)" << endl;
      return false;
    }
    // https://stackoverflow.com/questions/14643054/testing-directory-suing-s-isdir-but-it-doesnt-work
    // how to use S_ISDIR
    else if (S_ISDIR(info.st_mode)) {
      cout << "(True)" << endl;
      return true;
    } else {
      cout << "(False)" << endl;
      return false;
    }
  }
}
