#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>

using namespace std;

int main()
{
  // TODO: Option parser
  
  unsigned int timestamp_begin = 1;
  unsigned int timestamp_end = 6;
  string command = "distinct";
  string filepath = "logs.txt";
  

  map<string, unsigned int> logs;
  set<string> distincts;

  ifstream logs_file(filepath);
  if (logs_file.is_open()) {
    string line;
    while (getline(logs_file, line)) {
      istringstream iss(line);
      unsigned int key;
      string value;
      iss >> key;
      iss >> value;

      if (timestamp_end < key) {
        cout << "Break bc end<key" << endl;
        break;
      }
      if (timestamp_begin > key) {
        cout << "Break bc end>key" << endl;
        continue;
      }
      else {
        cout << "Process: " << key << ", " << value << endl;

        if (command == "top") {
          auto previous_top = logs.find(value);
          if (previous_top != logs.end()) {
            cout << previous_top->second + 1 << endl;
            logs.insert({value, previous_top->second + 1});
          }
          else
            logs.insert({value, 1});
        }

        else if (command == "distinct")
          distincts.insert(value);
      }

    }
    logs_file.close();
  }

  if (command == "top") {
    // TODO: Sort
    for (map<string, unsigned int>::iterator log = logs.begin();
        log != logs.end(); ++log) {
      cout << log->first << " " << log->second << endl;
    }
  }
  else if (command == "distinct") {
    cout << distincts.size() << endl;
  }
  return 0;
}
