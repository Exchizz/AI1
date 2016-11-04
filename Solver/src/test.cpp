#include <unordered_map>
#include <iostream>

class Test {
public:
  int a;
  int b;

  bool operator==(const Test & other) const {
    return (a == other.a && b == other.b);
  }
};



namespace std {
  template <>
  struct hash<Test>
  {
    std::size_t operator()(const Test& k) const
    {
      using std::size_t;
      using std::hash;
      //using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      std::cout << "hashing " << ((hash<int>()(k.a) ^ (hash<int>()(k.b) << 1)) >> 1) << std::endl;
      return ((hash<int>()(k.a) ^ (hash<int>()(k.b) << 1)) >> 1);
    }
  };

}


int main(){
  std::unordered_map<Test, int>maps;

  Test * test1 = new Test();
  test1->a = 2;
  test1->b = 4;

  auto retval = maps.insert(std::make_pair(*test1, 1));

  std::cout << "size: " <<  maps.size() << " inserted: " << retval.second << std::endl;

  Test * test2 = new Test();
  test2->a = 2;
  test2->b = 4;

  if( *test1 == *test2){
    std::cout << "equal" << std::endl;
  }
  retval = maps.insert(std::make_pair(*test2, 1));

  std::cout << "size: " <<  maps.size() << " inserted: " << retval.second << std::endl;


}
