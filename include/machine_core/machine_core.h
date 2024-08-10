#ifndef P64_ASM_MACHINE_CORE_H
#define P64_ASM_MACHINE_CORE_H

#include <atomic>
#include <cstdint>

enum MachineCoreState {
  STOPPED,
  RUNNING,
  STOPPING,
  DUMPED
};

class MachineCore {
 private:
  // Instruction pointer
  uint64_t ip = 0x0;

   // Stack pointer
  uint64_t sp = 0x0;

  // Flags register
  uint64_t fr = 0x0;

  // Mode
  uint8_t mode = 0x0;

  // State
  std::atomic<MachineCoreState> state = MachineCoreState::STOPPED;

  // Index of the core
  const uint8_t index;
 public:
  explicit MachineCore(uint8_t index): index(index) {};

  void start();
  void stop();

  uint64_t getIp();
  void setIp(uint64_t ip);

  uint64_t getSp();
  void setSp(uint64_t sp);

  uint64_t getFr();
  void setFr(uint64_t fr);

  MachineCoreState getState();
};

#endif  // P64_ASM_MACHINE_CORE_H
