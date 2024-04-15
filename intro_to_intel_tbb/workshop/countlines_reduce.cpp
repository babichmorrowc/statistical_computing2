#include "part1.h"
#include "filecounter.h"

using namespace part1;
using namespace filecounter;

int sum(int x, int y)
{
  return x + y;
}

int main(int argc, char **argv) // gives you access to command line arguments
{
  auto filenames = get_arguments(argc, argv);
  auto results = map(count_lines, filenames);
  auto total = reduce(sum, results);
  
  std::cout << "Total number of lines: " << total << std::endl;
  
  return 0;
  
}