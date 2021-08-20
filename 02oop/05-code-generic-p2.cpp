#include <iostream>
#include <string>
#include <sstream>

template< typename KeyType, typename ValueType>
class Mapping
{
public:
  Mapping(KeyType key, ValueType value) : key(key), value(value) {}
  std::string Print() const {
    std::ostringstream stream;
    stream << key << ": " << value;
    return stream.str();
  }
  KeyType key;
  ValueType value;
};

class Testing{};

std::ostream& operator<<(std::ostream &os, Mapping<std::string, int> const &mapping){
  os << mapping.key << ": " << mapping.value;
  return os;
}

int main()
{
  Mapping<std::string, int> mapping("age", 20);
  std::cout << mapping.Print() << std::endl;
  std::cout << mapping << "\n";
}