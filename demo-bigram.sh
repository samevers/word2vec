#! /bin/bash

## ----------------------
## By Yonghuahu.
## ----------------------

#time ./bin/word2vec-bigram -train data_/train_cor/train.all -output vectors.bin.text -cbow 0 -size 200 -window 3 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 0
time ./bin/word2vec-bigram -train data_/train_cor/train.all -output vectors.bin.text -cbow 0 -size 200 -window 3 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 0
#time ./bin/word2vec-bigram -train xx -output vectors.bin.text -cbow 0 -size 200 -window 3 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 0
#./bin/w2v-distance vectors.bin
