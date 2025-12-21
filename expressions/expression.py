from abc import ABC, abstractmethod
from expressions.constant import RegisterConstant, Constant, NumericConstant, ArgConstant, LabelConstant, MockConstant

class Expression(ABC):
    @abstractmethod
    def to_c(self) -> str:
        pass

class InstructionExpression(Expression):
    def __init__(self, instruction: str):
        self._instruction = instruction

    @property
    def instruction(self) -> str:
        return self._instruction

    @property
    @abstractmethod
    def args(self) -> list[str]:
        pass

    def to_c(self) -> str:
        c_function_name = f"_instr_{self.instruction}"
        c_function_args = ", ".join([arg.to_c() for arg in self.args])

        return f"{c_function_name}({c_function_args});"

    @abstractmethod
    def args(self) -> list[Constant]:
        pass

class RRRInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        dest: RegisterConstant,
        src1: RegisterConstant,
        src2: RegisterConstant,
    ):
        super().__init__(instruction)
        self.dest = dest
        self.src1 = src1
        self.src2 = src2

    @property
    def args(self) -> list[Constant]:
        return [self.dest, self.src1, self.src2]

class RIInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        dest: RegisterConstant,
        immediate: NumericConstant,
    ):
        super().__init__(instruction)
        self.dest = dest
        self.immediate = immediate

    @property
    def args(self) -> list[Constant]:
        return [self.dest, self.immediate]

class RRInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        dest: RegisterConstant,
        src: RegisterConstant,
    ):
        super().__init__(instruction)
        self.dest = dest
        self.src = src

    @property
    def args(self) -> list[Constant]:
        return [self.dest, self.src]

class RLInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        dest: RegisterConstant,
        label: LabelConstant,
    ):
        super().__init__(instruction)
        self.dest = dest
        self.label = label

    @property
    def args(self) -> list[Constant]:
        return [self.dest, self.label]

class RRLInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        src1: RegisterConstant,
        src2: RegisterConstant,
        label: LabelConstant,
    ):
        super().__init__(instruction)
        self.src1 = src1
        self.src2 = src2
        self.label = label

    @property
    def args(self) -> list[Constant]:
        return [self.src1, self.src2, self.label]
    
    def to_c(self) -> str:
        if self.instruction == "beq":
            return f"if (*{self.src1.to_c()} == *{self.src2.to_c()}) {{ goto {self.label.to_c()}; }}"
        else:
            return super().to_c()

class RRIInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        src1: RegisterConstant,
        dest: RegisterConstant,
        immediate: NumericConstant,
    ):
        super().__init__(instruction)
        self.src1 = src1
        self.dest = dest
        self.immediate = immediate

    @property
    def args(self) -> list[Constant]:
        return [self.src1, self.dest, self.immediate]

class RORInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        dest: RegisterConstant,
        offset: NumericConstant,
        src: RegisterConstant,
    ):
        super().__init__(instruction)
        self.dest = dest
        self.offset = offset
        self.src = src

    @property
    def args(self) -> list[Constant]:
        return [
            self.dest, 
            MockConstant(f"_offset({self.offset.to_c()}, {self.src.to_c()})"),
        ]

class RLIInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        dest: RegisterConstant,
        label: LabelConstant,
    ):
        super().__init__(instruction)
        self.dest = dest
        self.label = label
    
    @property
    def args(self) -> list[Constant]:
        return [self.dest, MockConstant(f"_label_address({self.label.to_c()})")]

class LInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        label: LabelConstant,
    ):
        super().__init__(instruction)
        self.label = label
    
    @property
    def args(self) -> list[Constant]:
        return [self.label]
    
    def to_c(self) -> str:
        return f"goto {self.label.to_c()};"

class RInstructionExpression(InstructionExpression):
    def __init__(
        self,
        instruction: str,
        dest: ArgConstant,
    ):
        super().__init__(instruction)
        self.dest = dest

    @property  
    def args(self) -> list[Constant]:
        return [self.dest]

class SyscallExpression(Expression):
    def to_c(self) -> str:
        return "syscall();"

class MacroExpression(Expression):
    def __init__(self, name: str, args: list[ArgConstant], body: list[Expression]):
        self.name = name
        self.args = args
        self.body = body

    def to_c(self) -> str:
        body = "\n".join([expr.to_c() for expr in self.body]).splitlines()

        body = "\n".join([f"\t{line}" for line in body])

        return f"""\nvoid _macro_{self.name}({", ".join([arg.to_c() for arg in self.args])}) {{{body}
}}"""

class MainWrapperExpression(Expression):
    def __init__(self, body: list[Expression], debug_mode: bool = False) -> None:
        self.body = body
        self.debug_mode = debug_mode
    
    def to_c(self) -> str:
        body = "\n".join([expr.to_c() for expr in self.body]).splitlines()

        if self.debug_mode:
            body.append("_mips_dump_registers(); // Debug info")

        body.append("return 0;")

        body = "\n".join([f"\t{line}" for line in body])
        return f"""\nint main() {{\n{body}\n}}"""

class MacroCallExpression(Expression):
    def __init__(self, name: str, args: list[Constant]):
        self.name = name
        self.args = args

    def to_c(self) -> str:
        return f"_macro_{self.name}({", ".join([arg.to_c() for arg in self.args])});"

class IncludeExpression(Expression):
    def __init__(self, file_name: str):
        self.file_name = file_name

    def to_c(self) -> str:
        return f"#include {self.file_name}"

class EmptyExpression(Expression):
    def to_c(self) -> str:
        return ""

class LabelExpression(Expression):  
    def __init__(self, label: str):
        self.label = label

    def to_c(self) -> str:
        return f"{self.label}"