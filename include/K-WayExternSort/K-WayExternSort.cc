#include "K-WayExternSort.h"

#include <algorithm>   // Sort function

int ExternSort::read_data(FILE* fp, int a[], int n) {
  int i = 0;
  while (i < n && (fscanf(fp, "%d", &a[i]) != EOF))
    ++i;
  LOG_OUT("read %d integers\n", i);
  return i;
}

void ExternSort::write_data(FILE* fp, int a[], int n) {
  for (int i = 0; i < n; ++i)
    fprintf(fp, "%d ", a[i]);
}

char* ExternSort::generate_temp_filename(const int& index) {
  char* name = new char[20];
  sprintf(name, "temp%d.txt", index);
  return name;
}

int ExternSort::memory_sort() {
  FILE* f_in = fopen(input_file_, "rt");
  int n = 0, file_count = 0;
  int* arr = new int[length_];
  while ((n = read_data(f_in, arr, length_)) >0) {
    //TODO: replace by sort funtion written by mine
    std::sort(arr, arr + length_);
    char *filename = generate_temp_filename(file_count++);
    FILE* f_out = fopen(filename, "w");
    write_data(f_out, arr, n);
    delete filename;
    fclose(f_out);
  }

  delete [] arr;
  fclose(f_in);
  return file_count;
}

void ExternSort::merge_sort(int file_count) {
  ASSERT(file_count >= 0);

  FILE* fout = fopen(output_file_, "w");

  FILE** fileArray = new FILE*[file_count];
  for (int i = 0; i < file_count; ++i) {
    char* filename = generate_temp_filename(i);
    fileArray[i] = fopen(filename, "rt");
    delete filename;
  }

  int* data = new int[file_count];
  bool* hasNext = new bool[file_count];

  memset(data, 0, sizeof(int) * file_count);
  memset(hasNext, true, sizeof(bool) * file_count);

  for (int i = 0; i < file_count; ++i) {
    if (fscanf(fileArray[i], "%d", &data[i]) == EOF)
      hasNext[i] = false;
  }

  while (true) {
    int min = data[0];
    int j = 0;
    while (j < file_count && !hasNext[j])
      ++j;
    if (j >= file_count)
      break;

    for (int i = j + 1; i < file_count; ++i) {
      if (hasNext[i] && data[i] < min) {
        min = data[i];
        j = i;
      }
    }

    if (fscanf(fileArray[j], "%d", &data[j]) == EOF)
      hasNext[j] = false;
    fprintf(fout, "%d ", min);
  }

  delete [] hasNext;
  delete [] data;

  for (int i = 0; i < file_count; ++i) {
    fclose(fileArray[i]);
  }

  delete [] fileArray;

  fclose(fout);
}

void ExternSort::Sort() {
  int file_count = memory_sort();
  merge_sort(file_count);
}
