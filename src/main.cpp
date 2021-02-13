#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>

#include "dna.hpp"

#define POPULATION_SIZE 1000

DNA pickParent(std::vector<DNA> const& matingPool);
DNA getFitest(std::vector<DNA> const& population, int const& dna_size);

int main(int argc, char *argv[])
{
    if (argc != 2) // check arguments correct
    {
        std::cout << "Usage: main.exe \"phrase\"" << std::endl;
        return EXIT_FAILURE;
    }

    // get phrase from arguments
    const std::string phrase = argv[1];
    const int pLen = phrase.size();
    
    /* initialize random seed: */
    srand (time(NULL));

    /* initializing population */
    std::vector<DNA> population;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        DNA entity(pLen);
        population.push_back(entity);
        population[i].updateFitness(phrase);
    }

    int epoch = 0;
    /* starting evolution */
    do
    {
        std::cout << "\r"; // \r will erase the current line at next cout

        /* creating matingPool */
        std::vector<DNA> matingPool;
        for (int i = 0; i < (int) population.size(); i++)
        {
            int n = (int) round(population[i].getFitness() * 100.0);
            for (int j = 0; j < n; j++)
            {
                matingPool.push_back(population[i]);
            }
        }

        /* Reproducting population */
        for (int i = 0; i < (int) population.size(); i++)
        {
            DNA parentA = pickParent(matingPool);
            DNA parentB = pickParent(matingPool);

            DNA child = parentA.getCrossoverChild(parentB);
            child.updateFitness(phrase);

            child.mutate();
            population[i] = child;
        }

        std::cout << "epoch: " << epoch << " => ";
        std::cout << getFitest(population, phrase.size());
        epoch++;
    }
    while (getFitest(population, phrase.size()).getGenes() != phrase);

    std::cout << std::endl;

    return EXIT_SUCCESS;
}

DNA pickParent(std::vector<DNA> const& matingPool)
{
    int r = rand() % matingPool.size();
    return matingPool[r];
}

DNA getFitest(std::vector<DNA> const& population, int const& dna_size)
{
    float bestFitness = 0.f;
    DNA fitest(dna_size);
    for(int i = 0; i < (int) population.size(); i++)
    {
        if (population[i].getFitness() > bestFitness)
        {
            fitest = population[i];
            bestFitness = population[i].getFitness();
        }
    }
    return fitest;
}