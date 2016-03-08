#!/bin/bash

make
#if [ ! -e text8 ];
#then
#	wget http://mattmahoney.net/dc/text8.zip -O text8.gz
#	gzip -d text8.gz -f
#fi
#time ./bin/word2vec -train text8 -output vectors.bin -cbow 0 -size 200 -window 5 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 1
time ./bin/word2vec -train ../../video.accuquery.filter.seg.post -output vectors.bin -cbow 0 -size 200 -window 5 -negative 0 -hs 1 -sample 1e-3 -threads 12 -binary 1
./bin/w2v-compute-accuracy vectors.bin 30000 < questions-words.txt
# to compute accuracy with the full vocabulary, use: ./compute-accuracy vectors.bin < questions-words.txt
