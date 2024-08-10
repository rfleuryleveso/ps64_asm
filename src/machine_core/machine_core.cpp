#include "machine_core/machine_core.h"

#include "spdlog/spdlog.h"
void MachineCore::start() {
  this->state = MachineCoreState::RUNNING;
  spdlog::info("Core {} is running", this->index);
}

void MachineCore::stop() {
  this->state = MachineCoreState::STOPPING;
}

MachineCoreState MachineCore::getState() {
  return this->state.load();
}
uint64_t MachineCore::getIp() { return ip; }
void MachineCore::setIp(uint64_t ip) { this->ip = ip; }

uint64_t MachineCore::getSp() { return sp; }
void MachineCore::setSp(uint64_t sp) { this->sp = sp; }

uint64_t MachineCore::getFr() { return fr; }
void MachineCore::setFr(uint64_t fr) { this->fr = fr; }
