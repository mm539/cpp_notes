#include <assert.h>
#include <string>
#include <sstream>

/*
  The purpose of this document is to show that the <maps> is implemented using templates by providing a very basic version of a map class.

*/

template <typename KeyType, typename ValueType>
class Mapping {
public:
  Mapping(KeyType key, ValueType value) : key(key), value(value) {}
  std::string Print() const{
    std::ostringstream stream;
    stream << key << ": " << value;
    return stream.str();
  }
  KeyType key;
  ValueType value;
};

int main()
{
  Mapping<std::string, int> bob("bob", 20);
  assert(bob.Print() == "bob: 20");
}