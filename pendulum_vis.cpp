#include <SFML/Graphics.hpp>
#include <cmath>
#include "pendulum.hpp"


int main(){


sf::RenderWindow window (sf::VideoMode(800,600), "Pendulum Simulation");
window.setFramerateLimit(60);
sf::Clock clock;

PendulumSystem p1(1,1);                    // objects
PIDcontroller pend(20,0.5,12);

float pivot_x= 400;
float pivot_y = 250;               
float pole_length = 200;
bool dragging = false;
int prev_mouse_x = 0;
float kp = 30.0f;
float ki = 0.5f;
float kd = 12.0f; 



sf::Font font;
font.loadFromFile("arial.ttf");

sf::Text info;
info.setFont(font);
info.setCharacterSize(18);
info.setFillColor(sf::Color::White);
info.setPosition(10, 10);

while (window.isOpen()){

sf::Event event;
while (window.pollEvent(event)){

if (event.type == sf::Event::Closed)
window.close();

if (event.type == sf::Event::MouseButtonPressed)
if(event.mouseButton.button == sf::Mouse::Left){

dragging = true;
prev_mouse_x = event.mouseButton.x;
}

if(event.type == sf::Event::MouseButtonReleased)
if(event.mouseButton.button == sf::Mouse::Left){


    dragging=false;
}
if (event.type == sf::Event::MouseMoved && dragging){

int dx = event.mouseMove.x - prev_mouse_x;
p1.theta+= dx*0.005f;
prev_mouse_x = event.mouseMove.x;



}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) kp += 1.5f;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) kp -= 1.5f;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) ki += 0.05f;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) ki -= 0.05f;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) kd += 1.0f;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) kd -= 1.0f;


if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
p1.theta = 0.5f;
p1.theta_dot = 0.0f;
pend.reset();
}


pend.setGains(kp, ki, kd);


}

double Fc = pend.compute(p1.theta, p1.theta_dot);
p1.updatesystem(Fc);                                            // 
 
float tip_x = pivot_x + pole_length*sin(p1.theta);
float tip_y = pivot_y - pole_length*cos(p1.theta);  // minus because Y is increasing dowmwards in the \\\SFML coordinate system

window.clear(sf::Color(30,30,30));



sf::Vertex pole [] = {

sf::Vertex(sf::Vector2f(pivot_x, pivot_y), sf::Color::Green),
sf::Vertex(sf::Vector2f(tip_x, tip_y), sf::Color::Green)


};


window.draw(pole, 2, sf::Lines);

sf::CircleShape pivot(8);
pivot.setFillColor(sf::Color::White);
pivot.setPosition(pivot_x-8, pivot_y-8);
window.draw(pivot);

sf::CircleShape tip(16);
tip.setFillColor(sf::Color::Blue);
tip.setPosition(tip_x-16, tip_y-16);
window.draw(tip);

info.setString(
"kp:" + std::to_string(kp).substr(0,5)+
"ki:" + std::to_string(ki). substr(0,5)+
"kd:" + std::to_string(kd).substr(0,5) +
"\nTheta:" + std::to_string(p1.theta*180.0f/PI).substr(0,6) + "degrees" +
"\n P/O: kp        I/U  ki           D/S: kd       R:  Reset"



);

window.draw(info);

window.display();



}





}
