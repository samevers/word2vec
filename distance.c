//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> // mac os x


#define MAX_STRING 100

const long long max_size = 2000;         // max length of strings
const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

void combineBigram(char *word_pre, char *word, char *word_bigram)
{
	int i;
	int j = 0;
	for(i = 0; i < max_size - 1; i++)
	{
		if(i < strlen(word_pre))
		{
			word_bigram[i] = word_pre[i];
			continue;
		}
		else if(i == strlen(word_pre))
		{
			word_bigram[i] = '_';
			continue;
		}
		if(j < strlen(word))
		{
			word_bigram[i] = word[j];
			j++;
		}
		else if(j == strlen(word))
			break;
	}
	word_bigram[i] = 0;
    //printf("word_pre : %s\n", word_pre);
    //printf("word : %s\n", word);
    //printf("word_bigram : %s\n", word_bigram);
}
void PreWord(char * word, char *word_pre)
{
	int i;
	for(i = 0; i < strlen(word); i++)
		word_pre[i] = word[i];
	word_pre[i] = 0;
}

void Trans2CharArray(char* word, char* st)
{
	int i;
	for(i = 0; i < strlen(st); i++)
		word[i] = st[i];
	if(i < max_size)
		word[i] = 0;
}

int main(int argc, char **argv) {
  FILE *f;
  char st1[max_size];
  char bestw[N][max_size];
  char file_name[max_size], st[100][max_size];
  float dist, len, bestd[N], vec[max_size];
  long long words, size, a, b, c, d, cn, bi[100];
  char ch;
  float *M;
  char *vocab;
  if (argc < 2) {
    printf("usage: ./distance <file>\nwhere file contains word projections in the binary format\n");
    return 0;
  }
  strcpy(file_name, argv[1]);
  f = fopen(file_name, "rb");
  if (f == NULL) {
    printf("Input file not found\n");
    return -1;
  }
  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));		// 存储每个bigram 词
  M = (float *)malloc((long long)words * (long long)size * sizeof(float));	// 存储每个bigram词的向量
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;
  }
  for (b = 0; b < words; b++) {
    fscanf(f, "%s%c", &vocab[b * max_w], &ch);
    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    len = sqrt(len);
    for (a = 0; a < size; a++) M[a + b * size] /= len;
  }
  fclose(f);

  char word[max_size];
  char pre[max_size];
  char bigram[max_size];

  while (fgets(st1,max_size,stdin)) {	// 输入字符串
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    a = 0;
	if(strcmp(st1, "") == 0)
		break;
    if (!strcmp(st1, "")) break;
	st1[strlen(st1)-1] = '\0';
	printf("------------%s\n", st1);
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
      st[cn][b] = st1[c];
      b++;
      c++;
      st[cn][b] = 0;
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {
        cn++;
        b = 0;
        c++;
      }
    }
    cn++;
	printf("-----1\n");
    for (a = 0; a < cn; a++) {
	  if(a == 0)
	  {
	  	  Trans2CharArray(pre, st[a]);
	printf("-----2\n");
		  continue;
	  }
	  Trans2CharArray(word, st[a]);
	printf("-----3\n");
	  //word = st[a];
	  combineBigram(pre, st[a], bigram);
	printf("-----4\n");
      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], bigram)) break;
      if (b == words) b = -1;
      bi[a] = b;// 第 a 个bigram 在vocab的第b个位置
      printf("\nWord: %s  Position in vocabulary: %lld\n", bigram, bi[a]);
      if (b == -1) {
        printf("Out of dictionary word!\n");
        break;
      }
	  //pre = word;
	printf("-----5\n");
	  Trans2CharArray(pre, word);
	printf("-----6\n");
    }
	printf("-----7\n");
    //if (b == -1) continue;
    printf("\n            Word       Cosine distance\n------------------------------------------------------------------------\n");
    for (a = 0; a < size; a++) vec[a] = 0;// vocab中的所有词初始化
	printf("-----7.1\n");
    for (b = 0; b < cn; b++) {
	printf("-----7.11\n");
      if (bi[b] == -1) continue;
	printf("-----7.12\n");
      for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
	printf("-----7.13\n");
    }
	printf("-----7.2\n");
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    for (a = 0; a < size; a++) vec[a] /= len;
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
	printf("-----7.5\n");
    for (c = 0; c < words; c++) {
      a = 0;
      for (b = 0; b < cn; b++) if (bi[b] == c) {a = 1; break;}
      if (a == 1) continue;
      dist = 0;
      for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
      for (a = 0; a < N; a++) {
        if (dist > bestd[a]) {
          for (d = N - 1; d > a; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[a] = dist;
          strcpy(bestw[a], &vocab[c * max_w]);
          break;
        }
      }
    }
	printf("-----8\n");
    for (a = 0; a < N; a++) 
	{
		if(bestw[a] == "" || bestd[a] == 0)
			continue;
		printf("%s:%f\t", bestw[a], bestd[a]);
	}
	printf("-----9\n");
	printf("\n");// del
	st1[0] = '\0';

  }
  return 0;
}
