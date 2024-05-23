#include <iostream>

class Employee {
private:
    double salary;
    int hoursOfWork;

public:
    
    void getInfo(double initialSalary, int hoursWorked) {
        salary = initialSalary;
        hoursOfWork = hoursWorked;
    }
    void AddSal() {
        if (salary < 500) {
            salary += 10;
        }
    }
    void AddWork() {
        if (hoursOfWork > 6) {
            salary += 5;
        }
    }

    void printSalary() const {
        std::cout << "Final Salary: $" << salary << std::endl;
    }
};

int main() {
    Employee emp;

    double initialSalary;
    int hoursWorked;
    
    std::cout << "Enter initial salary: ";
    std::cin >> initialSalary;

    std::cout << "Enter hours of work per day: ";
    std::cin >> hoursWorked;

    emp.getInfo(initialSalary, hoursWorked);

    
    emp.AddSal();
    emp.AddWork();

    emp.printSalary();

    return 0;
}
 