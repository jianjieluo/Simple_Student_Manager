#ifndef STUDENT_MANAGER_H_
#define STUDENT_MANAGER_H_

#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>

struct Student {
  int id;
  std::string name;
  double aGrade, bGrade, cGrade;
  // Student(int _id = 0, std::string _name = "Tom", double a = 0, double b = 0,
  //         double c = 0)
  //     : id(_id), name(_name), aGrade(a), bGrade(b), cGrade(c) {}
  void showGrade() const;
};

class studentManager {
 private:
  studentManager() {}
  std::list<Student>::iterator getStudent(int id);

 public:
  static std::unique_ptr<studentManager> &getInstance();
  void init(std::string file_path = "./student_information");
  void appendStudent();
  void searchStudent(int id);
  void sort();
  // void a_bScore(int a, int b);
  void deleteStudent(int id);
  void modifyStudnet(int id);
  void writeBack(std::string file_name = "./student_information");
  void help();

 private:
  static std::unique_ptr<studentManager> m_pInstance;
  std::list<Student> m_list;
};

#endif
