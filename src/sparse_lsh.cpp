#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <set>
#include <cmath>
#include <unordered_map>
#include <boost/tokenizer.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>


//#define cols 2612

// Parameters: b, r: argv[1], argv[2]

using namespace std;
using namespace boost::numeric::ublas;

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
typedef std::pair<std::string, int> mypair;
boost::char_separator<char> sep(" ");
tokenizer::iterator tok_iter;
//mapped_matrix<float> graph (cols, cols, cols*cols);
int i, j, k;

int main(int argc, char* argv[])
{
    if (argc < 4) {
        cout << "Usage:" << argv[0] << " b r signature-input-file\n";
        return -1;
    }
    int b = atoi(argv[1]);
    int r = atoi(argv[2]);
    int n = b*r;

    int cols;
    string filename (argv[3]);

    string foo = std::to_string(n);

    // signature reading, set rows and cols in header
    string line;
    // ifstream myfile ("penalty-hyp["+foo+"].txt");
    //ifstream myfile ("tf-idf["+foo+"].txt");
    ifstream myfile (filename);
    string val_wr;
    int val;

    if (myfile.is_open()) {
        getline(myfile,line);
        tokenizer tokens(line, sep);
        tok_iter = tokens.begin();
        val_wr = *tok_iter;
        //rows = stoi(val_wr);
        ++tok_iter;
        val_wr = *tok_iter;
        cols = stoi(val_wr);
        cout << "Cols:" << cols << endl;
    }

    mapped_matrix<int> signature (n, cols, n*cols); // n is the length of the signature when r=1
    mapped_matrix<float> graph (cols, cols, cols*cols);

    i = 0;
    j = 0;


    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            tokenizer tokens(line, sep);
            tok_iter = tokens.begin();

            while (tok_iter != tokens.end() ) {  
                val_wr = *tok_iter;
                val = stoi(val_wr);
                signature (i,j) = val;
                j++;
                ++tok_iter;
            }
            i++;
            j = 0;

            if( i== n )
                break; // allows to use longer signature files to fill the signature
        }
    } else std::cout << "Unable to open file!";
    cout << "signature read" << endl;
    // hashing by bands
    std::unordered_multimap<std::string, int> m;
    m.reserve(cols*b*10); // buckets >> cols*b
    std::vector<std::string> chunk;
    std::string shingle;
    // std::pair<std::string, int> mypair;
    for (k=0; k<b; k++) {
        for (j=0; j<cols; j++) {
            for (i=k*r; i<(k+1)*r; i++) {
                shingle = std::to_string(signature (i,j));
                chunk.push_back (shingle);
            }
            shingle = std::to_string(k);
            for (i=0; i < chunk.size(); i++) {
                shingle = shingle + " " + chunk[i]; // add ' ' betweeen chunks avoiding FP
            }
            mypair par(shingle,j);
            m.insert (par);
            chunk.clear();
            shingle.clear(); // newline
        }
    }
    cout << "hashing done" << endl;
    // Buckets traversal
    unsigned nbuckets = m.bucket_count();
    // std::cout << "mymap has " << nbuckets << " buckets:\n";
    /* for (i=0; i < nbuckets; i++){
         if (m.bucket_size(i) > 1){
    cout << "bucket " << i << " contents: ";
    for (auto it=m.begin(i); it != m.end(i); it++) {
      cout << "<" << it->first << "," << it->second << "> ";
    }
    cout << endl;
         }
    } */
    // DxD matrix generator (for graph clustering)
    int rowID, colID;
    int length;
    // std::set<std::string> my_set;
    // std::string my_edge;
    for (i=0; i < nbuckets; i++) {
        length = m.bucket_size(i);
        if (length > 1 && length < 100) {
            int my_nodes[length];
            j = 0;
            for (auto it=m.begin(i); it != m.end(i); it++) {
                val = stoi(std::to_string(it->second));
                my_nodes[j] = val;
                j++;
            }
            /* std::sort (my_nodes, my_nodes+length);
            do {
              my_edge = std::to_string(my_nodes[0]) + ' ' + std::to_string(my_nodes[1]);
              my_set.insert (my_edge);
            } while ( std::next_permutation(my_nodes,my_nodes+length) ); */
            for (k=0; k < length; k++)
                for (j=0; j < length; j++) {
                    rowID = my_nodes[k];
                    colID = my_nodes[j];
                    graph (rowID,colID) = graph (rowID,colID) + 1;
                }
            /*
                for (std::set<std::string>::iterator iT=my_set.begin(); iT!=my_set.end(); ++iT) {
                   my_edge = *iT;
                   tokenizer tokens(my_edge, sep);
                   tok_iter = tokens.begin();
                   val_wr = *tok_iter;
                   rowID = stoi(val_wr);
                   ++tok_iter;
                   val_wr = *tok_iter;
                   colID = stoi(val_wr);
                   graph (rowID,colID) = graph (rowID,colID) + 1;
                }
                my_set.clear(); */
        }
    }
    cout << "DxD matrix ready" << endl;
    // Graph flush, file output
    ofstream outfile;
    //outfile.open ("matrix-tf-idf["+foo+"]-["+std::to_string(b)+"-"+std::to_string(r)+"].txt");
    outfile.open (filename+"-["+std::to_string(b)+"-"+std::to_string(r)+"].txt");
    // outfile.open ("matrix-"+foo+"-penalty-hyp-["+std::to_string(b)+"-"+std::to_string(r)+"].txt");
    // outfile << "2596\n";
    //
    float base;
    float exponent;
    float weight;

    outfile << cols  << endl;
    for (i=0; i < cols; i++) {
        graph (i,i) = b;
        for (j=0; j < cols; j++) {
            base = (float)graph (i,j)/(float)b;
            graph (i,j)>0?exponent=(float)1/(float)(r*graph (i,j)):exponent=1;
            weight = std::pow(base,exponent);
            outfile << setprecision(2) << fixed << weight << ' ';
        }
        outfile << "\n";
    }
    return 0;
}

