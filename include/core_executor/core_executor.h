#ifndef P64_ASM_CORE_EXECUTOR_H
#define P64_ASM_CORE_EXECUTOR_H

#include "machine_core/machine_core.h"
#include "machine_memory/machine_memory.hpp"
class CoreExecutor {
  MachineCore* core = nullptr;
  MachineMemory* machine_memory = nullptr;

 public:
  explicit CoreExecutor(MachineCore*, MachineMemory*);
  void executeThread();
};

#endif  // P64_ASM_CORE_EXECUTOR_H
