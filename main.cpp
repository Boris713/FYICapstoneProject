#include "info.hpp"//adding outputs if user enters something not in presentations
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

void readFromFile(vector<Presentation_info> &); // reads all of the data from the file and inserts it into the class
void printAllData(vector<Presentation_info> &); // prints out all of the data with type of sorting
void sortRoom(vector<Presentation_info>&, string, string); // prints all rooms in the seleced day
void showCalendar(vector<Presentation_info> &);
void showDay(vector<Presentation_info> &, int);//show day from presentation 
void showPresenters(vector<Presentation_info> &);
void showPresentation(vector<Presentation_info> &);
void sortTime(vector<Presentation_info>&, int,int);
void enterContinue();
int main() {
  vector<Presentation_info> presentations;
  readFromFile(presentations);
  bool quit = false;
  while (!quit) {
    cout << "+------------------------------------+" << endl;
    cout << "|  National Learning Communities     |" << endl;
    cout << "|             Conference             |" << endl;
    cout << "+------------------------------------+" << endl;
    cout << "|                                    |" << endl;
    cout << "|  Please select a category to       |" << endl;
    cout << "|  search by:                        |" << endl;
    cout << "|                                    |" << endl;
    cout << "|  1. Calendar or Time               |" << endl;
    cout << "|  2. Presenters or Email Lists      |" << endl;
    cout << "|  3. Presentations                  |" << endl;
    cout << "|  4. Quit                           |" << endl;
    cout << "|                                    |" << endl;
    cout << "+------------------------------------+" << endl;
    cout << "Enter a number 1-4: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
      showCalendar(presentations);
      system("clear");
      break;
    case 2:
      showPresenters(presentations);
      system("clear");
      break;
    case 3:
      showPresentation(presentations);
      system("clear");
      break;
    case 4:
      system("clear");
      cout << "See you soon!" << endl;
      quit = true;
      break;
    default:
      system("clear");
      cout << "Invalid input. Please enter a number 1-4." << endl;
      cin.clear();
      cin.ignore();
      break;
    }
  }
  return 0;
}

void readFromFile(vector<Presentation_info> &presentations) {//getting info from file into vector
  ifstream infile("data.txt");
  if (!infile.is_open()) {
    cerr << "Unable to open file." << endl;
    return;
  }
  Presentation_info current_presentation;
  string line;
  while (getline(infile, line)) {
    current_presentation.setDataInfo(infile, line);
    if (line.empty()) {
      presentations.push_back(current_presentation);
      current_presentation = Presentation_info();
    }
  }
  presentations.push_back(current_presentation);
  infile.close();
}

void printAllData(vector<Presentation_info> &presentations) {
  for (auto &presentation : presentations)
    presentation.printPresentationData();
}

void showCalendar(vector<Presentation_info> &presentations) {//show calander based off selection made
  string time;
  int hour = 0,min = 0;
  int choice;
  system("clear");
  do {
    cout << "+--------------------------------------+" << endl;
    cout << "|               Calendar               |" << endl;
    cout << "+--------------------------------------+" << endl;
    cout << "|                                      |" << endl;
    cout << "|  1. Day 1                            |" << endl;
    cout << "|  2. Day 2                            |" << endl;
    cout << "|  3. Full Calendar                    |" << endl;
    cout << "|  4. Search by Time                   |" << endl;
    cout << "|  5. Go Back                          |" << endl;
    cout << "|                                      |" << endl;
    cout << "+--------------------------------------+" << endl;
    cout << "Enter a number 1-5: ";
    //sends user back to main menu
    cin >> choice;
    switch (choice) {//sub menu and choices 
    case 1:
      system("clear");
      showDay(presentations, choice);
      break;
    case 2:
      system("clear");
      showDay(presentations, choice);
      break;
    case 3:
      system("clear");
      printAllData(presentations);
      enterContinue();
      break;
    case 4://search for presentations at certain time
      system("clear");
      time.clear();
      hour = 0;
      min = 0;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Please enter time when presentation starts: ";
      getline(cin,time);
      system("clear");
      for(int i = 0; i < time.length(); i++){
        if(isdigit(time[i])){
          if(hour == 0){
            if(isdigit(time[i+1])){
            hour = stoi(time.substr(0,i+2));
            time = time.substr(i+2);
            i = 0;
            }
            else{
            hour = stoi(time.substr(0,i+1));
            time = time.substr(i+1);
            i = 0;
            }
          }
          else{
            min = stoi(time.substr(i));
            break;              
          }
        }
      }
      sortTime(presentations,hour,min);
      
      break;//while input is not a number and its less than 12 mins is 60
      default:
      system("clear");
      cout << "Invalid input. Please enter a number 1-5." << endl;
      cin.clear();
      cin.ignore();
      break;
    }
  } while (choice != 5);
}

void showDay(vector<Presentation_info> &presentations, int dayNum) {//show calander for specific room or all events
  int choice;
  string day = (dayNum == 1) ? "Friday" : "Saturday";
  system("clear");
    do {
        
        cout << "+------------------------------------+" << endl;
        cout << "| Please select a room for day " << dayNum << ":    |" << endl;
        cout << "+------------------------------------+" << endl;
        cout << "|                                    |" << endl;
        cout << "| 1. Bayview                         |" << endl;
        cout << "| 2. Nueces A                        |" << endl;
        cout << "| 3. Nueces B                        |" << endl;
        cout << "| 4. Laguna Madre                    |" << endl;
        cout << "| 5. Aransas                         |" << endl;
        cout << "| 6. Matagorda                       |" << endl;
        cout << "| 7. Copano                          |" << endl;
        cout << "| 8. Corpus A/B                      |" << endl;
        cout << "| 9. Corpus C                        |" << endl;
        cout << "| 10. Go Back                        |" << endl;
        cout << "|                                    |" << endl;
        cout << "+------------------------------------+" << endl;
        cout << "Enter a number 1-10: ";
          cin >> choice;
          switch (choice) {
             case 1: sortRoom(presentations,day,"Bayview");
               break;
             case 2: sortRoom(presentations,day,"Nueces A"); 
               break;
             case 3: sortRoom(presentations,day,"Nueces B"); 
               break;
             case 4: sortRoom(presentations,day,"Laguna Madre"); 
               break;
             case 5: sortRoom(presentations,day,"Aransas"); 
               break;
             case 6: sortRoom(presentations,day,"Matagorda"); 
               break;
             case 7: sortRoom(presentations,day,"Copano"); 
               break;
             case 8: sortRoom(presentations,day,"Corpus A/B");
               break;
            case 9: sortRoom(presentations,day,"Corpus C");
               break;
            case 10:
              break;
            default:
                system("clear");
                cout << "Invalid input. Please enter a number 1-10." << endl;
                cin.clear();
                cin.ignore();
                break;
           }
  } while (choice != 10);
  enterContinue();
}

void showPresenters(vector<Presentation_info> &presentations){//searching by name or email list
  bool in_list = false;
  int choice;
  string fullName,firstName,lastName;
  system("clear");
  do{
    
    cout << "+------------------------------------+" << endl;
    cout << "|   Presenter names or Email lists   |" << endl;
    cout << "+------------------------------------+" << endl;
    cout << "|                                    |" << endl;
    cout << "| 1. Search by presenter's name      |" << endl;
    cout << "| 2. Email list of presenters        |" << endl;
    cout << "| 3. Go Back                         |" << endl;
    cout << "|                                    |" << endl;
    cout << "+------------------------------------+" << endl;
    cout << "Enter a number 1-3: ";
    cin >> choice;
    switch(choice){
      case 1:
        system("clear");
        cout << "Please enter the Presenters Name: ";//adding bool variable to check if any presentations contain the name used 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,fullName);
        
        firstName = fullName.substr(0,fullName.find(' '));
        lastName = fullName.substr(fullName.find(' ')+1);
        for(auto &presentation : presentations)
          presentation.searchName(firstName,lastName,in_list);
        if(in_list == false)
          cout << "Name not in presentation list." << endl << endl;//add a pause between output and menu
        else
          in_list = false;
        enterContinue();
        break;
      case 2:
        system("clear");
        cout << endl << "Email List of all Presenters: " << endl << endl;//not clearing old outputs
        for(auto &presentation : presentations)
          presentation.emailList();
        cout << endl;
        enterContinue();
        break;
      case 3:
        break;
      default:
        system("clear");
        cout << "Invalid input. Please enter a number 1-3." << endl;
        cin.clear();
        cin.ignore();
        break;
    }
  }while(choice !=3);
}

void showPresentation(vector<Presentation_info> &presentations) {//search by pres name
  string name;
  int count = 0;
  system("clear");
  cout << "Please enter the Presentation Name: ";//not pulling up presentation
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, name);
  for (auto &presentation : presentations) {
    if (presentation.getPresentationName() == name) {
      count++;
      presentation.printPresentationData();
    }
  }
  if(count == 0)
  cout << "Presentation not found!\n";
  enterContinue();
}

void sortRoom(vector<Presentation_info>& presentations, string day, string room) {//sort by pres in a room 
  system("clear");
  int count = 0;
  for (auto &presentation : presentations) {
    if (presentation.getDay() == day && presentation.getRoomName() == room) {
      count++;
      presentation.printPresentationData();
    }
  }
  if(count == 0){
    cout << "No presentations for this Room found in the list" << endl;//extra enter to continue 
  }
  enterContinue();
}


void sortTime(vector<Presentation_info>& presentations, int hour, int min) {//sort what time pres are at
  int count = 0;
  for (auto &presentation : presentations) {
    if(presentation.getStartHour() == hour && presentation.getStartMin() == min) {
      count++;
      presentation.printPresentationData();
    }
  }
  if(count == 0){
    cout << "Time not found in list!";//extra enter to continue 
  }
  enterContinue();
}

void enterContinue()
{
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Press Enter to continue...";
  cin.get();
  system("clear");
}
