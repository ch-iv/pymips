from abc import ABC, abstractmethod
from expressions.register import RegisterLiteral

class Constant(ABC):
    @abstractmethod
    def to_c(self) -> str:
        pass

class NumericConstant(Constant):
    def __init__(self, value: str):
        if not value.isnumeric():
            raise ValueError(f"Expected numeric constant, got {value}")

        self._value = value

    def to_c(self) -> str:
        return str(self._value)

class StringConstant(Constant):
    def __init__(self, value: str):
        if not value.startswith('"') or not value.endswith('"'):
            raise ValueError(f"Invalid string constant: {value}")

        self._value = value

    def to_c(self) -> str:
        return self.value

class RegisterConstant(Constant):
    def __init__(self, value: str):
        self._value = value.strip().removeprefix("$")

        if self._value not in RegisterLiteral.__members__:
            raise ValueError(f"Unknown register literal: {self._value}")

    def to_c(self) -> str:
        return self._value

class ArgConstant(Constant):
    def __init__(self, value: str, definition: bool):
        self._value = value
        self._definition = definition

    def to_c(self) -> str:
        base_name = self._value.replace("%", "")
        if self._definition:
            return f"Arg *arg_{base_name}"
        else:
            return f"arg_{base_name}"

class LabelConstant(Constant):
    def __init__(self, value: str):
        self._value = value.rstrip(":")

    def to_c(self) -> str:
        return self._value

class MockConstant(Constant):
    def __init__(self, value: str):
        self._value = value

    def to_c(self) -> str:
        return self._value