from expressions.constant import RegisterConstant, NumericConstant, ArgConstant, LabelConstant
from tokens.instructions import instruction_types
from tokens.instructions import InstructionType

class Token:
    def __init__(self, lexeme: str, line_idx: int, column_start: int, column_end: int):
        self._lexeme = lexeme
        self._line_idx = line_idx
        self._column_start = column_start
        self._column_end = column_end

    @property
    def lexeme(self) -> str:
        return self._lexeme

    @property
    def line_idx(self) -> int:
        return self._line_idx

    @property
    def column_start(self) -> int:
        return self._column_start

    @property
    def column_end(self) -> int:
        return self._column_end

    def __repr__(self):
        return (f"{self.__class__.__name__}(lexeme='{self.lexeme}', "
                f"line_idx={self.line_idx}, "
                f"column_start={self.column_start}, "
                f"column_end={self.column_end})")



class InstructionToken(Token):
    def instruction_type(self) -> InstructionType:
        instruction_type = instruction_types[self.lexeme]

        if instruction_type is None:
            raise ValueError(f"Unknown instruction type for token: {self.lexeme}")

        return instruction_type
    


class RegisterToken(Token):
    def to_const(self) -> RegisterConstant:
        return RegisterConstant(self.lexeme)


class LiteralToken(Token):
    pass


class LeftParenToken(Token):
    pass


class RightParenToken(Token):
    pass


class IdentToken(Token):
    def to_const(self) -> LabelConstant:
        return LabelConstant(self.lexeme)


class KeywordToken(Token):
    pass


class LabelToken(Token):
    def to_const(self) -> LabelConstant:
        return LabelConstant(self.lexeme)


class ArgToken(Token):
    def to_const(self, definition: bool = False) -> ArgConstant:
        return ArgConstant(self.lexeme, definition)



class NumConstantToken(Token):
    def to_const(self) -> NumericConstant:
        return NumericConstant(self.lexeme)


class StrConstantToken(Token):
    pass


class CommentToken(Token):
    pass

class EOFToken(Token):
    pass
