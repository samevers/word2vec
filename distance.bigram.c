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
// Yonghua HU.

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
    fscanf(f, "%s%c", &vocab[b * max_w], &ch);								// 从文件 f 中读取一个bigram词，即一行中的《词》数据
    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f); // 从文件f 中读取一个size 大小的向量，放在M 的a+b*size 的位置；
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];	// 取所有向量元素的平方，进行加和
    len = sqrt(len);														// 再取平方根, 进而
    for (a = 0; a < size; a++) M[a + b * size] /= len;					// 对 M 进行归一化
  }
  fclose(f);

  char word[max_size];
  char pre[max_size];
  char bigram[max_size];

  // 对于输入的一串string 内容
  while (fgets(st1,max_size,stdin)) {	// 输入字符串
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    a = 0;
	if(strcmp(st1, "") == 0)
		break;
	st1[strlen(st1)-1] = '\0';
	printf("------------%s\n", st1);	// st1 是输入的一行string 串
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
      st[cn][b] = st1[c];	// 将st1 存放到二维char 数组 st 中
      b++;
      c++;
      st[cn][b] = 0;
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {	// 以空格为标记将st1 切分成term
        cn++;				// cn 为st1 中term 的数量
        b = 0;
        c++;
      }
    }
    cn++;
    for (a = 0; a < cn; a++) {
	  if(a == 0)
	  {
	  	  Trans2CharArray(pre, st[a]); // 前一个词term
		  continue;
	  }
	  Trans2CharArray(word, st[a]);		// 当前一个词term
	  combineBigram(pre, st[a], bigram);// 构成 bigram term
      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], bigram)) break; // 再vocab 词典中查找bigram，若存在该bigram，则跳出；
      if (b == words) b = -1;			// vocab 词典中找不到该bigram
      bi[a-1] = b;						// 第 a 个bigram 在vocab的第b个位置; 另外，这里之所以要a-1，是因为bigram 只有a-1 个
      printf("\nWord: %s  Position in vocabulary: %lld\n", bigram, bi[a]);
      if (b == -1) {
        printf("Out of dictionary word!\n");
        //break; 	// b=-1 的时候不能跳出，后面在访问bi 的时候会报 '段错误'
      }
	  Trans2CharArray(pre, word);
    }
    //if (b == -1) continue;
    for (a = 0; a < size; a++) vec[a] = 0;// vocab中的所有词初始化
	for (b = 0; b < cn -1; b++) {		// 因为上面已经知道bi中只有cn-1 个bigram，所以这里也同样需要将bi 的上限设置在cn-1；否则会报'段错误'
        if (bi[b] == -1) continue;
        for (a = 0; a < size; a++) {
			vec[a] += M[a + bi[b] * size];
		}
    }
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    for (a = 0; a < size; a++) vec[a] /= len;
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
      a = 0;
      for (b = 0; b < cn -1; b++) if (bi[b] == c) {a = 1; break;}	// 同样的，bi的b元素需要按照上面的数组大小进行限制；
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
    for (a = 0; a < N; a++) 
	{
		if(bestw[a] == "" || bestd[a] == 0)
			continue;
		printf("%s:%f\t", bestw[a], bestd[a]);
	}
	printf("\n");// del
	st1[0] = '\0';

  }
  return 0;
}
