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


### Purity statistics

| k  | Cosine | RH-500|RH-1000 | RH-1500 | RH-2000 | RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|---:|:------:|:-----:|:------:|:-------:|:-------:|:--------:|:--------:|:--------:|:--------:|
| 5  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|10  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|15  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|20  |   XXX  |  XXX  |  XXX   |   XXX   |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |


### Entropy

| k  | Jaccard| MW-2000 | MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|---:|:------:|:-------:|:--------:|:--------:|:--------:|:--------:|
| 5  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|10  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|15  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|20  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |


#### Purity

| k  | Jaccard| MW-2000 | MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|---:|:------:|:-------:|:--------:|:--------:|:--------:|:--------:|
| 5  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|10  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|15  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |
|20  |   XXX  |   XXX   |   XXX    |   XXX    |   XXX    |   XXX    |


---

#### Entropy 20-ng

| k   | Jaccard| MW-500   |  MW-1000 | MW-1500  | MW-2000  |MWb-500   |MWb-1000 | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX'  |  0.5670  |  0.5670  |  0.5670  |  0.5670  |   0.4660 |  0.4660 |  0.4660  |  0.4660  |
|  20 |  'XX'  |  0.5390  |  0.5390  |  0.5390  |  0.5390  |   0.4430 |  0.4430 |  0.4430  |  0.4430  |
|   5 |  'XX'  |  0.6450  |  0.6450  |  0.6450  |  0.6450  |   0.5220 |  0.5220 |  0.5220  |  0.5220  |
|  15 |  'XX'  |  0.5480  |  0.5480  |  0.5480  |  0.5480  |   0.4550 |  0.4550 |  0.4550  |  0.4550  |

### Purity 20-ng

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.6830  |  0.6830  |  0.6830  |  0.6830  |   0.7390 |  0.7390 |  0.7390 |  0.7390 |
|  20 |  'XX' |  0.6860  |  0.6860  |  0.6860  |  0.6860  |   0.7390 |  0.7390 |  0.7390 |  0.7390 |
|   5 |  'XX' |  0.6530  |  0.6530  |  0.6530  |  0.6530  |   0.7320 |  0.7320 |  0.7320 |  0.7320 |
|  15 |  'XX' |  0.6830  |  0.6830  |  0.6830  |  0.6830  |   0.7390 |  0.7390 |  0.7390 |  0.7390 |

---

### Entropy AP

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.6290  |  0.6290  |  0.6290  |  0.6290  |   0.6150 |  0.6150 |  0.6150 |  0.6150 |
|  20 |  'XX' |  0.5080  |  0.5080  |  0.5080  |  0.5080  |   0.5040 |  0.5040 |  0.5040 |  0.5040 |
|   5 |  'XX' |  0.7350  |  0.7350  |  0.7350  |  0.7350  |   0.7060 |  0.7060 |  0.7060 |  0.7060 |
|  15 |  'XX' |  0.5460  |  0.5460  |  0.5460  |  0.5460  |   0.5490 |  0.5490 |  0.5490 |  0.5490 |

### Purity AP

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.2320  |  0.2320  |  0.2320  |  0.2320  |   0.2270 |  0.2270 |  0.2270 |  0.2270 |
|  20 |  'XX' |  0.3330  |  0.3330  |  0.3330  |  0.3330  |   0.3360 |  0.3360 |  0.3360 |  0.3360 |
|   5 |  'XX' |  0.1490  |  0.1490  |  0.1490  |  0.1490  |   0.1510 |  0.1510 |  0.1510 |  0.1510 |
|  15 |  'XX' |  0.2880  |  0.2880  |  0.2880  |  0.2880  |   0.2910 |  0.2910 |  0.2910 |  0.2910 |

---

### Entropy DOE

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.3650  |  0.3650  |  0.3650  |  0.3650  |   0.3100 |  0.3100 |  0.3100 |  0.3100 |
|  20 |  'XX' |  0.2820  |  0.2820  |  0.2820  |  0.2820  |   0.2170 |  0.2170 |  0.2170 |  0.2170 |
|   5 |  'XX' |  0.4210  |  0.4210  |  0.4210  |  0.4210  |   0.3850 |  0.3850 |  0.3850 |  0.3850 |
|  15 |  'XX' |  0.3120  |  0.3120  |  0.3120  |  0.3120  |   0.2320 |  0.2320 |  0.2320 |  0.2320 |

### Purity DOE

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.6370  |  0.6370  |  0.6370  |  0.6370  |   0.6920 |  0.6920 |  0.6920 |  0.6920 |
|  20 |  'XX' |  0.7410  |  0.7410  |  0.7410  |  0.7410  |   0.7890 |  0.7890 |  0.7890 |  0.7890 |
|   5 |  'XX' |  0.5770  |  0.5770  |  0.5770  |  0.5770  |   0.6200 |  0.6200 |  0.6200 |  0.6200 |
|  15 |  'XX' |  0.6900  |  0.6900  |  0.6900  |  0.6900  |   0.7800 |  0.7800 |  0.7800 |  0.7800 |

---

### Entropy FR

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.3880  |  0.3880  |  0.3880  |  0.3880  |   0.3150 |  0.3150 |  0.3150 |  0.3150 |
|  20 |  'XX' |  0.2620  |  0.2620  |  0.2620  |  0.2620  |   0.2240 |  0.2240 |  0.2240 |  0.2240 |
|   5 |  'XX' |  0.5660  |  0.5660  |  0.5660  |  0.5660  |   0.5300 |  0.5300 |  0.5300 |  0.5300 |
|  15 |  'XX' |  0.2880  |  0.2880  |  0.2880  |  0.2880  |   0.2610 |  0.2610 |  0.2610 |  0.2610 |

### Purity FR

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.6470  |  0.6470  |  0.6470  |  0.6470  |   0.7130 |  0.7130 |  0.7130 |  0.7130 |
|  20 |  'XX' |  0.7600  |  0.7600  |  0.7600  |  0.7600  |   0.7780 |  0.7780 |  0.7780 |  0.7780 |
|   5 |  'XX' |  0.4650  |  0.4650  |  0.4650  |  0.4650  |   0.4790 |  0.4790 |  0.4790 |  0.4790 |
|  15 |  'XX' |  0.7300  |  0.7300  |  0.7300  |  0.7300  |   0.7490 |  0.7490 |  0.7490 |  0.7490 |

---

### Entropy SJMN

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.4540  |  0.4540  |  0.4540  |  0.4540  |   0.3570 |  0.3570 |  0.3570 |  0.3570 |
|  20 |  'XX' |  0.3280  |  0.3280  |  0.3280  |  0.3280  |   0.2070 |  0.2070 |  0.2070 |  0.2070 |
|   5 |  'XX' |  0.6040  |  0.6040  |  0.6040  |  0.6040  |   0.5280 |  0.5280 |  0.5280 |  0.5280 |
|  15 |  'XX' |  0.3920  |  0.3920  |  0.3920  |  0.3920  |   0.2500 |  0.2500 |  0.2500 |  0.2500 |

### Purity SJMN

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.5630  |  0.5630  |  0.5630  |  0.5630  |   0.6350 |  0.6350 |  0.6350 |  0.6350 |
|  20 |  'XX' |  0.7010  |  0.7010  |  0.7010  |  0.7010  |   0.8210 |  0.8210 |  0.8210 |  0.8210 |
|   5 |  'XX' |  0.3980  |  0.3980  |  0.3980  |  0.3980  |   0.3970 |  0.3970 |  0.3970 |  0.3970 |
|  15 |  'XX' |  0.6190  |  0.6190  |  0.6190  |  0.6190  |   0.7720 |  0.7720 |  0.7720 |  0.7720 |

---

### Entropy WSJ

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.6380  |  0.6380  |  0.6380  |  0.6380  |   0.6230 |  0.6230 |  0.6230 |  0.6230 |
|  20 |  'XX' |  0.5760  |  0.5760  |  0.5760  |  0.5760  |   0.5340 |  0.5340 |  0.5340 |  0.5340 |
|   5 |  'XX' |  0.7030  |  0.7030  |  0.7030  |  0.7030  |   0.7030 |  0.7030 |  0.7030 |  0.7030 |
|  15 |  'XX' |  0.6080  |  0.6080  |  0.6080  |  0.6080  |   0.5710 |  0.5710 |  0.5710 |  0.5710 |

### Purity WSJ

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.1840  |  0.1840  |  0.1840  |  0.1840  |   0.1850 |  0.1850 |  0.1850 |  0.1850 |
|  20 |  'XX' |  0.2610  |  0.2610  |  0.2610  |  0.2610  |   0.2710 |  0.2710 |  0.2710 |  0.2710 |
|   5 |  'XX' |  0.1450  |  0.1450  |  0.1450  |  0.1450  |   0.1370 |  0.1370 |  0.1370 |  0.1370 |
|  15 |  'XX' |  0.2180  |  0.2180  |  0.2180  |  0.2180  |   0.2240 |  0.2240 |  0.2240 |  0.2240 |

---

### Entropy ZF

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.5670  |  0.5670  |  0.5670  |  0.5670  |   0.5720 |  0.5720 |  0.5720 |  0.5720 |
|  20 |  'XX' |  0.4850  |  0.4850  |  0.4850  |  0.4850  |   0.4510 |  0.4510 |  0.4510 |  0.4510 |
|   5 |  'XX' |  0.6790  |  0.6790  |  0.6790  |  0.6790  |   0.6900 |  0.6900 |  0.6900 |  0.6900 |
|  15 |  'XX' |  0.5250  |  0.5250  |  0.5250  |  0.5250  |   0.4890 |  0.4890 |  0.4890 |  0.4890 |

### Purity ZF

| k  | Jaccard| MW-500 |  MW-1000 | MW-1500 | MW-2000 |MWb-500  |MWb-1000  | MWb-1500 | MWb-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.4330  |  0.4330  |  0.4330  |  0.4330  |   0.4120 |  0.4120 |  0.4120 |  0.4120 |
|  20 |  'XX' |  0.5040  |  0.5040  |  0.5040  |  0.5040  |   0.5280 |  0.5280 |  0.5280 |  0.5280 |
|   5 |  'XX' |  0.2840  |  0.2840  |  0.2840  |  0.2840  |   0.2850 |  0.2850 |  0.2850 |  0.2850 |
|  15 |  'XX' |  0.4630  |  0.4630  |  0.4630  |  0.4630  |   0.4830 |  0.4830 |  0.4830 |  0.4830 |


---

## Random hyperplanes

### Entropy 20-ng

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.7170  |  0.7170  |  0.7170  |  0.7170  |   0.7170 |  0.7170 |  0.7170 |  0.7170 |
|  20 |  'XX' |  0.5280  |  0.5280  |  0.5280  |  0.5280  |   0.5280 |  0.5280 |  0.5280 |  0.5280 |
|   5 |  'XX' |  0.8380  |  0.8380  |  0.8380  |  0.8380  |   0.8380 |  0.8380 |  0.8380 |  0.8380 |
|  15 |  'XX' |  0.6370  |  0.6370  |  0.6370  |  0.6370  |   0.6370 |  0.6370 |  0.6370 |  0.6370 |

### Purity 20-ng

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.4500  |  0.4500  |  0.4500  |  0.4500  |   0.4500 |  0.4500 |  0.4500 |  0.4500 |
|  20 |  'XX' |  0.5830  |  0.5830  |  0.5830  |  0.5830  |   0.5830 |  0.5830 |  0.5830 |  0.5830 |
|   5 |  'XX' |  0.3830  |  0.3830  |  0.3830  |  0.3830  |   0.3830 |  0.3830 |  0.3830 |  0.3830 |
|  15 |  'XX' |  0.5000  |  0.5000  |  0.5000  |  0.5000  |   0.5000 |  0.5000 |  0.5000 |  0.5000 |


### Entropy AP

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.5230  |  0.5230  |  0.5230  |  0.5230  |   0.5230 |  0.5230 |  0.5230 |  0.5230 |
|  20 |  'XX' |  0.4460  |  0.4460  |  0.4460  |  0.4460  |   0.4460 |  0.4460 |  0.4460 |  0.4460 |
|   5 |  'XX' |  0.6080  |  0.6080  |  0.6080  |  0.6080  |   0.6080 |  0.6080 |  0.6080 |  0.6080 |
|  15 |  'XX' |  0.4790  |  0.4790  |  0.4790  |  0.4790  |   0.4790 |  0.4790 |  0.4790 |  0.4790 |

### Purity AP

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.1640  |  0.1640  |  0.1640  |  0.1640  |   0.1640 |  0.1640 |  0.1640 |  0.1640 |
|  20 |  'XX' |  0.2060  |  0.2060  |  0.2060  |  0.2060  |   0.2060 |  0.2060 |  0.2060 |  0.2060 |
|   5 |  'XX' |  0.1330  |  0.1330  |  0.1330  |  0.1330  |   0.1330 |  0.1330 |  0.1330 |  0.1330 |
|  15 |  'XX' |  0.1820  |  0.1820  |  0.1820  |  0.1820  |   0.1820 |  0.1820 |  0.1820 |  0.1820 |

---

### Entropy DOE

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.6380  |  0.6380  |  0.6380  |  0.6380  |   0.6380 |  0.6380 |  0.6380 |  0.6380 |
|  20 |  'XX' |  0.5530  |  0.5530  |  0.5530  |  0.5530  |   0.5530 |  0.5530 |  0.5530 |  0.5530 |
|   5 |  'XX' |  0.7260  |  0.7260  |  0.7260  |  0.7260  |   0.7260 |  0.7260 |  0.7260 |  0.7260 |
|  15 |  'XX' |  0.5950  |  0.5950  |  0.5950  |  0.5950  |   0.5950 |  0.5950 |  0.5950 |  0.5950 |

### Purity DOE

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.3630  |  0.3630  |  0.3630  |  0.3630  |   0.3630 |  0.3630 |  0.3630 |  0.3630 |
|  20 |  'XX' |  0.4030  |  0.4030  |  0.4030  |  0.4030  |   0.4030 |  0.4030 |  0.4030 |  0.4030 |
|   5 |  'XX' |  0.3310  |  0.3310  |  0.3310  |  0.3310  |   0.3310 |  0.3310 |  0.3310 |  0.3310 |
|  15 |  'XX' |  0.3630  |  0.3630  |  0.3630  |  0.3630  |   0.3630 |  0.3630 |  0.3630 |  0.3630 |

---

### Entropy FR

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.7470  |  0.7470  |  0.7470  |  0.7470  |   0.7470 |  0.7470 |  0.7470 |  0.7470 |
|  20 |  'XX' |  0.6020  |  0.6020  |  0.6020  |  0.6020  |   0.6020 |  0.6020 |  0.6020 |  0.6020 |
|   5 |  'XX' |  0.8270  |  0.8270  |  0.8270  |  0.8270  |   0.8270 |  0.8270 |  0.8270 |  0.8270 |
|  15 |  'XX' |  0.6680  |  0.6680  |  0.6680  |  0.6680  |   0.6680 |  0.6680 |  0.6680 |  0.6680 |

### Purity FR

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.2470  |  0.2470  |  0.2470  |  0.2470  |   0.2470 |  0.2470 |  0.2470 |  0.2470 |
|  20 |  'XX' |  0.3220  |  0.3220  |  0.3220  |  0.3220  |   0.3220 |  0.3220 |  0.3220 |  0.3220 |
|   5 |  'XX' |  0.2120  |  0.2120  |  0.2120  |  0.2120  |   0.2120 |  0.2120 |  0.2120 |  0.2120 |
|  15 |  'XX' |  0.2740  |  0.2740  |  0.2740  |  0.2740  |   0.2740 |  0.2740 |  0.2740 |  0.2740 |

---

### Entropy SJMN

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.7310  |  0.7310  |  0.7310  |  0.7310  |   0.7310 |  0.7310 |  0.7310 |  0.7310 |
|  20 |  'XX' |  0.6220  |  0.6220  |  0.6220  |  0.6220  |   0.6220 |  0.6220 |  0.6220 |  0.6220 |
|   5 |  'XX' |  0.8150  |  0.8150  |  0.8150  |  0.8150  |   0.8150 |  0.8150 |  0.8150 |  0.8150 |
|  15 |  'XX' |  0.6690  |  0.6690  |  0.6690  |  0.6690  |   0.6690 |  0.6690 |  0.6690 |  0.6690 |

### Purity SJMN

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.2500  |  0.2500  |  0.2500  |  0.2500  |   0.2500 |  0.2500 |  0.2500 |  0.2500 |
|  20 |  'XX' |  0.3040  |  0.3040  |  0.3040  |  0.3040  |   0.3040 |  0.3040 |  0.3040 |  0.3040 |
|   5 |  'XX' |  0.2230  |  0.2230  |  0.2230  |  0.2230  |   0.2230 |  0.2230 |  0.2230 |  0.2230 |
|  15 |  'XX' |  0.2770  |  0.2770  |  0.2770  |  0.2770  |   0.2770 |  0.2770 |  0.2770 |  0.2770 |

---

### Entropy WSJ

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.5020  |  0.5020  |  0.5020  |  0.5020  |   0.5020 |  0.5020 |  0.5020 |  0.5020 |
|  20 |  'XX' |  0.4270  |  0.4270  |  0.4270  |  0.4270  |   0.4270 |  0.4270 |  0.4270 |  0.4270 |
|   5 |  'XX' |  0.5650  |  0.5650  |  0.5650  |  0.5650  |   0.5650 |  0.5650 |  0.5650 |  0.5650 |
|  15 |  'XX' |  0.4630  |  0.4630  |  0.4630  |  0.4630  |   0.4630 |  0.4630 |  0.4630 |  0.4630 |

### Purity WSJ

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.1210  |  0.1210  |  0.1210  |  0.1210  |   0.1210 |  0.1210 |  0.1210 |  0.1210 |
|  20 |  'XX' |  0.1520  |  0.1520  |  0.1520  |  0.1520  |   0.1520 |  0.1520 |  0.1520 |  0.1520 |
|   5 |  'XX' |  0.0940  |  0.0940  |  0.0940  |  0.0940  |   0.0940 |  0.0940 |  0.0940 |  0.0940 |
|  15 |  'XX' |  0.1390  |  0.1390  |  0.1390  |  0.1390  |   0.1390 |  0.1390 |  0.1390 |  0.1390 |

--- 

### Entropy ZF

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.6640  |  0.6640  |  0.6640  |  0.6640  |   0.6640 |  0.6640 |  0.6640 |  0.6640 |
|  20 |  'XX' |  0.5820  |  0.5820  |  0.5820  |  0.5820  |   0.5820 |  0.5820 |  0.5820 |  0.5820 |
|   5 |  'XX' |  0.7130  |  0.7130  |  0.7130  |  0.7130  |   0.7130 |  0.7130 |  0.7130 |  0.7130 |
|  15 |  'XX' |  0.6220  |  0.6220  |  0.6220  |  0.6220  |   0.6220 |  0.6220 |  0.6220 |  0.6220 |

### Purity ZF

| k  | Cosine| RH-500 |  RH-1000 | RH-1500 | RH-2000 |RHp-500  |RHp-1000  | RHp-1500 | RHp-2000 |
|----:|:------:|:--------:|:--------:|:--------:|:--------:|:--------:|:-------:|:--------:|:--------:|
|  10 |  'XX' |  0.2370  |  0.2370  |  0.2370  |  0.2370  |   0.2370 |  0.2370 |  0.2370 |  0.2370 |
|  20 |  'XX' |  0.2630  |  0.2630  |  0.2630  |  0.2630  |   0.2630 |  0.2630 |  0.2630 |  0.2630 |
|   5 |  'XX' |  0.2150  |  0.2150  |  0.2150  |  0.2150  |   0.2150 |  0.2150 |  0.2150 |  0.2150 |
|  15 |  'XX' |  0.2460  |  0.2460  |  0.2460  |  0.2460  |   0.2460 |  0.2460 |  0.2460 |  0.2460 |
