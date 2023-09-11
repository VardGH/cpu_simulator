#include "cpu.hpp"
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <algorithm> 

CPU::CPU()
    : m_cmp_flag {0}
    , m_ip {0}
    , m_alu {this}
{
    initialize_instructions();
    initialize_registers();
}

// Initialize the instruction set with lambda functions
void CPU::initialize_instructions()
{
    m_instruction_set["NOT"] = [this](const std::string& op1, const std::string& op2) { m_alu._not(op1); };
    m_instruction_set["MOV"] = [this](const std::string& op1, const std::string& op2) { m_alu._mov(op1, op2); };
    m_instruction_set["ADD"] = [this](const std::string& op1, const std::string& op2) { m_alu._add(op1, op2); };
    m_instruction_set["SUB"] = [this](const std::string& op1, const std::string& op2) { m_alu._sub(op1, op2); };
    m_instruction_set["MUL"] = [this](const std::string& op1, const std::string& op2) { m_alu._mul(op1, op2); };
    m_instruction_set["DIV"] = [this](const std::string& op1, const std::string& op2) { m_alu._div(op1, op2); };
    m_instruction_set["AND"] = [this](const std::string& op1, const std::string& op2) { m_alu._and(op1, op2); };
    m_instruction_set["OR"]  = [this](const std::string& op1, const std::string& op2) { m_alu._or(op1, op2); };
    
    m_instruction_set["INC"] = [this](const std::string& op1, const std::string& op2) { m_alu._inc(op1); };
    m_instruction_set["DEC"] = [this](const std::string& op1, const std::string& op2) { m_alu._dec(op1); };

    m_instruction_set["CMP"] = [this](const std::string& op1, const std::string& op2) { m_alu._cmp(op1, op2); };
    m_instruction_set["JMP"] = [this](const std::string& label1, const std::string& label2) { m_alu._jmp(label1); };
    m_instruction_set["JG"]  = [this](const std::string& label1, const std::string& label2) { m_alu._jg(label1); };
    m_instruction_set["JL"]  = [this](const std::string& label1, const std::string& label2) { m_alu._jl(label1); };
    m_instruction_set["JE"]  = [this](const std::string& label1, const std::string& label2) { m_alu._je(label1); };

    m_instruction_set["PRINT"] = [this](const std::string& reg1, const std::string& reg2) { m_alu._print(reg1); };
}

// Initialize CPU registers with default values
void CPU::initialize_registers()
{
    m_registers["R1"] = 0;
    m_registers["R2"] = 0;
    m_registers["R3"] = 0;
    m_registers["R4"] = 0;
    m_registers["R5"] = 0;
    m_registers["R6"] = 0;
    m_registers["R7"] = 0;
    m_registers["R8"] = 0;
    m_registers["R9"] = 0;
    m_registers["R10"] = 0;
}

// Set the comparison flag
void CPU::set_cmp_flag(const int value)
{
    m_cmp_flag = value;
}

// Get the value of the comparison flag
int CPU::get_cmp_flag() const
{
    return m_cmp_flag;
}

// Remove whitespace
std::string CPU::trim(const std::string& str) 
{
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

// Read and parse file - fetch
void CPU::load_from_file(const std::string& file_name) 
{
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    std::string line {};
    int address {};

    while (std::getline(file, line)) {
        // remove whitespace
        line = trim(line);

        // skip empty lines
        if (line.empty()) {
            continue;
        }

        // check if the line is a label
        bool is_label = false;
        if (line.front() == ':') {
            is_label = true;
            // remove the ':'
            std::string label = line.substr(1, line.length());
            m_labels[label] = address; // store label address
        } else {
            int comma_pos = line.find(',');
            if (comma_pos == std::string::npos) {
                throw std::runtime_error("Failed to open file: " + file_name);
            }
            line.erase(std::remove(line.begin(), line.end(), ','), line.end());

            // separate the instruction and operands
            std::istringstream iss(line);
            std::string instruction;
            std::string op1{};
            std::string op2{};
            iss >> instruction >> op1 >> op2;

            // check if the line contains an instruction with one operand
            if (!iss && !is_label) {
                if (is_one_operand_instruction(instruction)) {
                    op2 = "";
                } else {
                    throw std::runtime_error("Invalid instruction in file: " + line);
                }
            }

            // store instruction and operands in m_memory
            std::vector<std::string> instruction_tokens = {instruction, op1, op2};
            m_memory.push_back(instruction_tokens);
            ++address;
        }
    }
    file.close();
}

// Check if an instruction is one-operand
bool CPU::is_one_operand_instruction(const std::string& instruction) const
{
    std::vector<std::string> instructions = { "INC", "DEC", "JMP", "JG", "JL", "JE", "JGE", "JLE", "PRINT"};

    return std::find(instructions.begin(), instructions.end(), instruction) != instructions.end();
}

// Set the value of a register
void CPU::set_register(const std::string& register_name, const int value) 
{
    // check register_name is valid
    if (register_name.size() >= 2 && register_name[0] == 'R' && std::isdigit(register_name[1])) {
        m_registers[register_name] = value;
    } else {
        throw std::runtime_error("Invalid register name: " + register_name);
    }
}

// Set the value of a register
void CPU::set_register(const std::string& register_name1, const std::string& register_name2) 
{
    // check register_name is valid
    if (register_name1.size() >= 2 && register_name1[0] == 'R' && std::isdigit(register_name1[1])) {
        auto value = m_registers[register_name2];
        m_registers[register_name1] = value;
    } else {
        throw std::runtime_error("Invalid register name: " + register_name1);
    }
}

// Get the value of a register
int CPU::get_register(const std::string& register_name) const 
{
    // check egister_name is valid 
    if (register_name.size() >= 2 && register_name[0] == 'R' && std::isdigit(register_name[1])) {
        // find the register and return its value
        auto it = m_registers.find(register_name);
        if (it != m_registers.end()) {
            return it->second;
        } else {
            throw std::runtime_error("Register not found: " + register_name);
        }
    } else {
       throw std::runtime_error("Invalid register name: " + register_name);
    }

    return 0; // default value
}

// Get the label address
int CPU::get_label(const std::string& label) const
{
    auto label_it = m_labels.find(label);

    if (label_it != m_labels.end()) {
        return label_it->second;
    } else {
        std::cerr << "Label not found: " << label << std::endl;
        return -1; // if label not found
    }
}

// Print memory 
void CPU::print_memory() const 
{
    for (int i = 0; i < m_memory.size(); ++i) {
        std::cout << "Address " << i << ": ";
        for (const std::string& token : m_memory[i]) {
            std::cout << token << " ";
        }
        std::cout << std::endl;
    }
}

// Print registers 
void CPU::print_registers() const 
{
    std::cout << "Register Values:" << std::endl;
    for (const auto& elem : m_registers) {
        std::cout << elem.first << ": " << elem.second << std::endl;
    }

    std::cout << "cpm register: " << get_cmp_flag() << std::endl;
}

// Print labels
void CPU::print_labels() const
{
    std::cout << "Labels:" << std::endl;
    for (const auto& elem : m_labels) {
        std::cout << elem.first << ": " << elem.second << std::endl;
    }
}

// Execute loaded instructions
void CPU::execute() {
    while (m_ip >= 0 && m_ip < m_memory.size()) {
        const std::vector<std::string>& instruction = m_memory[m_ip];
        std::string opcode = instruction[0];

        if (m_instruction_set.find(opcode) != m_instruction_set.end()) {
            const std::string& op1 = instruction[1];
            const std::string& op2 = instruction[2];
            m_instruction_set[opcode](op1, op2);
        } else {
            throw std::runtime_error("Invalid instruction: " + opcode);
            return;
        }

        // check if a jump instruction was executed
        if (m_ip == get_ip()) {
            // no jump occurred, increment the instruction pointer
            set_ip(m_ip + 1);
        }

    }
}

// Set ip address
int CPU::get_ip() const
{
    return m_ip;
}

// Get ip address
void CPU::set_ip(const int ip)
{
    m_ip = ip;
}

// Check if an operand is a valid register name
bool CPU::is_register(const std::string& operand) const 
{
    if (operand.size() >= 2 && operand[0] == 'R') {
        for (int i = 1; i < operand.size(); ++i) {
            if (!std::isdigit(operand[i])) {
                return false; // invalid register
            }
        }
        return true; // valid register (r1 ... r10)
    }
    return false; // not a register
}