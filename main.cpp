#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void addEntry(const std::string &content);
void showUsage(const std::string &appName);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    showUsage(argv[0]);
    return 1;
  }

  std::string command = argv[1];

  if (command == "add" && argc > 2) {
    addEntry(argv[2]);
  } else if (command == "add") {
    std::cerr << "Error: 'add' command requires content." << std::endl;
    showUsage(argv[0]);
    return 1;
  } else {
    std::cerr << "Error: Unknown command '" << command << "'" << std::endl;
    showUsage(argv[0]);
    return 1;
  }

  return 0;
}

void addEntry(const std::string &content) {
  std::ofstream journalFile("memos.txt", std::ios::app);
  if (journalFile.is_open()) {
    journalFile << content << std::endl;
    journalFile.close();
    std::cout << "Entry added successfully." << std::endl;
  } else {
    std::cerr << "Error: Unable to open journal file." << std::endl;
  }
}

void showUsage(const std::string &appName) {
  std::cerr << "Usage: " << appName << " <command> [arguments]" << std::endl;
  std::cerr << "Commands:" << std::endl;
  std::cerr << "  add \"<content>\"    Add a new journal entry." << std::endl;
}
