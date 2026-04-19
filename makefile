CXXFLAGS=-Wall -g -std=gnu++17 -O0 -I./inc -I./src

all: clmg guimg

clmg: src/main.cpp src/grade.cpp src/dataImporter.cpp 
	${CXX} -o $@ ${CXXFLAGS}  $^

guimg: src/guimain.cpp src/grade.cpp src/dataImporter.cpp src/mainwindow.cpp
	${CXX} $^ ${CXXFLAGS}  `pkg-config gtkmm-4.0 --cflags --libs` -o $@

dropdown:./src/examplewindow.cpp ./src/guimain.cpp
	${CXX} $^ ${CXXFLAGS} `pkg-config gtkmm-4.0 --cflags --libs` -o $@


clean:
	rm -f clmg
	rm -f guimg
	rm -f dropdown
