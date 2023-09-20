CXX = g++ -g -Wall -Werror -Wextra -std=c++17
FILES_CC = CalcController.cc CalcController.h CalcModel.cc CalcModel.h
FILES_CPP = ./CalcView/mainwindow.cpp ./CalcView/mainwindow.h ./CalcView/mainwindow.ui ./CalcView/qcustomplot.cpp ./CalcView/qcustomplot.h
BUILD_FOLDER = build
P_NAME = SmartCalc_v2
T_NAME = $(P_NAME)-build-realese-v1.tar.gz
TEST_SOURSE = ./tests/CalcController.o ./tests/CalcModel.o
TEST_FLAGS = -lgtest -lgtest_main
OPEN = xdg-open

ifeq ($(shell uname -s), Darwin)
	OPEN=open
else
	TEST_FLAGS+=-lm
endif

all: clean dvi dist gcov_report install run
.PHONY : all

install: uninstall ./CalcView/main.cpp $(FILES_CC) $(FILES_CPP)
		if [ ! -f "build/$(P_NAME)" ]; then \
				cd CalcView/ && qmake6 $(P_NAME).pro && make; \
				if ! [ -d "./../build" ]; then \
						mkdir ./../build; \
				fi; \
				cp $(P_NAME) ./../build/; \
		fi
.PHONY : install

run:
		./build/$(P_NAME)
.PHONY : run

dvi:
		cd doxygen && doxygen Doxyfile
		$(OPEN) doxygen/html/index.html 2> /dev/null
.PHONY : dvi

dist: clean
		mkdir $(BUILD_FOLDER)
		touch $(BUILD_FOLDER)/$(T_NAME)
		tar --exclude=$(BUILD_FOLDER) -zcvf $(BUILD_FOLDER)/$(T_NAME) .

.PHONY : dist

test: clean_files
		@mkdir ./tests
		@$(CXX) -c --coverage CalcController.cc -o ./tests/CalcController.o
		@$(CXX) -c --coverage CalcModel.cc -o ./tests/CalcModel.o
		@$(CXX) test.cc $(TEST_SOURSE) --coverage $(TEST_FLAGS) -o ./tests/my_test
		@./tests/my_test
.PHONY : test

gcov_report: test ./tests/my_test
		@gcovr -r . --html --html-details -o ./tests/report.html
		@$(OPEN) ./tests/report.html 2> /dev/null
.PHONY : gcov_report

style:
		clang-format -style=google -n *.c* *.h* CalcView/*.c* CalcView/*.h*
.PHONY : style

rebuild: uninstall install
.PHONY : rebuild

clean: uninstall clean_files
.PHONY : clean

clean_files:
		rm -rf *.o
		rm -rf ./doxygen/html
		rm -rf ./tests
		rm -rf *.gcno *.gcda
		rm -rf my_test
		rm -rf *.gcov
		rm -rf build-SmartCalc_v2-Desktop-Debug
.PHONY : clean_files
		

uninstall:
		rm -rf build/$(T_NAME)
		rm -rf build/$(P_NAME)
		rm -rf ./CalcView/$(P_NAME)
		rm -rf $(BUILD_FOLDER)
		rm -rf ./CalcView/$(P_NAME).pro.user
		rm -rf ./CalcView/.qmake.stash
		rm -rf ./CalcView/*.o
		rm -rf ./CalcView/.qmake.stash
		rm -rf ./CalcView/Makefile
		rm -rf ./CalcView/moc_*
		rm -rf ./CalcView/ui_mainwindow.h
		rm -rf *.gz
.PHONY : uninstall
