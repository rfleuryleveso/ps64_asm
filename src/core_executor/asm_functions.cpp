#include "core_executor/asm_functions.h"

#include "spdlog/spdlog.h"

MachineAsm::asm_function MachineAsm::functions[MACHINEASM_OPCODE_MAX + 1] = {
    nullptr,

    MachineAsm::ADD,
    MachineAsm::ADC,

    MachineAsm::AND,
    MachineAsm::OR,
    MachineAsm::XOR,

    MachineAsm::CMP,
    MachineAsm::PUSH,
    MachineAsm::POP,
    MachineAsm::CALL,
};

inline void MachineAsm::ADD(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {
  auto * op_code = static_cast<uint64_t*>(host_ip);

  spdlog::info("OPCODE = {}", *op_code);

  machine_core->setIp(machine_core->getIp()+ 3 * sizeof(uint64_t));
}

inline void MachineAsm::ADC(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}

inline void MachineAsm::AND(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}

inline void MachineAsm::OR(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}

inline void MachineAsm::XOR(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}

inline void MachineAsm::CMP(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}
inline void MachineAsm::PUSH(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}
inline void MachineAsm::POP(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}
inline void MachineAsm::CALL(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip) {

}