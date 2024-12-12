#include "result.h"
#include <iostream>
#include <string>

// Define an enum class for error categories
enum class ErrorCode { DivisionByZero, InvalidInput };

// A function that uses Result with an enum class for errors
Result<int, ErrorCode> safe_divide(int a, int b) {
  if (b == 0) {
    return Result<int, ErrorCode>::Err(ErrorCode::DivisionByZero);
  }
  return Result<int, ErrorCode>::Ok(a / b);
}

// Helper function to convert ErrorCode to a readable string
std::string error_code_to_string(ErrorCode code) {
  switch (code) {
  case ErrorCode::DivisionByZero:
    return "Division by zero.";
  case ErrorCode::InvalidInput:
    return "Invalid input.";
  }
  return "Unknown error.";
}

int main() {
  auto result = safe_divide(10, 0);

  if (result.is_ok()) {
    std::cout << "Result: " << result.unwrap() << "\n";
  } else {
    std::cout << "Error: " << error_code_to_string(result.unwrap_err()) << "\n";
  }

  auto valid_result = safe_divide(10, 2);
  if (valid_result.is_ok()) {
    std::cout << "Result: " << valid_result.unwrap() << "\n";
  } else {
    std::cout << "Error: " << error_code_to_string(valid_result.unwrap_err())
              << "\n";
  }

  return 0;
}
