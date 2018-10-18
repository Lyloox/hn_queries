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

    unsigned int char2uint(const char* nchar_value) const{
      std::stringstream nss_value;
      nss_value << nchar_value;
      unsigned int n;
      nss_value >> n;
      return n;
    }

  private:
    std::vector <std::string> tokens;
};

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
  return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
  std::multimap<B,A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
      flip_pair<A,B>);
  return dst;
}


void print_result(std::string command, std::map<std::string, 
    unsigned int> tops, std::set<std::string> distincts, unsigned int n) {
  if (command == "top") {
    std::multimap<unsigned int, std::string> sorted_tops = flip_map(tops);
    std::multimap<unsigned int, std::string>::reverse_iterator sorted_top;
   
    unsigned int i = 0;
    for (sorted_top = sorted_tops.rbegin();
        sorted_top != sorted_tops.rend() && i < n;
        ++sorted_top) {
      std::cout << sorted_top->first << " " << sorted_top->second << std::endl;
      i++;
    }
  }
  else if (command == "distinct") {
    std::cout << distincts.size() << std::endl;
  }
}

void parse(std::string& command, std::ifstream& file, std::map<std::string,
  unsigned int>& tops, std::set<std::string>& distincts, unsigned int from,
  unsigned int to) {
  bool cmd_is_top = command == "top";
  bool cmd_is_distinct = command == "distinct";
  std::string line;
  unsigned int key;
  std::string value;
  while (getline(file, line)) {
    std::istringstream iss(line);
    iss >> key;
    iss >> value;

    if (to < key)
      break;

    if (from > key)
      continue;

    if (cmd_is_top) {
      auto previous_top = tops.find(value);
      if (previous_top != tops.end())
        tops[value] = previous_top->second + 1;
      else
        tops.insert({value, 1});
    }
    else if (cmd_is_distinct)
      distincts.insert(value);
  }
}

int main(int argc, char *argv[])
{
  if (argc - 1 == 0)
    return 1;

  std::string command = argv[1];
  std::string filepath = argv[argc - 1];

  InputParser input(argc, argv);
  unsigned int n = input.char2uint(argv[2]);
  unsigned int from = input.get_option("--from");
  unsigned int to = input.get_option("--to"); 

  std::map<std::string, unsigned int> tops;
  std::set<std::string> distincts;

  std::ifstream file(filepath);

  if (file.is_open()) {
    parse(command, file, tops, distincts, from, to);
    file.close();
  }
  print_result(command, tops, distincts, n);
  return 0;
}
