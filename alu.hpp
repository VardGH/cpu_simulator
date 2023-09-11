#ifndef ALU_HPP_
#define ALU_HPP_

#include <string>

class CPU;

class ALU
{
public:
    ALU(CPU* parent_cpu);
    ~ALU() = default;

public:
    void _mov(const std::string& op1, const std::string& op2); // move data
    void _add(const std::string& op1, const std::string& op2); // add two operands
    void _sub(const std::string& op1, const std::string& op2); // subtract op2 from op1
    void _mul(const std::string& op1, const std::string& op2); // multiply op1 by op2
    void _div(const std::string& op1, const std::string& op2); // divide op1 by op2
    void _and(const std::string& op1, const std::string& op2); // bitwise AND 
    void _or(const std::string& op1, const std::string& op2);  // bitwise OR 
    void _not(const std::string& op); // bitwise NOT 

    void _inc(const std::string& op); // increment an operand
    void _dec(const std::string& op); // dicrement an operand

    // comparison Operations
    void _cmp(const std::string& op1, const std::string& op2); // compare two operands

    // jump Operations
    void _jmp(const std::string& label); // unconditional jump
    void _jg(const std::string& label);  // jump if greater
    void _jl(const std::string& label);  // jump if less
    void _je(const std::string& label);  // jump if equal
    void _jge(const std::string& label); // jump if greater or equal
    void _jle(const std::string& label); // jump if less or equal

    void _print(const std::string& reg); // print the value of a register

private:
    CPU* m_cpu;
};

#endif // ALU_HPP_