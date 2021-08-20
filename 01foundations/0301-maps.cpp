#include <unordered_map>
#include <string>
#include <vector>

// this needs to be greatly expanded
// there was an example with the country codes.

int main(){
  std::string key{ "ni hao"};

  std::unordered_map <std::string, std::vector<std::string>> my_map{
    { key , {'a', 'b'}},
    { "bai", {'c', 'd'}}
    //...
  };

  

  my_map.find(key);
  my_map[key];
  my_map.end();

}
