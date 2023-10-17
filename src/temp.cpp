#include "temp.hpp"

Student::Student(const std::string firstName_, const std::string lastName_) {
    this->firstName = firstName_;
    this->lastName = lastName_;
}

std::string Student::getFirstName() const {
    return firstName;
}
std::string Student::getLastName() const {
    return lastName;
}
std::string Student::getFullName() const {
    return firstName + " " + lastName;
}
