#ifndef P64_ASM_MACHINE_MEMORY_HPP
#define P64_ASM_MACHINE_MEMORY_HPP

#include "machine_memory_slice.hpp"

#define MAX_SLICE_COUNT 64

class MachineMemory {
 private:
  MachineMemorySlice* slices[MAX_SLICE_COUNT] = {nullptr};
  uint32_t slice_count = 0;

 public:
  MachineMemorySlice* addSlice(uint64_t size, uint64_t flags,
                               uintptr_t guest_address);
  ~MachineMemory();
};


#endif  // P64_ASM_MACHINE_MEMORY_HPP
