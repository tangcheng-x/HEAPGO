#ifndef K_WAY_EXTERN_SORT_H_
#define K_WAY_EXTERN_SORT_H_

#include "../SimpleFunction.hpp"

#include <cstdlib>

// ----------------------------------------------------------------------------
// Class ExternSort
//
// Sort extern file data
//
class ExternSort {
 private:
  // The path of input file(unsort)
  char* input_file_;

  // The path of output file(sorted)
  char* output_file_;

  // The length of array which to sort
  int length_;

 protected:
  int read_data(FILE* fp, int a[], int n);
  void write_data(FILE* fp, int a[], int n);

  int memory_sort();

  void merge_sort(int file_count);

  char* generate_temp_filename(const int& index);


 public:
  ExternSort(const char* input_file,
             const char* output_file,
             const int length)
    : length_(length) {
    input_file_ = new char[strlen(input_file) + 1];
    ASSERT(myStrcpy(input_file_, input_file));
    output_file_ = new char[strlen(output_file) + 1];
    ASSERT(myStrcpy(output_file_, output_file));
  }

  virtual ~ExternSort() {
    if (input_file_)
      delete [] input_file_;
    if (output_file_)
      delete [] output_file_;
  }

  void Sort();
};  // class ExternClass


#endif  // K_WAY_EXTERN_SORT_H_
