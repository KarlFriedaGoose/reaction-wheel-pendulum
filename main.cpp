#include <iostream>
#include <cmath>
#include "pendulum.hpp"
using namespace std;




int main()
{  

    PendulumSystem p1(1,1);
    
    PIDcontroller pend(30,0.5,12);
    double t_end = 10.0;  

    while(p1.time < t_end){
        

        double Fc= pend.compute(p1.theta, p1.theta_dot);



        p1.updatesystem(Fc);
 
        p1.print();
        
        

    }
	

    
  
}
