#ifndef MOONLANDER_TEMP_HPP
#define MOONLANDER_TEMP_HPP

#endif //MOONLANDER_TEMP_HPP

#include <string>

class Student {
private:
    std::string firstName;
    std::string lastName;
public:
    Student(const std::string firstName_, const std::string lastName_);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
};