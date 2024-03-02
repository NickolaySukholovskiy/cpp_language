FL = -Wall -Werror -Wextra -std=c++17
TEST_FL = -lstdc++ -lgtest -lm
GCOV_FL = -ftest-coverage -fprofile-arcs --coverage
gcc = gcc $(FL)
CONTAINERS = array list map multiset queue set stack vector

all: test

test : clean
	for NAME in $(CONTAINERS); do \
		$(gcc) ./$$NAME/*_test.cc $(TEST_FL) -o ./$$NAME/test; \
		./$$NAME/test; \
	done

clean :
	rm -rf */*.gcda */*.gcno *.info */*.css */*.html gcov */test

clang-check:
	clang-format --style=Google -n *.h */*.h */*.cc

clang-format:
	clang-format --style=Google -i *.h */*.h */*.cc

gcov_report :
	for NAME in $(CONTAINERS); do \
		cd $$NAME; \
		$(gcc) $(GCOV_FL) *_test.cc $(TEST_FL) -o test; \
		./test; \
		gcovr -r . --html --html-details -o cov-rep.html; \
		open cov-rep.html; \
		cd ../; \
	done

valgrind: test
	for NAME in $(CONTAINERS); do \
		valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./$$NAME/test; \
		done

array_valgrind : 
	$(gcc) ./array/*_test.cc $(TEST_FL) -o ./array/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./array/test

list_valgrind : 
	$(gcc) ./list/*_test.cc $(TEST_FL) -o ./list/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./list/test

map_valgrind : 
	$(gcc) ./map/*_test.cc $(TEST_FL) -o ./map/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./map/test

multiset_valgrind : 
	$(gcc) ./multiset/*_test.cc $(TEST_FL) -o ./multiset/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./multiset/test

queue_valgrind : 
	$(gcc) ./queue/*_test.cc $(TEST_FL) -o ./queue/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./queue/test

set_valgrind : 
	$(gcc) ./set/*_test.cc $(TEST_FL) -o ./set/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./set/test

stack_valgrind : 
	$(gcc) ./stack/*_test.cc $(TEST_FL) -o ./stack/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./stack/test

vector_valgrind : 
	$(gcc) ./vector/*_test.cc $(TEST_FL) -o ./vector/test
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s ./vector/test


docker :
	./docker_run.sh




