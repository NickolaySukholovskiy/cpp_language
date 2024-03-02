#include "s21_multiset.h"

#include <gtest/gtest.h>

#include <set>

TEST(S21multisetTests, initializer_list_constructor_test) {
  s21::multiset<int> a{1, 1, 2, 4, 5, 6, 7, 8, 9};
  std::multiset<int> b{1, 1, 2, 4, 5, 6, 7, 8, 9};
  s21::multiset<int>::iterator a_it = a.Begin();
  std::multiset<int>::iterator b_it = b.begin();
  for (; a_it != a.End(); ++a_it, ++b_it) {
    ASSERT_TRUE(*a_it == *b_it);
  }
}

TEST(S21multisetTests, default_constructor_empty_test) {
  s21::multiset<int> a;
  std::multiset<int> b;
  ASSERT_TRUE(a.Empty() == b.empty());
}

TEST(S21multisetTests, copy_constructor_test) {
  s21::multiset<int> a_orig{1, 1, 2, 4, 5, 6, 7, 8, 9};
  s21::multiset<int> a_copy(a_orig);
  s21::multiset<int>::iterator a_orig_it = a_orig.Begin();
  s21::multiset<int>::iterator a_copy_it = a_copy.Begin();
  for (; a_orig_it != a_orig.End(); ++a_orig_it, ++a_copy_it) {
    ASSERT_TRUE(*a_orig_it == *a_copy_it);
  }
  --a_copy_it;
}

TEST(S21multisetTests, move_constructor_test) {
  s21::multiset<int> a_orig{1, 1, 2, 4, 5, 6, 7, 8, 9};
  size_t orig_size = a_orig.Size();
  s21::multiset<int> a_copy(std::move(a_orig));
  std::cout << orig_size << std::endl;
  ASSERT_EQ(orig_size, a_copy.Size());
  ASSERT_TRUE(a_orig.Empty());
}

TEST(S21multisetTests, size_test) {
  s21::multiset<int> a_1{1, 1, 2, 4, 5, 6, 7, 8, 9};
  std::multiset<int> b_1{1, 1, 2, 4, 5, 6, 7, 8, 9};
  s21::multiset<int> a_2;
  std::multiset<int> b_2;

  ASSERT_TRUE(a_1.Size() == b_1.size());
  ASSERT_TRUE(a_2.Size() == b_2.size());
}

TEST(S21multisetTests, clear_test) {
  s21::multiset<int> a{1, 1, 2, 4, 5, 6, 7, 8, 9};
  std::multiset<int> b{1, 1, 2, 4, 5, 6, 7, 8, 9};
  a.Clear();
  b.clear();
  ASSERT_TRUE(a.Empty() == b.empty());
}

TEST(S21multisetTests, insert_erase_test) {
  s21::multiset<int> a{1, 3, 7};
  std::multiset<int> b{1, 3, 7};
  std::pair<s21::multiset<int>::iterator, bool> a_pair = a.Insert(4);
  std::multiset<int>::iterator b_pair = b.insert(4);
  ASSERT_TRUE(*(a_pair.first) == *b_pair);
  ASSERT_TRUE(a_pair.second == true);
  s21::multiset<int>::iterator a_it = a.Begin();
  std::multiset<int>::iterator b_it = b.begin();
  for (; a_it != a.End(); ++a_it, ++b_it) {
    ASSERT_TRUE(*a_it == *b_it);
  }
  a.Erase(a_pair.first);
  b.erase(b_pair);
  for (a_it = a.Begin(), b_it = b.begin(); a_it != a.End(); ++a_it, ++b_it) {
    ASSERT_TRUE(*a_it == *b_it);
  }
}

TEST(S21multisetTests, swap) {
  s21::multiset<int> a{1, 3, 7};
  s21::multiset<int> b{2, 4, 8};

  s21::multiset<int> a_2{2, 4, 8};
  s21::multiset<int> b_2{1, 3, 7};

  a.Swap(b);

  s21::multiset<int>::iterator a_it = a.Begin();
  s21::multiset<int>::iterator a_2it = a.Begin();
  s21::multiset<int>::iterator b_it = b_2.Begin();
  s21::multiset<int>::iterator b_2it = b_2.Begin();
  for (; a_it != a.End(); ++a_it, ++a_2it, ++b_it, ++b_2it) {
    ASSERT_TRUE(*a_it == *a_2it);
    ASSERT_TRUE(*b_it == *b_2it);
  }
}

TEST(S21multisetTests, merge_test) {
  s21::multiset<char> p{'A', 'B', 'C'};
  s21::multiset<char> q{'C', 'D', 'E'};
  s21::multiset<char> p_check{'A', 'B', 'C', 'D', 'E'};
  s21::multiset<char> q_check{'C'};
  p.Merge(q);
  s21::multiset<char>::iterator p_it = p.Begin();
  s21::multiset<char>::iterator p_check_it = p_check.Begin();
  for (; p_it != p.End(); ++p_it, ++p_check_it) {
    ASSERT_TRUE(*p_it == *p_check_it);
  }
  s21::multiset<char>::iterator q_it = q.Begin();
  s21::multiset<char>::iterator q_check_it = q_check.Begin();
  for (; q_it != q.End(); ++q_it, ++q_check_it) {
    ASSERT_TRUE(*q_it == *q_check_it);
  }
}

TEST(S21multisetTests, count_test) {
  s21::multiset<int> a{1, 1, 2, 4, 5, 6, 7, 8, 9};
  s21::multiset<int> b;

  ASSERT_TRUE(a.Count(1) == 2);
  ASSERT_TRUE(a.Count(10) == 0);
  ASSERT_TRUE(b.Count(10) == 0);
}

TEST(S21multisetTests, find_test) {
  s21::multiset<int> a{1, 1, 2, 4, 5, 6, 7, 8, 9};
  s21::multiset<int> b;

  ASSERT_TRUE(*a.Find(1) == *a.Begin());
  ASSERT_TRUE(*(a.Find(2)) == 2);
  ASSERT_TRUE(a.Find(10).IsNull());
  ASSERT_TRUE(b.Find(10).IsNull());
}

TEST(S21multisetTests, contains_test) {
  s21::multiset<int> a{1, 1, 2, 4, 5, 6, 7, 8, 9};
  s21::multiset<int> b;

  ASSERT_TRUE(a.Contains(1));
  ASSERT_FALSE(a.Contains(10));
  ASSERT_FALSE(b.Contains(10));
}

TEST(S21multisetTests, equal_range_test) {
  s21::multiset<int> a{1, 1, 2, 4, 5, 6, 7, 8, 9};
  std::pair<typename s21::multiset<int>::iterator,
            typename s21::multiset<int>::iterator>
      res;
  res = a.Equal_range(4);
  ASSERT_TRUE(*(res.first) == 4);
  ASSERT_TRUE(*(res.second) == 5);
}

TEST(S21multisetTests, insert_many_test) {
  s21::multiset<int> a;
  std::multiset<int> b{1, 3, 7};
  a.Insert_many(1, 3, 7);
  s21::multiset<int>::iterator a_it = a.Begin();
  std::multiset<int>::iterator b_it = b.begin();
  for (; a_it != a.End(); ++a_it, ++b_it) {
    ASSERT_TRUE(*a_it == *b_it);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}