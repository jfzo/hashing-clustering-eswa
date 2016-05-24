echo "### Minwise Hashing Approximation"
cat  data_cross_jac/results.txt data_sparse_lsh/results.txt |grep 20-| cut -d " " -f 2-| python genera_tablas.py | sed 's/_out.*//g'
cat  data_cross_jac/results.txt data_sparse_lsh/results.txt |grep AP| cut -d " " -f 2-| python genera_tablas.py  | sed 's/_out.*//g'
cat  data_cross_jac/results.txt data_sparse_lsh/results.txt |grep DOE| cut -d " " -f 2-| python genera_tablas.py | sed 's/_out.*//g' 
cat  data_cross_jac/results.txt data_sparse_lsh/results.txt |grep FR| cut -d " " -f 2-| python genera_tablas.py  | sed 's/_out.*//g'
cat  data_cross_jac/results.txt data_sparse_lsh/results.txt |grep SJMN| cut -d " " -f 2-| python genera_tablas.py| sed 's/_out.*//g'
cat  data_cross_jac/results.txt data_sparse_lsh/results.txt |grep WSJ| cut -d " " -f 2-| python genera_tablas.py | sed 's/_out.*//g'
cat  data_cross_jac/results.txt data_sparse_lsh/results.txt |grep ZF| cut -d " " -f 2-| python genera_tablas.py  | sed 's/_out.*//g'

echo -ne "\n### Random hyperplanes Approximation\n"
cat  data_cross_cos/results.txt data_cross_penalty/results.txt |grep 20-ng| cut -d " " -f 2-| python genera_tablas.py | sed 's/MWb/RH\-p/g'| sed 's/MW/RH/g'|sed 's/Jaccard/Cosine/g'| sed 's/_out.*//g'
cat  data_cross_cos/results.txt data_cross_penalty/results.txt |grep AP | cut -d " " -f 2-| python genera_tablas.py   | sed 's/MWb/RH\-p/g'| sed 's/MW/RH/g'|sed 's/Jaccard/Cosine/g'| sed 's/_out.*//g'
cat  data_cross_cos/results.txt data_cross_penalty/results.txt |grep DOE | cut -d " " -f 2-| python genera_tablas.py  | sed 's/MWb/RH\-p/g'| sed 's/MW/RH/g'|sed 's/Jaccard/Cosine/g'| sed 's/_out.*//g'
cat  data_cross_cos/results.txt data_cross_penalty/results.txt |grep FR | cut -d " " -f 2-| python genera_tablas.py   | sed 's/MWb/RH\-p/g'| sed 's/MW/RH/g'|sed 's/Jaccard/Cosine/g'| sed 's/_out.*//g'
cat  data_cross_cos/results.txt data_cross_penalty/results.txt |grep WSJ | cut -d " " -f 2-| python genera_tablas.py  | sed 's/MWb/RH\-p/g'| sed 's/MW/RH/g'|sed 's/Jaccard/Cosine/g'| sed 's/_out.*//g'
cat  data_cross_cos/results.txt data_cross_penalty/results.txt |grep ZF | cut -d " " -f 2-| python genera_tablas.py   | sed 's/MWb/RH\-p/g'| sed 's/MW/RH/g'|sed 's/Jaccard/Cosine/g'| sed 's/_out.*//g'



