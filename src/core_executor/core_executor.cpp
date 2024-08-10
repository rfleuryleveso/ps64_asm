
#include "core_executor/core_executor.h"
#include "core_executor/asm_functions.h"

void CoreExecutor::executeThread() {
  while(core->getState() == MachineCoreState::RUNNING) {
    uint64_t ip = core->getIp();
    auto* op_code = (uint64_t* )machine_memory->getHostAddressFromGuestAddress(ip);
    if(*op_code > MACHINEASM_OPCODE_MAX) {
      core->stop();
      return;
    }
    MachineAsm::asm_function op_code_executor = MachineAsm::functions[*op_code];
    op_code_executor(core, machine_memory, op_code);
  }
}
CoreExecutor::CoreExecutor(MachineCore *core, MachineMemory* machine_memory) : core(core), machine_memory(machine_memory){

}
