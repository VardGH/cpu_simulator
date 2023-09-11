#include "alu.hpp"
#include "cpu.hpp"
#include <iostream>

ALU::ALU(CPU* parent_cpu)
    : m_cpu(parent_cpu) 
{
}

// Move the value from op2 to op1 in the CPU's registers
void ALU::_mov(const std::string& op1, const std::string& op2)
{
    if (m_cpu->is_register(op2)) {
        m_cpu->set_register(op1, op2);
    } else {
        m_cpu->set_register(op1, stoi(op2));
    }
}

// Add the values of op1 and op2 and store the result in op1
void ALU::_add(const std::string& op1, const std::string& op2)
{   
    if (m_cpu->is_register(op2)) {
        int tmp = m_cpu->get_register(op1) + m_cpu->get_register(op2);
        m_cpu->set_register(op1, tmp);
    } else {
        int res = m_cpu->get_register(op1) + stoi(op2);
        m_cpu->set_register(op1, res);
    }
}

// Subtract the value of op2 from op1 and store the result in op1
void ALU::_sub(const std::string& op1, const std::string& op2)
{
    if (m_cpu->is_register(op2)) {
        int tmp = m_cpu->get_register(op1) - m_cpu->get_register(op2);
        m_cpu->set_register(op1, tmp);
    } else {
        int res = m_cpu->get_register(op1) - stoi(op2);
        m_cpu->set_register(op1, res);
    }
}

// Multiply the values of op1 and op2 and store the result in op1
void ALU::_mul(const std::string& op1, const std::string& op2)
{
    if (m_cpu->is_register(op2)) {
        int tmp = m_cpu->get_register(op1) * m_cpu->get_register(op2);
        m_cpu->set_register(op1, tmp);
    } else {
        int res = m_cpu->get_register(op1) * stoi(op2);
        m_cpu->set_register(op1, res);
    }
}

// Divide the value of op1 by op2 and store the result in op1
void ALU::_div(const std::string& op1, const std::string& op2)
{
    if (m_cpu->is_register(op2)) {
        int tmp = m_cpu->get_register(op1) / m_cpu->get_register(op2);
        m_cpu->set_register(op1, tmp);
    } else {
        int res = m_cpu->get_register(op1) / stoi(op2);
        m_cpu->set_register(op1, res);
    }
}

// Perform a bitwise AND operation between op1 and op2 and store the result in op1
void ALU::_and(const std::string& op1, const std::string& op2)
{
    if (m_cpu->is_register(op2)) {
        int tmp = m_cpu->get_register(op1) & m_cpu->get_register(op2);
        m_cpu->set_register(op1, tmp);
    } else {
        int res = m_cpu->get_register(op1) & stoi(op2);
        m_cpu->set_register(op1, res);
    }
}

// Perform a bitwise OR operation between op1 and op2 and store the result in op1
void ALU::_or(const std::string& op1, const std::string& op2)
{
    if (m_cpu->is_register(op2)) {
        int tmp = m_cpu->get_register(op1) | m_cpu->get_register(op2);
        m_cpu->set_register(op1, tmp);
    } else {
        int res = m_cpu->get_register(op1) | stoi(op2);
        m_cpu->set_register(op1, res);
    }
}

// Perform a bitwise NOT operation on op and store the result in op
void ALU::_not(const std::string& op)
{
    int tmp = ~(m_cpu->get_register(op));
    m_cpu->set_register(op, tmp);
}

// Increment the value in op by 1
void ALU::_inc(const std::string& op)
{
    int tmp = m_cpu->get_register(op);
    m_cpu->set_register(op, ++tmp);
}

// Decrement the value in op by 1
void ALU::_dec(const std::string& op)
{
    int tmp = m_cpu->get_register(op);
    m_cpu->set_register(op, --tmp);
}

// Compare the values of op1 and op2 and set the CPU's comparison flag
void ALU::_cmp(const std::string& op1, const std::string& op2)
{
    int tmp1 = m_cpu->get_register(op1);
    int tmp2 {};
    if (m_cpu->is_register(op2)) {
        tmp2 = m_cpu->get_register(op2);
    } else {
        tmp2 = stoi(op2);
    }
    m_cpu->set_cmp_flag(tmp1 - tmp2);
}

// Jump to the specified label if the comparison flag is equal to 0
void ALU::_je(const std::string& label) 
{
    if (m_cpu->get_cmp_flag() == 0) {
        int jump_address = m_cpu->get_label(label);

        if (jump_address != -1) {
            m_cpu->set_ip(--jump_address);
        }
    } 
}

// Jump to the specified label if the comparison flag is greater than 0
void ALU::_jg(const std::string& label)
{
    if (m_cpu->get_cmp_flag() > 0) {
        int jump_address = m_cpu->get_label(label);
        if (jump_address != -1) {
            m_cpu->set_ip(--jump_address);
        }
    } 
}

// Jump to the specified label if the comparison flag is greater than or equal to 0
void ALU::_jge(const std::string& label)
{
    if (m_cpu->get_cmp_flag() >= 0) {
        int jump_address = m_cpu->get_label(label);

        if (jump_address != -1) {
            m_cpu->set_ip(--jump_address);
        }
    } 
}

// Jump to the specified label if the comparison flag is less than or equal to 0
void ALU::_jle(const std::string& label) 
{
    if (m_cpu->get_cmp_flag() <= 0) {
        int jump_address = m_cpu->get_label(label);

        if (jump_address != -1) {
            m_cpu->set_ip(--jump_address);
        }
    } 
}

// Jump to the specified label if the comparison flag is less than 0
void ALU::_jl(const std::string& label)
{
    if (m_cpu->get_cmp_flag() < 0) {
        int jump_address = m_cpu->get_label(label);

        if (jump_address != -1) {
            m_cpu->set_ip(--jump_address);
        }
    } 
}

// Jump unconditionally to the specified label
void ALU::_jmp(const std::string& label) 
{
    int jump_address = m_cpu->get_label(label);

    if (jump_address != -1) {
        m_cpu->set_ip(--jump_address);
    }
}

// Print the value of the specified register
void ALU::_print(const std::string& reg)
{
    std::cout << reg << " : " << m_cpu->get_register(reg) << std::endl;
}
