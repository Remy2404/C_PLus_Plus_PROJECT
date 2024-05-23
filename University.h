#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>

class University {
public:
    University(); // Constructor
    University(const std::string& name, int foundationYear);

    void DisplayInfo() const;

private:
    std::string name;
    int foundationYear;
};
#endif
