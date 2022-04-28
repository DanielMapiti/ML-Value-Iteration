#include "valueIteration.h"

state::state(){}
state::state(std::vector<char> a, std::map<int, int> r, int v, int sn, float d, float p){
    stateNo=sn;
    action=a;
    reward=r;
    value=v;
    discount=d;
    probability=p;
}
state::~state(){}
float state::get_discount(){
  return discount;
}
float state::get_probability(){
  return probability;
}
std::map<int, int> state::get_reward(){
  return reward;
}
int state::get_stateNo(){
  return stateNo;
}
float state::get_value(){
  return value;
}
void state::set_value(float v){
  value=v;
}
std::vector<char> state::get_action(){
  return action;
}

grid::grid(){}
grid::~grid(){}
grid::grid(std::vector<std::vector<state> > w){
  world=w;
}

int grid::getIterations(){
  return it;
}

bool grid::converge(grid lhs){
  for (int column = 0; column < 2; column++) {
    for (int row = 0; row < 3; row++) {
      if (world[column][row].get_value()!=lhs.world[column][row].get_value()) {
        return false;
      }
    }
  }
  return true;
}

void grid::Max() {
  grid g, temp;
  state s;
  s.set_value(1.0);
  g.world={{s,s,s},{s,s,s}};
  temp.world=g.world;
  int iteration = 0;
  while (!(converge(g))) {
    for (int column = 0; column < 2; column++) {
      for (int row = 0; row < 3; row++) {
        state next_state;
        for(char a: world[column][row].get_action()){
          if (a=='u') {
              next_state=world[column-1][row];
              world[column][row].set_value(std::max(world[column][row].get_value(), world[column][row].get_reward()[next_state.get_stateNo()]+world[column][row].get_discount()*next_state.get_value()));
            }
            
          else if(a== 'd'){
              next_state=world[column+1][row];
              world[column][row].set_value(std::max(world[column][row].get_value(), world[column][row].get_reward()[next_state.get_stateNo()]+world[column][row].get_discount()*next_state.get_value()));
            }
          else if(a=='l'){
              next_state=world[column][row-1];
              world[column][row].set_value(std::max(world[column][row].get_value(), world[column][row].get_reward()[next_state.get_stateNo()]+world[column][row].get_discount()*next_state.get_value()));
            }
         else if(a=='r'){
              next_state=world[column][row+1];
              world[column][row].set_value(std::max(world[column][row].get_value(), world[column][row].get_reward()[next_state.get_stateNo()]+world[column][row].get_discount()*next_state.get_value()));
            }
           
          
        }
      }
    }

    g.world=temp.world;
    temp.world=world;
    iteration++;
  }
it =iteration;
printToFile("Answers.txt");
}

void grid::printToFile(std::string filename){
    std::ofstream ofs;
    ofs.open(filename);
    ofs <<"\t\t\t\t\t Question 1 \n\n";
    ofs<<"- Number of iterations is: ";
    ofs<<this->getIterations()<<"\n\n";
    ofs<<"- All the optimal values for each state in the given gid are: "<<"\n";
    
    ofs<<"\tv* for state s1 = "<<world[0][0].get_value()<<"\n";
    ofs<<"\tv* for state s2 = "<<world[0][1].get_value()<<"\n";
    ofs<<"\tv* for state s3 = "<<world[0][2].get_value()<<"\n";
    ofs<<"\tv* for state s4 = "<<world[1][0].get_value()<<"\n";
    ofs<<"\tv* for state s5 = "<<world[1][1].get_value()<<"\n";
    ofs<<"\tv* for state s6 = "<<world[1][2].get_value()<<"\n"<<"\n";
    ofs<<"\n\n\n";
    ofs <<"\t\t\t\t\t Question 2 \n\n";
    ofs<<"- The are two paths that gives the optimal policy to reach states s3 from s1:\n";
    ofs<<"\t(i) s1->s2->s5->s6->s3\n\t(ii) s1->s4->s5->s6->s3\n\n\n";
    ofs<<"\n\n\n";
    ofs <<"\t\t\t\t\t Question 3 \n\n";
    ofs<<"-Yes it is possible to change the Reward function and the V* changes but the optimal policy remains unchanged. By doubling each immediate reward. Then V∗ is also doubled and π∗remains unchanged."<<"\n";
    ofs.close();
}


int main(){
  state s1, s2, s3, s4, s5, s6;
  s1=state({'r','d'},{},0,1,0.8,1.0);
  s2=state({'l','r','d'},{{3,50}},0,2,0.8,1.0);
  s3=state({'i'},{},0,3,0.8,1.0);
  s4=state({'u','r'},{},0,4,0.8,1.0);
  s5=state({'u','l','r'},{},0,5,0.8,1.0);
  s6=state({'u','l'},{{3,100}},0,6,0.8,1.0);
  grid g({{s1,s2,s3},{s4,s5,s6}});

  g.Max();
  return 0;
}
