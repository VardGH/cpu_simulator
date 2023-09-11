#ifndef CPU_HPP_
#define CPU_HPP_

#include "alu.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

class CPU 
{
public:
    CPU();
    ~CPU() = default;

public:
    void load_from_file(const std::string& file_name); // fetch instructions from a file
    void execute(); // execute loaded instructions

    void print_memory() const; // print memory 
    void print_registers() const; // print registers
    void print_labels() const; // print labels

    int get_register(const std::string& register_name) const; // get register value by name
    void set_register(const std::string& register_name, const int value); // set register value by name
    void set_register(const std::string& register_name1, const std::string& register_name2); 

    int get_cmp_flag() const; // get comparison flag value
    void set_cmp_flag(const int value); // set comparison flag value

    int get_label(const std::string& label) const; // get the address of a label in memory
    bool is_register(const std::string& operand) const; // check register name
    int get_ip() const; // get the instruction pointer value
    void set_ip(const int ip); // set the instruction pointer value

private:
    void initialize_instructions(); // initialize instructions
    void initialize_registers(); // initialize registers
    std::string trim(const std::string& str); // trim whitespace from a string
    bool is_one_operand_instruction(const std::string& instruction) const; // check if an instruction is one-operand

private:
    int m_cmp_flag;
    int m_ip;
    ALU m_alu;
    std::vector<std::vector<std::string>> m_memory;
    std::unordered_map<std::string, int> m_labels;
    std::unordered_map<std::string, std::function<void(const std::string&, const std::string&)>> m_instruction_set;
    std::unordered_map<std::string, int> m_registers;
};

#endif // CPU_HPP_