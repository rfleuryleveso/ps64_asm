#ifndef P64_ASM_MACHINE_HPP
#define P64_ASM_MACHINE_HPP

#include <thread>

#include "core_executor/core_executor.h"
#include "machine_core/machine_core.h"
#include "machine_memory/machine_memory.hpp"

#define MAX_CORE_COUNT 128

typedef enum MachineState {
  MACHINE_INIT = 0x0,
  MACHINE_RUNNING = 0x1,
  MACHINE_STOPPED = 0x2,
} MachineState;

class Machine {
 private:
  MachineMemory* machine_memory;
  MachineState state = MachineState ::MACHINE_INIT;
  MachineCore* cores[MAX_CORE_COUNT] = {nullptr};
  uint8_t core_count = 0;

  std::thread* core_threads[MAX_CORE_COUNT] = {nullptr};
  uint8_t core_threads_count = 0;

  CoreExecutor* core_executors[MAX_CORE_COUNT] = {nullptr};
  uint8_t core_executors_count = 0;

 public:
  /**
   * Halts a machine's execution without freeing it's resources
   */
  void stop();

  MachineMemory* getMemory();
  MachineState getState();

  /**
   * Creates a new machine core and adds it to the list
   * @return ptr to the machine core
   */
  MachineCore* createCore(uint8_t);

  void createCoreExecutor(MachineCore*);

  Machine();
  ~Machine();
};


#endif  // P64_ASM_MACHINE_HPP
