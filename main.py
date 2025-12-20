from typing import Any
from tokens.token import *
from expressions.expression import *
from tokens.instructions import all_instructions
from program import Program

source = """
.macro hi(%hi)
    li $t2 12
.endmacro

li $t0 34
li $t1 35
hi()    # do stuff

.include "board.c"
.include "pill_red_left.c"
"""

with open("sample3.asm", "r") as f:
    source = f.read()


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
        tokens.append(EOFToken("EOF", line_idx, len(line), len(line)))
        return tokens

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

class Parser:
    def __init__(self, tokens: list[Token]):
        self.tokens = tokens
        self.current_token = None

    def eat(self, expected: None | list[Token] = None) -> Token:
        self.current_token = self.tokens.pop(0)

        if expected and self.current_token.token_type not in expected:
            raise ValueError(f"Expected {expected}, got {self.current_token.token_type}")

        return self.current_token

    def peek(self) -> Token:
        return self.tokens[0]
    

    def parse_top_level(self) -> list[Expression]:
        prog = []

        while self.tokens:
            if isinstance(self.peek(), EOFToken):
                break

            prog.append(self.parse_expression())

        return prog

    def parse_expression(self) -> Expression:
        match self.peek():
            case InstructionToken():
                return self.parse_instruction()
            case KeywordToken():
                return self.parse_keyword()
            case IdentToken():
                return self.parse_macro_call()
            case CommentToken():
                self.eat()
                return EmptyExpression()
            case LabelToken():
                return self.parse_label()
            case _:
                raise ValueError(f"Unhandled token: {self.peek()}")

    def parse_label(self) -> LabelExpression:
        label_token = to(self.eat(), LabelToken)
        return LabelExpression(label_token.lexeme)

    def parse_macro_call(self) -> MacroCallExpression:
        macro_name_token = to(self.eat(), IdentToken)
        to(self.eat(), LeftParenToken)
        args = []
        while not isinstance(self.peek(), RightParenToken):
            arg = self.eat()
            if not isinstance(arg, RegisterToken) and not isinstance(arg, NumConstantToken) and not isinstance(arg, StrConstantToken) and not isinstance(arg, IdentToken):
                raise ValueError(f"Expected register, number, identifier or string, got {arg}")
            args.append(arg.to_const())
        to(self.eat(), RightParenToken)
        return MacroCallExpression(macro_name_token.lexeme, args)

    def parse_keyword(self) -> Expression:
        keyword_token = to(self.peek(), KeywordToken)
        match keyword_token.lexeme:
            case ".macro":
                return self.parse_macro()
            case ".include":
                return self.parse_include()
            case "syscall":
                self.eat()
                return SyscallExpression()
            case ".text":
                self.eat()
                return EmptyExpression()
            case _:
                raise ValueError(f"Unknown keyword: {keyword_token.lexeme}")

    def parse_include(self) -> IncludeExpression:
        include_token = to(self.eat(), KeywordToken)
        assert include_token.lexeme == ".include"
        file_name_token = to(self.eat(), StrConstantToken)

        return IncludeExpression(file_name_token.lexeme)

    def parse_instruction(self) -> InstructionExpression:
        instruction_token = to(self.eat(), InstructionToken)

        match instruction_token.instruction_type():
            case InstructionType.RRR:
                return RRRInstructionExpression(
                    instruction=instruction_token.lexeme,
                    dest=to(self.eat(), RegisterToken, ArgToken).to_const(),
                    src1=to(self.eat(), RegisterToken, ArgToken).to_const(),
                    src2=to(self.eat(), RegisterToken, ArgToken).to_const(),
                )
            case InstructionType.RI:
                return RIInstructionExpression(
                    instruction=instruction_token.lexeme,
                    dest=to(self.eat(), RegisterToken, ArgToken).to_const(),
                    immediate=to(self.eat(), NumConstantToken, ArgToken).to_const(),
                )
            case InstructionType.RR:
                return RRInstructionExpression(
                    instruction=instruction_token.lexeme,
                    dest=to(self.eat(), RegisterToken, ArgToken).to_const(),
                    src=to(self.eat(), RegisterToken, ArgToken).to_const(),
                )
            case InstructionType.RL:
                return RLInstructionExpression(
                    instruction=instruction_token.lexeme,
                    dest=to(self.eat(), RegisterToken, ArgToken).to_const(),
                    label=to(self.eat(), LabelToken, ArgToken, IdentToken).to_const(),
                )
            case InstructionType.RRL:
                return RRLInstructionExpression(
                    instruction=instruction_token.lexeme,
                    src1=to(self.eat(), RegisterToken, ArgToken, NumConstantToken).to_const(),
                    src2=to(self.eat(), RegisterToken, ArgToken, NumConstantToken).to_const(),
                    label=to(self.eat(), IdentToken, ArgToken).to_const(),
                )
            case InstructionType.RRI:
                return RRIInstructionExpression(
                    instruction=instruction_token.lexeme,
                    src1=to(self.eat(), RegisterToken, ArgToken).to_const(),
                    dest=to(self.eat(), RegisterToken, ArgToken).to_const(),
                    immediate=to(self.eat(), NumConstantToken, ArgToken).to_const(),
                )
            case InstructionType.ROR:
                # This type of instruction can have either an offset (e.g 0($t0)) or a label
                # as the last argument.
                dest = to(self.eat(), RegisterToken, ArgToken).to_const()

                if isinstance(self.peek(), NumConstantToken):
                    offset = to(self.eat(), NumConstantToken, ArgToken).to_const()
                    to(self.eat(), LeftParenToken)
                    src = to(self.eat(), RegisterToken, ArgToken).to_const()
                    to(self.eat(), RightParenToken)
                    return RORInstructionExpression(
                        instruction=instruction_token.lexeme,
                        dest=dest,
                        offset=offset,
                        src=src,
                    )
                else:
                    return RLIInstructionExpression(
                        instruction=instruction_token.lexeme,
                        dest=dest,
                        label=to(self.eat(), LabelToken, ArgToken, IdentToken, RegisterToken).to_const(),
                    )
            case InstructionType.L:
                return LInstructionExpression(
                    instruction=instruction_token.lexeme,
                    label=to(self.eat(), LabelToken, ArgToken, IdentToken).to_const(),
                )
            case InstructionType.R:
                return RInstructionExpression(
                    instruction=instruction_token.lexeme,
                    dest=to(self.eat(), RegisterToken, ArgToken).to_const(),
                )
            case _:
                raise ValueError(f"Unknown instruction type: {instruction_token.instruction_type()}")

    def parse_macro(self) -> MacroExpression:
        # Parse .macro and name
        macro_start_token = to(self.eat(), KeywordToken)
        assert macro_start_token.lexeme == ".macro"

        name_token = to(self.eat(), IdentToken)

        # Parse arguments
        to(self.eat(), LeftParenToken)
        args = []
        while not isinstance(self.peek(), RightParenToken):
            args.append(to(self.eat(), ArgToken).to_const(definition=True))
        to(self.eat(), RightParenToken)

        # Parse body
        body = []
        while not (isinstance(self.peek(), KeywordToken) and self.peek().lexeme == ".end_macro"):
            body.append(self.parse_expression())

        # Parse .end_macro
        end_macro_token = to(self.eat(), KeywordToken)
        assert end_macro_token.lexeme == ".end_macro"

        return MacroExpression(name_token.lexeme, args, body)

def to(token: Token, *accepted_types: list[type[Token]]) -> Token:
    if not any(isinstance(token, accepted_type) for accepted_type in accepted_types):
        highlight_token_in_source(token, source, f"Expected {accepted_types}, got {type(token)}")
        raise ValueError(f"Expected {accepted_types}, got {type(token)}")

    return token

def highlight_token_in_source(token: Token, source: str, error_message: str) -> str:
    RESET = '\033[0m'
    RED = '\033[31m'
    CYAN = '\033[36m'
    BOLD = '\033[1m'
    
    line_offset = 4
    source_lines = source.splitlines()
    start_line = max(0, token.line_idx - line_offset)
    end_line = min(len(source_lines), token.line_idx + line_offset)

    for line_idx in range(start_line, end_line):
        line = source_lines[line_idx]
        print(f"{CYAN}{line_idx + 1}{RESET} {line}")
        if line_idx == token.line_idx:
            caret = f"{RED}{BOLD}{'~' * (token.column_end - token.column_start)}{RESET}"
            print(f"    {' ' * (token.column_start)}{caret}", end="   ")
            print(f"{RED}{BOLD}{error_message}{RESET}", end="\n\n")

t = Tokenizer(source)
tokens = t.tokenize()

p = Parser(tokens)
statements = p.parse_top_level()

program = Program(statements)

with open("prog.c", "w") as f:
    f.write(program.to_c())
