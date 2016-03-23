#include "Chromosome.h"

Chromosome randomChromosome(int size)
{
    std::ostringstream sout;
    for (int i = 0; i < size; i++)
    {
        sout << (char) ((rand() % 26) + 97);
    }
    return Chromosome(sout.str());
}

std::vector<Chromosome> newVector(std::vector<Chromosome>& v, int size, int length)
{
	for (int i = 0; i<size; ++i)
	{
		v.push_back(randomChromosome(length));
	}

	return v;
}

void copyHalf(std::vector<Chromosome>& full, std::vector<Chromosome>& half)
{
	for (int i = 0; i<full.size() / 2; ++i)
	{
		half[i] = full[i];
	}
}

Chromosome runGA(std::string target, int popSize, double mr, double cr)
{
	// implement genetic algorithm here
	// use a vector<Chromosome> for the population
	// I recommend using STL algorithms such as std::sort

	// remember, the GA is a loop until you find a chromosome
	// of fitness 0

	// on each iteration, you should be generating a new population
	// of twice the size of popSize, filling it with chromosomes
	// that have been mutated, crossed, and/or copied based on
	// the probabilities given by mr and cr
	// then sort it and keep only the best half as the population
	// for the next iteration
	// when you find a chromosome of fitness 0, you have finished and
	// you should return it

	std::vector<Chromosome> population;
	population = newVector(population, popSize, target.length());

	Chromosome solution(population[0]);
	int iteration = 0;
	do
	{
		std::vector<Chromosome> newPopulation;

		for (int i = 0; i<(popSize * 2); ++i)
		{
			int randomIndex = rand() % population.size();
			Chromosome aChromosome(population[randomIndex]);

			double randomPercentage = (rand() % 101) / 100.0;
			if (randomPercentage <= mr)
			{
				aChromosome = aChromosome.mutate();
			}

			randomPercentage = (rand() % 101) / 100.0;
			if (randomPercentage <= cr)
			{
				randomIndex = rand() % population.size();

				aChromosome = aChromosome.crossover(population[randomIndex]);
			}

			newPopulation.push_back(aChromosome);
		}

		auto lessThan = [&target](Chromosome& a, Chromosome& b)->bool { return a.fitness(target) < b.fitness(target); };
		std::sort(newPopulation.begin(), newPopulation.end(), lessThan);

		copyHalf(newPopulation, population);

		solution = population[0];

		std::cout << "Iteration number: " << iteration << std::endl;
		std::cout << "Solution: " << solution << std::endl;
		++iteration;

	} while (solution.fitness(target));
	return solution;
}

int main(int argc, char **argv)
{
	srand(time(0));
	for (int i = 1; i<5; ++i)
	{
		if (argv[i] == NULL)
		{
			std::cout << "\nNot enough arguments. Should be:" << std::endl;
			std::cout << "( Chromosome, population, mutation_rate, crossover_rate )\n" << std::endl;
		}
	}

	std::string target = argv[1];
	int popSize = atoi(argv[2]);
	double mr = atof(argv[3]);
	double cr = atof(argv[4]);
	Chromosome answer = runGA(target, popSize, mr, cr);

	std::cout << "\nSolution found: " << answer << "\n" << std::endl;

}