#include "s21_stack.h"

#include <stack>

#include "gtest/gtest.h"

TEST(create_stack, check_create_stack_1) { s21::stack<int> ex; }

TEST(create_stack, check_create_stack_2) { s21::stack<char> ex; }

TEST(create_stack, check_copy_constructor_1) {
  s21::stack<int> st_1;
  st_1.Push(21);
  st_1.Push(2);
  st_1.Push(8);
  st_1.Push(-12);

  s21::stack<int> st_2(st_1);
  size_t size_1 = st_1.Size();
  size_t size_2 = st_2.Size();
  for (size_t i = 0; i < size_1 && i < size_2; i++) {
    EXPECT_EQ(st_1.Top(), st_2.Top());
    st_1.Pop();
    st_2.Pop();
  }
}

TEST(create_stack, check_move_constructor) {
  s21::stack<int> st_1;
  st_1.Push(1);
  st_1.Push(2);
  st_1.Push(3);

  std::stack<int> st_1_buf;
  st_1_buf.push(1);
  st_1_buf.push(2);
  st_1_buf.push(3);

  s21::stack<int> st_2(std::move(st_1));
  std::stack<int> st_2_buf(std::move(st_1_buf));

  while (st_2.Size() > 0 || st_2_buf.size() > 0) {
    EXPECT_EQ(st_2.Top(), st_2_buf.top());
    st_2.Pop();
    st_2_buf.pop();
  }
}

TEST(create_stack, check_constructor_with_initialization_list_1) {
  s21::stack<int> st_1{1, 2, 3, 4, 5};
  std::deque<int> st_1_buf_que{1, 2, 3, 4, 5};
  std::stack<int> st_1_buf{st_1_buf_que};

  while (st_1.Size() > 0 || st_1_buf.size() > 0) {
    EXPECT_EQ(st_1.Top(), st_1_buf.top());
    st_1.Pop();
    st_1_buf.pop();
  }
}

TEST(test_swap, cheack_swap_1) {
  s21::stack<int> st_1{1, 2, 3};
  s21::stack<int> st_2{3, 2, 1};

  std::deque<int> for_st_1_buf{1, 2, 3};
  std::deque<int> for_st_2_buf{3, 2, 1};

  std::stack<int> st_1_buf(for_st_1_buf);
  std::stack<int> st_2_buf(for_st_2_buf);

  st_1.Swap(st_2);
  st_1_buf.swap(st_2_buf);

  while (!st_1.Empty() || !st_1_buf.empty()) {
    EXPECT_EQ(st_1.Top(), st_1_buf.top());
    st_1.Pop();
    st_1_buf.pop();
  }

  while (!st_2.Empty() || !st_2_buf.empty()) {
    EXPECT_EQ(st_2.Top(), st_2_buf.top());
    st_2.Pop();
    st_2_buf.pop();
  }
}

TEST(test_assignment, check_assignment_1) {
  s21::stack<int> st_1{1, 2, 3};
  s21::stack<int> st_2 = st_1;

  std::deque<int> for_st_1_buf{1, 2, 3};

  std::stack<int> st_1_buf(for_st_1_buf);
  std::stack<int> st_2_buf = st_1_buf;

  while (!st_2.Empty() || !st_2_buf.empty()) {
    EXPECT_EQ(st_2.Top(), st_2_buf.top());
    st_2.Pop();
    st_2_buf.pop();
  }
}

TEST(test_insert_many, check_insert_many_1) {
  s21::stack<int> st_1{1, 2, 3};
  st_1.insert_many_front(1, 2, 3);

  std::deque<int> st_2_buf_que{1, 2, 3, 1, 2, 3};
  std::stack<int> st_2(st_2_buf_que);

  while (!st_1.Empty()) {
    EXPECT_EQ(st_1.Top(), st_2.top());
    st_1.Pop();
    st_2.pop();
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}