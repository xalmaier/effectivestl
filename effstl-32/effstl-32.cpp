#include <algorithm>
#include <iostream>
#include <vector>

void print(const std::vector<int> & v, const char * headline = "")
{
   std::cout << headline;
   for (auto n : v)
   {
      std::cout << n << ' ';
   }
   std::cout << "(size: " << v.size() << ")" << std::endl;
}

int main(void)
{
   std::cout << "std::vector<int> v = { 1, 2, 3, 0, 5, 0, 7, 8, 9, 0 };" << std::endl;
   std::vector<int> v = { 1, 2, 3, 0, 5, 0, 7, 8, 9, 0 };
   print(v, "v: ");// 1 2 3 0 5 0 7 8 9 0 (size: 10)

   std::cout << "const auto it = remove(v.begin(), v.end(), 0);" << std::endl;
   const auto it = remove(v.begin(), v.end(), 0);
   print(v, "v: ");// 1 2 3 5 7 8 9 8 9 0 (size: 10)
   //                               it

   // so what does remove do?
   // - moves elements in the range it's given until all "unremoved"
   //   elements are at the front of the range (in the same relative order)
   // - it returns an iterator pointing one past the last "unremoved" element
   // - the removed elements are NOT at the end of the range (NOT 0 0 0)

   std::cout << "print elements from it to v.end():" << std::endl;
   auto it2 = it;
   while (it2 != v.end())
   {
      std::cout << *it2++ << ' ';
   }
   std::cout << std::endl;

   std::cout << "v.erase(it, v.end());" << std::endl;
   v.erase(it, v.end());
   print(v, "v: ");// 1 2 3 5 7 8 9 (size: 7)

   // how does it work?
   // v: 1 2 3 0 5 0 7 8 9 0
   // v[0]: 1 -> no remove                                      // 1   2   3   0   5   0   7   8   9   0
   // v[1]: 2 -> no remove                                      // 1   2   3   0   5   0   7   8   9   0
   // v[2]: 3 -> no remove                                      // 1   2   3   0   5   0   7   8   9   0
   // v[3]: 0 -> remove -> note that v[3] may be overwritten    // 1   2   3  [0]  5   0   7   8   9   0
   // v[4]: 5 -> no remove -> v[3] will be overwritten with <5> // 1   2   3  <5>  5   0   7   8   9   0
   //                      -> v[4] may be overwritten           // 1   2   3   5  [5]  0   7   8   9   0
   // v[5]: 0 -> remove -> note that v[5] may be overwritten    // 1   2   3   5  [5] [0]  7   8   9   0
   // v[6]: 7 -> no remove -> v[4] will be overwritten with <7> // 1   2   3   5  <7> [0]  7   8   9   0
   //                      -> v[6] may be overwritten           // 1   2   3   5   7  [0] [7]  8   9   0
   // v[7]: 8 -> no remove -> v[5] will be overwritten with <8> // 1   2   3   5   7  <8> [7]  8   9   0
   //                      -> v[7] may be overwritten           // 1   2   3   5   7   8  [7] [8]  9   0
   // v[8]: 9 -> no remove -> v[6] will be overwritten with <9> // 1   2   3   5   7   8  <9> [8]  9   0
   //                      -> v[8] may be overwritten           // 1   2   3   5   7   8   9  [8] [9]  0
   // v[9]: 0 -> remove -> note that v[9] may be overwritten    // 1   2   3   5   7   8   9  [8] [9] [0]
   // end -> iterator is pointing to v[7] which is 8 at this moment

   std::cout << std::endl << "Now in one step..." << std::endl << "v = { 1, 2, 3, 0, 5, 0, 7, 8, 9, 0 };" << std::endl;
   v = { 1, 2, 3, 0, 5, 0, 7, 8, 9, 0 };
   print(v, "v: ");

   std::cout << "v.erase(std::remove(v.begin(), v.end(), 0), v.end());" << std::endl;
   v.erase(std::remove(v.begin(), v.end(), 0), v.end());
   print(v, "v: ");

   return 0;
}
