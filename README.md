# hashing-clustering-eswa

## About the work 
The code available in this repository corresponds to the one used in the experiments of the article:

__Juan Zamora, Marcelo Mendoza, Héctor Allende__, _Hashing-based clustering in high dimensional data_, In _Expert Systems with Applications_, Volume 62, 15 November 2016, Pages 202-211, ISSN 0957-4174, [http://dx.doi.org/10.1016/j.eswa.2016.06.008](http://dx.doi.org/10.1016/j.eswa.2016.06.008)

## Compiling and running our codes

* __Note:__ you need to compile each source code using g++ -std=c++0x -o foo.o foo.cpp

* A first test: Running min-wise and lsh algorithms using a small dataset. It takes sorted_rows.txt and generates a signature.txt file with the signatures achieved by each hashing strategy:
  ```
  $ ./simple_min_hashing.o
  $ ./simple_lsh.o
  ```

  Parameters can be tuned in each source code. Three parameters are defined: n (number of hashing functions), B (number of buckets), P (prime number used in the universal hashing function). The hashing function is  ,  and  are random integers, and  must be greater than  .

* Creating signatures from 20 Newsgroups with sparse_min_hashing. It takes tf-idf.cols, which comprises 2,612 news over 32,095 tf-idf weighted terms, in cols, and generates a tf-idf[n].txt file with an  - dimensional signature for each col.  is an input parameter. Default values:  and  .
  ```
   $ ./sparse_min_hashing.o 200
  ```

  it generates tf-idf[200].txt, a file with 200 rows and 2,612 cols.

* Cross_jacc produces a Jaccard pairwise similarity matrix from a signature file. The number of hashing functions is defined in the source code by the variable rows. The output matrix is flushed to a matrix_2_sig[rows].txt file. As default, rows = 200.
  ```
  $ ./cross_jacc.o
  ```

  it produces matrix_2_sig[200].txt.

* Using sparse_lsh we produce our variation of min-wise using bucket traversal. It takes tf-idf[n].txt and produces matrix-tf-idf[n]-[b-r].txt. We can use bands of rows, specifying parameters  and  , whose product is the total number of rows of the matrix  . In our paper we used  discarding the use of multibands.
  ```
  $ ./sparse_lsh.o 200 1
  ```

  it generates matrix-tf-idf[200]-[200-1].txt.

* Creating signatures from 20 Newsgroups with simple_random_hyp. It takes tf-idf.cols, and generates tf-idf-hyp[n].txt and penalty-hyp[n].txt files, which corresponds to signatures created using the original variation of random hyperplanes [Charikar 2002] and the input used by our penalized Hamming, respectively.   is a source code variable. Default values:  and  .

  ```
  $ ./simple_random_hyp.o
  ```

  it generates tf-idf-hyp[200].txt and penalty-hyp[200].txt.

* Using cross_cos we generate cosine similarity matrices from random hyperplanes signatures. It takes tf-idf-hyp[n].txt and produces matrix_2_sig_hyp[n].txt.  is a source code variable. Default  .

  ```
  $ ./cross_cos.o
  ```

  it generates matrix_2_sig_hyp[200].txt.

* Using cross_penalty we generate a similarity matrix that approximates the cosine similarity using penalized Hamming. It takes two inputs, tf-idf-hyp[n].txt (the mask of bits achieved using random hyperplanes) and penalty-hyp[n].txt (the signature). It produces matrix_2_sig_hyp_pen[n].txt.  is defined as a source code variable. Default  .

  ```
  $ ./cross_penalty.o
  ```

  it generates matrix_2_sig_hyp_pen[200].txt.


## Experimental design

* Exact solutions: matrix_1.txt (Jaccard), matrix_2.txt (cosine).
* Min-wise: matrix_2_sig[n].txt (original), matrix-tf-idf[n]-[b-r].txt (bucket-traversal).
* Random hyperplanes: matrix_2_sig_hyp[n].txt (original), matrix_2_sig_hyp_pen[n].txt (Hamming penalized)
* Cluto clustering command: 

```
$ scluster -clmethod=graph -grmodel=sd -nnbrs=30 -rclassfile=tf-idf.dat.rlabel matrix_XX.txt k
```

, where k is the number of clusters.


## Discarded in this paper

Multi-bandit LSH signatures are created using sparse_lsh. We can use bands of rows, specifying parameters  and  , whose product is the total number of rows of the matrix  . In our paper we used  discarding its use. It takes penalty-hyp[n].txt and produces matrix-n-penalty-hyp-[b-r].txt.

```
$ ./sparse_lsh.o 200 1
```

it generates matrix-200-penalty-hyp-[200-1].txt. No significant improvements were achieved using this variation.
