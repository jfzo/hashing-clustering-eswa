#include <string>
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>

//#define cols 2612
//#define rows 32095
//#define B 10000 // B >> cols i.e. the number of documents
//#define P 10007 // P > B

// n: num of hash funcs (argv[1]), B: num buckets, P: prime (P>B)

using namespace std;
using namespace boost::numeric::ublas;

int universal_hash(int key, int a, int b, int p, int N)
{
    int v;
    v = ((a*key+b)%p)%N;
    v<0?v=-v:v=v;
    return v;
}

mapped_matrix<int> bit_matrix;// (rows, cols, rows*cols);
int i, j, k;

int main(int argc, char* argv[])
{
    if (argc != 5){ 
        cerr << "Some arguments are missing"<< endl;
        cout << "Usage:"<<argv[0]<<" n B P <<filename>>\n";
        return -1;
    }

    int cols, rows, nnz; // It assumes that the input file contains #rows terms from #cols documents.
    int n = atoi(argv[1]);
    long int B = atol(argv[2]);
    long int P = atol(argv[3]);
    string filename (argv[4]);

    mapped_matrix<int> signature;// (n, cols, n*cols);
    // bit_matrix reading, set rows and cols in header
    string line;
    ifstream myfile (filename);
    boost::char_separator<char> sep(" ");
    string val_wr;
    int val, ix;
    double ix_val;
    i = 0;
    j = 0;
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    bool header_ok = false;
    /* In Cluto's format for sparse matrices, the first line contains the header (nrows, ncols and nnz values).
     * Documents processed as vectors are represented as a matrix, in which each row denotes a document and each column
     * denotes a term in the vocabulary.
     */
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            tokenizer tokens(line, sep);
            if( !header_ok ){
                tokenizer::iterator tok_iter = tokens.begin();
                val_wr = *tok_iter;
                cols = stoi(val_wr);
                ++tok_iter;
                val_wr = *tok_iter;
                rows = stoi(val_wr);
                ++tok_iter;
                val_wr = *tok_iter;nnz = stoi(val_wr);
                header_ok = true;
                bit_matrix = mapped_matrix<int> (rows, cols, nnz);
                signature = mapped_matrix<int> (n, cols, n*cols);
                cout << "rows:"<<rows<<" cols:"<<cols<<endl;
                continue;
            }
        
            tokenizer::iterator tok_iter = tokens.begin();
            while (tok_iter != tokens.end()) { //read in pairs
                val_wr = *tok_iter;
                ix = stoi(val_wr) - 1; // indices start at 1 in Cluto's format
                ++tok_iter;
                val_wr = *tok_iter;
                //cout << "VAL("<< ix  <<")="<< stod(val_wr) << endl;
                ix_val = (stod(val_wr)>0)?1:0;
                bit_matrix (ix,i) = ix_val;
                ++tok_iter;
            }
            i++;
            j = 0;
        }
    } else std::cout << "Unable to open file!\n";
    std::cout << "Matrix loaded!\n";

    /* showing the matrix (just for testing)
    for (unsigned i = 0; i < bit_matrix.size1 (); ++ i){
        for (unsigned j = 0; j < bit_matrix.size2 (); ++ j)
            cout << bit_matrix(i, j) << " ";
        cout << endl;
    }

    return 0;
    */




    // Signature creation
    int infty = B;
    for (i=0; i<n; i++) {
        for (j=0; j<cols; j++) {
            signature (i,j) = infty;
        }
    }
    int a = 0;
    int b = 1;
    int p = P;
    int N = B;
    int v [n]; // array of n hash values
    for (i=0; i<rows; i++) {
        a = a + b;
        b = a + b;
        for (j=0; j<n; j++) {
            v[j] = universal_hash(i,a,b,p,N);
            a = a + b;
            b = a + b;
        }
        for (j=0; j<cols; j++) {
            if (bit_matrix(i,j) == 1) {
                for (k=0; k<n; k++) {
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
    outfile.open (filename+"["+std::to_string(n)+"].txt");
    outfile << n << " " << cols << endl; // header
    for (i=0; i<n; i++) {
        for (j=0; j<cols; j++) {
            outfile << signature (i,j) << " ";
        }
        outfile << "\n";
    }
    outfile.close();
    return 0;
}
