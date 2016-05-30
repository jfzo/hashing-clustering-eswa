#include <string>
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/io.hpp>

//#define cols 2612
//#define rows 32095
#define B 10000
#define P 10007
#define n 1500


#define rows 41223
#define cols 4743



// n: num of hash funcs, B: num buckets, P: prime (P>B)

using namespace std;
using namespace boost::numeric::ublas;

int universal_hash(int key, int a, int b, int p){
   int v;
   v = ((a*key+b)%p)%2;
   v<0?v=-v:v=v;
   return v;
}

int bit_matrix [rows][cols];
int signature [n][cols];
int i, j, k;

int main() {
   // bit_matrix reading, set rows and cols in header
   for (i=0; i<rows; i++) {
      for (j=0; j<cols; j++) {
	bit_matrix[i][j] = 0;
      }
   }
   for (i=0; i<n; i++) {
      for (j=0; j<cols; j++) {
	signature[i][j] = 0;
      }
   }
   string line;
   ifstream myfile ("20-ng-tfidf-m5.dat_r41223c4743.dense");
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
		if (val > 0) bit_matrix[i][j] = val;
		j++;
		++tok_iter;
	   }
           i++;
	   j = 0;
        }
   }
   else std::cout << "Unable to open file!";
   std::cout << "Matrix downloaded!\n";
   // Signature creation
   int a = 0;
   int b = 1;
   int p = P;
   int v [n]; // array of n hash values
   for (i=0; i<rows; i++){
      a = a + b;
      b = a + b;
      for (j=0; j<n; j++) {
	v[j] = universal_hash(i,a,b,p);
	a = a + b;
	b = a + b;
      }
      for (j=0; j<cols; j++){
	   for (k=0; k<n; k++){
	      if (v[k] == 1) signature[k][j] = signature[k][j] + bit_matrix[i][j];
	      else signature[k][j] = signature[k][j] - bit_matrix[i][j];
	   }
      }
      a = 0;
      b = 1;
   }
   std::cout << "Signature created!\n";
   // Signature flush, file output
   ofstream outfile;
   ofstream penalty;
   outfile.open ("20-ng-tfidf-m5.dat_r41223c4743.dense-hyp["+std::to_string(n)+"].txt");
   penalty.open ("20-ng-tfidf-m5.dat_r41223c4743.dense-penalty-hyp["+std::to_string(n)+"].txt");
   for (i=0; i<n; i++){
      for (j=0; j<cols; j++){
	if (signature[i][j] >= 0) outfile << "1 ";
	else outfile << "-1 ";
	penalty << std::to_string(signature[i][j]) << " ";
      }
      outfile << "\n";
      penalty << "\n";
   }
   outfile.close();
   penalty.close();
   return 0;
}
