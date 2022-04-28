#include <iostream>
#include <vector>
#include <map>
#include "string.h"
#include <algorithm>    
#include <fstream>
#include "float.h"

#ifndef VALUEITERATION_H
#define VALUEITERATION_H
using namespace std;
class state{
    private:
        int stateNo;
        vector<char> action;
        map<int, int> reward;
        float discount;
        float probability;
        float value;
    public:
        state();
        state(std::vector<char> a, std::map<int, int> r, int v, int sn, float d, float p);
        ~state();
        int get_stateNo();
        vector<char> get_action();
        map<int,int> get_reward();
        float get_discount();
        float get_probability();
        float get_value();
        void  set_value(float v);
        

};


class grid{
    private:
      std::vector<std::vector<state>> world;
    public:
    int it;
      grid();
      ~grid();
      grid(std::vector<std::vector<state>> w);
      void to_string();
      void Max();
      bool converge(grid);
      void write_optimal(int);
      void printToFile(std::string filename);
      int getIterations();

};

#endif
