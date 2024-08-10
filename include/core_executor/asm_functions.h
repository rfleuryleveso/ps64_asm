//
// Created by Administrator on 05/08/2024.
//

#ifndef P64_ASM_ASM_FUNCTIONS_H
#define P64_ASM_ASM_FUNCTIONS_H


#include "machine_core/machine_core.h"
#include "machine_memory/machine_memory.hpp"


#define MACHINEASM_ADD 1
#define MACHINEASM_ADC 2
#define MACHINEASM_AND 3
#define MACHINEASM_OR 4
#define MACHINEASM_XOR 5
#define MACHINEASM_CMP 6
#define MACHINEASM_PUSH 7
#define MACHINEASM_POP 8
#define MACHINEASM_CALL 9
#define MACHINEASM_RET 10
#define MACHINEASM_JMP 11
#define MACHINEASM_OUT 12



#define MACHINEASM_OPCODE_MAX 12

namespace MachineAsm {
  typedef void (*asm_function)(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);

  void ADD(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void ADC(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void AND(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);

  void OR(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void XOR(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void CMP(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);

  void PUSH(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void POP(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void CALL(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void RET(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void JMP(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);
  void OUT(MachineCore* machine_core, MachineMemory* machine_memory, void* host_ip);

  extern asm_function functions[MACHINEASM_OPCODE_MAX + 1];
}


#endif  // P64_ASM_ASM_FUNCTIONS_H
