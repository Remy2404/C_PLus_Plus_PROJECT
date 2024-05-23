#ifndef CUP_H
#define CUP_H

#include <string>

class Cup {
public:
    Cup(); // Constructor
    Cup(const std::string& name, const std::string& material);

    void ShowInfo() const;

private:
    std::string name;
    std::string material;
};

#endif
