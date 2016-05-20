# hashing-clustering-eswa

## Compiling and running our codes

* __Note 1:__ you need to compile each source code using g++ -std=c++0x -o foo.o foo.cpp
* __Note 2:__ The values for parameters B and P could be safely set to 1073741824 and 2147483647

* Creating signatures from an input file with _sparse_min_hashing_. It takes an input file in Cluto's format, and generates a `FILE_IN_CLUTOS_FORMAT[_SIGNATURE_LEN_].txt` file with a `SIGNATURE_LEN` dimensional signature in each column.
  ```
   $ ./sparse_min_hashing SIGNATURE_LEN B P FILE_IN_CLUTOS_FORMAT
  ```

* Cross_jacc produces a Jaccard pairwise similarity matrix from a signature file. The number of hash functions is defined in the header of the signature file generated in the previous step. The output matrix is flushed to a `matrix_2_sig[SIGNATURE_LEN].txt` file. The first parameter, i.e. the signature length to use for similarity estimation, must be less or equal than the number of rows indicated in the header of the input file.
  ```
  $ ./cross_jacc SIGNATURE_LEN signature-input-file
  ```

* Using sparse_lsh we produce our variation of min-wise using bucket traversal. It takes a signature file as input and produces a `-[b-r].txt` file. We can use bands of rows, specifying parameters _b_  and _r_ , whose product is the total number of rows of the matrix. In our paper we discarded the use of multibands (r>1).
  ```
  $ ./sparse_lsh  b r signature-input-file
  ```

* Creating signatures with `simple_random_hyp`. It takes a term-document matrix in Cluto's format, generates `hyp[SIGNATURE_LEN].txt` file and a  `penalty-hyp[SIGNATURE_LEN].txt` files, which corresponds to signatures created using the original variation of random hyperplanes __[Charikar 2002]__ and the input used by our penalized Hamming, respectively.

  ```
  $ ./simple_random_hyp SIGNATURE_LEN B P FILE_IN_CLUTOS_FORMAT
  ```
  
* Using cross_cos we generate cosine similarity matrices from random hyperplanes signatures. It takes a `-hyp[n].txt` file and produces a `matrix_2_sig_hyp[n].txt` file. The value of  `n`,  i.e. the signature length, must be less or equal than the signature stored at the `-hyp[n].txt` file.

  ```
  $ ./cross_cos SIGNATURE_LEN hyp-filename-path
  ```

* Using cross_penalty we generate a similarity matrix that approximates the cosine similarity using penalized Hamming. It takes two inputs, a `-hyp[n].txt` (the mask of bits achieved using random hyperplanes) and a `penalty-hyp[n].txt` (the signature). It produces a `matrix_2_sig_hyp_pen[n].txt` file. The value of  `n`,  i.e. the signature length, must be less or equal than the signature stored at the `-hyp[n].txt` file.

  ```
  $ ./cross_penalty SIGNATURE_LEN hyp-input-filename penalty-input-filename
  ```


## Experimental design

* Exact solutions: matrix_1.txt (Jaccard), matrix_2.txt (cosine).
* Min-wise: matrix_2_sig[n].txt (original), matrix-tf-idf[n]-[b-r].txt (bucket-traversal).
* Random hyperplanes: matrix_2_sig_hyp[n].txt (original), matrix_2_sig_hyp_pen[n].txt (Hamming penalized)
* Cluto clustering: scluster -clmethod=graph -grmodel=sd -nnbrs=30 -rclassfile=tf-idf.dat.rlabel matrix*.txt k, where k is the number of clusters.


### Discarded in this paper

Multi-bandit LSH signatures are created using sparse_lsh. We can use bands of rows, specifying parameters  and  , whose product is the total number of rows of the matrix  . In our paper we used  discarding its use. It takes penalty-hyp[n].txt and produces matrix-n-penalty-hyp-[b-r].txt.

```
$ ./sparse_lsh.o 200 1
```

it generates matrix-200-penalty-hyp-[200-1].txt. No significant improvements were achieved using this variation.

## Results

### Entropy statistics

| k  | Cosine | RH-500|RH-1000 | RH-1500 | RH-2000 | RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|---:|:------:|:-----:|:------:|:-------:|:-------:|:--------:|:--------:|:--------:|:--------:|
| 5  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|10  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|15  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|20  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|25  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|30  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|35  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|40  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|45  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|50  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |


### Purity statistics

| k  | Cosine | RH-500|RH-1000 | RH-1500 | RH-2000 | RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|---:|:------:|:-----:|:------:|:-------:|:-------:|:--------:|:--------:|:--------:|:--------:|
| 5  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|10  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|15  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|20  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|25  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|30  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|35  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|40  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|45  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|50  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |


### Entropy

| k  | Jaccard| MW-2000 | MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|---:|:------:|:-------:|:--------:|:--------:|:--------:|:--------:|
| 5  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|10  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|15  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|20  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|25  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|30  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|35  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|40  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|45  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|50  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |

### Purity

| k  | Jaccard| MW-2000 | MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|---:|:------:|:-------:|:--------:|:--------:|:--------:|:--------:|
| 5  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|10  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|15  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|20  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|25  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|30  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|35  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|40  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|45  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|50  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
