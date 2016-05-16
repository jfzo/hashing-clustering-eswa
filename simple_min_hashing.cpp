#include <string>
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#define cols 8
#define rows 10
#define n 20
#define B 100
#define P 101


// n: num of hash funcs, B: num buckets, P: prime (P>B)

using namespace std;

int universal_hash(int key, int a, int b, int p, int N){
   int v;
   v = ((a*key+b)%p)%N;
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
   string line;
   ifstream myfile ("sorted_rows.txt");
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
		bit_matrix[i][j] = val;
		j++;
		++tok_iter;
	   }
           i++;  
	   j = 0;
        }
   }
   else std::cout << "Unable to open file!";
   // Signature creation
   int infty = 10000;
   for (i=0; i<n; i++){
      for (j=0; j<cols; j++){
	signature[i][j] = infty;
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
	if (bit_matrix[i][j] == 1) {
	   for (k=0; k<n; k++){
	      if (signature[k][j] > v[k]) {
		signature[k][j] = v[k];
	      }
	   }
	}
      }
      a = 0;
      b = 1;
   }
   // Signature flush, file output
   ofstream outfile;
   outfile.open ("signature.txt");
   for (i=0; i<n; i++){
      for (j=0; j<cols; j++){
	outfile << signature[i][j] << " ";
      }
      outfile << "\n";
   }
   outfile.close();
   return 0;
}
