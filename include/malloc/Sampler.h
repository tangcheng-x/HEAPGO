#ifndef SAMPLER_H_
#define SAMPLER_H_

// ----------------------------------------------------------------------------
// class Sampler
// The default allocator for TC
class Sampler {
 public:
  void Init(uint32_t seed);
  void CleanUp();

  bool SampleAllocation(size_t k);

  
};  // class Sampler

#endif  // SAMPLER_H_
