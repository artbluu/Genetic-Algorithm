#ifndef INDIVIDUAL_HPP_INCLUDED
#define INDIVIDUAL_HPP_INCLUDED

#include<map>

float Rastrigin(float w[]);

struct Individual {
    string bit;
    float fitness;
    Individual():bit(),fitness(0){}
    Individual(string a):bit(a){
        fitness = count_fitness();
    }
    /**
    The fitness is calculated by dividing every 10 bits by the principle 0000.000000 and then converted to a decade system.
    0010.000001 (2.1)
    */
    float count_fitness(){
        int part_one=0,first_border = 4,tmp=1,second_border=6;
        float part_two=0,storage[dim];
        for(int k=0; k<dim; k++)
        {
            for(int i=0; i<bit.length()/dim; i++)
            {
                if(i<4)
                {
                    first_border--;
                    if(bit[i+k*10]=='1')
                    {
                       for(int m=0; m<first_border; m++)
                            tmp *= 2;
                        part_one+=tmp;
                        tmp = 1;
                    }
                }
                else
                {
                    second_border--;
                    if(bit[i+k*10]=='1')
                    {
                       for(int m=0; m<second_border; m++)
                            tmp *= 2;
                        part_two+=tmp;
                        tmp=1;
                    }
                }
            }
            if(bit[0+k*10] == '1')
                storage[k] = part_one + part_two/100;
            else
                storage[k] = part_one - part_two/100;
            part_one = 0;
            part_two = 0;
            first_border = 4;
            second_border = 6;
        }
        return Rastrigin(storage);
    }

    void print(){
        cout << "Chromosome: " << bit <<", fitness = " << count_fitness() << endl;
    }
};
/**
Production of random individuals
*/
Individual random_unit(){
    Individual a;
    string s = "";
    for(int i=0; i<dim*10;i++)
    {
        s+= (rand() % 2)+'0';
    }
    a.bit = s;
    return a;
}

/**
In mathematical optimization, the Rastrigin function is a non-convex function used as a performance test problem
for optimization algorithms.
*/
float Rastrigin(float w[]) {
    float sum=0;
    for(int i=0; i<dim; i++)
        sum += w[i]*w[i]-10*cos(2*3.14*w[i]);
    float fitness = 10*dim + sum;
    return fitness;
};

#endif // INDIVIDUAL_HPP_INCLUDED
