#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <set>

using namespace std;

class BinaryTree {
  public:

    class LogObject {

      public:
        unsigned int timestamp;
        unsigned int nb_query;
        vector<string> queries;
        LogObject(unsigned int ts, string q) : timestamp(ts),
                                               nb_query(1),
                                               queries(1, q) {}

        void add(string& query) {
          nb_query++;
          queries.push_back(query);
        }

        friend ostream& operator<<(ostream& os, LogObject& log);
        friend class BinaryTree;
    };

  protected:
    map<unsigned int, LogObject> logs;

    friend ostream& operator<<(ostream& os, LogObject& log) {
      os << log.nb_query << " queries: ";
      for (vector<string>::iterator query = log.queries.begin(); 
          query != log.queries.end(); ++query) {
        os << *query << " ";
      }
      return os;
    }

  public:
    BinaryTree() {
    }

    int size() {
      return int(logs.size()) - 1;
    }

    void insert(unsigned int key, string value) {
      auto previous_log = logs.find(key);
      if (previous_log != logs.end()) {
        previous_log->second.add(value);
      }
      else {
        LogObject log(key, value);
        logs.insert({log.timestamp, log});
      }
    }

    void print() {
      for (map<unsigned int, LogObject>::iterator log = logs.begin();
          log != logs.end(); ++log) {
        cout << log->first << "; " << log->second << endl;
      }
    }
};

int main()
{
  ifstream logs_file("logs.txt");
  BinaryTree tree;
  if (logs_file.is_open()) {
    string line;
    while (getline(logs_file, line)) {
      istringstream iss(line);
      unsigned int key;
      string value;
      iss >> key;
      iss >> value;
      tree.insert(key, value);
    }
    logs_file.close();
  }
  tree.print();
  return 0;
}
