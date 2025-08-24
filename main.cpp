#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <random>
#include <sstream>
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
  auto now = std::chrono::system_clock::now();
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

  char timeBuffer[80];
  std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S",
                std::localtime(&currentTime));
  std::string timestampStr(timeBuffer);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(100, 999);
  int randomNum = dis(gen);

  std::stringstream idStream;
  idStream << currentTime << "-" << randomNum;
  std::string idStr = idStream.str();

  json newEntry = {
      {"id", idStr}, {"timestamp", timestampStr}, {"content", content}};

  std::vector<json> entries;
  std::ifstream inFile("journal.json");
  if (inFile.is_open()) {
    json existingData;
    inFile >> existingData;
    inFile.close();

    if (existingData.is_array()) {
      entries = existingData.get<std::vector<json>>();
    }
  }

  entries.push_back(newEntry);

  std::ofstream outFile("journal.json");
  outFile << json(entries).dump(2);
  outFile.close();

  std::cout << "Entry added with ID: " << idStr << std::endl;
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
      const auto &entry = journalData[i];
      std::cout << "Entry #" << (i + 1) << ":" << std::endl;

      if (entry.contains("content") && entry["content"].is_string()) {
        std::cout << "  Content: " << entry["content"].get<std::string>()
                  << std::endl;
      } else {
        std::cout << "  Content: (Invalid format)" << std::endl;
      }

      std::cout << std::endl;
    }
    std::cout << "Total entries: " << journalData.size() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Error reading journal file: " << e.what() << std::endl;
    std::cout << "No valid journal entries found." << std::endl;
  }
}

void showUsage(const std::string &appName) {
  std::cerr << "Usage: " << appName << " <command> [arguments]" << std::endl;
  std::cerr << "Commands:" << std::endl;
  std::cerr << "  add <content>    Add a new journal entry." << std::endl;
  std::cerr << "  list             List all journal entries." << std::endl;
}
