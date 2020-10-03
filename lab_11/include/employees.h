#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>

class Employee {
public:
    Employee();

    Employee(Employee &other) = delete;

    Employee &operator=(Employee &other) = delete;

    virtual ~Employee();

    virtual std::istream &read_employee(std::istream &) = 0;

    virtual std::ostream &write_employee(std::ostream &) const = 0;

    virtual std::ifstream &read_employee_binary(std::ifstream &) = 0;

    virtual std::ofstream &write_employee_binary(std::ofstream &) const = 0;

    virtual int salary() const = 0;

protected:
    char *_name;
    int32_t _base_salary;
};

std::istream &operator>>(std::istream &is, Employee &e);

std::ostream &operator<<(std::ostream &os, const Employee &e);

std::ifstream &operator>>(std::ifstream &is, Employee &e);

std::ofstream &operator<<(std::ofstream &os, const Employee &e);

class Developer final : public Employee {
public:
    Developer();

    Developer(Developer &other) = delete;

    Developer &operator=(Developer &other) = delete;

    ~Developer() override = default;

    int salary() const override;

    std::istream &read_employee(std::istream &is) override;

    std::ostream &write_employee(std::ostream &os) const override;

    std::ifstream &read_employee_binary(std::ifstream &is) override;

    std::ofstream &write_employee_binary(std::ofstream &os) const override;

private:
    bool _has_bonus;
};


class SalesManager final : public Employee {
public:
    SalesManager();

    SalesManager(SalesManager &other) = delete;

    SalesManager &operator=(SalesManager &other) = delete;

    ~SalesManager() override = default;

    int salary() const override;

    std::istream &read_employee(std::istream &is) override;

    std::ostream &write_employee(std::ostream &os) const override;

    std::ifstream &read_employee_binary(std::ifstream &is) override;

    std::ofstream &write_employee_binary(std::ofstream &os) const override;

private:
    int32_t _sold_nm, _price;

};

enum class EmployeeTypes : int {
    Developer = 1,
    SalesManager = 2
};

class EmployeesArray final {
public:
    EmployeesArray();

    EmployeesArray(EmployeesArray &other) = delete;

    EmployeesArray &operator=(EmployeesArray &other) = delete;

    ~EmployeesArray();

    void add(Employee *e);

    int total_salary() const;

    std::ostream &write_employee_array(std::ostream &os) const;

    std::ofstream &write_employee_array_binary(std::ofstream &os) const;

private:
    std::vector<Employee *> _employees;
    int _employees_number;

};

std::ostream &operator<<(std::ostream &os, const EmployeesArray &e);

std::ofstream &operator<<(std::ofstream &is, const EmployeesArray &e);

#endif

