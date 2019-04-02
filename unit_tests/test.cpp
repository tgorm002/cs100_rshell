#include <iostream>
#include <sstream>
#include <string>
#include "../header/and.hpp"
#include "../header/base.hpp"
#include "../header/command.hpp"
#include "../header/connector.hpp"
#include "../header/input.hpp"
#include "../header/or.hpp"
#include "../header/output1.hpp"
#include "../header/output2.hpp"
#include "../header/semi.hpp"
#include "../header/user.hpp"

#include "gtest/gtest.h"

using namespace std;

// TEST(OutputRedirection, CheckBuffer) {
//   // stringstream buffer;
//   // streambuf *sbuf = cout.rdbuf();

//   // std cout.rdbuf(buffer.rdbuf());

//   User *u = new User();

//   string s1 = "echo hello >> file.txt";
//   string s2 = "echo hi there > file.txt";
//   string s3 = "echo append this >> file.txt";
//   string s4 = "echo append that >> file.txt";

//   vector<Base *> userInput = {
//       u->parsing(s1),
//       u->parsing(s2),
//       u->parsing(s3),
//       u->parsing(s4)};

//   testing::internal::CaptureStdout();
//   for (unsigned i = 0; i < userInput.size(); ++i) {
//     userInput[i]->execute();
//   }

//   string output1 = testing::internal::GetCapturedStdout();
//   EXPECT_EQ("hi there\nappend this\nappend that\n", output1);

//   string s5 = "test -e file.txt";
//   EXPECT_TRUE(u->parsing(s5));

//   delete u;
// }

TEST(inputTest1, LiveLoveNicole) {
  string testing = "wc -l < names.txt";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(intputTest2, LiveLoveNicole) {
  string testing = "wc -l < fjdakljflaks.fhdasjkfhadkls";  //an invlaid location
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(inputTest3, LiveLoveNicole) {
  string testing = "tail < CMakeLists.txt || ls ";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(inputTest4, LiveLoveNicole) {
  string testing = "tail < CMakeLists.txt && ls ";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(inputTest5, LiveLoveNicole) {
  string testing = "I Love Gurneet Kaur && tail < CMakeLists.txt";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

//---------------------------------------------------------------------------------------------------------------------------------

TEST(output1Test1, LiveLoveLaugh) {
  string testing = "cat names.txt > names2.txt";  //under the ass that it has not been created yet
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(output1Test2, LiveLoveLaugh) {
  string testing = "cat names.txt > names2.txt";  //under the ass that it has been created already and will now fill it
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(output1Test3, LiveLoveLaugh) {
  string testing = "cat names.txt > names2.txt";  //under the ass that it has been created and filled already
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

//---------------------------------------------------------------------------------------------------------------------------------

TEST(output2Test1, LiveLoveLaughz) {
  string testing = "cat names.txt >> names3.txt";  //under the ass that it has not been created yet
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(output2Test2, LiveLoveLaughz) {
  string testing = "cat names.txt >> names3.txt";  //under the ass that it has been created already and will now fill it
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(output2Test3, LiveLoveLaughz) {
  string testing = "cat names.txt >> names3.txt";  //under the ass that it has been created and filled already
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

//---------------------------------------------------------------------------------------------------------------------------------

TEST(PipeTest1, MarioAndLuigi) {
  string testing = "ls | more";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(PipeTest2, MarioAndLuigi) {
  string testing = "ls | more && echo hello there";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(PipeTest3, MarioAndLuigi) {
  string testing = "ls | less";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(PipeTest4, MarioAndLuigi) {
  string testing = "cat CMakeLists.txt | sort -r";
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}


//---------------------------------------------------------------------------------------------------------------------------------

TEST(TestCommand1, SimpleTest) {
  string testing = "test -e src/main.cpp";  // a valid location
  Command *test = new TestCommand(testing);
  EXPECT_TRUE(test->execute());
  delete test;
}

TEST(TestCommand2, SimpleTest) {
  string testing = "test -e srcccccc/NICOLE.cpp";  // a non-valid location so expect false
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(TestCommand3, SimpleTest) {
  string testing = "test -f src/main.cpp";  // a valid location
  Command *test = new Command(testing);
  EXPECT_TRUE(test->execute());
  delete test;
}

TEST(TestCommand4, SimpleTest) {
  string testing = "test -d src";  // a valid location
  Command *test = new Command(testing);
  EXPECT_TRUE(test->execute());
  delete test;
}

TEST(TestCommand5, LargeTest) {
  User *u = new User();

  string testing1 = "test -e src/main.cpp && echo work";
  string testing2 = "test -f src/main.cpp && echo testing";
  string testing3 = "(test -d src) || echo b";

  vector<Base *> userInput = {
      u->parsing(testing1),
      u->parsing(testing2),
      u->parsing(testing3)};

  testing::internal::CaptureStdout();
  userInput[0]->execute();
  string s1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("(True)\nwork\n", s1);

  testing::internal::CaptureStdout();
  userInput[1]->execute();
  string s2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("(True)\ntesting\n", s2);

  testing::internal::CaptureStdout();
  userInput[2]->execute();
  string s3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("(True)\n", s3);

  delete u;
}

TEST(TestSymbolic1, SimpleTest) {
  string testing = "[ -e src/main.cpp ]";  // a valid location
  Command *test = new Command(testing);
  EXPECT_TRUE(test->execute());
  delete test;
}

TEST(TestSymbolic2, SimpleTest) {
  string testing = "[ -e srcccccc/NICOLE.cpp ]";  // a non-valid location so expect false
  Command *test = new Command(testing);
  EXPECT_FALSE(test->execute());
  delete test;
}

TEST(TestSymbolic3, SimpleTest) {
  string testing = "[ -f src/main.cpp ]";  // a valid location
  Command *test = new Command(testing);
  EXPECT_TRUE(test->execute());
  delete test;
}

TEST(TestSymbolic4, SimpleTest) {
  string testing = "[ -d src ]";  // a valid location
  Command *test = new Command(testing);
  EXPECT_TRUE(test->execute());
  delete test;
}

TEST(TestSymbolic5, LargeTest) {
  User *u = new User();

  string testing1 = "[ -e src/main.cpp ] && echo work";
  string testing2 = "[ -f src/main.cpp ] && echo testing";
  string testing3 = "[ -d src ] || echo b";

  vector<Base *> userInput = {
      u->parsing(testing1),
      u->parsing(testing2),
      u->parsing(testing3)};

  testing::internal::CaptureStdout();
  userInput[0]->execute();
  string s1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("(True)\nwork\n", s1);

  testing::internal::CaptureStdout();
  userInput[1]->execute();
  string s2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("(True)\ntesting\n", s2);

  testing::internal::CaptureStdout();
  userInput[2]->execute();
  string s3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("(True)\n", s3);

  delete u;
}

//--------------------------------------------TELL ME WHY AINT NOTHING BUT A MISTAKE ----------- TELL ME WHY-----------------------
//-------------------------------------NOW NUMBER FIVE--------------------------- I NEVER WANNA HEAR YOU SAY ----------------------

TEST(CommandTestSet, EchoCommand) {
  string s1 = "echo hello";
  Command *test1 = new Command(s1);
  EXPECT_TRUE(test1->execute());
  delete test1;

  string s2 = "echo \"hello\"";
  Command *test2 = new Command(s2);
  EXPECT_TRUE(test2->execute());
  delete test2;

  string s3 = "echo hello world";
  Command *test3 = new Command(s3);
  EXPECT_TRUE(test3->execute());
  delete test3;

  string s4 = "echo ab#cde";
  Command *test4 = new Command(s4);
  EXPECT_TRUE(test4->execute());
  delete test4;

  string s5 = "echo";
  Command *test5 = new Command(s5);
  EXPECT_TRUE(test5->execute());
  delete test5;

  string s6 = "echo beef#jerky && echo hihihi";
  Command *test6 = new Command(s6);
  EXPECT_TRUE(test6->execute());
  delete test6;

  string s7 = "echo \"bold party mix\" && echo \"chex mixxx\"";
  Command *test7 = new Command(s7);
  EXPECT_TRUE(test7->execute());
  delete test7;
}

TEST(CommandTestSet, LsCommand) {
  string s1 = "ls -a";
  Command *test1 = new Command(s1);
  EXPECT_TRUE(test1->execute());
  delete test1;

  string s2 = "ls";
  Command *test2 = new Command(s2);
  EXPECT_TRUE(test2->execute());
  delete test2;

  string s3 = "-a";
  Command *test3 = new Command(s3);
  EXPECT_FALSE(test3->execute());
  delete test3;

  string s4 = "ls-a";
  Command *test4 = new Command(s4);
  EXPECT_FALSE(test4->execute());
  delete test4;
}

TEST(CommandTestSet, MkdirCommand) {
  string s1 = "mkdir file1";
  Command *test1 = new Command(s1);
  EXPECT_TRUE(test1->execute());
  delete test1;

  string s2 = "rm-rffile1";
  Command *test2 = new Command(s2);
  EXPECT_FALSE(test2->execute());
  delete test2;

  string s3 = "rm -rf file1";
  Command *test3 = new Command(s3);
  EXPECT_TRUE(test3->execute());
  delete test3;

  string s4 = "mkdir";
  Command *test4 = new Command(s4);
  EXPECT_FALSE(test4->execute());
  delete test4;

  string s5a = "mkdir pineapple";
  Command *test5a = new Command(s5a);
  EXPECT_TRUE(test5a->execute());
  delete test5a;

  string s5b = "rm -rf pineapple";
  Command *test5b = new Command(s5b);
  EXPECT_TRUE(test5b->execute());
  delete test5b;

  string s6 = "mkdir V#$$...";
  Command *test6 = new Command(s6);
  EXPECT_TRUE(test6->execute());
  delete test6;

  string s7 = "rm -rf V#$$...";
  Command *test7 = new Command(s7);
  EXPECT_TRUE(test7->execute());
  delete test7;
}

// TEST(CommandTestSet, allCommands) {
//   string s1a = "ls -a || echo an apple tree && mkdir file2";
//   Command *test1a = new Command(s1a);
//   EXPECT_TRUE(test1a->execute());
//   delete test1a;

//   string s1b = "rm -rf file2";
//   Command *test1b = new Command(s1b);
//   EXPECT_TRUE(test1b->execute());
//   delete test1b;

//   string s2a = "ls -a && echo \"hello\" || mkdir file3 ; mkdir file4";
//   Command *test2a = new Command(s2a);
//   EXPECT_FALSE(test2a->execute());
//   delete test2a;

//   string s2b = "rm -rf file3 && rm -rf file4";
//   Command *test2b = new Command(s2b);
//   EXPECT_TRUE(test2b->execute());
//   delete test2b;

//   string s3a = "echo all that's not falls down && ls ; mkdir \"file5;\"";
//   Command *test3a = new Command(s3a);
//   EXPECT_TRUE(test3a->execute());
//   delete test3a;

//   string s3b = "rm -rf file5 || echo hey && ls";
//   Command *test3b = new Command(s3b);
//   EXPECT_TRUE(test3b->execute());
//   delete test3b;

//   string s4 = "echo ; ls ; mkdir";
//   Command *test4 = new Command(s4);
//   EXPECT_TRUE(test4->execute());
//   delete test4;
// }

TEST(UserTests, ParseFunction) {
  User *u = new User();
  string t1 = "echo map # || echo ls";
  string t2 = "echo an && echo apple || echo orange";
  string t3 = "echo test || echo what && echo whale";
  vector<Base *> userInput = {u->parsing(t1), u->parsing(t2), u->parsing(t3)};

  testing::internal::CaptureStdout();
  userInput[0]->execute();
  string s1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("map\n", s1);

  testing::internal::CaptureStdout();
  userInput[1]->execute();
  string s2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("an\napple\n", s2);

  testing::internal::CaptureStdout();
  userInput[2]->execute();
  string s3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("test\nwhale\n", s3);
}

TEST(PrecedenceTests, SimpleParentheses) {
  User *u = new User();
  string t1 = "(echo hello)";
  string t2 = "(echo hello there)";
  string t3 = "(echo b) && echo a";
  string t4 = "(echo a && echo b)";
  string t5 = "echo b && (echo a) || echo c";
  string t6 = "(echo hi || ls) || echo b";
  string t7 = "echo A && (echo b || echo c)";
  string t8 = "echo c || (echo a && echo b)";
  string t9 = "echo sup t || (echo hi && echo c) && echo d";
  string t10 = "(echo a && echo b) || (echo c && echo d)";
  string t11 = "echo b && (echo h || echo c && echo d)";
  string t12 = "(echo b && (echo c || echo d) && echo v)";

  vector<Base *> userInput = {
      u->parsing(t1),
      u->parsing(t2),
      u->parsing(t3),
      u->parsing(t4),
      u->parsing(t5),
      u->parsing(t6),
      u->parsing(t7),
      u->parsing(t8),
      u->parsing(t9),
      u->parsing(t10),
      u->parsing(t11),
      u->parsing(t12)};

  testing::internal::CaptureStdout();
  userInput[0]->execute();
  string s1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("hello\n", s1);

  testing::internal::CaptureStdout();
  userInput[1]->execute();
  string s2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("hello there\n", s2);

  testing::internal::CaptureStdout();
  userInput[2]->execute();
  string s3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("b\na\n", s3);

  testing::internal::CaptureStdout();
  userInput[3]->execute();
  string s4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("a\nb\n", s4);

  testing::internal::CaptureStdout();
  userInput[4]->execute();
  string s5 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("b\na\n", s5);

  testing::internal::CaptureStdout();
  userInput[5]->execute();
  string s6 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("hi\n", s6);

  testing::internal::CaptureStdout();
  userInput[6]->execute();
  string s7 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("A\nb\n", s7);

  testing::internal::CaptureStdout();
  userInput[7]->execute();
  string s8 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("c\n", s8);

  testing::internal::CaptureStdout();
  userInput[8]->execute();
  string s9 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("sup t\nd\n", s9);

  testing::internal::CaptureStdout();
  userInput[9]->execute();
  string s10 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("a\nb\n", s10);

  testing::internal::CaptureStdout();
  userInput[10]->execute();
  string s11 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("b\nh\nd\n", s11);

  testing::internal::CaptureStdout();
  userInput[11]->execute();
  string s12 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("b\nc\nv\n", s12);

  delete u;
}

TEST(PrecedenceTests, MultipleParentheses) {
  User *u = new User();

  string p1 = "((echo b && echo c) && echo d)";
  string p2 = "echo b && (echo h && (echo c && echo d))";
  string p3 = "echo sup t || (echo hi && (echo c && echo d))";
  string p4 = "echo a && ((echo b && echo c)) && echo d";

  vector<Base *> userInput = {
      u->parsing(p1),
      u->parsing(p2),
      u->parsing(p3),
      u->parsing(p4)};

  testing::internal::CaptureStdout();
  userInput[0]->execute();
  string s1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("b\nc\nd\n", s1);

  testing::internal::CaptureStdout();
  userInput[1]->execute();
  string s2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("b\nh\nc\nd\n", s2);

  testing::internal::CaptureStdout();
  userInput[2]->execute();
  string s3 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("sup t\n", s3);

  testing::internal::CaptureStdout();
  userInput[3]->execute();
  string s4 = testing::internal::GetCapturedStdout();
  EXPECT_EQ("a\nb\nc\nd\n", s4);
}

// TEST(CommandTestSet, ExitCommand) {
//   string s1 = "exit";
//   Command *test1 = new Command(s1);
//   EXPECT_TRUE(test1->execute());
//   delete test1;

//   string s2 = "(exit)";
//   Command *test2 = new Command(s2);
//   EXPECT_FALSE(test2->execute());
//   delete test2;

//   string s3 = "ls && exit";
//   Command *test3 = new Command(s3);
//   EXPECT_TRUE(test3->execute());
//   delete test3;

//   string s4 = "echo hi || exit";
//   Command *test4 = new Command(s4);
//   EXPECT_TRUE(test4->execute());
//   delete test4;

//   string s5 = "exit || mkdir file";
//   Command *test5 = new Command(s5);
//   EXPECT_TRUE(test5->execute());
//   delete test5;

//   string s6 = "\"exit\"";
//   Command *test6 = new Command(s6);
//   EXPECT_TRUE(test6->execute());
//   delete test6;
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
