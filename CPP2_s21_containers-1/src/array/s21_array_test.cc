
#include "s21_array.h"

#include <array>

#include "gtest/gtest.h"

TEST(test_it_array, test_it_array_1) {
  s21::array<int, 3> ar_1{1, 2, 3};
  std::array<int, 3> ar_2{1, 2, 3};

  s21::array<int, 3>::iterator it_1;
  it_1 = ar_1.Begin();
  std::array<int, 3>::iterator it_2 = ar_2.begin();

  for (size_t i = 0; i < ar_1.Size(); i++) {
    EXPECT_EQ(*it_1, *it_2);
    it_1++;
    it_2++;
  }
}

TEST(test_it_array, test_it_array_2) {
  s21::array<int, 3> ar_1{1, 2, 3};
  s21::array<int, 3> ar_2{1, 2, 3};

  s21::array<int, 3>::iterator it_1;
  s21::array<int, 3>::iterator it_2;
  it_1 = ar_1.Begin();
  it_2 = ar_2.Begin();

  EXPECT_EQ(it_1 != it_2, 1);
}

TEST(test_it_array, test_it_array_3) {
  s21::array<int, 3> ar_1{1, 2, 3};
  std::array<int, 3> ar_2{1, 2, 3};

  s21::array<int, 3>::iterator it_1;
  std::array<int, 3>::iterator it_2;

  it_1 = ar_1.Begin();
  it_2 = ar_2.begin();

  for (; it_1 != ar_1.End() || it_2 != ar_2.end(); it_1++) {
    EXPECT_EQ(*it_1, *it_2);
    it_2++;
  }
}

TEST(test_array, test_1) {
  s21::array<int, 4> ar_1{1, 2, 3};
  std::array<int, 4> ar_2{1, 2, 3};

  EXPECT_EQ(ar_1.Size(), ar_2.size());
  EXPECT_EQ(ar_1.Max_size(), ar_2.max_size());
  EXPECT_EQ(ar_1.Empty(), ar_2.empty());
}

TEST(test_array, test_fill_1) {
  s21::array<int, 4> ar_1;
  std::array<int, 4> ar_2;

  ar_1.Fill(7);
  ar_2.fill(7);

  for (size_t i = 0; i < ar_1.Size(); i++) {
    EXPECT_EQ(ar_1[i], ar_2[i]);
  }
}

TEST(test_array, test_swap_1) {
  s21::array<int, 4> ar_1{1, 2, 3, 4};
  s21::array<int, 4> ar_1_buf{4, 3, 2, 1};
  std::array<int, 4> ar_2{1, 2, 3, 4};
  std::array<int, 4> ar_2_buf{4, 3, 2, 1};

  ar_1.Swap(ar_1_buf);
  ar_2.swap(ar_2_buf);

  for (size_t i = 0; i < ar_1.Size(); i++) {
    EXPECT_EQ(ar_1[i], ar_2[i]);
  }

  for (size_t i = 0; i < ar_1_buf.Size(); i++) {
    EXPECT_EQ(ar_1_buf[i], ar_2_buf[i]);
  }
}

TEST(test_array, test_copy_constructor_1) {
  s21::array<int, 4> ar_1{1, 2, 3, 4};
  s21::array<int, 4> ar_1_buf(ar_1);

  for (size_t i = 0; i < ar_1.Size(); i++) {
    EXPECT_EQ(ar_1[i], ar_1_buf[i]);
  }
}

TEST(test_array, test_getters_1) {
  s21::array<int, 2> ar_1{1, 2};
  std::array<int, 2> ar_2{1, 2};

  EXPECT_EQ(ar_1[0], ar_2[0]);
  EXPECT_EQ(ar_1.At(1), ar_2.at(1));
  EXPECT_ANY_THROW(ar_1.At(3));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
