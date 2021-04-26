#include <string>
#include <iostream>

std::string F(bool cond = false) {
  std::string first("first");
  std::string second("second");
  // the function may return one of two named objects
  // depending on its argument. RVO might not be applied
  return cond ? first : second;
}

int main() {
  std::string result = F();
  std::cout << result << std::endl;

}

