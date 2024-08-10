#include "machine/machine.hpp"

#include <stdexcept>

#include "core_executor/core_executor.h"
#include "spdlog/spdlog.h"

Machine::~Machine() {
  if(this->state == MachineState::MACHINE_RUNNING) {
    spdlog::error("Machine is still marked as running, you should stop before freeing it. Auto-stopping...");
    this->stop();
  }

  for(size_t core_i = 0; core_i < this->core_count; core_i++) {
    spdlog::debug("Deleting core {}", core_i);
    delete this->cores[core_i];
  }

  delete this->machine_memory;
}

void Machine::stop() {
  this->state = MachineState::MACHINE_STOPPED;
  for(size_t core_i = 0; core_i < this->core_count; core_i++) {
    this->cores[core_i]->stop();
  }

  for(size_t core_i = 0; core_i < this->core_threads_count; core_i++) {
    spdlog::debug("Waiting for core {} to exit", core_i);
    std::thread* core_thread = this->core_threads[core_i];
    if(core_thread->joinable()) {
      core_thread->join();
    }
  }
}
MachineMemory* Machine::getMemory() { return this->machine_memory; }
MachineState Machine::getState() { return this->state; }

Machine::Machine() {
  this->machine_memory = new MachineMemory();
}
MachineCore* Machine::createCore(uint8_t index) {
  auto core = new MachineCore(index);
  this->cores[this->core_count++] = core;
  return core;
}

void Machine::createCoreExecutor(MachineCore* core) {
  auto core_executor = new CoreExecutor(core, this->machine_memory);
  this->core_executors[this->core_executors_count++] = core_executor;

  auto core_executor_thread = new std::thread(&CoreExecutor::executeThread, core_executor);
  this->core_threads[this->core_threads_count++] = core_executor_thread;
}
