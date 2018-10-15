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

    void process(unsigned int ts_begin, unsigned int ts_end) {
      auto lb = logs.lower_bound(ts_begin);
      auto ub = logs.upper_bound(ts_end);
      auto lower_ts = (lb != logs.end()) ? lb : logs.begin();
      auto upper_ts = (ub != logs.end()) ? ub : logs.end();

      unsigned int total_nb_queries = 0;
      vector<string> total_queries(10);

      for (; lower_ts != upper_ts; ++lower_ts) {
        cout << lower_ts->first << "; " << lower_ts->second << endl;
        total_nb_queries += lower_ts->second.nb_query;
        total_queries.insert(total_queries.end(), 
            lower_ts->second.queries.begin(), lower_ts->second.queries.end());
      }

      cout << "Total queries: " << total_nb_queries << endl;
      cout << "List of queries: ";
      for (vector<string>::iterator query = total_queries.begin(); 
          query != total_queries.end(); ++query) {
        cout << *query << " ";
      }
      cout << endl;
    }
};

int main()
{
  // Preprocess
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

  // Query!
  unsigned int timestamp_begin = 4;
  unsigned int timestamp_end = 5;
  tree.process(timestamp_begin, timestamp_end);

  return 0;
}
