#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <string>
using namespace std;

class GA
{
    int populationSize;
    int initialFeatures;
    int kSection;
    int noOfGeneration;
    int **chromosomes;
    int *survivalPoints;
    int *Weights;
    int weightLimit;
    int previousSurvival;

public:
    void initGa()
    {
        cout << "Input Population Size:  ";
        cin >> populationSize;
        // cout << "Input Feature Size:  ";
        // cin >> initialFeatures;
        cout << "Input K Section:  ";
        cin >> kSection;

        cout << "Input Number of Generations:  ";
        cin >> noOfGeneration;

        // Setting the Features for this GA to be 10
        initialFeatures = 8;
        previousSurvival = -1;

        weightLimit = 30;

        survivalPoints = new int[initialFeatures];
        Weights = new int[initialFeatures];

        survivalPoints[0] = 10; //Pocket Knife
        survivalPoints[1] = 15; //Potatoes
        survivalPoints[2] = 30; //Seeping Bag
        survivalPoints[3] = 10; //Rope
        survivalPoints[4] = 30; //Compass
        survivalPoints[5] = 15; //Carrots
        survivalPoints[6] = 25; //Torch
        survivalPoints[7] = 25; //Skate Board

        Weights[0] = 1;  //Pocket Knife
        Weights[1] = 10; //Potatoes
        Weights[2] = 7;  //Seeping Bag
        Weights[3] = 5;  //Rope
        Weights[4] = 2;  //Compass
        Weights[5] = 10; //Carrots
        Weights[6] = 2;  //Torch
        Weights[7] = 10; //Skate Board

        chromosomes = new int *[populationSize];
        for (int i = 0; i < populationSize; i++)
        {
            chromosomes[i] = new int[initialFeatures];
        }

        srand(time(NULL));
        for (int i = 0; i < populationSize; i++)
        {
            for (int j = 0; j < initialFeatures; j++)
            {
                chromosomes[i][j] = rand() % 2;
            }

                if (isFit(i))
                {
                    for (int j = 0; j < initialFeatures; j++)
                    {
                        chromosomes[i][j] = rand() % 2;
                    }
                }
                
        }

        // cout << "pop = " << populationSize << endl;
    }

    bool Fitness(int index)
    {
        int tWEight = 0;
        int count = 0;
        int currentSurvivalPoint = 0;

        for (int i = 0; i < initialFeatures; i++)
        {
            if (chromosomes[index][i] != 0)
                tWEight += Weights[i];
        }

        if (tWEight > weightLimit)
        {
            // cout << "Failed due to weight\n";
            return false;
        }

        for (int i = 0; i < initialFeatures; i++)
        {
            if (chromosomes[index][i] != 0)
            {
                currentSurvivalPoint += (survivalPoints[i] / Weights[i]);
            }
        }

        if (currentSurvivalPoint > previousSurvival)
        {
            // cout << "surv = " << currentSurvivalPoint << endl;
            previousSurvival = currentSurvivalPoint;
        }

        if (currentSurvivalPoint > 14)
        {
            return true;
        }

        return false;
    }


    bool isFit(int index)
    {
        int currentSurvivalPoint = 0;
        for (int i = 0; i < initialFeatures; i++)
        {
            if (chromosomes[index][i] != 0)
            {
                currentSurvivalPoint += survivalPoints[i];
            }
        }
        if (currentSurvivalPoint > 14)
        {
            return true;
        }

        return false;
    }

    void Selection()
    {
        previousSurvival = -1;
        vector<int *> Selected;
        int tCount = 0;
        for (int i = 0; i < populationSize; i++)
        {
            if (Fitness(i))
            {
                // cout << "selected: " << i << endl;
                Selected.push_back(chromosomes[i]);
                tCount++;
            }
        }

        //    for (int i = 0; i < populationSize; i++)
        //    {
        //        delete chromosomes[i];
        //    }

        populationSize = tCount;
        chromosomes = new int *[populationSize];
        for (int i = 0; i < populationSize; i++)
        {
            chromosomes[i] = new int[initialFeatures];
        }

        for (int i = 0; i < populationSize; i++)
        {
            chromosomes[i] = Selected[i];
        }
        // cout << "pop = " << populationSize << endl;
    }

    void CrossOver()
    {
        float number_of_chromosomes;
        int number_of_chromosomes_round;
        number_of_chromosomes = populationSize;
        // number_of_chromosomes = static_cast<float>(populationSize) / static_cast<float>(initialFeatures);
        // cout << number_of_chromosomes << endl;
        number_of_chromosomes_round = ceil(number_of_chromosomes);
        // cout << number_of_chromosomes_round << endl;
        // chromosomes = new int *[number_of_chromosomes_round];
        // for (int i = 0; i < number_of_chromosomes_round; i++)
        // {
        //     chromosomes[i] = new int[initialFeatures];
        // }
        // srand(time(NULL));
        //Randomly generating values in chromosomes
        // for (int i = 0; i < number_of_chromosomes_round; i++)
        // {
        //     for (int j = 0; j < initialFeatures; j++)
        //     {
        //         chromosomes[i][j] = rand() % 100;
        //     }
        // }
        //chromosomes before crossover
        // for (int i = 0; i < number_of_chromosomes_round; i++)
        // {
        //     for (int j = 0; j < initialFeatures; j++)
        //     {
        //         cout << chromosomes[i][j] << ",";
        //     }
        //     cout << endl;
        // }

        //Crossover
        float crossover_point;
        crossover_point = static_cast<float>(initialFeatures) / 2.0;
        // cout << crossover_point << endl;
        int crossover_point_round;
        crossover_point_round = ceil(crossover_point);
        // cout << crossover_point_round << endl;
        int crossover_point_two;
        crossover_point_two = initialFeatures - crossover_point_round;
        // cout << crossover_point_two << endl;
        int *temp_2 = new int[crossover_point_two];
        int *temp_4 = new int[crossover_point_two];
        int chromosomes_final;
        if (number_of_chromosomes_round % 2 == 0)
        {
            chromosomes_final = number_of_chromosomes_round;
        }
        else if (number_of_chromosomes_round % 2 != 0)
        {
            chromosomes_final = number_of_chromosomes_round - 1;
        }
        for (int i = 0; i < chromosomes_final; i = i + 2)
        {
            for (int j = 0; j < crossover_point_two; j++)
            {
                temp_2[j] = 0;
                temp_4[j] = 0;
            }
            for (int j = crossover_point_round, k = 0; j < initialFeatures; j++, k++)
            {
                temp_2[k] = chromosomes[i + 1][j];
                temp_4[k] = chromosomes[i][j];
            }
            for (int j = crossover_point_round, k = 0; j < initialFeatures; j++, k++)
            {
                chromosomes[i][j] = temp_2[k];
                chromosomes[i + 1][j] = temp_4[k];
            }
        }
    }

    void Mutation()
    {
        srand(time(NULL));
        for (int i = 0; i < populationSize; i++)
        {
            for (int j = initialFeatures - 3; j < initialFeatures; j++)
            {

                chromosomes[i][j] = rand() % 2;
            }
        }
    }

    void initAlgo()
    {
        for (int i = 0; i < noOfGeneration; i++)
        {
            Selection();
            CrossOver();
            Mutation();
            // cout << populationSize << endl;
            // cout << "Generation id: " << i + 1 << "  :: Most Advanced Fitness: " << previousSurvival << endl;
        }
    }

    void Display()
    {
        for (int i = 0; i < populationSize; i++)
        {
            for (int j = 0; j < initialFeatures; j++)
            {
                cout << chromosomes[i][j] << "   ";
            }
            cout << endl;
        }
    }
};

int main()
{
    GA algo;
    srand(time(NULL));
    algo.initGa();

    int i = 0;
    algo.Display();
    // cout << "------------------\n------------------\n";
    algo.initAlgo();
    cout << "------------------\n------------------\n-------------------\n";
    algo.Display();
}