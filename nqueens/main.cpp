#include<bits/stdc++.h>
using namespace std;
#include<chrono>
using namespace std::chrono;
#include "TextTable.h"

#include "BruteForce.h"

// step 1 representing individual in the form of array where

// index represents column and value represents row now at which queen is present

// step 2 generate initial population 4*N population are generated..

// step 3 calculate the fitness per person

// step 4 cross and mutant

// step 5 selection on the basis of the most good fitness

// step 6 repeat if solution not found

class GeneticAlgo{

public:
    vector<vector<int>>population;
    int size;
    int popsize=500;
    int IdealFit;

    GeneticAlgo(int n){
        IdealFit=(n*(n-1))/2;
        size=n;
        population.clear();
        popsize*=4;
    }


    void InitialPopulation(){
        for(int i=0;i<popsize;i++){
            vector<int>p(size);
            for(int j=0;j<size;j++){
                p[j]= GetRandom(0,size-1);
            }
            population.push_back(p);
        }
    }


    int Fitness(vector<int>person){
        int fit=IdealFit;
        for(int i=0;i<size;i++){
            for(int j=i+1;j<size;j++){
                if(HitCondition(person[i],i,person[j],j))
                    fit--;
            }
        }
        return fit;
    }

    bool HitCondition(int r1,int c1,int r2,int c2){
        if(r1==r2)
            return true;
        if(c1==c2)
            return true;

        int dif=abs(r1-r2);
        if(c1+dif==c2)
            return true;
        if(c1-dif==c2)
            return true;

        return false;
    }

    void CrossOver(vector<int>&p1,vector<int>&p2){
        for(int i=1;i<size;i++){
            if(abs(p1[i-1]-p1[i])<2)
                swap(p1[i],p2[i]);
            if(abs(p2[i-1]-p2[i])<2)
                swap(p2[i],p1[i]);
        }
    }

    vector<int> MutantGen(vector<int>&p){
        int bound=size/2;
        int leftside= GetRandom(0,bound);
        int rightside= GetRandom(bound+1,size-1);
        vector<int>newp;
        set<int>have;

        for(auto it:p){
            if(have.find(it)==have.end()){
                have.insert(it);
                newp.push_back(it);
            }
        }
        for(int i=0;i<size;i++){
            if(have.find(i)==have.end()){
                have.insert(i);
                newp.push_back(i);
            }
        }
        while((int)newp.size()>size)
            newp.pop_back();

        swap(newp[leftside],newp[rightside]);
        return newp;
    }

    int GetRandom(int l,int r){
        if(l>r)return l;
        std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(l,r); // define the range
        return distr(gen);
    }


    void CrossOverMutant(){
        for(int i=1;i<popsize;i+=2){
            auto p1=population[i-1];
            auto p2=population[i];
            CrossOver(p1,p2);
            p1= MutantGen(p1);
            p2= MutantGen(p2);
            population.push_back(p1);
            population.push_back(p2);
        }
    }

    vector<vector<int>>makeSelection(){
        int nsize=(int)population.size();
        vector<vector<int>>newpopulation;
        vector<pair<int,vector<int>>>storefit(nsize);
        for(int i=0;i<nsize;i++){
            storefit[i].first=Fitness(population[i]);
            storefit[i].second=population[i];
        }

        sort(storefit.begin(),storefit.end());
        reverse(storefit.begin(),storefit.end());
        for(int i=0;i<popsize;i++)
            newpopulation.push_back(storefit[i].second);

        return newpopulation;
    }
    vector<int>solveGA(){
        InitialPopulation();

        while(true){
            for(int i=0;i<popsize;i++){
                if(Fitness(population[i])==IdealFit)
                    return population[i];
            }

            CrossOverMutant();
            population=makeSelection();
        }
    }
};


void printboard(vector<vector<int>>board){
   TextTable t('-','|','+');
   int n=(int)board.size();
   for(int i=0;i<n;i++){
       for(int j=0;j<n;j++){
           if(board[i][j])
               t.add(" Q ");
           else
               t.add("   ");
       }
       t.endOfRow();
   }
    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    std::cout << t;
    cout<<endl;
}


void RunBruteForc(int n){

    if(n>29){
        cout<<"Warning n>29  it might take minutes to compute :("<<endl;
    }
    auto start = high_resolution_clock::now(); // Start time
    vector<vector<int>>board=solveNQueens(n);

    auto stop = high_resolution_clock::now(); // Stop time


    printboard(board);
    cout<<endl;

    auto duration = duration_cast<microseconds>(stop - start); // Duration
    double x=duration.count()/1000000.00;
    cout << fixed<<"\nTime taken by Brute force backtracking Algorithm is : "<< x << " seconds";
    cout<<endl;

}

int main(){
    cout<<"give the size of board : ";
    int n;cin>>n;
    cout<<endl;


    GeneticAlgo ga(n);

    auto start = high_resolution_clock::now(); // Start time

    auto temp=ga.solveGA();

    auto stop = high_resolution_clock::now(); // Stop time


    vector<vector<int>>board(n,vector<int>(n));
    for(int i=0;i<n;i++){
        board[temp[i]][i]=1;
    }


    printboard(board);
    cout<<endl;

    auto duration = duration_cast<microseconds>(stop - start); // Duration
    double x=duration.count()/1000000.00;
    cout << fixed<<"\nTime taken by Genetic Algorithm is : "<< x << " seconds";

    cout<<endl<<endl;
    cout<<"* Press 1 to compare with Brute force backtracking Algorithm"<<endl;
    cout<<"* Else press 0 to exit ";

    int comm;
    cin>>comm;
    if(comm){
        RunBruteForc(n);
    }

        cout<<"Thank You :)";

    return 0;
}