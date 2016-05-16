#include <string>
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/io.hpp>

//#define cols 2612
//#define rows 32095
//#define B 10000
//#define P 10007
//#define n 200

// n: num of hash funcs, B: num buckets, P: prime (P>B)

using namespace std;
using namespace boost::numeric::ublas;

int universal_hash(int key, int a, int b, int p)
{
    int v;
    v = ((a*key+b)%p)%2;
    v<0?v=-v:v=v;
    return v;
}

//int bit_matrix [rows][cols];
//int signature [n][cols];
int i, j, k;

int main(int argc, char* argv[])
{
    if (argc != 5) {
        cerr << "Some arguments are missing"<< endl;
        cout << "Usage:"<<argv[0]<<" n B P <<filename>>\n";
        return -1;
    }

    int cols, rows, nnz; // It assumes that the input file contains #rows terms from #cols documents.
    int n = atoi(argv[1]);
    long int B = atol(argv[2]);
    long int P = atol(argv[3]);
    string filename (argv[4]);



    string line;
    //ifstream myfile ("tf-idf.cols");
    ifstream myfile (filename);
    boost::char_separator<char> sep(" ");
    string val_wr;
    int ix;
    double val;


    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

    if (myfile.is_open()) {
        getline(myfile,line);
        tokenizer tokens(line, sep);
        tokenizer::iterator tok_iter = tokens.begin();

        val_wr = *tok_iter;
        cols = stoi(val_wr);
        ++tok_iter;
        val_wr = *tok_iter;
        rows = stoi(val_wr);
        ++tok_iter;
        val_wr = *tok_iter;
        nnz = stoi(val_wr);
        cout << "rows: " << rows << " cols: " << cols << endl;
    }


    int** bit_matrix = new int*[rows];//[rows][cols];
    for(i=0; i<rows; i++){
        bit_matrix[i] = new int[cols];
        for(j=0; j<cols; j++)
            bit_matrix[i][j] = 0;
    }


    int** signature = new int*[n];//[n][cols];
    for(i=0; i<n; i++){
        signature[i] = new int[cols];
        for(j=0; j<cols; j++)
            signature[i][j] = 0;
    }


    i = 0;
    j = 0;

    if (myfile.is_open()) {
        while (getline(myfile,line)) {

            tokenizer tokens(line, sep);
            tokenizer::iterator tok_iter = tokens.begin();
            while (tok_iter != tokens.end()) {               
                val_wr = *tok_iter;
                ix = stoi(val_wr) - 1; // indices start at 1 in Cluto's format
                ++tok_iter;
                val_wr = *tok_iter;
                val = stod(val_wr);
                if (val > 0) bit_matrix[ix][i] = val;// value in column ix for example i
                j++;
                ++tok_iter;
            }
            i++;
            j = 0;
        }
    } else std::cout << "Unable to open file!";
    std::cout << "Matrix downloaded!\n";
    // Signature creation
    int a = 0;
    int b = 1;
    int p = P;
    int v [n]; // array of n hash values
    for (i=0; i<rows; i++) {
        a = a + b;
        b = a + b;
        for (j=0; j<n; j++) {
            v[j] = universal_hash(i,a,b,p);
            a = a + b;
            b = a + b;
        }
        for (j=0; j<cols; j++) {
            for (k=0; k<n; k++) {
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
    //outfile.open ("tf-idf-hyp["+std::to_string(n)+"].txt");
    //penalty.open ("penalty-hyp["+std::to_string(n)+"].txt");
    outfile.open (filename+"-hyp["+std::to_string(n)+"].txt");
    penalty.open (filename+"-penalty-hyp["+std::to_string(n)+"].txt");

    outfile << n << " " << cols <<"\n";
    penalty << n << " " << cols <<"\n";

    for (i=0; i<n; i++) {
        for (j=0; j<cols; j++) {
            if (signature[i][j] >= 0) outfile << "1 ";
            else outfile << "-1 ";
            penalty << std::to_string(signature[i][j]) << " ";
        }
        outfile << "\n";
        penalty << "\n";
    }
    outfile.close();
    penalty.close();



    for(i=0; i<rows; i++)
        delete[] bit_matrix[i];
    delete[] bit_matrix;


    for(i=0; i<n; i++)
        delete[] signature[i];
    delete[] signature;

    return 0;
}
