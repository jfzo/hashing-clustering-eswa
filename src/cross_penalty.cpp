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

    if(argc != 4){
        cerr<<"Usage: "<< argv[0] <<" SIGNATURELEN(<= signature len in hyp-file) hyp-input-filename penalty-input-filename\n";
        return -1;
    }

    string line;
    //string foo = std::to_string(rows);
    int n = atoi(argv[1]);
    string filename1(argv[2]);//path to hyp file
    string filename2(argv[3]);//path to penalty file

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

    assert(n <= rows );

    float** jaccard_graph = new float*[cols];// [cols][cols];
    for(i=0; i<cols; i++)
        jaccard_graph[i] = new float[cols];

    int** bit_matrix = new int*[n];// [n][cols];
    for (i=0; i<n; i++) {
        bit_matrix[i] = new int[cols];
        for (j=0; j<cols; j++) {
            bit_matrix [i][j] = 0;
        }
    }

    int** cost_matrix = new int*[n];// [n][cols];
    for(i=0; i<n; i++)
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
            if(i==n)
                break;
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
            if(i==n)
                break;
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
            for (k=0; k<n; k++) {
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
    string foo = std::to_string(n);
    outfile.open (filename1+"_matrix_2_sig_hyp_pen["+foo+"].txt");
    outfile << cols << "\n";
    for (i=0; i<cols; i++) {
        for (j=0; j<cols; j++) {
            outfile << setprecision(5) << fixed << jaccard_graph [i][j] << ' ';
        }
        outfile << "\n";
    }


    for(i=0; i<cols; i++)
        delete[] jaccard_graph[i];
    delete[] jaccard_graph;

    for (i=0; i<n; i++) 
        delete[] bit_matrix[i];
    delete[] bit_matrix;

    for(i=0; i<n; i++)
        delete[] cost_matrix[i];
    delete[] cost_matrix;

    return 0;
}
