#ifndef P64_ASM_MACHINE_MEMORY_SLICE_HPP
#define P64_ASM_MACHINE_MEMORY_SLICE_HPP

#include <cstdint>

enum MachineMemorySliceFlag { MMSF_READONLY = 0b1, MMSF_EXECUTABLE = 0b10 };

class MachineMemorySlice {
 private:
  uint64_t size;

  uintptr_t host_address;
  uintptr_t guest_address;

  uint64_t flags;

 public:
  MachineMemorySlice(uint64_t size, uintptr_t guest_address, uint64_t flags);
  MachineMemorySlice(uint64_t size, uintptr_t guest_address);

  uint64_t getFlags();

  uint64_t setFlags(uint64_t newFlags);

  uint64_t getSize();

  uintptr_t getHostAddress();

  uintptr_t getGuestAddress();
};

#endif  // P64_ASM_MACHINE_MEMORY_SLICE_HPP
