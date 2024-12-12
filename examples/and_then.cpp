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

Result<int, std::string> multiply_by_two(int num) {
  return Result<int, std::string>::Ok(num * 2);
}

int main() {
  auto chained_result = parse_number("21").and_then(multiply_by_two);

  if (chained_result.is_ok()) {
    std::cout << "Chained Result: " << chained_result.unwrap() << "\n";
  } else {
    std::cout << "Error: " << chained_result.unwrap_err() << "\n";
  }

  return 0;
}
