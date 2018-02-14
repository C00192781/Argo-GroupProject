




#include <random>
#include <numeric> 
#include <assert.h>
#include <fstream>



int number_of_lines = 4;

// a vector to hold all the indices: 0 to number_of_lines
std::vector<int> line_indices(number_of_lines);
std::iota(begin(line_indices), end(line_indices), 0); // init line_indices

													  // C++11 random library (should be preferred over rand()/srand())
std::random_device r;
std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
std::mt19937 eng(seed);

// shuffle the line_indices:
std::shuffle(begin(line_indices), end(line_indices), eng);

int number_of_lines_to_select = 1;
assert(number_of_lines_to_select <= number_of_lines);

std::string line;
std::ifstream file("Resources/Config/Rumours.txt");

int line_number = 0;
while (std::getline(file, line))
{
	for (int i = 0; i < number_of_lines_to_select; ++i)
	{
		if (line_number == line_indices[i]) {
			std::cout << line << '\n';
		}
	}
	++line_number;
}