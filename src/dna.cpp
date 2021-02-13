#include "dna.hpp"

const float DNA::MUTATION_RATE = 0.01;
const std::string DNA::DICT= " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

DNA::DNA(int const& size): m_size(size)
{
    m_genes = getRandomString();
}

DNA::~DNA()
{
}

char DNA::getRandomChar() const
{
    int randInt = rand() % DNA::DICT.size();
    return DNA::DICT[randInt];
}

std::string DNA::getRandomString() const
{
    std::string randStr = "";
    for (int i = 0; i < m_size; i++)
    {
        randStr.push_back(getRandomChar());
    }

    return randStr;
}

float DNA::getFitness() const
{
    return m_fitness;
}

std::string DNA::getGenes() const
{
    return m_genes;
}

char DNA::getGene(int const& i) const
{
    return m_genes[i];
}

void DNA::setGene(int const& i, char const& newGene)
{
    m_genes[i] = newGene;
}

void DNA::updateFitness(std::string const& answer)
{
    int nb_of_correct_chars = 0;
    for (int i = 0; i < m_size; i++)
    {
        if (m_genes[i] == answer[i]) nb_of_correct_chars++;
    }

    float score = (float) nb_of_correct_chars * (float) nb_of_correct_chars;
    m_fitness = score / ((float) answer.size() * (float) answer.size());
    //std::cout << "fitness " << m_fitness << std::endl;
}

DNA DNA::getCrossoverChild(DNA const& parentB)
{
    DNA child(m_size);

    int midpoint = rand() % m_size;

    for (int i = 0; i < m_size; i++)
    {
        char newGene = (i < midpoint)? m_genes[i] : parentB.getGene(i);
        child.setGene(i, newGene);
    }

    return child;
}

void DNA::mutate()
{
    for (int i = 0; i < m_size; i++)
    {
        float r = (float) (rand() % 101) / 100.f; // random number between 0 and 1
        if (r < DNA::MUTATION_RATE)
        {
            m_genes[i] = getRandomChar();
        }
    }
}

std::ostream& operator<<(std::ostream &out, DNA const& self)
{
    out << self.m_genes;
    return out;
}