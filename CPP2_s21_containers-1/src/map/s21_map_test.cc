#include "s21_map.h"

#include <gtest/gtest.h>

#include <map>

TEST(map, ConstructorDefaultMap) {
  s21::map<int, char> my_empty_map;
  std::map<int, char> orig_empty_map;
  EXPECT_EQ(my_empty_map.Empty(), orig_empty_map.empty());
}
TEST(map, ConstructorDefaultMap1) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.Size(), 0ul);
  EXPECT_TRUE(m.Empty());
}

TEST(map, ConstructorInitializerMap0) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.Size(), 3ul);
  EXPECT_FALSE(m.Empty());
  EXPECT_EQ(m.At(1), "one");
  EXPECT_EQ(m.At(2), "two");
  EXPECT_EQ(m.At(3), "three");
}

TEST(map, ConstructorInitializerMap1) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.Size(), orig_map.size());
  auto my_it = my_map.Begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorInitializerMap2) {
  s21::map<int, char> my_map = {};
  std::map<int, char> orig_map = {};
  EXPECT_EQ(my_map.Size(), orig_map.size());
  auto my_it = my_map.Begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorCopyMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = my_map;
  std::map<int, int> orig_map_copy = orig_map;
  EXPECT_EQ(my_map_copy.Size(), orig_map_copy.size());
  auto my_it = my_map_copy.Begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> my_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> orig_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> my_map_copy = std::move(my_map);
  std::map<int, int> orig_map_copy = std::move(orig_map);
  EXPECT_EQ(my_map_copy.Size(), orig_map_copy.size());
  auto my_it = my_map_copy.Begin();
  auto orig_it = orig_map_copy.begin();
  for (; my_it != my_map_copy.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, MapOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map['a'] = "Alisa";
  orig_map['a'] = "Alisa";
  orig_map['b'] = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(map, MapAtOperatorException) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(my_map.At('g') = "Alisa", std::out_of_range);
}

TEST(map, MapAtOperator) {
  s21::map<char, std::string> my_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> orig_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  my_map.At('a') = "Alisa";
  orig_map.at('a') = "Alisa";
  orig_map.at('b') = "Ben";
  EXPECT_TRUE(my_map['a'] == orig_map['a']);
  EXPECT_FALSE(my_map['b'] == orig_map['b']);
  EXPECT_TRUE(my_map['c'] == orig_map['c']);
}

TEST(map, MapCapacity) {
  s21::map<char, std::string> my_map;
  std::map<char, std::string> orig_map;
  EXPECT_TRUE(my_map.Empty() == orig_map.empty());
  my_map.Insert('z', "wow");
  EXPECT_FALSE(my_map.Empty() == orig_map.empty());
  EXPECT_EQ(my_map.Size(), 1ul);
}

TEST(map, MapClear) {
  s21::map<int, int> my_map;
  std::map<int, int> orig_map;
  my_map.Clear();
  orig_map.clear();
  EXPECT_EQ(my_map.Empty(), orig_map.empty());
  my_map.Insert(std::make_pair(1, 1));
  orig_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(my_map.Empty(), orig_map.empty());
  my_map.Clear();
  orig_map.clear();
  EXPECT_EQ(my_map.Empty(), orig_map.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.Insert(std::make_pair(1, 'a'));
  my_map.Insert(std::make_pair(2, 'a'));
  my_map.Insert(std::make_pair(3, 'a'));
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.Begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.Insert(std::make_pair(1, 'c'));
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.Insert(1, 'a');
  my_map.Insert(2, 'a');
  my_map.Insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.Begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.Insert(1, 'a');
  auto pr2 = orig_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> my_map;
  std::map<int, char> orig_map;
  my_map.Insert(1, 'a');
  my_map.Insert(2, 'a');
  my_map.Insert(3, 'a');
  orig_map.insert(std::make_pair(1, 'a'));
  orig_map.insert(std::make_pair(2, 'a'));
  orig_map.insert(std::make_pair(3, 'a'));

  auto my_it = my_map.Begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }

  auto pr1 = my_map.InsertOrAssign(1, 'b');
  auto i = orig_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapErase) {
  s21::map<int, char> my_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> orig_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(my_map.Size(), orig_map.size());
  my_map.Erase(my_map.Begin());
  orig_map.erase(orig_map.begin());
  EXPECT_EQ(my_map.Size(), orig_map.size());
  auto my_it = my_map.Begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
}

TEST(map, SwapMap) {
  s21::map<int, int> my_map = {{1, 1}};
  s21::map<int, int> my_swap_map = {{3, 3}, {4, 4}};

  my_map.Swap(my_swap_map);
  EXPECT_EQ(my_map.Size(), 2ul);
  EXPECT_EQ(my_swap_map.Size(), 1ul);
  auto x = (*(my_map.Begin())).first;
  auto y = (*(my_swap_map.Begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(map, MergeMap) {
  s21::map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  s21::map<int, int> my_map_merge = {{3, 3}, {4, 4}};

  std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2}};
  std::map<int, int> orig_map_merge = {{3, 3}, {4, 4}};

  my_map.Merge(my_map_merge);
  orig_map.merge(orig_map_merge);

  auto my_it = my_map.Begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.End(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
  EXPECT_EQ(my_map_merge.Contains(4),
            (orig_map_merge.find(4) != orig_map_merge.end()));
  EXPECT_EQ(my_map_merge.Contains(3),
            !(orig_map_merge.find(3) == orig_map_merge.end()));
}

/*
 Another tests for map container
*/

TEST(mapTest, InsertKeyValue) {
  s21::map<int, std::string> map;

  map.Insert(1, "one");

  EXPECT_EQ(map.Size(), 1ul);

  EXPECT_EQ(map.Contains(1), true);
  EXPECT_EQ(map[1], "one");

  map.Insert(2, "two");

  EXPECT_EQ(map.Size(), 2ul);

  EXPECT_EQ(map.Contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.Contains(2), true);
  EXPECT_EQ(map[2], "two");
}

TEST(mapTest, InsertPair) {
  s21::map<int, std::string> map;

  map.Insert(std::make_pair(1, "one"));

  EXPECT_EQ(map.Size(), 1ul);

  EXPECT_EQ(map.Contains(1), true);
  EXPECT_EQ(map[1], "one");

  map.Insert(std::make_pair(2, "two"));

  EXPECT_EQ(map.Size(), 2ul);

  EXPECT_EQ(map.Contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.Contains(2), true);
  EXPECT_EQ(map[2], "two");
}
TEST(mapTest, InsertOrAssign) {
  s21::map<int, std::string> map;

  auto [it1, inserted1] = map.InsertOrAssign(1, "one");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, "one");

  auto [it2, inserted2] = map.InsertOrAssign(1, "ONE");
  EXPECT_TRUE(inserted2);
  EXPECT_EQ((*it2).first, 1);
  EXPECT_EQ((*it2).second, "ONE");

  map.InsertOrAssign(2, "two");
  map.InsertOrAssign(3, "three");
  map.InsertOrAssign(4, "four");
  map.InsertOrAssign(5, "five");
  EXPECT_EQ(map.Size(), 5ul);
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}
TEST(mapTest, AtAndOperatorBrackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.At(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.At(4), std::out_of_range);
  EXPECT_ANY_THROW(map[4] = "four");

  map[2] = "TWO";
  EXPECT_EQ(map[2], "TWO");
}

TEST(mapTest, EmptyAndSize) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(empty_map.Empty());
  EXPECT_EQ(empty_map.Size(), 0ul);

  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 3ul);
}
TEST(mapTest, Erase) {
  s21::map<int, std::string> map;

  map.Insert({1, "one"});
  map.Insert({2, "two"});
  map.Insert({3, "three"});
  map.Insert({5, "five"});

  auto it1 = ++map.Begin();
  map.Erase(it1);
  EXPECT_EQ(map.Size(), 3ul);
  EXPECT_FALSE(map.Contains(1));
}

TEST(mapTest, Erase1) {
  s21::map<int, std::string> map;
  map.Insert({1, "one"});
  map.Insert({2, "two"});
  s21::map<int, std::string>::iterator it = map.Begin();
  auto it1 = it++;
  it--;
  map.Erase(it);
  map.Erase(it1);
  EXPECT_TRUE(map.Empty());
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.Insert({1, "one"});
  map1.Insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.Insert({3, "three"});
  map2.Insert({4, "four"});

  map1.Swap(map2);

  EXPECT_EQ(map1.Size(), 2ul);
  EXPECT_TRUE(map1.Contains(3));
  EXPECT_TRUE(map1.Contains(4));

  EXPECT_EQ(map2.Size(), 2ul);
  EXPECT_TRUE(map2.Contains(1));
  EXPECT_TRUE(map2.Contains(2));
}

TEST(mapTest, Merge) {
  s21::map<int, std::string> map1;
  map1.Insert({1, "one"});
  map1.Insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.Insert({3, "three"});
  map2.Insert({4, "four"});

  map1.Merge(map2);

  EXPECT_EQ(map1.Size(), 4ul);
  EXPECT_TRUE(map1.Contains(1));
  EXPECT_TRUE(map1.Contains(2));
  EXPECT_TRUE(map1.Contains(3));
  EXPECT_TRUE(map1.Contains(4));
}

TEST(mapTest, Contains) {
  s21::map<int, std::string> map;

  map.Insert({1, "one"});
  map.Insert({2, "two"});
  EXPECT_TRUE(map.Contains(2));
  EXPECT_FALSE(map.Contains(3));
}

TEST(mapTest, InsertMany) {
  s21::map<int, std::string> map;
  s21::vector vec =
      map.InsertMany(std::make_pair(1, "one"), std::make_pair(2, "two"));
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_TRUE(vec[0].second);
  EXPECT_EQ((*(vec[1].first)).second, "two");
}

TEST(mapTest, InsertMany1) {
  s21::map<int, std::string> map;
  map.Insert(2, "two");
  s21::vector vec =
      map.InsertMany(std::make_pair(1, "one"), std::make_pair(2, "two"));
  EXPECT_EQ(map[1], "one");
  EXPECT_FALSE(vec[1].second);
  EXPECT_TRUE(vec[1].first == map.End());
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}