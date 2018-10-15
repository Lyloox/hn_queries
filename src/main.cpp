#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

class BinaryTree {
  public:
    class LogObject {
      public:
        unsigned int timestamp;
        string query;
        LogObject(unsigned int ts, string q) : timestamp(ts),
                                               query(q) {}
        friend class BinaryTree;
    };

  protected:
    vector<LogObject> logs;

  public:
    BinaryTree() {
    }

    int size() {
      return int(logs.size()) - 1;
    }

    void insert(const LogObject& log) {
      logs.push_back(log);
    }

    void print() {
      for (vector<LogObject>::iterator log = logs.begin();
          log != logs.end(); ++log) {
        cout << log->timestamp << "; " << log->query << endl;
      }
    }
};

int main()
{
  typedef BinaryTree::LogObject LogObject;

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
      LogObject log(key, value);
      tree.insert(log);
    }
    logs_file.close();
  }
  tree.print();
  return 0;
}
