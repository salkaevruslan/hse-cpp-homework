#include "employees.h"
#include "bin_manip.h"
#include <cassert>
#include <cstring>

Employee::Employee() {
    _name = new char[101];
    assert(_name);
    _base_salary = 0;
}

Developer::Developer() : Employee() {
    _has_bonus = false;
}

SalesManager::SalesManager() : Employee() {
    _sold_nm = 0;
    _price = 0;
}

Employee::~Employee() {
    delete[] _name;
}

std::ostream &Developer::write_employee(std::ostream &os) const {
    os << "Developer" << '\n'
       << "Name:" << _name << '\n'
       << "Base salary: " << _base_salary << '\n';
    if (_has_bonus) os << "Has bonus: +" << '\n';
    else os << "Has bonus: -" << '\n';
    return os;
}


std::istream &Developer::read_employee(std::istream &is) {
    is >> _name
       >> _base_salary
       >> _has_bonus;
    return is;
}

std::ifstream &Developer::read_employee_binary(std::ifstream &is) {
    is >> read_c_str(_name, 100)
       >> read_le_int32(_base_salary)
       >> read_bool(_has_bonus);
    return is;
}

std::ofstream &Developer::write_employee_binary(std::ofstream &os) const {
    os << write_le_int32(static_cast<int>(EmployeeTypes::Developer))
       << write_c_str(_name)
       << write_le_int32(_base_salary)
       << write_bool(_has_bonus);
    return os;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) {
        salary += 1000;
    }
    return salary;
}

std::ostream &SalesManager::write_employee(std::ostream &os) const {
    os << "SalesManager" << '\n'
       << "Name:" << _name << '\n'
       << "Base salary: " << _base_salary << '\n'
       << "Sold items: " << _sold_nm << '\n'
       << "Item price: " << _price << '\n';
    return os;
}

std::istream &SalesManager::read_employee(std::istream &is) {
    is >> _name
       >> _base_salary
       >> _sold_nm
       >> _price;
    return is;
}

std::ifstream &SalesManager::read_employee_binary(std::ifstream &is) {
    is >> read_c_str(_name, 100)
       >> read_le_int32(_base_salary)
       >> read_le_int32(_sold_nm)
       >> read_le_int32(_price);
    return is;
}

std::ofstream &SalesManager::write_employee_binary(std::ofstream &os) const {
    os << write_le_int32(static_cast<int>(EmployeeTypes::SalesManager))
       << write_c_str(_name)
       << write_le_int32(_base_salary)
       << write_le_int32(_sold_nm)
       << write_le_int32(_price);
    return os;
}


int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}


std::ostream &operator<<(std::ostream &os, const Employee &e) {
    return e.write_employee(os);
}

std::ofstream &operator<<(std::ofstream &os, const Employee &e) {
    return e.write_employee_binary(os);
}

std::istream &operator>>(std::istream &is, Employee &e) {
    return e.read_employee(is);
}

std::ifstream &operator>>(std::ifstream &is, Employee &e) {
    return e.read_employee_binary(is);
}

EmployeesArray::EmployeesArray() {
    _employees = std::vector<Employee *>();
    _employees_number = 0;
}

EmployeesArray::~EmployeesArray() {
    for (int index = 0; index < _employees_number; ++index) {
        delete _employees[index];
    }
}

std::ostream &EmployeesArray::write_employee_array(std::ostream &os) const {
    for (int index = 0; index < _employees_number; ++index) {
        os << (index + 1) << ". ";
        (*_employees[index]).write_employee(os);
    }
    os << "== Total Salary: " << total_salary() << "\n\n";
    return os;
}

std::ofstream &EmployeesArray::write_employee_array_binary(std::ofstream &os) const {
    os << write_le_int32(_employees_number);
    for (int index = 0; index < _employees_number; ++index) {
        (*_employees[index]).write_employee_binary(os);
    }
    return os;
}

int EmployeesArray::total_salary() const {
    int result = 0;
    for (int index = 0; index < _employees_number; ++index) {
        result += _employees[index]->salary();
    }
    return result;
}

void EmployeesArray::add(Employee *e) {
    assert(e);
    ++_employees_number;
    _employees.push_back(e);
}

std::ostream &operator<<(std::ostream &os, const EmployeesArray &e) {
    return e.write_employee_array(os);
}

std::ofstream &operator<<(std::ofstream &os, const EmployeesArray &e) {
    return e.write_employee_array_binary(os);
}



