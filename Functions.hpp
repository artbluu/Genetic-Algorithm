#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_HPP_INCLUDED

#include<map>
#include <sstream>
#include <string>

/**
Two individuals are crossovering themselves creating a new one.
A new individual for each bit has a 50% chance of inheriting from one parent
*/
void crossover(Population &k)
{
    int first,second;
    int cr = (Cr*k.population.size())/100;
    for(int i=0; i<cr; i++)
    {
        map<int,Individual>::iterator it1,it2,it3;
        first = rand()%cr;
        second = rand()%cr;
        if(first == second)
        {
            first+=1;
            if(first == cr)
                first-=2;
        }
        it1 = k.population.find(first);
        it2 = k.population.find(second);
        k.add_individual(it1->second,k.population.size());

        for(int p=0; p<dim*10; p++)
        {
            int way = rand()%2;
            if(way == 0)
                it1->second.bit[p] = it2->second.bit[p];
        }
        /**
        The mutation chance is 0.8%, one bit is selected and changed.
        */
        int mutation = rand()%80;
        if(mutation == 1)
        {
            int k = rand()%(dim*10);
            if(it1->second.bit[k] == '1')
                it1->second.bit[k]= '0';
            else
                it1->second.bit[k] = '1';
        }
        it3 = k.population.end();
        it3--;

        string temp1, temp2;
        temp1 = it1->second.bit;
        temp2 = it3->second.bit;
        it1->second.bit = temp2;
        it3->second.bit = temp1;
        it1->second.fitness = it1->second.count_fitness();
        it3->second.fitness = it3->second.count_fitness();
    }
}

/**
Population size is fixed. After each evolution, population is increasing because of crossover.
In order to keep population number same we use reduction.The worse individuals die unti a limit is reached.
(The worst individual = the one with highest fitness)
*/
void reduce(Population &k, int max_population)
{
    while(k.population.size() != max_population)
    {
        map<int,Individual>::iterator it,it_begin;
        it_begin = k.population.begin();
        int fitness = it_begin->second.count_fitness();
        int key = it_begin->first;
        for(it = k.population.begin(); it!=k.population.end(); it++)
        {
            if(fitness < it->second.count_fitness())
            {
                fitness = it->second.count_fitness();
                key = it->first;
            }
        }
        k.population.erase(key);

    }
    /**
    Placing all survived individuals in map
    */
    map<int,Individual> maps;
    map<int,Individual>::iterator it,mit;
    int position = 0;
    Individual temp;
    for(it = k.population.begin(); it!=k.population.end(); it++)
    {
        temp = it->second;
        maps.insert(maps.begin(),std::pair<int,Individual>(position,temp));
        position++;
    }
    k.population = maps;

}
void print_generation(Population k)
{
    for(map<int,Individual>::iterator it=k.population.begin(); it!=k.population.end(); it++)
    {
        cout << it->first << " ";
        it->second.print();
    }
}
/**
Creating next generation
*/
void evolve(Population &k, int n, int max_population)
{
    for(int i=0; i<n; i++)
    {
        crossover(k);
        reduce(k,max_population);
    }

}

#endif // FUNCTIONS_HPP_INCLUDED
