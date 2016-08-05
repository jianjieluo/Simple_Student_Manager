#include <exception>
#include <map>
#include <utility>
#include "Student_Manager.hpp"
using std::make_pair;

enum choice {
  Invalid,
  Quit,
  Help,
  Write,
  Append,
  Delete,
  Search,
  Modify,
  Sort,
  Show,
  Size,
  Query
};

int main() {
  // Initialization
  system("clear");
  std::cout << "Please input the file path you want to import,\nor just input "
               "\"default\" to use the default file"
            << std::endl;
  std::string file_path;
  std::cin >> file_path;
  try {
    if (file_path == "default")
      studentManager::getInstance()->init();
    else
      studentManager::getInstance()->init(file_path);
  } catch (std::exception &ex) {
    std::cerr << "Input file failed !" << std::endl;
    std::cout << ex.what() << std::endl;
  };

  // begin to work
  system("clear");
  studentManager::getInstance()->help();
  // params
  int t_id;
  std::map<std::string, int> choices = {
      make_pair("quit", Quit),     make_pair("help", Help),
      make_pair("write", Write),   make_pair("append", Append),
      make_pair("delete", Delete), make_pair("search", Search),
      make_pair("modify", Modify), make_pair("sort", Sort),
      make_pair("show", Show),     make_pair("size", Size),
      make_pair("query", Query)};
  bool state_judge = true;

  while (state_judge) {
    std::string comm;
    std::cin >> comm;
    switch (choices[comm]) {
      case Quit:
        state_judge = false;
        break;
      case Help:
        studentManager::getInstance()->help();
        break;
      case Append:
        studentManager::getInstance()->appendStudent();
        break;
      case Delete:
        std::cout << "Please input the id of the student you want to delete."
                  << std::endl;
        std::cin >> t_id;
        studentManager::getInstance()->deleteStudent(t_id);
        break;
      case Search:
        std::cout << "Please input the id of the student you want to search."
                  << std::endl;
        std::cin >> t_id;
        studentManager::getInstance()->searchStudent(t_id);
        break;
      case Modify:
        std::cout << "Please input the id of the student you want to modify."
                  << std::endl;
        std::cin >> t_id;
        studentManager::getInstance()->modifyStudnet(t_id);
        break;
      case Sort:
        std::cout << "The sort report is below :" << std::endl;
        studentManager::getInstance()->sort();
        break;
      case Show:
        studentManager::getInstance()->showTheLast();
        break;
      case Size:
        std::cout << "The current number of students is : "
                  << studentManager::getInstance()->size() << std::endl;
        break;
      case Query:
        double lhs, rhs;
        std::cout << "Please input the bounds of the scores you want to query"
                  << std::endl;
        std::cin >> lhs >> rhs;
        studentManager::getInstance()->a_bScore(lhs, rhs);
        break;
      case Write:
        try {
          if (file_path == "default")
            studentManager::getInstance()->writeBack();
          else
            studentManager::getInstance()->writeBack(file_path);
        } catch (std::exception &ex) {
          std::cerr << "Write back the file failed!" << std::endl;
          std::cout << ex.what() << std::endl;
        }
        break;
      case Invalid:
        std::cout << "Invalid input! Please try again!" << std::endl;
        break;
      default:
        std::cout << "Unknown" << std::endl;
        break;
    }
    if (!state_judge) {
      std::cout << "See You next time !!" << std::endl;
      break;
    }
    std::cout << "\n"
              << "Please enter your choice, thanks~" << std::endl;
  }
  return 0;
}
