#!/bin/sh

file=$1
#echo ${file} | python bin/segsam.py | python bin/wsplit.py | ./bin/w2v-distance.test vectors.vslog.bin > x
#echo ${file} | python bin/segsam.py | python bin/wsplit.py | ./bin/w2v-distance.test bak/vectors.bin > x
#cat ${file} | python bin/segsam.py | python bin/wsplit.py | ./bin/w2v-distance.test vectors.vslog.bin > x 
#echo ${file} | sh segment.sh | python bin/wsplit.py | ./bin/w2v-distance.test vectors.bin > x

cat ${file} | sh segment.sh | python bin/wsplit.py | ./distance vectors.bin > x
python bin/classify.extend.2vec.2.py x
cat ../x.extend.2vec.cla 

