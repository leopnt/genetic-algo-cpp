#ifndef DEF_DNA_HPP
#define DEF_DNA_HPP

#include <stdlib.h>
#include <iostream>

class DNA
{
private:
    static const float MUTATION_RATE;
    static const std::string DICT;

    int m_size;
    std::string m_genes;
    float m_fitness;

    char getRandomChar() const;
    std::string getRandomString() const;

    friend std::ostream& operator<<(std::ostream &out, DNA const& self);

public:
    DNA(int const& length);
    ~DNA();
    float getFitness() const;
    std::string getGenes() const;
    char getGene(int const& i) const;
    void setGene(int const& i, char const& newGene);
    void updateFitness(std::string const& answer);
    DNA getCrossoverChild(DNA const& parentB);
    void mutate();
};

#endif