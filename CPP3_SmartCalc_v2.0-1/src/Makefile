
CC = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra -g #-fsanitize=address
GTESTFLAG = -lgtest
GCOVFLAGS = -ftest-coverage -fprofile-arcs --coverage
TAR_DIR = SmartCalc_v1.0_v1.0_Archive

BACK_DIR = back
SOURCES = $(shell find $(BACK_DIR) -name '*.cc' && find . -name 'test.cc')
OBJECTS = $(patsubst $(BACK_DIR)/%.cc, %.o, $(SOURCES))
EXECUTABLE = test

QT_PROJECT_NAME = calc_interface
QT_PROJECT_FOLDER = $(QT_PROJECT_NAME)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = build
QT_APP_FOLDER = ../app
DIST_FOLDER_NAME = SmartCalc-1.0
OS_NAME = $(shell uname -s)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(GTESTFLAG) -o $(EXECUTABLE) -lpthread
	./$(EXECUTABLE)

%.o: $(BACK_DIR)/%.cc
	$(CC) $(FLAGS) -c $< -o $@

main: $(OBJECTS)
	$(CC) $(FLAGS) -c main.cc 
	$(CC) $(FLAGS) $(OBJECTS) main.o -o main

generate_make:
	qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
	rm -rf .qmake.stash

install: generate_make
	cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	mkdir -p ./$(QT_APP_FOLDER)
ifeq ($(OS_NAME), Linux) 
	mv build/$(QT_PROJECT_NAME) $(QT_APP_FOLDER)
endif 
ifeq ($(OS_NAME), Darwin)
	mv build/$(QT_PROJECT_NAME).app $(QT_APP_FOLDER) 
endif
	rm -rf $(QT_BUILD_FOLDER)

uninstall:
	rm -rf $(QT_APP_FOLDER)

dvi:
	doxygen Doxyfile
	open doxy/html/index.html

TAR_DIR = SmartCalc_v1.0_v1.0_Archive

dist:
	rm -Rf $(TAR_DIR)
	mkdir $(TAR_DIR)
	mkdir $(TAR_DIR)/src
	cp $(BACK_DIR)/* $(QT_PROJECT_NAME)/* $(TAR_DIR)/src
	tar cvzf $(TAR_DIR).tgz $(TAR_DIR)
	mv $(TAR_DIR).tgz ..
	rm -Rf $(TAR_DIR)

clang-format:
	clang-format --style=Google -i $(QT_PROJECT_NAME)/*.h $(QT_PROJECT_NAME)/*.cpp $(BACK_DIR)/*.h $(BACK_DIR)/*.cc

clang-check:
	clang-format --style=Google -n $(QT_PROJECT_NAME)/*.h $(QT_PROJECT_NAME)/*.cpp $(BACK_DIR)/*.h $(BACK_DIR)/*.cc

rebuild:
	make clean
	make all

clean:
	rm -f *.o
	rm -f main
	rm -f test
	rm -rf *.dSYM
	rm -f *.gcda
	rm -f *.gcno
	rm -f gcov_report
	rm -f *.info
	rm -f $(BACK_DIR)/*.o
	rm -f $(BACK_DIR)/*.gch
	rm -rf ../$(QT_BUILD_FOLDER)/*
	rm -rf doxy
	rm -f ../*.tgz
	rm -rf build-calc_interface*