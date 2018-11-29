#include <algorithm>
#include <iostream>
#include <vector>

void print(const char * headline, const std::vector<int> & v)
{
   std::cout << headline << ' ';
   for (auto n : v)
   {
      std::cout << n << ' ';
   }
   std::cout << "(size: " << v.size() << ")" << std::endl;
}

int main(void)
{
   const std::vector<int> org = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
   std::vector<int> v = org;
   print("vector:         ", v);

   std::remove(v.begin(), v.end(), 3);
   print("remove 3:       ", v);

   v = org;
   v.erase(std::remove(v.begin(), v.end(), 3), v.end());
   print("erase-remove 3: ", v);

   return 0;
}
