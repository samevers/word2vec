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


const long long max_size = 2000;         // max length of strings
//const long long N = 40;                  // number of closest words that will be shown
//const long long N = 5;                  // number of closest words that will be shown
const long long N = 20;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries

// sam
int split_(char* str, char* out[], int n)
{
	int loc = -1;
	int i = 0;
	int j = 0;
	for(;i < strlen(str); i++)
	{
		if(str[i] > ' ' || str[i] < ' ')
		{
			j++;
		}else
		{
			//string tmp = 
			// strcat(out[j],str[i]);
		}
	}
	return j;
}
// sam
void print_(char* out[], int n)
{
	int i = 0;
	for(; i < n; i++)
	{
		printf("%s\n",out[i]);
	}
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
  /*if (argc < 2) {
    printf("Usage: ./distance <FILE>\nwhere FILE contains word projections in the BINARY FORMAT\n");
    return 0;
  }
  strcpy(file_name, argv[1]);
  f = fopen(file_name, "rb");
*/
  f = fopen("vectors.bin", "rb");
  if (f == NULL) {
    printf("Input file not found\n");
    return -1;
  }
  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);
  //printf("words : %lld\n",words);
  //printf("size : %lld\n", size);
	printf("===1\n");
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));
  M = (float *)malloc((long long)words * (long long)size * sizeof(float));
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;
  }
	printf("===2\n");
  for (b = 0; b < words; b++) {
    fscanf(f, "%s%c", &vocab[b * max_w], &ch);
	printf("%c\n", ch);
    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    len = sqrt(len);
    for (a = 0; a < size; a++) M[a + b * size] /= len;
  }
  fclose(f);
	printf("===3\n");
  int num = 10;
// sam
	int flag = 0;
int i = 0;
  while (fgets(st1,max_size,stdin)) {	// ÊäÈë×Ö·û´®
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    a = 0;
	if(strcmp(st1, "") == 0)
		break;
    if (!strcmp(st1, "")) break;
st1[strlen(st1)-1] = '\0';
	if(strcmp(st1,"===") == 0)
	{
		printf("===\n");
		continue;
	}
	printf("===4\n");
  printf("%s\t",st1);
	printf("===5\n");
	char* out[100];
	int num;
	char* str;
	strcpy(str,st1);
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
	printf("===6\n");
    for (a = 0; a < cn; a++) {
      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
      if (b == words) b = -1;
      bi[a] = b;
      //printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
      if (b == -1) {
        //printf("Out of dictionary word!\n");
        break;
      }
    }
	printf("===7\n");
   //if (b == -1) continue;
    for (a = 0; a < size; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
      if (bi[b] == -1) continue;
      for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
    }
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    for (a = 0; a < size; a++) vec[a] /= len;
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
   int nn = 0;
	printf("===8\n");
     for (c = 0; c < words; c++) {
// output
//if(bestd[0] > 0 && bestd[N-1] > 0)
//	break;

	nn++;
      a = 0;
      for (b = 0; b < cn; b++) {
	if (bi[b] == c)
	{
		 a = 1;
		break;
	}
	
      }
	printf("===9\n");
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
	printf("===10\n");
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
