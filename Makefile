SRCDIR=./src


all: ${SRCDIR}/simple_lsh.cpp ${SRCDIR}/simple_min_hashing.cpp ${SRCDIR}/sparse_min_hashing.cpp ${SRCDIR}/cross_jacc.cpp ${SRCDIR}/sparse_lsh.cpp ${SRCDIR}/simple_random_hyp.cpp ${SRCDIR}/cross_cos.cpp ${SRCDIR}/cross_penalty.cpp
	g++ -std=c++0x -o simple_lsh ${SRCDIR}/simple_lsh.cpp
	g++ -std=c++0x -o simple_min_hashing ${SRCDIR}/simple_min_hashing.cpp
	g++ -std=c++0x -o sparse_min_hashing ${SRCDIR}/sparse_min_hashing.cpp
	g++ -std=c++0x -o cross_jacc ${SRCDIR}/cross_jacc.cpp
	g++ -std=c++0x -o sparse_lsh ${SRCDIR}/sparse_lsh.cpp
	g++ -std=c++0x -o simple_random_hyp ${SRCDIR}/simple_random_hyp.cpp
	g++ -std=c++0x -o cross_cos ${SRCDIR}/cross_cos.cpp
	g++ -std=c++0x -o cross_penalty ${SRCDIR}/cross_penalty.cpp

