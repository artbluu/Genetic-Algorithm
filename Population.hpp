#ifndef POPULATION_HPP_INCLUDED
#define POPULATION_HPP_INCLUDED

#include<map>

struct Population {
    map<int,Individual> population;
    float total_fitness;

    Population():total_fitness(0){}
    void add_individual(Individual a,int i){
        population.insert(population.begin(),std::pair<int,Individual>(i,a));
    }
    /**
    Total fitness of population
    */
    float calculate_total(){
        total_fitness = 0;
        for(map<int,Individual>::iterator it = population.begin(); it!=population.end(); it++)
        {
            total_fitness += (*it).second.count_fitness();
        }
        return total_fitness;
    }
    /**
    The best individual is result of genetic algorithm,
    best individual is one with the lowest fitness
    */
    void print_the_best() {

        map<int,Individual>::iterator ib = population.begin(),k;
        float fit = ib->second.count_fitness();
        int key = 0;
        for(map<int,Individual>::iterator it = population.begin(); it!=population.end(); it++)
        {
            if(fit > it->second.count_fitness())
            {
                fit = it->second.count_fitness();
                key = it->first;
            }
        }
        k = population.find(key);
        cout << endl;
        k->second.print();

    }
    void print() {
         cout << endl << "Total fitness of generation is " << calculate_total() << endl;
    }
};

#endif // POPULATION_HPP_INCLUDED
