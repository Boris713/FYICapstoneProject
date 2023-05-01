#include "info.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

Person_info::Person_info()
    : first_name("N/A"), last_name("N/A"), email("N/A"), institution("N/A") {}//deafaults for person info 
void Person_info::setFirstName(string fn) { first_name = fn; }
void Person_info::setLastName(string ln) { last_name = ln; }
void Person_info::setEmail(string el) { email = el; }
void Person_info::setInstitution(string in) { institution = in; }
string Person_info::getFirstName() { return first_name; }
string Person_info::getLastName() { return last_name; }
string Person_info::getEmail() { return email; }
string Person_info::getInstitution() { return institution; }

Presentation_info::Presentation_info()//defaults for presentation info
    : presentation_name("N/A"), room_name("N/A"), day("N/A"),
      description("N/A"), startHour(0), startMin(0), endHour(0), endMin(0) {}

void Presentation_info::setPresentationName(string pn) { presentation_name = pn; }
void Presentation_info::setRoomName(string rn) { room_name = rn; }
void Presentation_info::setDay(string da) { day = da; }
void Presentation_info::setDescription(string de) { description = de; }
void Presentation_info::setStartHour(int sh) {startHour = sh;}
void Presentation_info::setStartMin(int sm) {startMin = sm;}
void Presentation_info::setEndHour(int eh) {endHour = eh;}
void Presentation_info::setEndMin(int em) {endMin = em;}
string Presentation_info::getPresentationName() { return presentation_name; }
string Presentation_info::getRoomName() { return room_name; }
string Presentation_info::getDay() { return day; }
string Presentation_info::getDescription() { return description; }
int Presentation_info::getStartHour() {return startHour;}
int Presentation_info::getStartMin() {return startMin;}
int Presentation_info::getEndHour() {return endHour;}
int Presentation_info::getEndMin() {return endMin;}

void Presentation_info::addPerson(Person_info temp) {
  presenters.push_back(temp);//used when reading from file to get multiple people
}

void Presentation_info::setDataInfo(ifstream &infile, string line) {//reading from txt file
  if (line.find("Name: ") != string::npos) {
    presentation_name = line.substr(6);
  }
  if (line.find("Day: ") != string::npos) {
    day = line.substr(5);
  }
  if (line.find("Time: ") != string::npos) {//gets time by seperating hours and mins from file
    string time = line.substr(6);
    for(int i = 0; i < time.length();i++){
      if(time[i] == ':'){
        if(startHour == 0)
          startHour = stoi(time.substr(0,i));
        else
          endHour = stoi(time.substr(0,i));
        if(startMin == 0)
          startMin = stoi(time.substr(i+1, time.find('m')-(i+2)));
        else
          endMin = stoi(time.substr(i+1, time.find('m')-(i+2)));
      }
      if(time[i] == '-'){
        time = time.substr(i+2);
        i = 0;
      }
    }
  }
  if (line.find("Room: ") != string::npos) {
    room_name = line.substr(6);
  }
  if (line.find("Presenters: ") != string::npos) {//gets presentors first and last name and seperates individuals by ','
    Person_info tempPerson; // temp object
    string str = line.substr(12);
    for (int i = 0; i < str.length(); i++) {
      if (str[i] == ' ') {
        string s(str, 0, i);
        tempPerson.setFirstName(s);
        tempPerson.setLastName(str.substr(i + 1, str.find(',') - (i + 1)));
      }
      if (str[i] == ',') {
        str = str.substr(i + 2);
        addPerson(tempPerson);
        i = 0;
      }
    }
    addPerson(tempPerson);
  }
  if (line.find("Emails: ") != string::npos) {//seperates emails by individual by ','
    string str = line.substr(8);
    int count = 1;
    this->presenters[0].setEmail(str.substr(0, str.find(',')));
    for (int i = 0; i < str.length(); i++) {
      if (str[i] == ',') {
        str = str.substr(i + 2);
        this->presenters[count].setEmail(str.substr(0, str.find(',')));
        count++;
        i = 0;
      }
    }
  }
  if (line.find("Institution: ") != string::npos) {//seperates school by individual by ','
    for (int i = 0; i < this->presenters.size(); i++) {
      this->presenters[i].setInstitution(line.substr(13));
    }
  }
  if (line.find("Description: ") != string::npos) {
    description = line.substr(13);
  }
  if (line.find("Track: ") != string::npos) {
    presentation_type = line.substr(7);
  }
}

void Presentation_info::printPresentationData() {//used when displaying presentation in schedule or in search
  
  cout << "Title: " << presentation_name << endl
       << "Type: " << presentation_type << endl
       << "Day & Time: " << day << " " << startHour << ":" << startMin << " - " << endHour << ":" << endMin << endl
       << "Room: " << room_name << endl
       << "Institution: " << this->presenters[0].getInstitution() << endl;
  for (int i = 0; i < this->presenters.size(); i++) {
    cout << "Presenter " << i + 1 << ": " << this->presenters[i].getFirstName()
         << " " << this->presenters[i].getLastName() << endl;
    cout << "Email: " << this->presenters[i].getEmail() << endl;
  }
  cout << endl << "Description: " << endl;
  const int LINE_WIDTH = 80;
    istringstream iss(description);
    string word, l;
    while (iss >> word) {
        if (l.size() + word.size() + 1 <= LINE_WIDTH) {
            l += (l.empty() ? "" : " ") + word;
        } else {
            cout << l << endl;
            l = word;
        }
    }
    cout << l << endl;
  cout << "--------------------------------------------------------------------------------\n--------------------------------------------------------------------------------\n--------------------------------------------------------------------------------" << endl << endl;
}

void Presentation_info::emailList() {//all emails
  for (int i = 0; i < this->presenters.size()-1; i++) {
    cout << this->presenters[i].getEmail() << ", ";
  }
    cout << this->presenters[this->presenters.size()-1].getEmail();
}

void Presentation_info::searchName(string fn, string ln, bool &in_list){//to search for presentor and their presentations
  
  for (int i = 0; i < this->presenters.size(); i++) {
    if(fn == presenters[i].getFirstName() && ln == presenters[i].getLastName()){
      in_list = true;
      printPresentationData();
    }
  }

}
