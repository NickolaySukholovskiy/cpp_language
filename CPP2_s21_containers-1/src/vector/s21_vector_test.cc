#include "s21_vector.h"

#include <gtest/gtest.h>

TEST(Constructor, Subtest_1) {
  s21::vector<int> test;
  ASSERT_EQ(test.Empty(), true);
  ASSERT_EQ(test.capacity(), 100);
}

TEST(Constructor, Subtest_2) {
  ASSERT_THROW(s21::vector<int> test(-3), std::invalid_argument);
}

TEST(Constructor, Subtest_3) {
  s21::vector<int> test(3);
  ASSERT_EQ(test.Empty(), true);
  ASSERT_EQ(test.capacity(), 3);
}

TEST(Constructor, Subtest_4) {
  ASSERT_THROW(s21::vector<int> test(-3, 6), std::invalid_argument);
}

TEST(Constructor, Subtest_5) {
  s21::vector<int> test(3, 6);
  ASSERT_EQ(test.Empty(), false);
  ASSERT_EQ(test.capacity(), 3);
  ASSERT_EQ(test.size(), 3);
  ASSERT_EQ(test[2], 6);
}

TEST(Constructor, Subtest_6) {
  s21::vector<int> test({});
  ASSERT_EQ(test.Empty(), true);
  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.size(), 0);
}

TEST(Constructor, Subtest_7) {
  s21::vector<int> test({0, 1, 2, 3, 4, 5, 6, 7});
  ASSERT_EQ(test.Empty(), false);
  ASSERT_EQ(test.capacity(), 8);
  ASSERT_EQ(test.size(), 8);
  for (int i = 0; i < test.size(); i++) {
    ASSERT_EQ(test[i], i);
  }
}

TEST(Constructor, Subtest_8) {
  s21::vector<int> test_1({0, 1, 2, 3, 4, 5, 6, 7});
  s21::vector<int> test_2(test_1);
  ASSERT_EQ(test_2.Empty(), false);
  ASSERT_EQ(test_2.capacity(), 8);
  ASSERT_EQ(test_2.size(), 8);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], test_2[i]);
  }
}

TEST(Constructor, Subtest_9) {
  s21::vector<int> test_1({});
  s21::vector<int> test_2(test_1);
  ASSERT_EQ(test_2.Empty(), true);
  ASSERT_EQ(test_2.capacity(), 0);
  ASSERT_EQ(test_2.size(), 0);
}

TEST(Constructor, Subtest_10) {
  s21::vector<int> test_1({});
  s21::vector<int> test_2(&test_1);
  ASSERT_EQ(test_2.Empty(), true);
  ASSERT_EQ(test_2.capacity(), 0);
  ASSERT_EQ(test_2.size(), 0);
}

TEST(Constructor, Subtest_11) {
  s21::vector<int> test_1({0, 1, 2, 3, 4, 5, 6, 7});
  s21::vector<int> test_2(&test_1);
  ASSERT_EQ(test_2.Empty(), false);
  ASSERT_EQ(test_2.capacity(), 8);
  ASSERT_EQ(test_2.size(), 8);
  ASSERT_EQ(test_1.Empty(), true);
  ASSERT_EQ(test_1.capacity(), 0);
  ASSERT_EQ(test_1.size(), 0);
}

TEST(Destructor, Subtest_1) {
  s21::vector<int> test;
  test.~vector();
  ASSERT_EQ(test.Empty(), true);
  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.size(), 0);
}

TEST(Destructor, Subtest_2) {
  s21::vector<char> test(5);
  test.~vector();
  ASSERT_EQ(test.Empty(), true);
  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.size(), 0);
}

TEST(Destructor, Subtest_3) {
  s21::vector<char> test(5, 'g');
  test.~vector();
  ASSERT_EQ(test.Empty(), true);
  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.size(), 0);
}

TEST(Destructor, Subtest_4) {
  s21::vector<char> test({'a', 'b', 'c', 'd'});
  test.~vector();
  ASSERT_EQ(test.Empty(), true);
  ASSERT_EQ(test.capacity(), 0);
  ASSERT_EQ(test.size(), 0);
}

TEST(Destructor, Subtest_5) {
  s21::vector<char> test_1({'a', 'b', 'c', 'd'});
  s21::vector<char> test_2(test_1);
  test_1.~vector();
  ASSERT_EQ(test_1.Empty(), true);
  ASSERT_EQ(test_1.capacity(), 0);
  ASSERT_EQ(test_1.size(), 0);
  ASSERT_EQ(test_2.Empty(), false);
  ASSERT_EQ(test_2.capacity(), 4);
  ASSERT_EQ(test_2.size(), 4);
  test_2.~vector();
  ASSERT_EQ(test_2.Empty(), true);
  ASSERT_EQ(test_2.capacity(), 0);
  ASSERT_EQ(test_2.size(), 0);
}

TEST(Destructor, Subtest_6) {
  s21::vector<char> test_1({'a', 'b', 'c', 'd'});
  s21::vector<char> test_2(&test_1);
  ASSERT_EQ(test_1.Empty(), true);
  ASSERT_EQ(test_1.capacity(), 0);
  ASSERT_EQ(test_1.size(), 0);
  ASSERT_EQ(test_2.Empty(), false);
  ASSERT_EQ(test_2.capacity(), 4);
  ASSERT_EQ(test_2.size(), 4);
  test_2.~vector();
  ASSERT_EQ(test_2.Empty(), true);
  ASSERT_EQ(test_2.capacity(), 0);
  ASSERT_EQ(test_2.size(), 0);
}

TEST(Geters, Subtest_1) {
  s21::vector<char> test_1({'a', 'b', 'c', 'd'});
  ASSERT_THROW(test_1[-3], std::out_of_range);
  ASSERT_THROW(test_1[6], std::out_of_range);
}

TEST(Geters, Subtest_2) {
  s21::vector<char> test_1({'a', 'b', 'c', 'd'});
  ASSERT_EQ(test_1[1], 'b');
}

TEST(Geters, Subtest_3) {
  s21::vector<char> test_1({'a', 'b', 'c', 'd'});
  ASSERT_THROW(test_1.At(-3), std::out_of_range);
  ASSERT_THROW(test_1.At(6), std::out_of_range);
}

TEST(Geters, Subtest_4) {
  std::string answers[] = {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  for (int i = 0; i < test_1.size(); i++) {
    std::string *pointer = test_1.At(i);
    ASSERT_EQ(*pointer, answers[i]);
  }
}

TEST(Geters, Subtest_5) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  ASSERT_EQ(test_1.front(), test_1.At(0));
}

TEST(Geters, Subtest_6) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  ASSERT_EQ(test_1.Back(), test_1.At(5));
}

TEST(Geters, Subtest_7) {
  s21::vector<std::string> test_1({});
  ASSERT_EQ(test_1.Back(), nullptr);
  ASSERT_EQ(test_1.front(), nullptr);
}

TEST(Check, Subtest_1) {
  s21::vector<std::string> test_1({});
  ASSERT_EQ(test_1.Empty(), true);
}

TEST(Check, Subtest_2) {
  s21::vector<std::string> test_1;
  ASSERT_EQ(test_1.Empty(), true);
}

TEST(Check, Subtest_3) {
  s21::vector<std::string> test_1(13);
  ASSERT_EQ(test_1.Empty(), true);
}

TEST(Check, Subtest_4) {
  s21::vector<std::string> test_1(13, "fsdf");
  ASSERT_EQ(test_1.Empty(), false);
}

TEST(Check, Subtest_5) {
  s21::vector<std::string> test_1;
  ASSERT_EQ(test_1.capacity(), 100);
  ASSERT_EQ(test_1.size(), 0);
}

TEST(Check, Subtest_6) {
  s21::vector<std::string> test_1(13);
  ASSERT_EQ(test_1.capacity(), 13);
  ASSERT_EQ(test_1.size(), 0);
}

TEST(Check, Subtest_7) {
  s21::vector<std::string> test_1(13, "dfd");
  ASSERT_EQ(test_1.capacity(), 13);
  ASSERT_EQ(test_1.size(), 13);
}

TEST(Check, Subtest_8) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  ASSERT_EQ(test_1.capacity(), 6);
  ASSERT_EQ(test_1.size(), 6);
}

TEST(Mutators, Subtest_1) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.clear();
  ASSERT_EQ(test_1.capacity(), 6);
  ASSERT_EQ(test_1.size(), 0);
  ASSERT_THROW(test_1[0], std::out_of_range);
}

TEST(Mutators, Subtest_2) {
  s21::vector<std::string> test_1({});
  ASSERT_THROW(test_1.erase(2), std::invalid_argument);
}

TEST(Mutators, Subtest_3) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  ASSERT_THROW(test_1.erase(-4), std::invalid_argument);
  ASSERT_THROW(test_1.erase(13), std::invalid_argument);
}

TEST(Mutators, Subtest_4) {
  std::string answers[] = {"fsdfdsf", "nnnnn", "jt", "tere", "trrre"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.erase(0);
  ASSERT_EQ(test_1.size(), 5);
  ASSERT_EQ(test_1.capacity(), 6);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_5) {
  std::string answers[] = {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.erase(5);
  ASSERT_EQ(test_1.size(), 5);
  ASSERT_EQ(test_1.capacity(), 6);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_6) {
  std::string answers[] = {"fsdfsd", "fsdfdsf", "jt", "tere", "trrre"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.erase(2);
  ASSERT_EQ(test_1.size(), 5);
  ASSERT_EQ(test_1.capacity(), 6);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_7) {
  s21::vector<std::string> test_1({});
  ASSERT_THROW(test_1.erase(2, 3), std::invalid_argument);
}

TEST(Mutators, Subtest_8) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  ASSERT_THROW(test_1.erase(-4, 3), std::invalid_argument);
  ASSERT_THROW(test_1.erase(13, 13), std::invalid_argument);
  ASSERT_THROW(test_1.erase(4, 3), std::invalid_argument);
}

TEST(Mutators, Subtest_9) {
  std::string answers[] = {"jt", "tere", "trrre"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.erase(0, 2);
  ASSERT_EQ(test_1.size(), 3);
  ASSERT_EQ(test_1.capacity(), 6);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_10) {
  std::string answers[] = {"fsdfsd"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.erase(1, 5);
  ASSERT_EQ(test_1.size(), 1);
  ASSERT_EQ(test_1.capacity(), 6);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_11) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.erase(0, 5);
  ASSERT_EQ(test_1.size(), 0);
  ASSERT_EQ(test_1.capacity(), 6);
  ASSERT_EQ(test_1.Empty(), true);
}

TEST(Mutators, Subtest_12) {
  std::string answers[] = {"fsdfsd", "fsdfdsf", "trrre"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.erase(2, 4);
  ASSERT_EQ(test_1.size(), 3);
  ASSERT_EQ(test_1.capacity(), 6);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_13) {
  std::string answers[] = {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere",
                           "trrre",  "1",       "2",     "3"};
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  test_1.push_back("1");
  test_1.push_back("2");
  test_1.push_back("3");
  ASSERT_EQ(test_1.size(), 9);
  ASSERT_EQ(test_1.capacity(), 56);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_14) {
  std::string answers[] = {"1", "2", "3"};
  s21::vector<std::string> test_1({});
  test_1.push_back("1");
  test_1.push_back("2");
  test_1.push_back("3");
  ASSERT_EQ(test_1.size(), 3);
  ASSERT_EQ(test_1.capacity(), 50);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Mutators, Subtest_15) {
  std::string answers[] = {"1", "2", "3"};
  s21::vector<std::string> test_1;
  test_1.push_back("1");
  test_1.push_back("2");
  test_1.push_back("3");
  ASSERT_EQ(test_1.size(), 3);
  ASSERT_EQ(test_1.capacity(), 100);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Iterator, Subtest_1) {
  s21::vector<int>::vector_iterator pointer;
  ASSERT_EQ(*pointer, NULL);
}

TEST(Iterator, Subtest_2) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  s21::vector<std::string>::vector_iterator pointer(test_1.front());
  ASSERT_EQ(*pointer, "fsdfsd");
}

TEST(Iterator, Subtest_3) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  s21::vector<std::string>::vector_iterator pointer_1(test_1.front());
  s21::vector<std::string>::vector_iterator pointer_2(pointer_1);
  ASSERT_EQ(*pointer_1, "fsdfsd");
  ASSERT_EQ(*pointer_1, *pointer_2);
}

TEST(Iterator, Subtest_4) {
  s21::vector<int>::vector_iterator pointer_1;
  ++pointer_1;
  --pointer_1;
  ASSERT_EQ(*pointer_1, NULL);
}

TEST(Iterator, Subtest_5) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  s21::vector<std::string>::vector_iterator pointer_1(test_1.front());
  s21::vector<std::string>::vector_iterator pointer_2(pointer_1);
  for (int i = 0; i < 6; i++) {
    ASSERT_EQ(*pointer_1 == *pointer_2, true);
    ++pointer_1;
    ++pointer_2;
  }
}

TEST(Iterator, Subtest_6) {
  s21::vector<std::string> test_1(
      {"fsdfsd", "fsdfdsf", "nnnnn", "jt", "tere", "trrre"});
  s21::vector<std::string>::vector_iterator pointer_1(test_1.front());
  s21::vector<std::string>::vector_iterator pointer_2;
  pointer_2 = test_1.Back();
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(*pointer_1 != *pointer_2, true);
    ++pointer_1;
    --pointer_2;
  }
  ASSERT_EQ(*pointer_1 != *pointer_2, true);
  pointer_2 = pointer_1;
  ASSERT_EQ(*pointer_1 != *pointer_2, false);
}

TEST(Insert_many, Subtest_1) {
  int answers[] = {-2, -1, 0, 1, 2, 3, 4, 5, 6};
  s21::vector<int> test_1({1, 2, 3, 4, 5});
  test_1.push_back(6);
  s21::vector<int>::vector_iterator pointer_1(test_1.front());
  test_1.insert_many(pointer_1, -2, -1, 0);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_EQ(test_1[i], answers[i]);
  }
}

TEST(Insert_many, Subtest_2) {
  double answers[] = {1.54, -2.5, -1.5, 0.5, 2.53453, 3.54, 4.43, 5.5445, 6};
  s21::vector<double> test_1({1.54, 2.53453, 3.54, 4.43, 5.5445});
  test_1.push_back(6);
  s21::vector<double>::vector_iterator pointer_1(test_1.front());
  ++pointer_1;
  test_1.insert_many(pointer_1, -2.5, -1.5, 0.5);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_DOUBLE_EQ(test_1[i], answers[i]);
  }
}

TEST(Insert_many, Subtest_3) {
  s21::vector<double> test_1({1.54, 2.53453, 3.54, 4.43, 5.5445});
  s21::vector<double>::vector_iterator pointer_1(test_1.front());
  ++pointer_1;
  ++pointer_1;
  ++pointer_1;
  ++pointer_1;
  ++pointer_1;
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_THROW(test_1.insert_many(pointer_1, -2.5, -1.5, 0.5),
                 std::out_of_range);
  }
}

TEST(Insert_many, Subtest_4) {
  double answers[] = {1.54, 2.53453, 3.54, 4.43, -2.5, -1.5, 0.5, 5.5445};
  s21::vector<double> test_1({1.54, 2.53453, 3.54, 4.43, 5.5445});
  s21::vector<double>::vector_iterator pointer_1(test_1.front());
  ++pointer_1;
  ++pointer_1;
  ++pointer_1;
  ++pointer_1;
  test_1.insert_many(pointer_1, -2.5, -1.5, 0.5);
  for (int i = 0; i < test_1.size(); i++) {
    ASSERT_DOUBLE_EQ(test_1[i], answers[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
