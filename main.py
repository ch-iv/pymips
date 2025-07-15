from typing import Literal, Any
from enum import Enum

source = """
.macro hi($a)
    li $t2 12
.endmacro

li $t0 34
li $t1 35
add $t0 $t0 $t1
hi()    # do stuff

.include "board.c"
.include "pill_red_left.c"
.include "pill_red_right.c"
"""

instructions = [
    "li", "add", "move", "lw", "sll", "sw", "bgtz", "andi", "ori", "j", "jal", "beq", "addi", "sub", "mul", "div",
    "xor", "nor", "slt", "slti", "srl", "sra", "bne", "subi", "bgez", "la", "addiu", "bge", "mfhi", "mflo"
]

class TokenType(Enum):
    INSTRUCTION = (230, 57, 70, 0.3)
    REGISTER = (69, 240, 157, 0.3)
    LITERAL = (244, 162, 97, 0.3)
    LEFT_PAREN = (42, 157, 143, 0.3)
    RIGHT_PAREN = (42, 157, 144, 0.3)
    IDENT = (38, 70, 150, 0.3)
    KEYWORD = (233, 196, 106, 0.3)
    LABEL = (141, 153, 174, 0.3)
    ARG = (168, 218, 220, 0.3)
    NUM_CONSTANT = (255, 175, 204, 0.3)
    STR_CONSTANT = (181, 23, 158, 0.3)
    COMMENT = (45, 45, 45, 0.1)


class Token:
    def __init__(self, lexeme: str, tok_type: TokenType, line_idx, column_start, column_end):
        self.lexeme = lexeme
        self.token_type = tok_type
        self.line_idx = line_idx
        self.column_start = column_start
        self.column_end = column_end

    def __repr__(self):
        return (f"Token(lexeme='{self.lexeme}', token_type={self.token_type.name}),"
                f" line_idx={self.line_idx}, column_start={self.column_start}, column_end={self.column_end})")

class Tokenizer:
    def __init__(self, corpus: str):
        self.corpus = corpus

    def tokenize(self) -> list[Token]:
        tokens = []
        lines = self.corpus.splitlines()

        for line_idx in range(len(lines)):
            line = lines[line_idx]
            if not line:
                continue
            i = 0
            while i < len(line):
                c = line[i]
                i += 1
                if c == " ":
                    continue
                elif c == "(":
                    tokens.append(Token(c, TokenType.LEFT_PAREN, line_idx, i - 1, i))
                elif c == ")":
                    tokens.append(Token(c, TokenType.RIGHT_PAREN, line_idx, i - 1, i))
                elif c == "$":
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i].isalnum():
                        buff += line[i]
                        i += 1
                    tokens.append(Token(buff, TokenType.REGISTER, line_idx, col_start, i))
                elif c.isalpha() or c == "." or c == "%":
                    buff = c
                    col_start = i - 1
                    while i < len(line) and (line[i].isalnum() or line[i] == "_" or line[i] == ":"):
                        buff += line[i]
                        i += 1
                    token_type = TokenType.IDENT
                    if buff in instructions:
                        token_type = TokenType.INSTRUCTION
                    elif buff.endswith(":"):
                        token_type = TokenType.LABEL
                    elif buff.startswith("."):
                        token_type = TokenType.KEYWORD
                    elif buff.startswith("%"):
                        token_type = TokenType.ARG
                    tokens.append(Token(buff, token_type, line_idx, col_start, i))
                elif c.isnumeric():
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i].isalnum():
                        buff += line[i]
                        i += 1
                    tokens.append(Token(buff, TokenType.NUM_CONSTANT, line_idx, col_start, i))
                elif c == '"':
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i] != '"':
                        buff += line[i]
                        i += 1
                    if i < len(line) and line[i] == '"':
                        buff += line[i]
                        i += 1
                    tokens.append(Token(buff, TokenType.STR_CONSTANT, line_idx, col_start, i))
                elif c == "#":
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i] != "\n":
                        buff += line[i]
                        i += 1
                    tokens.append(Token(buff, TokenType.COMMENT, line_idx, col_start, i))

        return tokens

def instruction_type(token: Token) -> Literal["r", "i", "j"]:
    assert token.token_type == TokenType.INSTRUCTION

    if token.lexeme in {"add", "sub", "mul", "div"}:
        return "r"
    elif token.lexeme in {"li", "lw", "sw"}:
        return "i"
    elif token.lexeme in {"j", "jal"}:
        return "j"

    raise ValueError(f"Unknown instruction type for token: {token.lexeme}")


from abc import ABC, abstractmethod

class Machine:
    def __init__(self):
        self.registers = {f"$t{i}": 0 for i in range(9)}

    def set(self, register: str, val: Any) -> None:
        assert register in self.registers
        self.registers[register] = val

    def get(self, register: str) -> Any:
        assert register in self.registers
        return self.registers[register]

    def print_registers(self) -> None:
        for reg, val in self.registers.items():
            print(f"{reg}: {val}", end=", ")

class Statement(ABC):
    def __init__(self):
        pass

    @abstractmethod
    def execute(self, machine: Machine) -> None:
        pass

    @abstractmethod
    def __repr__(self) -> str:
        pass


class RTypeStatement(Statement):
    def __init__(self, instruction: Token, op1: Token, op2: Token, dest: Token):
        super().__init__()
        assert instruction.token_type == TokenType.INSTRUCTION
        assert instruction_type(instruction) == "r"
        assert op1.token_type == TokenType.REGISTER
        assert op2.token_type == TokenType.REGISTER
        assert dest.token_type == TokenType.REGISTER

        self.instruction = instruction
        self.op1 = op1
        self.op2 = op2
        self.dest = dest

    def execute(self, machine: Machine) -> None:
        if self.instruction.lexeme == "add":
            result = machine.get(self.op1.lexeme) + machine.get(self.op2.lexeme)
            machine.set(self.dest.lexeme, result)

    def __repr__(self) -> str:
        return f"RTypeStatement(instruction={self.instruction.lexeme}, op1={self.op1.lexeme}, op2={self.op2.lexeme}, dest={self.dest.lexeme})"


class ITypeStatement(Statement):
    def __init__(self, instruction: Token, dest: Token, literal: Token):
        super().__init__()
        assert instruction.token_type == TokenType.INSTRUCTION
        assert instruction_type(instruction) == "i"
        assert dest.token_type == TokenType.REGISTER
        assert literal.token_type == TokenType.LITERAL

        self.instruction = instruction
        self.dest = dest
        self.literal = literal

    def execute(self, machine: Machine) -> None:
        if self.instruction.lexeme == "li":
            machine.set(self.dest.lexeme, int(self.literal.lexeme))

    def __repr__(self) -> str:
        return f"ITypeStatement(instruction={self.instruction.lexeme}, dest={self.dest.lexeme}, literal={self.literal.lexeme})"

class Parser:
    def __init__(self, tokens: list[Token]):
        self.tokens = tokens

    def parse(self):
        statements = []
        i = 0
        while i < len(self.tokens):
            token = self.tokens[i]
            if token.token_type == TokenType.INSTRUCTION:
                if instruction_type(token) == "r":
                    dest = self.tokens[i + 1]
                    op1 = self.tokens[i + 2]
                    op2 = self.tokens[i + 3]
                    statements.append(RTypeStatement(token, op1, op2, dest))
                    i += 4
                elif instruction_type(token) == "i":
                    dest = self.tokens[i + 1]
                    literal = self.tokens[i + 2]
                    statements.append(ITypeStatement(token, dest, literal))
                    i += 3
                else:
                    raise ValueError(f"Unknown instruction type for token: {token.lexeme}")
            else:
                raise ValueError(f"Expected instruction token, got: {token.lexeme}")

        return statements

def generate_html_highlight(tokens: list[Token], source: str, output_file: str):
    html = [
        "<!DOCTYPE html>",
        "<html>",
        "<head>",
        "<meta charset='UTF-8'>",
        "<style>",
        "body { font-family: monospace }",
        "span { padding: 2px; }"
        ".line { white-space: pre; padding: 0px; margin: 0; display: block; }",
    ]

    for token_type in TokenType:
        html.append(f".{token_type.name} {{ background-color: rgba({token_type.value[0]}, {token_type.value[1]}, {token_type.value[2]}, {token_type.value[3]}); }}")

    html += ["</style>", "</head>", "<body>"]

    tokens_by_pos = {(t.line_idx, t.column_start): t for t in tokens}

    lines = source.splitlines()

    for line_idx, line in enumerate(lines):
        html.append("<div class='line' style='display: flex;'>")

        in_span = False
        i = 0
        while i < len(line):
            token = tokens_by_pos.get((line_idx, i))

            if token:
                if in_span:
                    html[-1] += "</span>"
                    in_span = False
                token_text = line[token.column_start:token.column_end]
                html.append(
                    f"<span class='{token.token_type.name}' title='{token.token_type.name}'>{escape_html(token_text)}</span>")
                i = token.column_end
            else:
                h = escape_html(line[i])
                if not in_span:
                    in_span = True
                    html.append(f"<span style='white-space: pre'>{h}")
                else:
                    html[-1] += h
                i += 1

        html.append("</div>")

    html += ["</body>", "</html>"]

    with open(output_file, "w") as f:
        f.write("\n".join(html))


def escape_html(text: str) -> str:
    return (
        text.replace("&", "&amp;")
            .replace("<", "&lt;")
            .replace(">", "&gt;")
            .replace('"', "&quot;")
    )


t = Tokenizer(source)
tokens = t.tokenize()
generate_html_highlight(tokens, source, output_file="example.html")
