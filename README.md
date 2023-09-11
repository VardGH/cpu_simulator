# CPU simulator

This project is a CPU emulator written in C++. It simulates the operation of a simple CPU with registers, memory, and a set of instructions. You can use this simulator to load programs, execute instructions, and observe the state of registers and memory.

## Features

- **Instruction Set**: The simulator supports a variety of instructions, including arithmetic operations, conditional jumps, and register manipulation.

- **Registers**: The CPU has a set of registers (R1 to R10) that can be used to store and manipulate data.

- **Memory**: Instructions and data are stored in memory, which can be loaded from a file.

- **Labels**: You can define labels in your code and use them as targets for jump instructions.

- **Comparison Flag**: The CPU maintains a comparison flag (cmp_flag) that can be used for conditional jumps.

- **ALU (Arithmetic Logic Unit)**: The ALU is responsible for performing arithmetic and logical operations on CPU registers. It is a separate class that interacts with the CPU.

## Usage

The simulator accepts the following commands:

- `load <file>`: Load a program from a file.
- `execute`: Execute the loaded program.
- `print memory`: Display the contents of memory.
- `print registers`: Show the values of CPU registers.
- `print labels`: Display the defined labels.

## ALU (Arithmetic Logic Unit)

The Arithmetic Logic Unit (ALU) is responsible for performing arithmetic and logical operations on CPU registers. It is a separate class that interacts with the CPU.

### ALU Instructions

- `_mov(op1, op2)`: Move the value from `op2` to `op1` in the CPU's registers.

- `_add(op1, op2)`: Add the values of `op1` and `op2` and store the result in `op1`.

- `_sub(op1, op2)`: Subtract the value of `op2` from `op1` and store the result in `op1`.

- `_mul(op1, op2)`: Multiply the values of `op1` and `op2` and store the result in `op1`.

- `_div(op1, op2)`: Divide the value of `op1` by `op2` and store the result in `op1`.

- `_and(op1, op2)`: Perform a bitwise AND operation between `op1` and `op2` and store the result in `op1`.

- `_or(op1, op2)`: Perform a bitwise OR operation between `op1` and `op2` and store the result in `op1`.

- `_not(op)`: Perform a bitwise NOT operation on `op` and store the result in `op`.

- `_inc(op)`: Increment the value in `op` by 1.

- `_dec(op)`: Decrement the value in `op` by 1.

- `_cmp(op1, op2)`: Compare the values of `op1` and `op2` and set the CPU's comparison flag.

- `_je(label)`: Jump to the specified `label` if the comparison flag is equal to 0.

- `_jg(label)`: Jump to the specified `label` if the comparison flag is greater than 0.

- `_jge(label)`: Jump to the specified `label` if the comparison flag is greater than or equal to 0.

- `_jle(label)`: Jump to the specified `label` if the comparison flag is less than or equal to 0.

- `_jl(label)`: Jump to the specified `label` if the comparison flag is less than 0.

- `_jmp(label)`: Jump unconditionally to the specified `label`.

- `_print(reg)`: Print the value of the specified register.
