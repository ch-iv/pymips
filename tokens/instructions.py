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
    R = "r"

instructions: dict[InstructionType, list[str]] = {
    InstructionType.RRR: [
        "add",
        "sub",
        "mul",
        "div",
        "xor",
        "and",
        "or",
    ],
    InstructionType.RR: [
        "move",
        "div",
    ],
    InstructionType.RI: [
        "li"
    ],
    InstructionType.RRI: [
        "addi",
        "andi",
        "ori",
        "xori",
        "subi",
        "sll",
        "srl",
    ],
    InstructionType.RL: [
        "la",
        "bgtz",
        "bltz",
    ],
    InstructionType.RRL: [
        "blt",
        "ble",
        "bgt",
        "bge",
        "beq",
        "bne"
    ],
    InstructionType.ROR: [
        "lw",
        "sw",
        "beqz",
        "bgez",
    ],
    InstructionType.L: [
        "j",
        "jal",
    ],
    InstructionType.R: [
        "mfhi",
        "mflo",
    ],
}

instruction_types: dict[str, InstructionType] = {
    instruction: instruction_type
    for instruction_type, instruction_list in instructions.items()
    for instruction in instruction_list
}

all_instructions: set[str] = set(instruction_types.keys())