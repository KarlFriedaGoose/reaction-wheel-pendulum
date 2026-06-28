#include <cmath>
#include <iostream>
using namespace std;
const double PI = 3.14159265358979323846;
const double dt = 0.01;

class PendulumSystem {

    private:

//physical parameters of the rod

double L;   
double m;
double g;
double I_body;
// State 



public:
double time = 0;    // theta is positive clockwise
double theta;
double theta_dot;
double theta_dotdot;


PendulumSystem(double mass, double length){

m=mass;
L=length;
g= 9.81;
I_body = m*L*L/3;   
theta = 0.5;        // initial conditions 
theta_dot = 0;

}

void updatesystem(double Fc) {




theta_dotdot = (m*g*L*sin(theta) - Fc)/I_body;    // equation of motion of pendulum
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


class PIDcontroller {

private:

double kp; 
double ki;
double kd;
double integral;



                     
public: PIDcontroller(double p_coefficient, double i_coefficient, double d_coefficient ){


    kp = p_coefficient;
    ki = i_coefficient;
    kd = d_coefficient;
    integral = 0;

}

double compute ( double error, double d_error) {

integral += error *dt;


 double Fc = kp*error + ki*integral + kd*d_error; /* Ive used "error " and "d_error" because id like to
                                                      reuse this PID class for controlling the wheel    */
                                                                                  

     return Fc;                                      
}

void setGains(double p, double i, double d){

kp = p;
ki = i;
kd = d;



}

void reset (){

integral = 0.0;

 

}


 };
