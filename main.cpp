#include <exception>
#include "Student_Manager.hpp"

enum choices { Quit, Help, Append, Delete, Search, Modify, Sort, Calculate };

int main() {
  // Initialization
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
  studentManager::getInstance()->help();
  // params
  int t_id;

  bool state_judge = true;
  while (state_judge) {
    int choice;
    std::cin >> choice;
    switch (choice) {
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

      default:
        std::cout << "Unvalid input! Please try again!" << std::endl;
        break;
    }
    if (!state_judge) {
      std::cout << "It is going to write back to the file...." << std::endl;
      break;
    }
    std::cout << "\n"
              << "Please enter your choice, thanks~" << std::endl;
  }

  try {
    if (file_path == "default")
      studentManager::getInstance()->writeBack();
    else
      studentManager::getInstance()->writeBack(file_path);
  } catch (std::exception &ex) {
    std::cerr << "Write back the file failed!" << std::endl;
    std::cout << ex.what() << std::endl;
  }

  std::cout << "See You next time !!" << std::endl;
  return 0;
}
