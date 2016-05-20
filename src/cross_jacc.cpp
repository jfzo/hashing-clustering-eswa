#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>

//#define cols 2612
//#define rows 200

using namespace std;
using namespace boost::numeric::ublas;
typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

// mapped_matrix<int> bit_matrix (rows, cols, 184306);
//float jaccard_graph [cols][cols];
int i, j, k;
//int bit_matrix [rows][cols];

int main(int argc, char* argv[])
{

    if( argc < 3 ) {
        cout<< "Usage: "<< argv[0] << " SIGNATURE_LEN(<input file signature length)  signature-input-file"<<endl;
        return -1;
    }

    int cols, rows;

    string line;
    int n;
    n= stoi(argv[1]);
    //string foo = std::to_string(n);
    string filename (argv[2]);
    //ifstream myfile ("tf-idf["+foo+"].txt");
    ifstream myfile (filename);
    boost::char_separator<char> sep(" ");
    string val_wr;
    int val;

    if (myfile.is_open()) {
        getline(myfile,line);
        tokenizer tokens(line, sep);
        tokenizer::iterator tok_iter = tokens.begin();

        val_wr = *tok_iter;
        rows = stoi(val_wr);
        ++tok_iter;
        val_wr = *tok_iter;
        cols = stoi(val_wr);
        cout << "rows: " << rows << " cols: " << cols << endl;
    }

    assert(n < rows);

    float** jaccard_graph = new float*[cols];// [cols][cols];
    for(i=0; i<cols; i++){
        jaccard_graph[i] = new float[cols];
        for(j=0; j<cols; j++)
            jaccard_graph[i][j] = 0.0;
    }


    int** bit_matrix = new int*[n];//[rows][cols];
    for(i=0; i<n; i++){
        bit_matrix[i] = new int[cols];
        for(j=0; j<cols; j++)
            bit_matrix[i][j] = 0;
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
            if(n==i)
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
                if (bit_matrix [k][i] == bit_matrix [k][j]) {
                    den++;
                    num++;
                } else {
                    if (bit_matrix [k][i] > 0) den++;
                    if (bit_matrix [k][j] > 0) den++;
                }
            }
            jaccard_graph [i][j] = ((float)num/(float)den);
        }
        // cout << std::to_string(i) << endl;
    }
    ofstream outfile;
    outfile.open (filename+"_matrix_2_sig["+std::to_string(n)+"].txt");
    outfile << cols << '\n';
    float sim;
    for (i=0; i<cols; i++) {
        for (j=0; j<cols; j++) {
            // sim = (2*jaccard_graph [i][j])-1; // cosine sim
            // if (sim < 0) sim = 0;
            sim = jaccard_graph[i][j]; // jaccard sim
            outfile << setprecision(4) << fixed << sim << ' ';
        }
        outfile << "\n";
    }

    
    for(i=0; i<cols; i++)
        delete[] jaccard_graph[i];
    delete[] jaccard_graph;


    for(i=0; i<n; i++)
        delete[] bit_matrix[i];
    delete[] bit_matrix;


    return 0;
}
