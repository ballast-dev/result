#include "result.h"
#include <iostream>
#include <string>

Result<std::string, std::string> read_file(const std::string &filename) {
  if (filename == "exists.txt") {
    return Result<std::string, std::string>::Ok("File contents here.");
  }
  return Result<std::string, std::string>::Err("File not found.");
}

int main() {
  auto file_result = read_file("exists.txt");
  if (file_result.is_ok()) {
    std::cout << "File read successfully: " << file_result.unwrap() << "\n";
  } else {
    std::cout << "Error: " << file_result.unwrap_err() << "\n";
  }

  auto non_existent =
      read_file("missing.txt").unwrap_or("Default file contents.");
  std::cout << "Fallback: " << non_existent << "\n";

  return 0;
}
