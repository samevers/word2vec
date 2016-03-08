SCRIPTS_DIR=./scripts
BIN_DIR=./bin

CC = gcc
#The -Ofast might not work with older versions of gcc; in that case, use -O2
CFLAGS = -lm -pthread -O2 -Wall -funroll-loops

all: word2vec word2vec-bigram word2phrase distance w2v-distance-bigram w2v-word-analogy w2v-compute-accuracy

word2vec : word2vec.c
	$(CC) word2vec.c -o ${BIN_DIR}/word2vec $(CFLAGS)
word2vec-bigram : word2vec.bigram.c
	$(CC) word2vec.bigram.c -g -rdynamic -o ${BIN_DIR}/word2vec-bigram $(CFLAGS)
word2phrase : word2phrase.c
	$(CC) word2phrase.c -o ${BIN_DIR}/word2phrase $(CFLAGS)
distance : distance.c
	$(CC) distance.c -o ${BIN_DIR}/distance $(CFLAGS)
w2v-distance-bigram : distance.bigram.c
	$(CC) distance.bigram.c -o ${BIN_DIR}/w2v-distance-bigram $(CFLAGS)
w2v-word-analogy : word-analogy.c
	$(CC) word-analogy.c -o ${BIN_DIR}/w2v-word-analogy $(CFLAGS)
w2v-compute-accuracy : compute-accuracy.c
	$(CC) compute-accuracy.c -o ${BIN_DIR}/w2v-compute-accuracy $(CFLAGS)

clean:
	pushd ${BIN_DIR} && rm -rf word2vec word2vec-bigram word2phrase distance w2v-distance-bigram word-analogy compute-accuracy; popd
