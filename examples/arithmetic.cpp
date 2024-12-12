#include "result.h"
#include <iostream>
#include <string>

using MyType = Result<int, std::string>;

MyType divide(int a, int b) {
  if (b == 0) {
    return MyType::Err("Division by zero");
  }
  return MyType::Ok(a / b);
}

int main() {
  auto result = divide(10, 2);
  if (result.is_ok()) {
    std::cout << "Result: " << result.unwrap() << "\n";
  } else {
    std::cout << "Error: " << result.unwrap_err() << "\n";
  }

  auto error_result = divide(10, 0);
  std::cout << "Handled Error: " << error_result.unwrap_or(-1) << "\n";

  return 0;
}
