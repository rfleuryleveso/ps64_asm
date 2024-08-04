#ifndef P64_ASM_MACHINE_HPP
#define P64_ASM_MACHINE_HPP

#include "machine_memory/machine_memory.hpp"

typedef enum MachineState {
  MACHINE_INIT = 0x0,
  MACHINE_RUNNING = 0x1,
  MACHINE_STOPPED = 0x2,
} MachineState;

class Machine {
 private:
  MachineMemory* machine_memory;
  MachineState state = MachineState ::MACHINE_INIT;

 public:
  /**
   * Halts a machine's execution without freeing it's resources
   */
  void stop();

  MachineMemory* getMemory();
  MachineState getState();
  Machine();
  ~Machine();
};


#endif  // P64_ASM_MACHINE_HPP
