CXXFLAGS=-Wall -g -std=gnu++17 -I./inc -I./src

clmg: src/main.cpp src/grade.cpp src/dataImporter.cpp #src/weedout.cpp
	${CXX} -o $@ ${CXXFLAGS}  $^

clean:
	rm -f clmg
