#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>

//#define cols 2612
//#define rows 32095
//#define n 200

using namespace std;
using namespace boost::numeric::ublas;
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

// //mapped_matrix<int> bit_matrix (rows, cols, 184306);
//float cosine_graph [cols][cols];
//int bit_matrix [rows][cols];
int i, j, k;

int main(int argc, char* argv[])
{

    if(argc  != 3 ) {
        cerr << "Usage: " << argv[0] << " n hyp-filename-path\n";
        return -1;
    }

    int rows, cols;
    int n;// = atoi(argv[1]);
    string filename(argv[2]);
    string line;

 
    // ifstream myfile ("sorted_rows.txt"); // 10x8
    //ifstream myfile ("tf-idf-hyp["+foo+"].txt");
    ifstream myfile (filename);
    // ifstream myfile ("tf-idf.cols");
    boost::char_separator<char> sep(" ");
    string val_wr;
    int val;


    if (myfile.is_open()) {
        getline(myfile,line);
        tokenizer tokens(line, sep);
        tokenizer::iterator tok_iter = tokens.begin();
        // get rows and cols ...
        val_wr = *tok_iter;
        rows = stoi(val_wr);
        ++tok_iter;
        val_wr = *tok_iter;
        cols = stoi(val_wr);
        cout << "rows:"<<rows << " cols:" << cols << endl;
    }

    n = rows;
    string foo = std::to_string(n);

    float** cosine_graph = new float*[cols];// [cols][cols];
    for(i=0; i<cols; i++){
        cosine_graph[i] = new float[cols];
        for(j=0; j<cols; j++)
            cosine_graph[i][j] = 0.0;
    }

    int** bit_matrix = new int*[rows];
    for (i=0; i<rows; i++) {
        bit_matrix[i] = new int[cols];
        for (j=0; j<cols; j++) {
            bit_matrix [i][j] = 0;
        }
    }

    i = 0;
    j = 0;


    if (myfile.is_open()) {
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
    } else std::cout << "Unable to open file!";
    cout << "matrix read\n";
    // Cosine graph generation
    // Norms
    float norms [cols];
    for (j=0; j < cols; j++) {
        norms[j] = 0;
        for (i=0; i < rows; i++) {
            norms[j] = norms[j] + pow(bit_matrix[i][j],2);
        }
        norms[j] = sqrt(norms[j]);
    }
    float num;
    float den;
    for (i=0; i<cols; i++) {
        for (j=0; j<cols; j++) {
            num = 0;
            den = norms[i]*norms[j];
            for (k=0; k<rows; k++) {
                num = num + bit_matrix[k][i]*bit_matrix[k][j];
            }
            cosine_graph [i][j] = ((float)num/(float)den);
        }
        // cout << std::to_string(i) << endl;
    }
    ofstream outfile;
    // outfile.open ("matrix_1_hyp.txt");
    //outfile.open ("matrix_2_sig_hyp["+foo+"].txt");
    outfile.open (filename+"_matrix_2_sig_hyp["+foo+"].txt");


    outfile << cols << '\n';

    for (i=0; i<cols; i++) {
        for (j=0; j<cols; j++) {
            outfile << setprecision(2) << fixed << cosine_graph [i][j] << ' ';
        }
        outfile << "\n";
    }



    for(i=0; i<cols; i++)
        delete[] cosine_graph[i];
    delete[] cosine_graph;


    for(i=0; i<rows; i++)
        delete[] bit_matrix[i];
    delete[] bit_matrix;

    return 0;
}
