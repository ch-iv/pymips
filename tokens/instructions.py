from enum import Enum

class InstructionType(Enum):
    RRR = "rrr"
    RR = "rr"
    RI = "ri"
    RL = "rl"
    RRI = "rri"
    RRL = "rrl"
    ROR = "ror"
    L = "l"

instructions: dict[InstructionType, list[str]] = {
    InstructionType.RRR: [
        "add",
        "sub",
        "mul",
        "div",
        "xor",
    ],
    InstructionType.RR: [
        "move"
    ],
    InstructionType.RI: [
        "li"
    ],
    InstructionType.RRI: [
        "addi",
        "andi",
        "ori",
        "xori",
        "subi"
    ],
    InstructionType.RL: [
        "la"
        "bgtz",
    ],
    InstructionType.RRL: [
        "blt",
        "ble",
        "bgt",
        "bge",
        "beq"
    ],
    InstructionType.ROR: [
        "lw",
        "sw",
        "beqz",
        "bgez",
        "beq",
    ],
    InstructionType.L: [
        "j",
        "jal",
    ],
}

instruction_types: dict[str, InstructionType] = {
    instruction: instruction_type
    for instruction_type, instruction_list in instructions.items()
    for instruction in instruction_list
}

all_instructions: list[str] = set(instruction_types.keys())