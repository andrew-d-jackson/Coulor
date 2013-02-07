EASY_BMP_FILES := $(wildcard src/easybmp/*.cpp)


coulor: src/main.cpp
	g++ src/main.cpp $(EASY_BMP_FILES) -o coulor
