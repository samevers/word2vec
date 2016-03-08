#!/bin/bash
time ./bin/word2phrase -train accuquery.filter.seg.post -output phrase.out -threshold 500 -debug 2
time ./bin/word2vec -train phrase.out -output vectors-phrase.bin -cbow 0 -size 300 -window 10 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 1
./bin/w2v-distance vectors-phrase.bin
