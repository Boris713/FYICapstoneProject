#ifndef INFO_H
#define INFO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;

class Person_info { // Information about the person
private:
  string first_name, last_name, email, institution;

public:
  Person_info(); // constructor
  void setFirstName(string fn);
  void setLastName(string ln);
  void setEmail(string el);
  void setInstitution(string in);
  string getFirstName();
  string getLastName();
  string getEmail();
  string getInstitution();
  //~Person_info(){};
};

class Presentation_info { //Information about the presentation
private:
  string presentation_name, room_name, day, description, presentation_type;
  int startHour,startMin,endHour,endMin;
  bool accepted;
  vector<Person_info> presenters;//will hold all presentations and info

public:
  Presentation_info(); //constructor
  Presentation_info(string pn, string rn, string da, string de, bool ac); // another constructor
  void setPresentationName(string pn);//start of setters
  void setRoomName(string rn);
  void setDay(string da);
  void setDescription(string de);
  void setStartHour(int sh);
  void setStartMin(int sm);
  void setEndHour(int eh);
  void setEndMin(int em);
  string getPresentationName();//start of getters
  string getRoomName();
  string getDay();
  string getDescription();
  int getStartHour();
  int getStartMin();
  int getEndHour();
  int getEndMin();
  void addPerson(Person_info temp); // adds presentor
  void setDataInfo(ifstream& infile, string line); //gets data from txt file
  void printPresentationData(); //prints out the data of the presentation
  void emailList();
  void searchName(string fn, string ln, bool &in_list);

  //~Presentation_info(){};
};

#endif
