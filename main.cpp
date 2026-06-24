#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;
const double dt = 0.01;  // time stamp

class PendulumSystem {

    private:

//physical parameters of the rod

double L;   
double m;
double g;
double I_body;
// State 

double theta;  // im taking theta as positive clockwise
double theta_dot;
double theta_dotdot;


public:
double time = 0;



PendulumSystem(double mass, double length){

m=mass;
L=length;
g= 9.81;
I_body = m*L*L/3;   
theta = 0.5;        // initial conditions 
theta_dot = 0;

}

void updatesystem() {




theta_dotdot = m*g*L*sin(theta)/I_body;    // equation of motion of pendulum
theta_dot += theta_dotdot*dt;
theta += theta_dot*dt;
time +=dt;

if (theta > PI){


    theta -= 2.0*PI;
} else if (theta < -PI){            // I chose to have theta [-Pi,Pi], instead of [0,2pi]


    theta += 2.0 * PI;
}

}
void print (){

    cout << time << " " << theta << "  " << theta_dot <<"\n";
}

};

 



int main()
{  

    PendulumSystem p1(1,1);
    
    double t_end = 1.0;

    while(p1.time < t_end){


        p1.updatesystem();
 
        p1.print();
        
        

    }
	

    
  
}