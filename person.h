#include <iostream>

using namespace std;

class Person {
private:
    string id;
    string name;
    string gender;
    string phoneNumber;
    string birthday;
public:
    Person() {};

    Person(string id, string name, string gender, string phoneNumber, string birthday) {
        this->id = id;
        this-> name = name;
        this->gender = gender;
        this->phoneNumber = phoneNumber;
        this->birthday = birthday;
    }

    ~Person() {};

    string getId();

    void setId(string id);

    string getName();
    
    void setName(string name);

    string getGender();

    void setGender(string gender) ;

    string getPhoneNumber();

    void setPhoneNumber(string phoneNumber);

    string getBirthday();

    void setBirthday(string birthday);
};

string Person::getId() {
    return this->id;
}

void Person::setId(string id) {
    this->id = id;
}

string Person::getName() {
    return this->name;
}

void Person::setName(string name) {
    this->name = name;
}
string Person::getGender() {
    return this->gender;
}

void Person::setGender(string gender) {
    this->gender = gender;
}
string Person::getPhoneNumber() {
    return this->id;
}

void Person::setPhoneNumber(string id) {
    this->id = id;
}

string Person::getBirthday() {
    return this->birthday;
}

void Person::setBirthday(string birthday) {
    // // Regular expression pattern for "dd/MM/yyyy"
    // regex pattern("\\b(0[1-9]|[1-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/((19|20)\\d\\d)\\b");

    // // Check if the date string matches the pattern
    // bool isValidDate = regex_match(birthday, pattern);

    // if (!isValidDate) cout << "Invalid date string\n";
    // else this->birthday = birthday;
    this->birthday = birthday;
}