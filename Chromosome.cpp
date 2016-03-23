#include "Chromosome.h"

Chromosome::Chromosome(std::string d) : data(d)
{
}

std::string Chromosome::getData() const
{
	return data;
}

Chromosome Chromosome::mutate() const
{
	// implement mutation here
	// your mutate function should randomly choose
	// a character to modify then randomly choose
	// to either increment or decrement it
	// make sure to keep in range of lower-case letters!

	char randomChar;
	Chromosome c(data);

	int i = (rand() % data.length());
	randomChar = data.at(i);

	// randomizing increment/decrement
	if (rand() % 2 == 0) {
		randomChar--;
		if (randomChar == 96) {
			randomChar = 'z';
		}
	}
	else {
		randomChar++;
		if (randomChar == 123) {
			randomChar = 'a';
		}
	}
		// assign to data string
		c.data.at(i) = randomChar;

	return c;
}

Chromosome Chromosome::crossover(const Chromosome& c) const
{
	// implement crossover here
	// your crossover function should randomly choose
	// an index in the range of the chromosomes
	// then take the first part (up to the index) from *this
	// and the last part (from index to end) from c and
	// concatenate those together then return the result

	int index = 0;
	std::string result = "";

	index = rand() % (data.length()-2)+1;

	for (int i = 0; i < index; i++) {
		result += this->data.at(i);
	}

	for (int j = index; j < c.data.length(); j++) {
		result += c.data.at(j);
	}

	Chromosome cNew(result);

	return cNew;

}

int Chromosome::fitness(const std::string& target) const
{
	// computes fitness by sum of differences of each character
	// smaller is better (0 is perfect)

	int diff = 0;
	for (int i = 0; i < data.size(); i++)
	{
		int change = std::abs(data[i] - target[i]);
		if (change > 13) // handles wrap around for letters
		{
			change = 26 - change;
		}
		diff += change;
	}
	return diff;
}

int Chromosome::sizeChromosome() const
{
	return data.length();
}

std::ostream& operator<<(std::ostream& os, const Chromosome& c)
{
	os << c.getData();
	return os;
}
