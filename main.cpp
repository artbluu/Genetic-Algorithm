#include <iostream>
using namespace std;
#include <stdlib.h>
#include<time.h>
#include<math.h>
#define dim 4
#define Cr 85
#include"Individual.hpp"
#include"Population.hpp"
#include"Functions.hpp"

int main(){
    Individual individual;
    Population population;
    int generations_num,new_number_of_units,menu;
    int max_population;
    srand(time(0));

    cout << "Genetic Algorithm " << endl;
    cout << "Enter population maximum: ";
    cin >> max_population;
    if(cin.fail()) return 1;

    if(max_population < 4)
    {
        cout << "Error, you haven't entered a number larger than 3";
        return 1;
    }
    for(int i=0; i<max_population; i++)
    {
        individual = random_unit();
        population.add_individual(individual,i);
    }
    while(menu != 8)
    {

        cout << endl << "Enter option: (Menu 0, Exit 8)  ";
        cin >> menu;
        if (cin.fail()) break;


        switch(menu)
        {
            case 8 : return 0;
                break;
            case 1 :    print_generation(population);
                break;
            case 2 :    evolve(population,1,max_population);
                break;
            case 3 :    evolve(population,10,max_population);
                break;
            case 4 :    cout << "Enter number of generations ";
                        cin >> generations_num;
                        if(cin.fail()) return 1;

                        evolve(population,generations_num,max_population);
                break;
            case 5 :    population.print_the_best();
                break;
            case 6 :    population.print();
                break;
            case 7 :    cout << "Currently there is " << max_population <<" individuals, enter new number of individuals: ";
                        cin >> new_number_of_units;
                        if(new_number_of_units < 4)
                        {
                            cout << "the number of individuals can not be less than 4 !";
                            return 1;
                        }
                        if(new_number_of_units > max_population)
                        {
                            for(int i=0; i<(new_number_of_units-max_population); i++)
                            {
                                individual = random_unit();
                                population.add_individual(individual,population.population.size()+1);
                            }
                        }
                        max_population = new_number_of_units;
                        reduce(population,max_population);
                break;
            case 0 :    cout << endl << "Menu: " << endl << "1.Show generation" << endl;
                        cout << "2.Evolve 1 generation"   << endl;
                        cout << "3.Evolve 10 generations" << endl;
                        cout << "4.Evolve arbitrary number of generations" << endl;
                        cout << "5.Print the best individual" << endl;
                        cout << "6.Show total fitness of generation" << endl;
                        cout << "7.Change population size" << endl;
                        cout << "8.End of program" << endl;
                break;
            default:    cout <<"Error, wrong number";
        }
    }
}
