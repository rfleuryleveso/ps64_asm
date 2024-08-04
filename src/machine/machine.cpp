#include "machine/machine.hpp"

#include <stdexcept>

#include "spdlog/spdlog.h"

Machine::~Machine() {
  if(this->state == MachineState::MACHINE_RUNNING) {
    spdlog::error("Machine is still marked as running, you should stop before freeing it. Auto-stopping...");
    this->stop();
  }

  delete this->machine_memory;
}

void Machine::stop() {
  this->state = MachineState::MACHINE_STOPPED;
}
MachineMemory* Machine::getMemory() { return this->machine_memory; }
MachineState Machine::getState() { return this->state; }

Machine::Machine() {
  this->machine_memory = new MachineMemory();
}
