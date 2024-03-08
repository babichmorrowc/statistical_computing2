#include "part1.h"
#include "filecounter.h"

using namespace part1;
using namespace filecounter;

int main(int argc, char **argv) // gives you access to command line arguments
{
  auto filenames = get_arguments(argc, argv);
  auto results = map(count_lines, filenames);
  
  // print_vector(filenames);
  // print_vector(results);
  
  for (int i = 0; i < filenames.size(); i++)
  {
    std::cout << filenames[i] << " has " << results[i] << " lines." << std::endl;
  }
  
  return 0;
  
}