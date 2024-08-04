#ifndef P64_ASM_MACHINE_CORE_H
#define P64_ASM_MACHINE_CORE_H

#include <cstdint>

class MachineCore {
 private:
  // Instruction pointer
  uint64_t ip;

  // Stack pointer
  uint64_t sp;

  // Flags register
  uint64_t fr;

  // Mode
  uint8_t mode;
};

#endif  // P64_ASM_MACHINE_CORE_H
