#include "result.h"
#include <iostream>
#include <string>

using namespace noexception;

Result<int, std::string> divide(int a, int b) {
  if (b == 0)
    return Result<int, std::string>::Err("division by zero");
  return Result<int, std::string>::Ok(a / b);
}

int main() {
  auto r1 = divide(10, 2);
  if (r1.is_ok()) {
    std::cout << "result: " << r1.unwrap() << "\n";
  }

  auto r2 = divide(10, 0);
  if (r2.is_err()) {
    std::cout << "error: " << r2.unwrap_err() << "\n";
  }

  // using unwrap_or
  auto val = divide(10, 0).unwrap_or(-1);
  std::cout << "unwrap_or: " << val << "\n";

  return 0;
}
