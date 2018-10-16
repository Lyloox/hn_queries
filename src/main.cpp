#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <limits>

class InputParser{
  public:
    InputParser (int &argc, char **argv){
      for (int i=1; i < argc; ++i)
        this->tokens.push_back(std::string(argv[i]));
    }

    unsigned int get_option(const std::string &option) const{
      std::vector<std::string>::const_iterator itr;
      itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
      if (itr != this->tokens.end() && ++itr != this->tokens.end())
        return std::stoul(*itr);
      if (option == "--to")
        return std::numeric_limits<unsigned int>::max();
      return 0;
    }

  private:
    std::vector <std::string> tokens;
};

int main(int argc, char *argv[])
{
  if (argc - 1 == 0)
    return 1;

  std::string command = argv[1];
  std::string filepath = argv[argc - 1];

  InputParser input(argc, argv);
  unsigned int from = input.get_option("--from");
  unsigned int to = input.get_option("--to"); 

  std::map<std::string, unsigned int> tops;
  std::set<std::string> distincts;

  std::ifstream file(filepath);
  if (file.is_open()) {
    std::string line;

    while (getline(file, line)) {
      std::istringstream iss(line);
      unsigned int key;
      std::string value;
      iss >> key;
      iss >> value;

      if (to < key)
        break;

      if (from > key)
        continue;

      std::cout << "Process: " << key << ", " << value << std::endl;

      if (command == "top") {
        auto previous_top = tops.find(value);
        if (previous_top != tops.end()) {
          std::cout << previous_top->second + 1 << std::endl;
          tops.insert({value, previous_top->second + 1});
        }
        else
          tops.insert({value, 1});
      }

      else if (command == "distinct")
        distincts.insert(value);

    }
    file.close();
  }

  if (command == "top") {
    // TODO: Sort
    for (std::map<std::string, unsigned int>::iterator log = tops.begin();
        log != tops.end(); ++log) {
      std::cout << log->first << " " << log->second << std::endl;
    }
  }
  else if (command == "distinct") {
    std::cout << distincts.size() << std::endl;
  }
  return 0;
}
