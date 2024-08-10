#include "machine_memory/machine_memory_slice.hpp"

#include <malloc.h>
#include "spdlog/spdlog.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "Memoryapi.h"

#else

#endif


MachineMemorySlice::MachineMemorySlice(uint64_t size, uintptr_t guest_address,
                                       uint64_t flags) {
  spdlog::trace("mms");
  this->flags = flags;
  this->size = size;
  this->guest_address = guest_address;
  spdlog::trace("malloc(size) size = {}", size);
  void* host_address = malloc(size);
  if(host_address == nullptr) {
    spdlog::error("Alloc failed for slice guest_address = {}, size = {}, flags = {}", guest_address, size, flags);
  }
  spdlog::trace("host_address = {}", host_address);

  this->host_address = reinterpret_cast<uintptr_t>(host_address);
  spdlog::trace("guest_address = {} host_address = {}", (void*)this->guest_address, (void*)this->host_address);
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
uintptr_t MachineMemorySlice::getGuestAddress() { return this->guest_address; }

void MachineMemorySlice::hostLock() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  bool result = VirtualLock((LPVOID)this->getHostAddress(), this->getSize());
  if(!result) {
    spdlog::warn("Could not lock slice @ {} ({} bytes)", this->getHostAddress(), this->getSize());
  }
#else
  spdlog::error("Unhandled platform for hostLock");
#endif
}

void MachineMemorySlice::hostUnlock() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  bool result = VirtualUnlock((LPVOID)this->getHostAddress(), this->getSize());
  if(!result) {
    spdlog::warn("Could not lock slice @ {} ({} bytes)", this->getHostAddress(), this->getSize());
  }
#else
  spdlog::error("Unhandled platform for hostUnlock");
#endif
};


