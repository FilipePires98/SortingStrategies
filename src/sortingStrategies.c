//
// AED, November 2017
//
// João Alegria 85048
// Filipe Pires 85122
//
// Sorting Algorithms
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int T;
typedef int (*sort_function)(int *,int,int);

void show(T *data,int first,int one_after_last) {
  int i;

  printf("[%2d,%2d]",first,one_after_last - 1);
  for(i = first;i < one_after_last;i++) {printf(" %5d",data[i]);}
  printf("\n");
}

int bubble_sort(T *data,int first,int one_after_last) {
  int i,i_low,i_high,i_last;
  int count = 0;

  i_low = first;
  i_high = one_after_last - 1;
  while(i_low < i_high) {
    for(i = i_last = i_low;i < i_high;i++) {
      if(data[i] > data[i + 1]) {
        T tmp = data[i];
        data[i] = data[i + 1];
        data[i + 1] = tmp;
        i_last = i;
      }
      count++;
    }
    i_high = i_last;
  }

  return count;
}

int shaker_sort(T *data,int first,int one_after_last) {
  int i,i_low,i_high,i_last;
  int count = 0;

  i_low = first;
  i_high = one_after_last - 1;
  while(i_low < i_high) {
    // up pass
    for(i = i_last = i_low;i < i_high;i++) {
      if(data[i] > data[i + 1]) {
        T tmp = data[i];
        data[i] = data[i + 1];
        data[i + 1] = tmp;
        i_last = i;
      }
      count++;
    }
    i_high = i_last;
    // down pass
    for(i = i_last = i_high;i > i_low;i--) {
      if(data[i] < data[i - 1]) {
        T tmp = data[i];
        data[i] = data[i - 1];
        data[i - 1] = tmp;
        i_last = i;
      }
      count++;
    }
    i_low = i_last;
  }

  return count;
}

int insertion_sort(T *data,int first,int one_after_last) {
  int i,j;
  int count = 0;

  for(i = first + 1;i < one_after_last;i++) {
    T tmp = data[i];
    for(j = i;j > first;j--) {
      count++;
      if(tmp >= data[j - 1]) { break; }
      data[j] = data[j - 1];
    }
    data[j] = tmp;
  }

  return count;
}

int shell_sort(T *data,int first,int one_after_last) {
  int i,j,h;
  int count = 0;

  for(h = 1;h < (one_after_last - first) / 3;h = 3 * h + 1)
    ;
  while(h >= 1) { // for each stride h, use insertion sort
    for(i = first + h;i < one_after_last;i++) {
      T tmp = data[i];
      for(j = i;j - h >= first;j -= h) {
      	count++;
      	if (tmp >= data[j - h]) { break; }
        data[j] = data[j - h];
      }
      data[j] = tmp;
    }
    h /= 3;
  }

  return count;
}

int quick_sort(T *data,int first,int one_after_last) {
  int left, right, i, j;
  left = first; right = one_after_last - 1; i = left; j = right;
  int count = 0;

  T pivot = data[(left + right) / 2];
  while (i <= j) {
    while (data[i] < pivot) { i++; count++; }
    while (data[j] > pivot) { j--; count++; }
    if (i <= j) {
      T tmp = data[i];
      data[i] = data[j];
      data[j] = tmp;
      i++; j--;
    }
    count++;
  }
  if (left < j) { count += quick_sort(data, left, j + 1); }
  if (i < right) { count += quick_sort(data, i, right + 1); }

  return count;
}

int merge_sort(T *data,int first,int one_after_last) {
  int i,j,k,middle;
  T *buffer;
  int count = 0;

  if(one_after_last - first < 40) {// do not allocate less than 40 bytes
    count += insertion_sort(data,first,one_after_last);
  } else {
    middle = (first + one_after_last) / 2;

    count += merge_sort(data,first,middle);
    count += merge_sort(data,middle,one_after_last);

    buffer = (T *)malloc((size_t)(one_after_last - first) * sizeof(T)) - first; // no error check!
    i = first;  // first input (first half)
    j = middle; // second input (second half)
    k = first;  // merged output

    while(k < one_after_last) {
      if(j == one_after_last || (i < middle && data[i] <= data[j])) {
        buffer[k++] = data[i++];
      } else {
        buffer[k++] = data[j++];
      }
      count++;
    }
    for(i = first;i < one_after_last;i++) {
      data[i] = buffer[i];
    }

    free(buffer + first);
  }

  return count;
}

int heap_sort(T *data,int first,int one_after_last) {
  int i,j,k,n;
  T tmp;
  int count = 0;

  data += first - 1;          // adjust pointer (data[first] becomes data[1])
  n = one_after_last - first; // number of items to sort

  // phase 1. heap construction 
  for(i = n / 2;i >= 1;i--) {
    for(j = i;2 * j <= n;j = k){
      k = (2 * j + 1 <= n && data[2 * j + 1] > data[2 * j]) ? 2 * j + 1 : 2 * j;
      count = count + 2;
      if(data[j] >= data[k]) { break; }
      tmp = data[j];
      data[j] = data[k];
      data[k] = tmp;
    }
  }

  // phase 2. sort
  while(n > 1) {
    tmp = data[1]; // largest
    data[1] = data[n];
    data[n--] = tmp;
    for(j = 1;2 * j <= n;j = k) {
      k = (2 * j + 1 <= n && data[2 * j + 1] > data[2 * j]) ? 2 * j + 1 : 2 * j;
      count = count + 2;
      if(data[j] >= data[k]) {break;}
      tmp = data[j];
      data[j] = data[k];
      data[k] = tmp;
    }
  }

  return count;
}

int rank_sort(T *data,int first,int one_after_last){
  int i,j,*rank;
  T *buffer;
  int count = 0;

  rank = (int *)malloc((size_t)(one_after_last - first) * sizeof(int)) - first; // no error check!
  for(i = first;i < one_after_last;i++) {rank[i] = first;}
  for(i = first + 1;i < one_after_last;i++) {
    for(j = first;j < i;j++) {
      rank[(data[i] < data[j]) ? j : i]++;
      count++;
    }
  }
  buffer = (T *)malloc((size_t)(one_after_last - first) * sizeof(T)) - first; // no error check!
  for(i = first;i < one_after_last;i++) {buffer[i] = data[i];}
  for(i = first;i < one_after_last;i++) {data[rank[i]] = buffer[i];}

  free(buffer + first);
  free(rank + first);

  return count;
}

int selection_sort(T *data,int first,int one_after_last){
  int i,j,k;
  int count = 0;

  for(i = one_after_last - 1;i > first;i--){
    for(j = first,k = 1;k <= i;k++) {
      if(data[k] > data[j]) {j = k;}
      count++;
    }
    if(j < i) {
      T tmp = data[i];
      data[i] = data[j];
      data[j] = tmp;
    }
    count++;
  }

  return count;
}

// time measure function
double elapsed_time(void) {
  static struct timespec last_time, current_time;
  last_time = current_time;
  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &current_time) != 0) {// the first argument could also be CLOCK_REALTIME
    return -1.0; // clock_gettime() failed!!!
  }
  return ((double) current_time.tv_sec - (double) last_time.tv_sec) + 1.0e-9 * ((double) current_time.tv_nsec - (double) last_time.tv_nsec);
}

int main(void) {
# define max_n  100000
# define max_a  50
# define n_tests 100

	static struct {
	sort_function function;
		char *name;
	}

	functions[] = {
	{ bubble_sort   ,"bubble_sort"    },
	{ shaker_sort   ,"shaker_sort"    },
	{ insertion_sort,"insertion_sort" },
	{ shell_sort    ,"shell_sort"     },
	{ quick_sort    ,"quick_sort"     },
	{ merge_sort    ,"merge_sort"     },
	{ heap_sort     ,"heap_sort"      },
	{ rank_sort     ,"rank_sort"      },
	{ selection_sort,"selection_sort" }
	};

	int a,i,j,k,n,first,one_after_last;
	int nof = (int)(sizeof(functions) / sizeof(functions[0])); // number of sorting functions
	double t = 0.0;

	T master[max_n],data[max_n];
	double elapsed_times[nof], averages[max_a-10+1][nof], averages_squared[max_a-10+1][nof], deviations[max_a-10+1][nof];
	int n_comparisons[nof];

	srand((unsigned int)time(NULL));
	for(a = 10;a <= max_a;a++) {
		n = (int)round(pow(10.0,0.1*(double)a));

		// generate n random numbers
		for(i = 0;i < n;i++) {
			master[i] = (T)((int)rand() % max_n);
		}

		// test all sorting functions
		first = 0;
		one_after_last = n;
	    for(j = 0;j < n_tests;j++) {
			fprintf(stderr,"%4d[%4d,%4d] \r",n,first,one_after_last);
			for(k = 0;k < nof;k++) {
				// all functions use the same unsorted data
				for(i = 0;i < first;i++) {data[i] = (T)(-1);}
				for(;i < one_after_last;i++) {data[i] = master[i];}
				for(;i < n;i++) {data[i] = (T)(-1);}

				//measure time
				(void) elapsed_time();
				// sort
				n_comparisons[k] = (*functions[k].function)(data,first,one_after_last);
				t = elapsed_time();
				elapsed_times[k] += t;
				// calculate averages - first step
				averages[a-10][k] += t; averages_squared[a-10][k] += t*t;

				// test
				if(data[first] < (T)(0)) {
					fprintf(stderr,"%s() failed for n=%d, first=%d, and one_after_last=%d (access error)\n",functions[k].name,n,first,one_after_last);
					exit(1);
				}
				for(i = first + 1;i < one_after_last;i++) {
					if(data[i] < data[i - 1]){
						show(data,first,one_after_last);
						fprintf(stderr,"%s() failed for n=%d, first=%d, and one_after_last=%d (sort error for i=%d)\n",functions[k].name,n,first,one_after_last,i);
						exit(1);
					}
				}
			}

			// change index range
			first = (int)rand() % (1 + (3 * n) / 4);
			do {
				one_after_last = (int)rand() % (1 + n);
			} while(one_after_last <= first);
	    }
	}

	// save results for processing later
	FILE *ficheiro = fopen("to_be_processed.txt","w");
	for(a = 10;a <= max_a;a++) {
		n = (int)round(pow(10.0,0.1*(double)a));
		// calculate averages - second step and the standard deviations
		for(k = 0;k < nof;k++) {
			averages[a-10][k] = averages[a-10][k]/(double)n_tests;
			averages_squared[a-10][k] = averages_squared[a-10][k]/(double)n_tests;
			deviations[a-10][k] = averages_squared[a-10][k] - pow(averages[a-10][k],2);
			fprintf(ficheiro,"%d %f %f\n",n,averages[a-10][k],deviations[a-10][k]);
		}
	}
	fclose(ficheiro);

	// save time measurements and comparisons counts
	FILE *out = fopen("output.txt","w");
	fprintf(out,"//\n// Autores: Filipe Pires e João Alegria\n// Data: Dezembro de 2017\n//\n\nTempos de execução dos algoritmos de ordenação:\n\n");
	for(int i = 0; i < nof; i++) {
		fprintf(out,"%20s -> %10fs\n",functions[i].name,elapsed_times[i]);
	}
	fprintf(out,"\nContagem de comparações feitas pelos algoritmos de comparação:\n");
	for(int i = 0; i < nof; i++) {
		fprintf(out,"%20s -> %10d\n",functions[i].name,n_comparisons[i]);
	}
	fclose(out);

	//
	// done
	//
	printf("No errors found :-)\n");
	return 0;
# undef max_n
# undef max_a
# undef n_tests
}