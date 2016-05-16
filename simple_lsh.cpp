#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <boost/tokenizer.hpp>
#define b 5
#define r 2
#define n 20
#define cols 8

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
boost::char_separator<char> sep(" ");
tokenizer::iterator tok_iter;

using namespace std;

int graph [cols][cols];
int signature [n][cols];
int i, j, k;

int main() {
   // signature reading, set rows and cols in header
   for (i=0; i<n; i++) {
      for (j=0; j<cols; j++) {
        signature[i][j] = 0;
      }
   }
   string line;
   ifstream myfile ("signature.txt");
   // boost::char_separator<char> sep(" ");
   string val_wr;
   int val;
   i = 0;
   j = 0;
   if (myfile.is_open()){
        while (getline(myfile,line)) {
           // typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
           tokenizer tokens(line, sep);
           tok_iter = tokens.begin();
           while (tok_iter != tokens.end()) {
                val_wr = *tok_iter;
                val = stoi(val_wr);
                signature[i][j] = val;
                j++;
                ++tok_iter;
           }
           i++;
           j = 0;
        }
   }
   else std::cout << "Unable to open file!";
   // hashing by bands
   std::unordered_multimap<std::string, int> m;
   m.reserve(cols*b*10);
   std::vector<std::string> chunk;
   std::string shingle;
   for (k=0; k<b; k++){
      for (j=0; j<cols; j++){
	for (i=k*r; i<(k+1)*r; i++){
	   shingle = std::to_string(signature[i][j]);
	   chunk.push_back (shingle);
	}
	shingle = std::to_string(k);
	for (i=0; i < chunk.size(); i++){
	   shingle = shingle + chunk[i];
	}
	std::pair<std::string, int> mypair (shingle,j);
	m.insert (mypair);
	chunk.clear();
      }
   }
   // Buckets traversal
   unsigned nbuckets = m.bucket_count();
   std::cout << "mymap has " << nbuckets << " buckets:\n";
   for (i=0; i < nbuckets; i++){
        if (m.bucket_size(i) > 1){
	cout << "bucket " << i << " contents: ";
	for (auto it=m.begin(i); it != m.end(i); it++) {
	  cout << "<" << it->first << "," << it->second << "> ";
	}
	cout << endl;
        }
   }
   // Graph list generator
   /*
   std::set<std::string> my_set;
   std::string my_edge;
   for (i=0; i < nbuckets; i++){
     if (m.bucket_size(i) > 1){
	int my_nodes[m.bucket_size(i)];
	j = 0;
        for (auto it=m.begin(i); it != m.end(i); it++) {
	  val = stoi(std::to_string(it->second));
	  my_nodes[j] = val;
          j++;
        }
	std::sort (my_nodes, my_nodes+j);
        do {
    	  my_edge = std::to_string(my_nodes[0]) + ' ' + std::to_string(my_nodes[1]);
    	  my_set.insert (my_edge);
  	} while ( std::next_permutation(my_nodes,my_nodes+j) );
        for (std::set<std::string>::iterator iT=my_set.begin(); iT!=my_set.end(); ++iT)
    	   std::cout << *iT << '\n';
	my_set.clear();
     }
   } */
   // DxD matrix generator (for graph clustering)
   int rowID, colID;
   for (i=0; i<cols; i++) {
      for (j=0; j<cols; j++) {
        graph [i][j] = 0;
      }
      graph [i][i] = 1;
   }
   int length;
   std::set<std::string> my_set;
   std::string my_edge;
   for (i=0; i < nbuckets; i++){
     length = m.bucket_size(i);
     if (length > 1){
        int my_nodes[length];
	j = 0;
        for (auto it=m.begin(i); it != m.end(i); it++) {
          val = stoi(std::to_string(it->second));
          my_nodes[j] = val;
	  j++;
        }
        std::sort (my_nodes, my_nodes+length);
        do {
          my_edge = std::to_string(my_nodes[0]) + ' ' + std::to_string(my_nodes[1]);
          my_set.insert (my_edge);
        } while ( std::next_permutation(my_nodes,my_nodes+length) );
	for (std::set<std::string>::iterator iT=my_set.begin(); iT!=my_set.end(); ++iT) {
	   my_edge = *iT;
	   tokenizer tokens(my_edge, sep);
	   tok_iter = tokens.begin();
	   val_wr = *tok_iter;
           rowID = stoi(val_wr);
           ++tok_iter;
	   val_wr = *tok_iter;
           colID = stoi(val_wr);
           graph [rowID][colID] = graph[rowID][colID] + 1;
	}
        my_set.clear();
     }
   }
   float base;
   float exponent;
   float weight;
   for (i=0; i < cols; i++) {
      graph [i][i] = b;
      for (j=0; j < cols; j++) {
	base = (float)graph [i][j]/(float)b;
	graph[i][j]>0?exponent=(float)1/(float)(r*graph[i][j]):exponent=1;
        weight = std::pow(base,exponent);
	cout << setprecision(2) << fixed << weight << ' ';
      }
      cout << "\n";
   }
   return 0;
}

