#include "result.h"
#include <iostream>
#include <string>

Result<int, std::string> parse_number(const std::string &input) {
  try {
    return Result<int, std::string>::Ok(std::stoi(input));
  } catch (...) {
    return Result<int, std::string>::Err("Invalid number.");
  }
}

Result<int, std::string> handle_parse_error(const std::string &error) {
  std::cerr << "Error logged: " << error << "\n";
  return Result<int, std::string>::Ok(0);
}

int main() {
  auto safe_result = parse_number("not_a_number").or_else(handle_parse_error);

  std::cout << "Final Value: " << safe_result.unwrap() << "\n";

  return 0;
}
