#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

void addEntry(const std::string &content);
void listEntries();
void showUsage(const std::string &appName);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    showUsage(argv[0]);
    return 1;
  }

  std::string command = argv[1];

  if (command == "add") {
    if (argc <= 2) {
      std::cerr << "Error: 'add' command requires content." << std::endl;
      showUsage(argv[0]);
      return 1;
    }
    addEntry(argv[2]);
  } else if (command == "list") {
    if (argc != 2) {
      std::cerr << "Error: 'list' command requires no argument." << std::endl;
      showUsage(argv[0]);
      return 1;
    }
    listEntries();
  } else {
    std::cerr << "Error: Unknown command '" << command << "'" << std::endl;
    showUsage(argv[0]);
    return 1;
  }

  return 0;
}

void addEntry(const std::string &content) {
  json journalData;
  std::ifstream inputFile("journal.json");
  if (inputFile.is_open()) {
    try {
      inputFile >> journalData;
    } catch (const std::exception &e) {
      journalData = json::array();
    }
    inputFile.close();
  } else {
    journalData = json::array();
  }
  json newEntry = {{"content", content}};
  journalData.push_back(newEntry);
  std::ofstream outputFile("journal.json");
  if (outputFile.is_open()) {
    outputFile << journalData.dump(2);
    outputFile.close();
    std::cout << "Entry added successfully." << std::endl;
  } else {
    std::cerr << "Error: Unable to open journal file." << std::endl;
  }
}

void listEntries() {
  std::ifstream inputFile("journal.json");
  
  if (!inputFile.is_open()) {
    std::cout << "No journal entries found." << std::endl;
    return;
  }
  try {
    json journalData;
    inputFile >> journalData;
    inputFile.close();
    if (!journalData.is_array() || journalData.empty()) {
      std::cout << "No journal entries found." << std::endl;
      return;
    }
    std::cout << "Journal Entries:" << std::endl;
    std::cout << "================\n" << std::endl;
    for (size_t i = 0; i < journalData.size(); ++i) {
      const auto& entry = journalData[i];
      std::cout << "Entry #" << (i + 1) << ":" << std::endl;
      
      if (entry.contains("content") && entry["content"].is_string()) {
        std::cout << "  Content: " << entry["content"].get<std::string>() << std::endl;
      } else {
        std::cout << "  Content: (Invalid format)" << std::endl;
      }
      
      std::cout << std::endl;
    }
    std::cout << "Total entries: " << journalData.size() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error reading journal file: " << e.what() << std::endl;
    std::cout << "No valid journal entries found." << std::endl;
  }
}

void showUsage(const std::string &appName) {
  std::cerr << "Usage: " << appName << " <command> [arguments]" << std::endl;
  std::cerr << "Commands:" << std::endl;
  std::cerr << "  add \"<content>\"    Add a new journal entry." << std::endl;
  std::cerr << "  list             List all journal entries." << std::endl;
}
