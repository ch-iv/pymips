from tokens.token import *
from tokens.instructions import all_instructions

class Tokenizer:
    def __init__(self, corpus: str):
        self.lines = corpus.splitlines()

    def tokenize(self) -> list[Token]:
        tokens = []

        for line_idx, line in enumerate(self.lines):
            i = 0
            while i < len(line):
                c = line[i]
                i += 1
                if c == " ":
                    continue
                elif c == "(":
                    tokens.append(LeftParenToken(c, line_idx, i - 1, i))
                elif c == ")":
                    tokens.append(RightParenToken(c, line_idx, i - 1, i))
                elif c == "$":
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i].isalnum():
                        buff += line[i]
                        i += 1
                    tokens.append(RegisterToken(buff, line_idx, col_start, i))
                elif c.isalpha() or c == "." or c == "%":
                    buff = c
                    col_start = i - 1
                    while i < len(line) and (line[i].isalnum() or line[i] == "_" or line[i] == ":"):
                        buff += line[i]
                        i += 1
                    if buff in all_instructions:
                        tokens.append(InstructionToken(buff, line_idx, col_start, i))
                    elif buff.endswith(":"):
                        tokens.append(LabelToken(buff, line_idx, col_start, i))
                    elif buff.startswith(".") or buff == "syscall":
                        tokens.append(KeywordToken(buff, line_idx, col_start, i))
                    elif buff.startswith("%"):
                        tokens.append(ArgToken(buff, line_idx, col_start, i))
                    else:
                        tokens.append(IdentToken(buff, line_idx, col_start, i))
                elif c.isnumeric():
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i].isalnum():
                        buff += line[i]
                        i += 1
                    tokens.append(NumConstantToken(buff, line_idx, col_start, i))
                elif c == '"':
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i] != '"':
                        buff += line[i]
                        i += 1
                    if i < len(line) and line[i] == '"':
                        buff += line[i]
                        i += 1
                    tokens.append(StrConstantToken(buff, line_idx, col_start, i))
                elif c == "#":
                    buff = c
                    col_start = i - 1
                    while i < len(line) and line[i] != "\n":
                        buff += line[i]
                        i += 1
                    tokens.append(CommentToken(buff, line_idx, col_start, i))

        tokens.append(EOFToken("EOF", len(self.lines), 0, 0))
        return tokens