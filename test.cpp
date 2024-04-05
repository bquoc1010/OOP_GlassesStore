#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "utils.h"

using namespace std;

class Person {
public:
    string id;
    string name;

    Person(const string& id, const string& name) : id(id), name(name) {}
};

void saveObjectsToFile(const vector<Person>& objects, const string& filename) {
    ofstream file(filename, ios::app);  // Open in append mode
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& obj : objects) {
        file << obj.id << "\t" << obj.name << "\n";
    }

    file.close();
}

vector<Person> readObjectsFromFile(const string& filename) {
    vector<Person> objects;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for reading: " << filename << endl;
        return objects;
    }

    string line;
    // Skip the header line
    getline(file, line);
    while (getline(file, line)) {
        size_t pos = line.find('\t');
        if (pos != string::npos) {
            string id = line.substr(0, pos);
            string name = line.substr(pos + 1);
            objects.emplace_back(id, name);
        }
    }

    file.close();
    return objects;
}

Person findPersonByID(const string& targetID, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for reading: " << filename << endl;
        return Person("", "");  // Return an empty person if file cannot be opened
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find('\t');
        if (pos != string::npos) {
            string id = line.substr(0, pos);
            string name = line.substr(pos + 1);
            if (id == targetID) {
                file.close();
                return Person(id, name);
            }
        }
    }

    file.close();
    return Person("", "");  // Return an empty person if ID is not found
}

int main() {
    // vector<Person> persons = {
    //     {"01", "test 1"},
    //     {"02", "test 2"},
    //     {"04", "test 4"}
    // };

    // // Save objects to file
    // saveObjectsToFile(persons, "persons.txt");
    // cout << "Objects saved to persons.txt" << endl;

    // // Read objects from file
    // vector<Person> loadedPersons = readObjectsFromFile("persons.txt");
    // cout << "Loaded persons:\n";
    // for (const auto& person : loadedPersons) {
    //     cout << "ID: " << person.id << ", Name: " << person.name << endl;
    // }

    // Person newPerson("03", "test 3");

    // // Append the new person to the file
    // saveObjectsToFile({newPerson}, "persons.txt");
    // cout << "New person added to persons.txt" << endl;
    string test;
    // cout << stob(test);
    cout << getCurrentDate();
    return 0;
}
