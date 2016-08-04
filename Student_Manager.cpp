#include "Student_Manager.hpp"
#include <algorithm>
#include <cstdio>

void Student::showGrade() const {
  std::cout << "id: " << id << " name: " << name << std::endl;
  std::cout << "aGrade: " << aGrade << std::endl;
  std::cout << "bGrade: " << bGrade << std::endl;
  std::cout << "cGrade: " << cGrade << std::endl;
}

std::list<Student>::iterator studentManager::getStudent(int id) {
  for (auto iter = m_list.begin(); iter != m_list.end(); ++iter) {
    if (iter->id == id) {
      return iter;
    }
  }
  return m_list.end();
}

std::unique_ptr<studentManager> studentManager::m_pInstance(nullptr);

std::unique_ptr<studentManager> &studentManager::getInstance() {
  if (m_pInstance == nullptr) {
    m_pInstance.reset(new studentManager());
  }
  return m_pInstance;
}

void studentManager::init(std::string file_path) {
  if (!m_list.empty()) {
    m_list.clear();
  }
  std::ifstream open_file(file_path);
  if (open_file) {
    int id;
    double a, b, c;
    std::string name;
    while (open_file >> id >> name >> a >> b >> c) {
      m_list.push_back(Student{id, name, a, b, c});
    }
  } else {
    std::cout << "Import the file failed!" << std::endl;
  }
  open_file.close();
}

void studentManager::appendStudent() {
  std::cout << "Please input the new id of a student." << std::endl;
  int id;
  std::cin >> id;
  for (auto iter = m_list.begin(); iter != m_list.end(); ++iter) {
    if (iter->id == id) {
      std::cout << "Failed!" << std::endl;
      std::cout << "The id has been in the students' documentary!" << std::endl;
      return;
    }
  }
  std::string name;
  double a, b, c;
  std::cout
      << "Please input the name, aGrade, bGrade, cGrade of the new student."
      << std::endl;
  std::cin >> name >> a >> b >> c;
  m_list.push_back(Student{id, name, a, b, c});
  std::cout << "Append the student information sucessfully." << std::endl;
}

void studentManager::searchStudent(int id) {
  auto iter = getStudent(id);
  if (iter == m_list.end()) {
    std::cout << "There is no such a person !" << std::endl;
  } else {
    iter->showGrade();
  }
}

void studentManager::sort() {
  if (m_list.empty()) {
    std::cout << "There is no student information in the file!" << std::endl;
    return;
  }
  auto t_list = m_list;
  t_list.sort([](const Student &lhs, const Student &rhs) -> bool {
    double l = (lhs.aGrade + lhs.bGrade + lhs.cGrade) / 3;
    double r = (rhs.aGrade + rhs.bGrade + rhs.cGrade) / 3;
    return l > r;
  });
  for_each(t_list.begin(), t_list.end(),
           [](const Student &person) { person.showGrade(); });
}

void studentManager::a_bScore(double lhs, double rhs) {
  int count;
  if (lhs == rhs) {
    count = count_if(
        m_list.begin(), m_list.end(), [lhs](const Student &person) -> bool {
          double average = (person.aGrade + person.bGrade + person.cGrade) / 3;
          return lhs == average;
        });
  } else {
    if (lhs > rhs) {
      double temp = lhs;
      lhs = rhs;
      rhs = temp;
    }
    count = count_if(m_list.begin(), m_list.end(),
                     [lhs, rhs](const Student &person) -> bool {
                       double average =
                           (person.aGrade + person.bGrade + person.cGrade) / 3;
                       return (lhs <= average && average < rhs);
                     });
  }
  printf("The number of students whose averages are in [%lf, %lf) is %d", lhs,
         rhs, count);
}

void studentManager::deleteStudent(int id) {
  auto iter = getStudent(id);
  if (iter != m_list.end()) {
    m_list.remove_if(
        [id](const Student &person) -> bool { return (person.id == id); });
    std::cout << "Remove the student's information successfully." << std::endl;
  } else {
    std::cout << "There is no such a student!" << std::endl;
  }
}

void studentManager::modifyStudnet(int id) {
  auto iter = getStudent(id);
  if (iter == m_list.end()) {
    std::cout << "There is no such a student!" << std::endl;
  } else {
    std::cout << "Please input the new information about the student."
              << std::endl;
    std::cout << "name\t aGrade\t bGrade\t cGrade" << std::endl;
    std::string name;
    double a, b, c;
    std::cin >> name >> a >> b >> c;
    iter->name = name;
    iter->aGrade = a;
    iter->bGrade = b;
    iter->cGrade = c;
    std::cout << "Change the information sucessfully!!" << std::endl;
  }
}

int studentManager::size() { return m_list.size(); }

void studentManager::writeBack(std::string file_name) {
  std::ofstream out(file_name);
  if (out) {
    for_each(m_list.begin(), m_list.end(), [&](const Student &person) {
      out << person.id << " " << person.name << " " << person.aGrade << " "
          << person.bGrade << " " << person.cGrade << "\n";
    });
  } else {
    std::cout << "Open file failed!" << std::endl;
  }
  out.close();
}

void studentManager::show50() {
  std::cout << "The last 50 students's information is listed below :"
            << std::endl;
  int count = 50;
  auto riter = m_list.rbegin();
  while (count--) {
    if (riter == m_list.rend()) break;
    riter->showGrade();
    --riter;
  }
}

void studentManager::help() {
  system("clear");
  std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-Welcome To The Student Manager "
               "!-=-=-=-=-=-=-=-=-=-=-=-="
            << std::endl;
  std::cout << "\n"
            << "Here is the help page" << std::endl;
  std::cout << "quit -> quit" << std::endl;
  std::cout << "help -> help pages" << std::endl;
  std::cout << "append -> add a student's information" << std::endl;
  std::cout << "delete -> delete a student's information" << std::endl;
  std::cout << "search -> search a student's information" << std::endl;
  std::cout << "modify -> modify a student's information" << std::endl;
  std::cout
      << "sort -> sort the informations according to the average grades and "
         "print out them"
      << std::endl;
  std::cout << "show -> show the latest 50 students information." << std::endl;
  std::cout << "size -> show the current number of students" << std::endl;
  std::cout << "query -> calculate the number of students in [a, b)"
            << std::endl;
  std::cout << "write -> write your changes back to the file" << std::endl;
  std::cout << "\n"
            << "Please enter your choice, thanks~" << std::endl;
}
