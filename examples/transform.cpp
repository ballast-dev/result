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

int main() {
  auto number_result = parse_number("42").map([](int num) { return num * 2; });

  if (number_result.is_ok()) {
    std::cout << "Transformed Result: " << number_result.unwrap() << "\n";
  } else {
    std::cout << "Error: " << number_result.unwrap_err() << "\n";
  }

  return 0;
}
