#include "s21_list.h"

#include <gtest/gtest.h>

TEST(Constructor, Subtest_1) {
  s21::list<int> temp;
  ASSERT_EQ(temp.get_beginning(), nullptr);
}

TEST(Constructor, Subtest_2) {
  ASSERT_THROW(s21::list<int> temp(-2), std::invalid_argument);
}

TEST(Constructor, Subtest_3) {
  s21::list<int> temp(0);
  ASSERT_EQ(temp.get_beginning(), nullptr);
}

TEST(Constructor, Subtest_4) {
  s21::list<int> temp(1);
  ASSERT_EQ(temp.get_beginning_next(), nullptr);
}

TEST(Constructor, Subtest_5) {
  s21::list<int> temp(2);
  ASSERT_EQ(temp.get_beginning_next(), temp.get_end());
}

TEST(Constructor, Subtest_6) {
  s21::list<int> temp(3);
  ASSERT_EQ(temp.get_beginning_next(), temp.get_end_prev());
}

TEST(Constructor, Subtest_7) {
  ASSERT_THROW(s21::list<int> temp(-4, 3), std::invalid_argument);
}

TEST(Constructor, Subtest_8) {
  s21::list<char> temp(0, 'n');
  ASSERT_EQ(temp.get_beginning(), nullptr);
}

TEST(Constructor, Subtest_9) {
  s21::list<std::string> temp(1, "Yup");
  ASSERT_EQ(temp.get_beginning_next(), nullptr);
  ASSERT_EQ(temp[0], "Yup");
}

TEST(Constructor, Subtest_10) {
  s21::list<char> temp(2, 'n');
  ASSERT_EQ(temp[0], 'n');
  ASSERT_EQ(temp[1], 'n');
}

TEST(Constructor, Subtest_11) {
  s21::list<char> temp(3, 'n');
  ASSERT_EQ(temp[0], 'n');
  ASSERT_EQ(temp[1], 'n');
  ASSERT_EQ(temp[2], 'n');
}

TEST(Constructor, Subtest_12) {
  s21::list<char> temp_1(0, 'n');
  s21::list<char> temp_2(temp_1);
  ASSERT_EQ(temp_2.get_beginning(), nullptr);
}

TEST(Constructor, Subtest_13) {
  s21::list<float> temp_1(1, 3.14);
  s21::list<float> temp_2(temp_1);
  ASSERT_FLOAT_EQ(temp_2[0], 3.14);
}

TEST(Constructor, Subtest_14) {
  s21::list<double> temp_1(2, 3.14345);
  s21::list<double> temp_2(temp_1);
  ASSERT_DOUBLE_EQ(temp_2[0], 3.14345);
  ASSERT_DOUBLE_EQ(temp_2[1], 3.14345);
}

TEST(Constructor, Subtest_15) {
  s21::list<double> temp_1(5, 3.14345);
  s21::list<double> temp_2(temp_1);
  ASSERT_DOUBLE_EQ(temp_2[0], 3.14345);
  ASSERT_DOUBLE_EQ(temp_2[1], 3.14345);
  ASSERT_DOUBLE_EQ(temp_2[2], 3.14345);
  ASSERT_DOUBLE_EQ(temp_2[3], 3.14345);
  ASSERT_DOUBLE_EQ(temp_2[4], 3.14345);
}

TEST(Constructor, Subtest_16) {
  s21::list<double> temp_1(0, 3.14345);
  s21::list<double> temp_2(&temp_1);
  ASSERT_EQ(temp_1.get_beginning(), nullptr);
  ASSERT_EQ(temp_2.get_beginning(), nullptr);
}

TEST(Constructor, Subtest_17) {
  s21::list<bool> temp_1(1, true);
  s21::list_elem<bool> *address = temp_1.get_beginning();
  s21::list<bool> temp_2(&temp_1);
  ASSERT_EQ(temp_1.get_beginning(), nullptr);
  ASSERT_EQ(temp_2[0], true);
  ASSERT_EQ(temp_2.get_beginning(), address);
}

TEST(Constructor, Subtest_18) {
  s21::list<bool> temp_1(23, false);
  s21::list_elem<bool> *address_1 = temp_1.get_beginning();
  s21::list_elem<bool> *address_2 = temp_1.get_end();
  s21::list<bool> temp_2(&temp_1);
  ASSERT_EQ(temp_1.get_beginning(), nullptr);
  ASSERT_EQ(temp_2[0], false);
  ASSERT_EQ(temp_2[22], false);
  ASSERT_EQ(temp_2.get_beginning(), address_1);
  ASSERT_EQ(temp_2.get_end(), address_2);
}

TEST(Constructor, Subtest_19) {
  s21::list<bool> temp_1({});
  ASSERT_EQ(temp_1.get_beginning(), nullptr);
  ASSERT_EQ(temp_1.get_end(), nullptr);
}

TEST(Constructor, Subtest_20) {
  s21::list<bool> temp_1({true});
  ASSERT_EQ(temp_1[0], true);
}

TEST(Constructor, Subtest_21) {
  s21::list<double> temp_1({2.34, 56.656});
  ASSERT_DOUBLE_EQ(temp_1[0], 2.34);
  ASSERT_DOUBLE_EQ(temp_1[1], 56.656);
}

TEST(Constructor, Subtest_22) {
  double answers[] = {2.34, 56.656, 453.65, 96.23, 5655, 656};
  s21::list<double> temp_1({2.34, 56.656, 453.65, 96.23, 5655, 656});
  s21::list_iterator<double> iter(temp_1.first());
  for (int i = 0; i < temp_1.Size(); i++) {
    ASSERT_DOUBLE_EQ(answers[i], *iter);
    ++iter;
  }
}

TEST(Destructor, Subtest_1) {
  s21::list<wchar_t> temp;
  temp.~list();
  ASSERT_EQ(temp.get_beginning(), nullptr);
  ASSERT_EQ(temp.get_end(), nullptr);
}

TEST(Destructor, Subtest_2) {
  s21::list<wchar_t> temp(3);
  temp.~list();
  ASSERT_EQ(temp.get_beginning(), nullptr);
  ASSERT_EQ(temp.get_end(), nullptr);
}

TEST(Destructor, Subtest_3) {
  s21::list<wchar_t> temp(3, L'A');
  temp.~list();
  ASSERT_EQ(temp.get_beginning(), nullptr);
  ASSERT_EQ(temp.get_end(), nullptr);
}

TEST(Destructor, Subtest_4) {
  s21::list<wchar_t> temp_1(3, L'A');
  s21::list<wchar_t> temp_2(temp_1);
  temp_1.~list();
  ASSERT_EQ(temp_1.get_beginning(), nullptr);
  ASSERT_EQ(temp_1.get_end(), nullptr);
  ASSERT_EQ(temp_2[0], L'A');
  temp_2.~list();
  ASSERT_EQ(temp_2.get_beginning(), nullptr);
  ASSERT_EQ(temp_2.get_end(), nullptr);
}

TEST(Destructor, Subtest_5) {
  s21::list<wchar_t> temp_1(3, L'A');
  s21::list<wchar_t> temp_2(&temp_1);
  ASSERT_EQ(temp_1.get_beginning(), nullptr);
  ASSERT_EQ(temp_1.get_end(), nullptr);
  ASSERT_EQ(temp_2[0], L'A');
  temp_2.~list();
  ASSERT_EQ(temp_2.get_beginning(), nullptr);
  ASSERT_EQ(temp_2.get_end(), nullptr);
}

TEST(Push_back, Subtest_1) {
  s21::list<int> temp(0);
  temp.push_back(1);
  ASSERT_EQ(temp[0], 1);
}

TEST(Push_back, Subtest_2) {
  s21::list<int> temp(1);
  temp.push_back(3);
  ASSERT_EQ(temp[0], 0);
  ASSERT_EQ(temp[1], 3);
}

TEST(Push_back, Subtest_3) {
  s21::list<int> temp(5);
  temp.push_back(3);
  ASSERT_EQ(temp[0], 0);
  ASSERT_EQ(temp[1], 0);
  ASSERT_EQ(temp[2], 0);
  ASSERT_EQ(temp[3], 0);
  ASSERT_EQ(temp[4], 0);
  ASSERT_EQ(temp[5], 3);
}

TEST(Push_back, Subtest_4) {
  s21::list<char> temp(0);
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  ASSERT_EQ(temp[0], 'a');
  ASSERT_EQ(temp[1], 'b');
  ASSERT_EQ(temp[2], 'c');
  ASSERT_EQ(temp[3], 'd');
  ASSERT_EQ(temp[4], 'e');
}

TEST(Push_front, Subtest_1) {
  s21::list<int> temp(0);
  temp.push_front(1);
  ASSERT_EQ(temp[0], 1);
}

TEST(Push_front, Subtest_2) {
  s21::list<int> temp(1);
  temp.push_front(3);
  ASSERT_EQ(temp[0], 3);
  ASSERT_EQ(temp[1], 0);
}

TEST(Push_front, Subtest_3) {
  s21::list<int> temp(5);
  temp.push_front(3);
  ASSERT_EQ(temp[0], 3);
  ASSERT_EQ(temp[1], 0);
  ASSERT_EQ(temp[2], 0);
  ASSERT_EQ(temp[3], 0);
  ASSERT_EQ(temp[4], 0);
  ASSERT_EQ(temp[5], 0);
}

TEST(Push_front, Subtest_4) {
  s21::list<char> temp(0);
  temp.push_front('a');
  temp.push_front('b');
  temp.push_front('c');
  temp.push_front('d');
  temp.push_front('e');
  ASSERT_EQ(temp[0], 'e');
  ASSERT_EQ(temp[1], 'd');
  ASSERT_EQ(temp[2], 'c');
  ASSERT_EQ(temp[3], 'b');
  ASSERT_EQ(temp[4], 'a');
}

TEST(Is_empty, Subtest_1) {
  s21::list<int> temp(0);
  ASSERT_EQ(temp.is_empty(), true);
}

TEST(Is_empty, Subtest_2) {
  s21::list<int> temp(1);
  ASSERT_EQ(temp.is_empty(), false);
}

TEST(Pop_back, Subtest_1) {
  s21::list<int> temp(0);
  ASSERT_THROW(temp.pop_back(), std::logic_error);
}

TEST(Pop_back, Subtest_2) {
  s21::list<int> temp(1);
  temp.pop_back();
  ASSERT_EQ(temp.is_empty(), true);
}

TEST(Pop_back, Subtest_3) {
  s21::list<int> temp(2);
  temp.pop_back();
  ASSERT_EQ(temp.get_beginning_next(), nullptr);
}

TEST(Pop_back, Subtest_4) {
  s21::list<int> temp(0);
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.push_back(5);
  ASSERT_EQ(temp[4], 5);
  temp.pop_back();
  ASSERT_EQ(temp[3], 4);
  temp.pop_back();
  ASSERT_EQ(temp[2], 3);
  temp.pop_back();
  ASSERT_EQ(temp[1], 2);
  temp.pop_back();
  ASSERT_EQ(temp[0], 1);
  temp.pop_back();
  ASSERT_EQ(temp.get_beginning(), nullptr);
  ASSERT_THROW(temp.pop_back(), std::logic_error);
}

TEST(Pop_front, Subtest_1) {
  s21::list<int> temp(0);
  ASSERT_THROW(temp.pop_front(), std::logic_error);
}

TEST(Pop_front, Subtest_2) {
  s21::list<int> temp(1);
  temp.pop_front();
  ASSERT_EQ(temp.is_empty(), true);
}

TEST(Pop_front, Subtest_3) {
  s21::list<int> temp(2);
  temp.pop_front();
  ASSERT_EQ(temp.get_beginning_next(), nullptr);
}

TEST(Pop_front, Subtest_4) {
  s21::list<int> temp(0);
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.push_back(5);
  ASSERT_EQ(temp[0], 1);
  temp.pop_front();
  ASSERT_EQ(temp[0], 2);
  temp.pop_front();
  ASSERT_EQ(temp[0], 3);
  temp.pop_front();
  ASSERT_EQ(temp[0], 4);
  temp.pop_front();
  ASSERT_EQ(temp[0], 5);
  temp.pop_front();
  ASSERT_EQ(temp.get_beginning(), nullptr);
  ASSERT_THROW(temp.pop_front(), std::logic_error);
}

TEST(Size, Subtest_1) {
  s21::list<int> temp(0);
  ASSERT_EQ(temp.Size(), 0);
}

TEST(Size, Subtest_2) {
  s21::list<int> temp(1);
  ASSERT_EQ(temp.Size(), 1);
}

TEST(Size, Subtest_3) {
  s21::list<int> temp(32);
  ASSERT_EQ(temp.Size(), 32);
}

TEST(Size, Subtest_4) {
  s21::list<int> temp(32);
  temp.push_front(1);
  temp.push_front(1);
  temp.push_front(1);
  temp.push_front(1);
  temp.push_back(1);
  temp.push_back(1);
  ASSERT_EQ(temp.Size(), 38);
}

TEST(Size, Subtest_5) {
  s21::list<int> temp(32);
  temp.pop_front();
  temp.pop_front();
  temp.pop_front();
  temp.pop_front();
  temp.pop_back();
  temp.pop_back();
  ASSERT_EQ(temp.Size(), 26);
}

TEST(Get_element, Subtest_1) {
  s21::list<int> temp(32);
  ASSERT_THROW(temp.get_element(-3), std::invalid_argument);
}

TEST(Get_element, Subtest_2) {
  s21::list<int> temp(0);
  ASSERT_THROW(temp.get_element(1), std::invalid_argument);
}

TEST(Get_element, Subtest_3) {
  s21::list<int> temp(6);
  ASSERT_THROW(temp.get_element(6), std::invalid_argument);
}

TEST(Get_element, Subtest_4) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  ASSERT_EQ(temp.get_element(6), 'g');
}

TEST(Get_element, Subtest_5) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  ASSERT_EQ(temp.get_element(0), 'a');
}

TEST(Erase, Subtest_1) {
  s21::list<int> temp(0);
  ASSERT_THROW(temp.erase(1), std::invalid_argument);
}

TEST(Erase, Subtest_2) {
  s21::list<int> temp(6);
  ASSERT_THROW(temp.erase(6), std::invalid_argument);
}

TEST(Erase, Subtest_3) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(6);
  ASSERT_EQ(temp[5], 'f');
}

TEST(Erase, Subtest_4) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(0);
  ASSERT_EQ(temp[0], 'b');
}

TEST(Erase, Subtest_5) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(3);
  ASSERT_EQ(temp.get_element(3), 'e');
}

TEST(Erase, Subtest_6) {
  s21::list<int> temp(0);
  ASSERT_THROW(temp.erase(1, 2), std::invalid_argument);
}

TEST(Erase, Subtest_7) {
  s21::list<int> temp(6);
  ASSERT_THROW(temp.erase(2, 6), std::invalid_argument);
}

TEST(Erase, Subtest_8) {
  s21::list<int> temp(6);
  ASSERT_THROW(temp.erase(6, 7), std::invalid_argument);
}

TEST(Erase, Subtest_9) {
  s21::list<int> temp(6);
  ASSERT_THROW(temp.erase(5, 3), std::invalid_argument);
}

TEST(Erase, Subtest_10) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(0, 6);
  ASSERT_EQ(temp.get_beginning(), nullptr);
}

TEST(Erase, Subtest_11) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(0, 5);
  ASSERT_EQ(temp.get_beginning_next(), nullptr);
  ASSERT_EQ(temp[0], 'g');
}

TEST(Erase, Subtest_12) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(3, 6);
  ASSERT_EQ(temp[2], 'c');
}

TEST(Erase, Subtest_13) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(1, 5);
  ASSERT_EQ(temp[0], 'a');
  ASSERT_EQ(temp[1], 'g');
}

TEST(Erase, Subtest_14) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  temp.erase(1, 6);
  ASSERT_EQ(temp[0], 'a');
}

TEST(Iterator, Subtest_1) {
  s21::list_iterator<char> iter;
  ++iter;
  ASSERT_EQ(*iter, NULL);
}

TEST(Iterator, Subtest_2) {
  s21::list_elem<char> temp;
  s21::list_iterator<char> iter(&temp);
  temp.data = 'g';
  ASSERT_EQ(*iter, 'g');
}

TEST(Iterator, Subtest_3) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  s21::list_iterator<char> iter(temp.first());
  ASSERT_EQ(*iter, 'a');
}

TEST(Iterator, Subtest_4) {
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  s21::list_iterator<char> iter(temp.last());
  ASSERT_EQ(*iter, 'g');
}

TEST(Iterator, Subtest_5) {
  char answers[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  s21::list<char> temp;
  temp.push_back('a');
  temp.push_back('b');
  temp.push_back('c');
  temp.push_back('d');
  temp.push_back('e');
  temp.push_back('f');
  temp.push_back('g');
  s21::list_iterator<char> iter(temp.first());
  for (int i = 0; i < temp.Size(); i++) {
    ASSERT_EQ(*iter, answers[i]);
    ++iter;
  }
  ASSERT_EQ(*iter, 'a');
}

TEST(Iterator, Subtest_6) {
  int answers[] = {7, 6, 5, 4, 3, 2, 1};
  s21::list<int> temp;
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.push_back(5);
  temp.push_back(6);
  temp.push_back(7);
  s21::list_iterator<int> iter(temp.last());
  for (int i = 0; i < temp.Size(); i++) {
    ASSERT_EQ(*iter, answers[i]);
    --iter;
  }
  ASSERT_EQ(*iter, 7);
}

TEST(Iterator, Subtest_7) {
  s21::list<double> temp;
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.push_back(5);
  temp.push_back(6);
  temp.push_back(7);
  s21::list_iterator<double> iter(temp.last());
  s21::list_iterator<double> iter_2;
  iter_2 = iter;
  for (int i = 0; i < temp.Size(); i++) {
    ASSERT_EQ(iter == iter_2, true);
    --iter;
    --iter_2;
  }
}

TEST(Iterator, Subtest_8) {
  s21::list<double> temp;
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.push_back(5);
  temp.push_back(6);
  temp.push_back(7);
  s21::list_iterator<double> iter(temp.last());
  s21::list_iterator<double> iter_2;
  for (int i = 0; i < temp.Size(); i++) {
    ASSERT_EQ(iter != iter_2, true);
    --iter;
    --iter_2;
  }
}

TEST(Insert_many, Subtest_1) {
  s21::list<double> temp;
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.push_back(5);
  temp.push_back(6);
  temp.push_back(7);
  s21::list_iterator<double> iter(temp.first());
  temp.insert_many(iter, 5.66, 7.88, 9.99);
  ASSERT_EQ(temp[0], 5.66);
  ASSERT_EQ(temp[9], 7);
}

TEST(Insert_many, Subtest_2) {
  s21::list<std::string> temp;
  temp.push_back("1");
  temp.push_back("2");
  temp.push_back("3");
  temp.push_back("4");
  temp.push_back("5");
  temp.push_back("6");
  temp.push_back("7");
  s21::list_iterator<std::string> iter(temp.first());
  temp.insert_many(iter, "new", "strings");
  ASSERT_EQ(temp[0], "new");
  ASSERT_EQ(temp[8], "7");
}

TEST(Insert_many, Subtest_3) {
  s21::list<int> temp;
  temp.push_back(1);
  temp.push_back(2);
  temp.push_back(3);
  temp.push_back(4);
  temp.push_back(5);
  temp.push_back(6);
  temp.push_back(7);
  s21::list_iterator<int> iter(temp.last());
  temp.insert_many(iter, 66, 77);
  ASSERT_EQ(temp[0], 1);
  ASSERT_EQ(temp[6], 66);
  ASSERT_EQ(temp[7], 77);
  ASSERT_EQ(temp[8], 7);
}

TEST(Insert_many, Subtest_4) {
  s21::list<std::string> temp;
  temp.push_back("12");
  temp.push_back("22");
  temp.push_back("32");
  temp.push_back("42");
  temp.push_back("52");
  temp.push_back("62");
  temp.push_back("72");
  s21::list_iterator<std::string> iter(temp.last());
  s21::list_iterator<std::string> iter_copy(&iter);
  temp.insert_many(iter, "n", "strings2");
  ASSERT_EQ(temp[0], "12");
  ASSERT_EQ(temp[6], "n");
  ASSERT_EQ(temp[7], "strings2");
  ASSERT_EQ(temp[8], "72");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
