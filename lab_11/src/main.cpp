#include "employees.h"
#include "bin_manip.h"
#include <iostream>
#include <string>
#include <cassert>

Employee *create_new_employee(int type) {
    if (type == static_cast<int>(EmployeeTypes::Developer)) {
        Developer *developer = new Developer();
        return developer;
    }
    if (type == static_cast<int>(EmployeeTypes::SalesManager)) {
        SalesManager *sales_manager = new SalesManager();
        return sales_manager;
    }
    return nullptr;
}

void add_new_employee(EmployeesArray &employees_array) {
    int type;
    std::cin >> type;
    Employee *e = create_new_employee(type);
    assert(e);
    std::cin >> *e;
    employees_array.add(e);
}

void load_file(EmployeesArray &employees_array) {
    std::string file_name;
    std::cin >> file_name;
    std::ifstream input_stream;
    input_stream.open(file_name, std::ios::binary);
    assert(input_stream);
    int32_t employees_number = 0;
    input_stream >> read_le_int32(employees_number);
    assert(employees_number >= 0);
    int type;
    for (int32_t i = 0; i < employees_number; ++i) {
        input_stream >> read_le_int32(type);
        Employee *e = create_new_employee(type);
        assert(e);
        input_stream >> *e;
        employees_array.add(e);
    }
}

void save_to_file(EmployeesArray &employees_array) {
    std::string file_name;
    std::cin >> file_name;
    std::ofstream output_stream;
    output_stream.open(file_name, std::ios::binary);
    assert(output_stream);
    output_stream << employees_array;
}

int main() {
    EmployeesArray employees_array;
    std::string s;
    while (true) {
        std::cin >> s;
        if (s == "add") {
            add_new_employee(employees_array);
            continue;
        }
        if (s == "load") {
            load_file(employees_array);
            continue;
        }
        if (s == "save") {
            save_to_file(employees_array);
            continue;
        }
        if (s == "list") {
            std::cout << employees_array;
            continue;
        }
        if (s == "exit") {
            break;
        }
        std::cout << "Wrong command\n";
	break;
    }
    return 0;
}

