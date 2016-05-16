#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#define cols 2612
#define rows 200

using namespace std;
using namespace boost::numeric::ublas;
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

// mapped_matrix<int> bit_matrix (rows, cols, 184306);
float jaccard_graph [cols][cols];
int i, j, k;
int bit_matrix [rows][cols];
int cost_matrix [rows][cols];

int main(int argc, char* argv[]) {
   string line;
   string foo = std::to_string(rows);
   // ifstream myfile ("sorted_rows.txt"); // 10x8
   ifstream myfile ("tf-idf-hyp["+foo+"].txt");
   // ifstream myfile ("tf-idf["+foo+"].txt");
   boost::char_separator<char> sep(" ");
   string val_wr;
   int val;
   for (i=0; i<rows; i++){
      for (j=0; j<cols; j++){
	bit_matrix [i][j] = 0;
      }
   }
   ifstream penalty ("penalty-hyp["+foo+"].txt");
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
   i = 0;
   j = 0;
   if (penalty.is_open()){
        while (getline(penalty,line)) {
           tokenizer tokens(line, sep);
           tokenizer::iterator tok_iter = tokens.begin();
           while (tok_iter != tokens.end()) {
                val_wr = *tok_iter;
                val = stoi(val_wr);
                cost_matrix [i][j] = val;
                j++;
                ++tok_iter;
           }
           i++;
           j = 0;
        }
   }
   else std::cout << "Unable to open file!";
   cout << "matrix read\n";
   // Jaccard graph generation
   int num;
   int den;
   for (i=0; i<cols; i++){
      for (j=0; j<cols; j++){
	num = 0;
	den = 0;
	for (k=0; k<rows; k++){
	   den = den + std::abs(cost_matrix[k][i]) + std::abs(cost_matrix[k][j]);
	   if (bit_matrix [k][i] == bit_matrix [k][j]) {
		num = num + std::abs(cost_matrix[k][i]) + std::abs(cost_matrix[k][j]);
	   }
	}
	jaccard_graph [i][j] = 2*((float)num/(float)den)-1;
	if (jaccard_graph [i][j] < 0) jaccard_graph [i][j] = 0;
      }
      // cout << std::to_string(i) << endl;
   }
   ofstream outfile;
   outfile.open ("matrix_2_sig_hyp_pen["+foo+"].txt");
   for (i=0; i<cols; i++){
      for (j=0; j<cols; j++){
	outfile << setprecision(4) << fixed << jaccard_graph [i][j] << ' ';
      }
      outfile << "\n";
   }
   return 0;
}
