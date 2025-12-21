from expressions.expression import Expression, IncludeExpression, MacroExpression, MainWrapperExpression

class Program:
    def __init__(self, statements: list[Expression]):
        self.statements = statements
        self.hoist_macros_and_includes()

    def bubble_up_nested_macros(self, macro: MacroExpression) -> list[Expression]:
        for statement in macro.body:
            if isinstance(child_macro := statement, MacroExpression):
                self.bubble_up_nested_macros(child_macro)
                self.statements.append(child_macro)
                macro.body.remove(child_macro)

    def hoist_macros_and_includes(self) -> list[Expression]:
        # Nested macros are bubbled up to the outer layer.
        for statement in self.statements:
            if isinstance(macro := statement, MacroExpression):
                self.bubble_up_nested_macros(macro)

        # Filter statements into relevant categories.
        includes = []
        macros = []
        other = []
        for statement in self.statements:
            if isinstance(statement, IncludeExpression):
                includes.append(statement)
            elif isinstance(statement, MacroExpression):
                macros.append(statement)
            else:
                other.append(statement)

        # Wrap all non macro and non include statements into a main block.
        main_block = MainWrapperExpression(other, debug_mode=True)

        self.statements = [*includes, *macros, main_block]

    def to_c(self) -> str:
        source = "#include <libmips.cpp>\n"
        source += "\n".join([statement.to_c() for statement in self.statements])
        return source