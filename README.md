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

# Results

## Minwise Hashing Approximation

### Entropy  20-ng

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.378 |  0.645  |  0.606  |  0.631  |  0.611  |   0.579 |  0.522 |  0.509 |  0.516 |
|  10 |  0.329 |  0.567  |  0.559  |  0.556  |  0.539  |   0.526 |  0.466 |  0.460 |  0.454 |
|  15 |  0.323 |  0.548  |  0.541  |  0.540  |  0.526  |   0.504 |  0.455 |  0.449 |  0.439 |
|  20 |  0.313 |  0.539  |  0.533  |  0.532  |  0.517  |   0.490 |  0.443 |  0.433 |  0.432 |


### Purity  20-ng

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.826 |  0.653  |  0.666  |  0.613  |  0.623  |   0.695 |  0.732 |  0.738 |  0.731 |
|  10 |  0.858 |  0.683  |  0.691  |  0.678  |  0.691  |   0.719 |  0.739 |  0.743 |  0.743 |
|  15 |  0.858 |  0.683  |  0.691  |  0.685  |  0.697  |   0.727 |  0.739 |  0.743 |  0.743 |
|  20 |  0.863 |  0.686  |  0.691  |  0.696  |  0.711  |   0.727 |  0.739 |  0.743 |  0.746 |


### Entropy  AP

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.769 |  0.735  |  0.705  |  0.688  |  0.713  |   0.730 |  0.706 |  0.703 |  0.696 |
|  10 |  0.674 |  0.629  |  0.612  |  0.593  |  0.601  |   0.640 |  0.615 |  0.606 |  0.602 |
|  15 |  0.621 |  0.546  |  0.543  |  0.543  |  0.548  |   0.579 |  0.549 |  0.551 |  0.536 |
|  20 |  0.590 |  0.508  |  0.490  |  0.489  |  0.491  |   0.547 |  0.504 |  0.506 |  0.494 |


### Purity  AP

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.118 |  0.149  |  0.138  |  0.141  |  0.147  |   0.147 |  0.151 |  0.151 |  0.158 |
|  10 |  0.177 |  0.232  |  0.233  |  0.232  |  0.234  |   0.221 |  0.227 |  0.230 |  0.235 |
|  15 |  0.223 |  0.288  |  0.291  |  0.284  |  0.279  |   0.278 |  0.291 |  0.281 |  0.285 |
|  20 |  0.258 |  0.333  |  0.348  |  0.338  |  0.338  |   0.299 |  0.336 |  0.331 |  0.319 |


### Entropy  DOE

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.464 |  0.421  |  0.378  |  0.371  |  0.373  |   0.401 |  0.385 |  0.382 |  0.410 |
|  10 |  0.323 |  0.365  |  0.288  |  0.285  |  0.257  |   0.323 |  0.310 |  0.298 |  0.291 |
|  15 |  0.277 |  0.312  |  0.243  |  0.248  |  0.233  |   0.287 |  0.232 |  0.248 |  0.235 |
|  20 |  0.249 |  0.282  |  0.213  |  0.231  |  0.220  |   0.266 |  0.217 |  0.227 |  0.220 |


### Purity  DOE

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.535 |  0.577  |  0.618  |  0.618  |  0.618  |   0.615 |  0.620 |  0.617 |  0.581 |
|  10 |  0.683 |  0.637  |  0.718  |  0.712  |  0.756  |   0.673 |  0.692 |  0.712 |  0.692 |
|  15 |  0.738 |  0.690  |  0.768  |  0.772  |  0.769  |   0.730 |  0.780 |  0.751 |  0.756 |
|  20 |  0.775 |  0.741  |  0.803  |  0.780  |  0.789  |   0.755 |  0.789 |  0.774 |  0.784 |


### Entropy  FR

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.636 |  0.566  |  0.556  |  0.507  |  0.493  |   0.586 |  0.530 |  0.670 |  0.661 |
|  10 |  0.362 |  0.388  |  0.409  |  0.386  |  0.386  |   0.354 |  0.315 |  0.390 |  0.398 |
|  15 |  0.254 |  0.288  |  0.276  |  0.320  |  0.310  |   0.280 |  0.261 |  0.324 |  0.305 |
|  20 |  0.239 |  0.262  |  0.265  |  0.268  |  0.254  |   0.257 |  0.224 |  0.263 |  0.277 |


### Purity  FR

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.357 |  0.465  |  0.505  |  0.526  |  0.529  |   0.454 |  0.479 |  0.373 |  0.373 |
|  10 |  0.653 |  0.647  |  0.620  |  0.651  |  0.641  |   0.683 |  0.713 |  0.629 |  0.645 |
|  15 |  0.781 |  0.730  |  0.747  |  0.688  |  0.712  |   0.745 |  0.749 |  0.710 |  0.722 |
|  20 |  0.802 |  0.760  |  0.747  |  0.745  |  0.760  |   0.757 |  0.778 |  0.765 |  0.731 |


### Entropy  SJMN

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.560 |  0.604  |  0.579  |  0.543  |  0.530  |   0.569 |  0.528 |  0.512 |  0.525 |
|  10 |  0.373 |  0.454  |  0.393  |  0.384  |  0.370  |   0.392 |  0.357 |  0.321 |  0.342 |
|  15 |  0.287 |  0.392  |  0.308  |  0.281  |  0.280  |   0.326 |  0.250 |  0.253 |  0.267 |
|  20 |  0.221 |  0.328  |  0.235  |  0.229  |  0.215  |   0.274 |  0.207 |  0.208 |  0.211 |


### Purity  SJMN

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.416 |  0.398  |  0.394  |  0.436  |  0.438  |   0.433 |  0.397 |  0.431 |  0.427 |
|  10 |  0.590 |  0.563  |  0.608  |  0.571  |  0.606  |   0.623 |  0.635 |  0.669 |  0.655 |
|  15 |  0.727 |  0.619  |  0.704  |  0.725  |  0.729  |   0.701 |  0.772 |  0.762 |  0.759 |
|  20 |  0.819 |  0.701  |  0.800  |  0.803  |  0.826  |   0.766 |  0.821 |  0.806 |  0.825 |


### Entropy  WSJ

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.714 |  0.703  |  0.697  |  0.693  |  0.693  |   0.730 |  0.703 |  0.698 |  0.695 |
|  10 |  0.637 |  0.638  |  0.636  |  0.644  |  0.619  |   0.652 |  0.623 |  0.615 |  0.612 |
|  15 |  0.596 |  0.608  |  0.589  |  0.579  |  0.583  |   0.614 |  0.571 |  0.573 |  0.573 |
|  20 |  0.567 |  0.576  |  0.545  |  0.542  |  0.547  |   0.584 |  0.534 |  0.537 |  0.540 |


### Purity  WSJ

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.117 |  0.145  |  0.148  |  0.147  |  0.144  |   0.132 |  0.137 |  0.135 |  0.125 |
|  10 |  0.170 |  0.184  |  0.208  |  0.186  |  0.202  |   0.176 |  0.185 |  0.187 |  0.184 |
|  15 |  0.224 |  0.218  |  0.258  |  0.247  |  0.234  |   0.227 |  0.224 |  0.221 |  0.218 |
|  20 |  0.252 |  0.261  |  0.297  |  0.283  |  0.270  |   0.246 |  0.271 |  0.264 |  0.247 |


### Entropy  ZF

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.665 |  0.679  |  0.672  |  0.647  |  0.662  |   0.701 |  0.690 |  0.700 |  0.691 |
|  10 |  0.544 |  0.567  |  0.585  |  0.535  |  0.566  |   0.610 |  0.572 |  0.573 |  0.582 |
|  15 |  0.483 |  0.525  |  0.508  |  0.477  |  0.496  |   0.561 |  0.489 |  0.508 |  0.506 |
|  20 |  0.441 |  0.485  |  0.473  |  0.459  |  0.445  |   0.526 |  0.451 |  0.459 |  0.453 |


### Purity  ZF

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.335 |  0.284  |  0.328  |  0.300  |  0.307  |   0.291 |  0.285 |  0.272 |  0.292 |
|  10 |  0.465 |  0.433  |  0.407  |  0.457  |  0.396  |   0.373 |  0.412 |  0.399 |  0.389 |
|  15 |  0.536 |  0.463  |  0.479  |  0.510  |  0.462  |   0.433 |  0.483 |  0.473 |  0.470 |
|  20 |  0.560 |  0.504  |  0.518  |  0.522  |  0.547  |   0.469 |  0.528 |  0.534 |  0.529 |


### Random hyperplanes Approximation for the Cosine similarity

#### Entropy  20-ng

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:------:|:------:|:------:|
|   5 |  0.475 |  0.830  |  0.830  |  0.830  |  0.830  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |
|  10 |  0.354 |  0.651  |  0.651  |  0.651  |  0.651  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |
|  15 |  0.341 |  0.470  |  0.470  |  0.470  |  0.470  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |
|  20 |  0.335 |  0.317  |  0.317  |  0.317  |  0.317  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |

#### Purity  20-ng

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:-------:|:-------:|:-------:|:-------:|:-------:|:------:|:------:|:--------:|
|   5 |  0.715 |  0.394  |  0.394  |  0.394  |  0.394  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |
|  10 |  0.832 |  0.455  |  0.455  |  0.455  |  0.455  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |
|  15 |  0.832 |  0.606  |  0.606  |  0.606  |  0.606  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |
|  20 |  0.832 |  0.697  |  0.697  |  0.697  |  0.697  |   0.xxx |  0.xxx |  0.xxx |  0.xxx |


#### Entropy  AP

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.767 |  0.608  |  0.652  |  0.608  |  0.608  |   0.635 |  0.706 |  0.705 |  0.701 |
|  10 |  0.684 |  0.523  |  0.591  |  0.523  |  0.523  |   0.587 |  0.648 |  0.638 |  0.636 |
|  15 |  0.624 |  0.479  |  0.539  |  0.479  |  0.479  |   0.550 |  0.606 |  0.594 |  0.595 |
|  20 |  0.584 |  0.446  |  0.505  |  0.446  |  0.446  |   0.512 |  0.576 |  0.558 |  0.556 |


#### Purity  AP

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.106 |  0.133  |  0.100  |  0.133  |  0.133  |   0.114 |  0.092 |  0.092 |  0.087 |
|  10 |  0.173 |  0.164  |  0.114  |  0.164  |  0.164  |   0.120 |  0.098 |  0.109 |  0.106 |
|  15 |  0.219 |  0.182  |  0.129  |  0.182  |  0.182  |   0.135 |  0.111 |  0.118 |  0.115 |
|  20 |  0.259 |  0.206  |  0.143  |  0.206  |  0.206  |   0.144 |  0.117 |  0.133 |  0.127 |


#### Entropy  DOE

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.461 |  0.726  |  0.748  |  0.726  |  0.726  |   0.749 |  0.755 |  0.749 |  0.749 |
|  10 |  0.330 |  0.638  |  0.670  |  0.638  |  0.638  |   0.679 |  0.679 |  0.679 |  0.679 |
|  15 |  0.275 |  0.595  |  0.608  |  0.595  |  0.595  |   0.622 |  0.627 |  0.622 |  0.622 |
|  20 |  0.254 |  0.553  |  0.546  |  0.553  |  0.553  |   0.586 |  0.573 |  0.586 |  0.586 |


#### Purity  DOE

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.553 |  0.331  |  0.319  |  0.331  |  0.331  |   0.313 |  0.320 |  0.313 |  0.313 |
|  10 |  0.681 |  0.363  |  0.340  |  0.363  |  0.363  |   0.327 |  0.340 |  0.327 |  0.327 |
|  15 |  0.754 |  0.363  |  0.369  |  0.363  |  0.363  |   0.340 |  0.354 |  0.340 |  0.340 |
|  20 |  0.775 |  0.403  |  0.390  |  0.403  |  0.403  |   0.347 |  0.374 |  0.347 |  0.347 |


#### Entropy  FR

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.624 |  0.827  |  0.795  |  0.827  |  0.827  |   0.841 |  0.848 |  0.841 |  0.850 |
|  10 |  0.373 |  0.747  |  0.731  |  0.747  |  0.747  |   0.767 |  0.764 |  0.767 |  0.786 |
|  15 |  0.263 |  0.668  |  0.679  |  0.668  |  0.668  |   0.703 |  0.710 |  0.703 |  0.729 |
|  20 |  0.216 |  0.602  |  0.616  |  0.602  |  0.602  |   0.666 |  0.658 |  0.666 |  0.668 |


#### Purity  FR

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.356 |  0.212  |  0.206  |  0.212  |  0.212  |   0.194 |  0.206 |  0.194 |  0.193 |
|  10 |  0.646 |  0.247  |  0.238  |  0.247  |  0.247  |   0.230 |  0.243 |  0.230 |  0.224 |
|  15 |  0.766 |  0.274  |  0.262  |  0.274  |  0.274  |   0.262 |  0.265 |  0.262 |  0.245 |
|  20 |  0.814 |  0.322  |  0.294  |  0.322  |  0.322  |   0.288 |  0.286 |  0.288 |  0.260 |


#### Entropy  SJMN

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.535 |  0.815  |  0.796  |  0.815  |  0.815  |   0.830 |  0.813 |  0.822 |  0.822 |
|  10 |  0.343 |  0.731  |  0.730  |  0.731  |  0.731  |   0.760 |  0.732 |  0.748 |  0.748 |
|  15 |  0.273 |  0.669  |  0.644  |  0.669  |  0.669  |   0.703 |  0.666 |  0.686 |  0.686 |
|  20 |  0.213 |  0.622  |  0.598  |  0.622  |  0.622  |   0.647 |  0.606 |  0.647 |  0.647 |


#### Purity  SJMN

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.430 |  0.223  |  0.242  |  0.223  |  0.223  |   0.211 |  0.217 |  0.199 |  0.199 |
|  10 |  0.606 |  0.250  |  0.255  |  0.250  |  0.250  |   0.217 |  0.247 |  0.235 |  0.235 |
|  15 |  0.733 |  0.277  |  0.295  |  0.277  |  0.277  |   0.241 |  0.283 |  0.259 |  0.259 |
|  20 |  0.824 |  0.304  |  0.322  |  0.304  |  0.304  |   0.271 |  0.313 |  0.289 |  0.289 |


#### Entropy  WSJ

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.711 |  0.565  |  0.596  |  0.565  |  0.565  |   0.654 |  0.644 |  0.671 |  0.589 |
|  10 |  0.638 |  0.502  |  0.547  |  0.502  |  0.502  |   0.603 |  0.588 |  0.612 |  0.539 |
|  15 |  0.589 |  0.463  |  0.492  |  0.463  |  0.463  |   0.562 |  0.551 |  0.575 |  0.508 |
|  20 |  0.562 |  0.427  |  0.465  |  0.427  |  0.427  |   0.537 |  0.522 |  0.547 |  0.473 |


#### Purity  WSJ

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.116 |  0.094  |  0.083  |  0.094  |  0.094  |   0.095 |  0.091 |  0.091 |  0.104 |
|  10 |  0.158 |  0.121  |  0.101  |  0.121  |  0.121  |   0.103 |  0.101 |  0.099 |  0.124 |
|  15 |  0.223 |  0.139  |  0.119  |  0.139  |  0.139  |   0.115 |  0.108 |  0.108 |  0.131 |
|  20 |  0.254 |  0.152  |  0.130  |  0.152  |  0.152  |   0.121 |  0.120 |  0.116 |  0.147 |


#### Entropy  ZF

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.668 |  0.713  |  0.727  |  0.713  |  0.713  |   0.839 |  0.818 |  0.838 |  0.836 |
|  10 |  0.549 |  0.664  |  0.661  |  0.664  |  0.664  |   0.798 |  0.779 |  0.798 |  0.796 |
|  15 |  0.485 |  0.622  |  0.612  |  0.622  |  0.622  |   0.765 |  0.744 |  0.758 |  0.755 |
|  20 |  0.447 |  0.582  |  0.580  |  0.582  |  0.582  |   0.731 |  0.700 |  0.731 |  0.720 |


#### Purity  ZF

|  k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RH-p-500  |RH-p-1000  | RH-p-1500 | RH-p-2000 |
|----:|:-----:|:--------:|:-------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|   5 |  0.332 |  0.215  |  0.207  |  0.215  |  0.215  |   0.169 |  0.170 |  0.164 |  0.165 |
|  10 |  0.471 |  0.237  |  0.232  |  0.237  |  0.237  |   0.181 |  0.177 |  0.173 |  0.177 |
|  15 |  0.520 |  0.246  |  0.263  |  0.246  |  0.246  |   0.192 |  0.185 |  0.187 |  0.196 |
|  20 |  0.566 |  0.263  |  0.273  |  0.263  |  0.263  |   0.207 |  0.200 |  0.197 |  0.210 |

