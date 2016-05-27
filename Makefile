SRCDIR=./


all: ${SRCDIR}/simple_lsh.cpp ${SRCDIR}/simple_min_hashing.cpp ${SRCDIR}/sparse_min_hashing.cpp ${SRCDIR}/cross_jacc.cpp ${SRCDIR}/sparse_lsh.cpp ${SRCDIR}/simple_random_hyp.cpp ${SRCDIR}/cross_cos.cpp ${SRCDIR}/cross_penalty.cpp
	g++ -std=c++0x -o simple_lsh.o ${SRCDIR}/simple_lsh.cpp
	g++ -std=c++0x -o simple_min_hashing.o ${SRCDIR}/simple_min_hashing.cpp
	g++ -std=c++0x -o sparse_min_hashing.o ${SRCDIR}/sparse_min_hashing.cpp
	g++ -std=c++0x -o cross_jacc.o ${SRCDIR}/cross_jacc.cpp
	g++ -std=c++0x -o sparse_lsh.o ${SRCDIR}/sparse_lsh.cpp
	g++ -std=c++0x -o simple_random_hyp.o ${SRCDIR}/simple_random_hyp.cpp
	g++ -std=c++0x -o cross_cos.o ${SRCDIR}/cross_cos.cpp
	g++ -std=c++0x -o cross_penalty.o ${SRCDIR}/cross_penalty.cpp
