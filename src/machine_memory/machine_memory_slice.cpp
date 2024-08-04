#include "machine_memory/machine_memory_slice.hpp"

#include <malloc.h>

MachineMemorySlice::MachineMemorySlice(uint64_t size, uintptr_t guest_address,
                                       uint64_t flags) {
  this->flags = flags;
  this->size = size;
  this->guest_address = guest_address;
  this->host_address = reinterpret_cast<uintptr_t>(malloc(size));
}
MachineMemorySlice::MachineMemorySlice(uint64_t size, uintptr_t guest_address)
    : MachineMemorySlice(size, guest_address,
                         MachineMemorySliceFlag::MMSF_READONLY) {}

uint64_t MachineMemorySlice::getFlags() { return this->flags; }

uint64_t MachineMemorySlice::setFlags(uint64_t newFlags) {
  this->flags = newFlags;
  return newFlags;
}

uint64_t MachineMemorySlice::getSize() { return this->size; }

uintptr_t MachineMemorySlice::getHostAddress() { return this->host_address; }
uintptr_t MachineMemorySlice::getGuestAddress() { return this->guest_address; };


