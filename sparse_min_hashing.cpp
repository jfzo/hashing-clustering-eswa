#include <string>
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#define cols 2612
#define rows 32095
#define B 10000 // B >> cols
#define P 10007 // P > B

// n: num of hash funcs (argv[1]), B: num buckets, P: prime (P>B)

using namespace std;
using namespace boost::numeric::ublas;

int universal_hash(int key, int a, int b, int p, int N){
   int v;
   v = ((a*key+b)%p)%N;
   v<0?v=-v:v=v;
   return v;
}

mapped_matrix<int> bit_matrix (rows, cols, rows*cols);
int i, j, k;

int main(int argc, char* argv[]) {
   if (argc != 2) return -1;
   int n = atoi(argv[1]);
   mapped_matrix<int> signature (n, cols, n*cols);
   // bit_matrix reading, set rows and cols in header
   string line;
   ifstream myfile ("tf-idf.cols");
   boost::char_separator<char> sep(" ");
   string val_wr;
   int val;
   i = 0;
   j = 0;
   if (myfile.is_open()){
        while (getline(myfile,line)) {
           typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
           tokenizer tokens(line, sep);
           tokenizer::iterator tok_iter = tokens.begin();
	   while (tok_iter != tokens.end()) {
		val_wr = *tok_iter;
		val = stoi(val_wr);
		if (val > 0) bit_matrix (i,j) = val;
		j++;
		++tok_iter;
	   }
           i++;
	   j = 0;
        }
   }
   else std::cout << "Unable to open file!\n";
   std::cout << "Matrix downloaded!\n";
   // Signature creation
   int infty = B;
   for (i=0; i<n; i++){
      for (j=0; j<cols; j++){
	signature (i,j) = infty;
      }
   }
   int a = 0;
   int b = 1;
   int p = P;
   int N = B;
   int v [n]; // array of n hash values
   for (i=0; i<rows; i++){
      a = a + b;
      b = a + b;
      for (j=0; j<n; j++) {
	v[j] = universal_hash(i,a,b,p,N);
	a = a + b;
	b = a + b;
      }
      for (j=0; j<cols; j++){
	if (bit_matrix(i,j) == 1) {
	   for (k=0; k<n; k++){
	      if (signature (k,j) > v[k]) {
		signature (k,j) = v[k];
	      }
	   }
	}
      }
      a = 0;
      b = 1;
   }
   std::cout << "Signature created!\n";
   // Signature flush, file output
   ofstream outfile;
   outfile.open ("tf-idf["+std::to_string(n)+"].txt");
   for (i=0; i<n; i++){
      for (j=0; j<cols; j++){
	outfile << signature (i,j) << " ";
      }
      outfile << "\n";
   }
   outfile.close();
   return 0;
}
