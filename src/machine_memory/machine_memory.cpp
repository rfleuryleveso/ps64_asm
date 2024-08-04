#include "machine_memory/machine_memory.hpp"

#include "spdlog/spdlog.h"
MachineMemorySlice* MachineMemory::addSlice(uint64_t size, uint64_t flags,
                                            uintptr_t guest_address) {
  if(this->slice_count == MAX_SLICE_COUNT) {
    throw std::runtime_error("MAX_SLICE_COUNT REACHED");
  }

  auto slice = new MachineMemorySlice(size, guest_address, flags);

  // Add the slice to the slices array and increment the number of slices
  this->slices[this->slice_count++] = slice;
  spdlog::debug("Registered #{} start = {}, size = {}", this->slice_count - 1, slice->getGuestAddress(), slice->getHostAddress());
  return slice;
}
MachineMemory::~MachineMemory() {
  for(size_t slice = 0; slice < this->slice_count; slice++) {
    spdlog::debug("Unregistering slice #{} start = {}, size = {}", slice, this->slices[slice]->getGuestAddress(), this->slices[slice]->getHostAddress());
    delete this->slices[slice];
  }
  this->slice_count = 0;
}
