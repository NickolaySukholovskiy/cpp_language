
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -g -fsanitize=address
GTESTFLAG = -lgtest
GFLAGS = -ftest-coverage -fprofile-arcs #--coverage

#--------------------------------------------

all: test

test: s21_matrix_oop.a
	$(CC) $(CFLAGS) new_test.cc s21_matrix_oop.a -o test $(GTESTFLAG)
	./test

s21_matrix_oop.a: s21_matrix_oop.cc
	$(CC) $(CFLAGS) s21_matrix_oop.cc -c
	ar rvs s21_matrix_oop.a s21_matrix_oop.o

gcov_report:
	$(CC) $(CFLAGS) $(GFLAGS) new_test.cc s21_matrix_oop.cc -o gcov_report $(GTESTFLAG)
	./gcov_report
	mkdir test_output
	cd test_output
	gcov ../s21_matrix_oop.gcno ../new_test.gcno
	cd ..
	gcovr -r . --html --html-details -o ./test_output/coverage-report.html
	open test_output/coverage-report.html

style:
	clang-format -style=Google -n *.cc *.h

leaks:
	make main
	leaks -atExit -- ./main
	make clean
	
clean:
	rm -f main
	rm -f *.o
	rm -f *.a
	rm -rf *.dSYM
	rm -f test
	rm -f *.gcno
	rm -f *.gcda
	rm -f gcov_report
	rm -f *.info
	rm -rf report
	rm -rf test_output

rebuild:
	make clean
	make all
