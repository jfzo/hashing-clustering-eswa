#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
//#define cols 2612
//#define rows 200

using namespace std;
using namespace boost::numeric::ublas;
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

// mapped_matrix<int> bit_matrix (rows, cols, 184306);

int i, j, k;


int main(int argc, char* argv[])
{

    if(argc != 3){
        cerr<<"Usage: "<< argv[0] <<" hyp-input-filename penalty-input-filename\n";
        return -1;
    }

    string line;
    //string foo = std::to_string(rows);
    string filename1(argv[1]);//path to hyp file
    string filename2(argv[2]);//path to penalty file

    // ifstream myfile ("sorted_rows.txt"); // 10x8
    //ifstream myfile ("tf-idf-hyp["+foo+"].txt");
    ifstream myfile (filename1);
    // ifstream myfile ("tf-idf["+foo+"].txt");
    boost::char_separator<char> sep(" ");
    string val_wr;

    int rows, cols;
    int val;


    //ifstream penalty ("penalty-hyp["+foo+"].txt");
    ifstream penalty (filename2);
    
    //obtener filas y columnas

    if (myfile.is_open()) {    
        getline(myfile,line);
        tokenizer tokens(line, sep);
        tokenizer::iterator tok_iter = tokens.begin();
        val_wr = *tok_iter;
        rows = stoi(val_wr);
        ++tok_iter;
        val_wr = *tok_iter;
        cols = stoi(val_wr);
        cout << "Rows:"<<rows<<" cols:"<<cols<<endl;
    }

    float** jaccard_graph = new float*[cols];// [cols][cols];
    for(i=0; i<cols; i++)
        jaccard_graph[i] = new float[cols];

    int** bit_matrix = new int*[rows];// [rows][cols];
    for (i=0; i<rows; i++) {
        bit_matrix[i] = new int[cols];
        for (j=0; j<cols; j++) {
            bit_matrix [i][j] = 0;
        }
    }

    int** cost_matrix = new int*[rows];// [rows][cols];
    for(i=0; i<rows; i++)
        cost_matrix[i] = new int[cols];


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
    i = 0;
    j = 0;
    if (penalty.is_open()) {
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
    } else std::cout << "Unable to open file!";
    cout << "matrix read\n";
    // Jaccard graph generation
    int num;
    int den;
    for (i=0; i<cols; i++) {
        for (j=0; j<cols; j++) {
            num = 0;
            den = 0;
            for (k=0; k<rows; k++) {
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
    //outfile.open ("matrix_2_sig_hyp_pen["+foo+"].txt");
    outfile.open (filename1+"_matrix_2_sig_hyp_pen.txt");
    outfile << cols << "\n";
    for (i=0; i<cols; i++) {
        for (j=0; j<cols; j++) {
            outfile << setprecision(4) << fixed << jaccard_graph [i][j] << ' ';
        }
        outfile << "\n";
    }


    for(i=0; i<cols; i++)
        delete[] jaccard_graph[i];
    delete[] jaccard_graph;

    for (i=0; i<rows; i++) 
        delete[] bit_matrix[i];
    delete[] bit_matrix;

    for(i=0; i<rows; i++)
        delete[] cost_matrix[i];
    delete[] cost_matrix;

    return 0;
}
