#include <iostream>
#include <ctime>
#include <filesystem>
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std;

string getCurrentDate() {
    time_t currentDate = time(0);
    return ctime(&currentDate);
}

bool isFileEmpty(const string& filename) {
    try {
        // Get the file size
        uintmax_t fileSize = filesystem::file_size(filename);
        return fileSize == 0;
    } catch (const filesystem::filesystem_error& e) {
        cerr << "Error checking file size: " << e.what() << endl;
        return false;
    }
}

std::string left_trim(const std::string& str) {
    int numStartSpaces = 0;
    for (char ch : str) {
        if (!std::isspace(ch))
            break;
        numStartSpaces++;
    }
    return str.substr(numStartSpaces);
}

// Right trim the given string
std::string right_trim(const std::string& str) {
    int numEndSpaces = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        if (!std::isspace(str[i]))
            break;
        numEndSpaces++;
    }
    return str.substr(0, str.length() - numEndSpaces);
}

string trim(string& str) {
    return right_trim(left_trim(str));
}

bool stob(string str) {
    return str != "0";
}