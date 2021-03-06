#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#define cols 4743
#define rows 41223
#define n 2000


using namespace std;
using namespace boost::numeric::ublas;
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

// mapped_matrix<int> bit_matrix (rows, cols, 184306);
float cosine_graph [cols][cols];
int bit_matrix [rows][cols];
int i, j, k;

int main() {
   string line;
   string foo = std::to_string(n);
   // ifstream myfile ("sorted_rows.txt"); // 10x8
   ifstream myfile ("20-ng-tfidf-m5.dat_r41223c4743.dense-hyp[2000].txt");
   // ifstream myfile ("tf-idf.cols");
   boost::char_separator<char> sep(" ");
   string val_wr;
   int val;
   for (i=0; i<rows; i++){
      for (j=0; j<cols; j++){
	bit_matrix [i][j] = 0;
      }
   }
   i = 0;
   j = 0;
   if (myfile.is_open()){
        while (getline(myfile,line)) {
           tokenizer tokens(line, sep);
           tokenizer::iterator tok_iter = tokens.begin();
           while (tok_iter != tokens.end()) {
                val_wr = *tok_iter;
                val = stoi(val_wr);
		if (val > 0) bit_matrix [i][j] = val;
                j++;
                ++tok_iter;
           }
           i++;
           j = 0;
        }
   }
   else std::cout << "Unable to open file!";
   cout << "matrix read\n";
   // Cosine graph generation
   // Norms
   float norms [cols];
   for (j=0; j < cols; j++){
      norms[j] = 0;
      for (i=0; i < rows; i++){
	norms[j] = norms[j] + pow(bit_matrix[i][j],2);
      }
      norms[j] = sqrt(norms[j]);
   }
   float num;
   float den;
   for (i=0; i<cols; i++){
      for (j=0; j<cols; j++){
	num = 0;
	den = norms[i]*norms[j];
	for (k=0; k<rows; k++){
	   num = num + bit_matrix[k][i]*bit_matrix[k][j];
	}
	cosine_graph [i][j] = ((float)num/(float)den);
      }
      // cout << std::to_string(i) << endl;
   }
   ofstream outfile;
   // outfile.open ("matrix_1_hyp.txt");
   outfile.open ("20-ng-tfidf-m5.dat_r41223c4743.dense-matrix_2_sig_hyp["+foo+"].txt");
   for (i=0; i<cols; i++){
      for (j=0; j<cols; j++){
	outfile << setprecision(10) << fixed << cosine_graph [i][j] << ' ';
      }
      outfile << "\n";
   }
   return 0;
}
