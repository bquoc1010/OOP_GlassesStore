#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // For setw()

class Person {
public:
    std::string id;
    std::string name;

    Person(const std::string& _id, const std::string& _name) : id(_id), name(_name) {}
};

void save_to_file(const std::string& filename, const std::vector<Person>& people) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const Person& person : people) {
        // Format the ID and Name fields
        std::string formatted_id = person.id;
        std::string formatted_name = person.name;
        formatted_id.resize(20, ' ');
        formatted_name.resize(50, ' ');

        file << formatted_id << formatted_name << '\n';
    }

    file.close();
}

std::vector<Person> read_from_file(const std::string& filename) {
    std::vector<Person> people;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return people;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string id = line.substr(0, 20);
        std::string name = line.substr(20, 50);
        people.emplace_back(id, name);
    }

    file.close();
    return people;
}

int main() {
    std::vector<Person> people = {
        {"01", "test 1"},
        {"02", "test 2"}
    };

    // Save to file
    save_to_file("people.txt", people);
    std::cout << "Data saved to people.txt." << std::endl;

    // Read from file
    std::vector<Person> loaded_people = read_from_file("people.txt");
    for (const Person& person : loaded_people) {
        std::cout << "ID: " << person.id << ", Name: " << person.name << std::endl;
    }

    return 0;
}