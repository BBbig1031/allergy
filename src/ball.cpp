//
//  ball.cpp
//  ball
//
//  Created by BBbig on 15/02/2017.
//
//

#include "ball.hpp"

Ball::Ball(){
   
}

void Ball::setup(float _x, float _y, int _dim){
    x = _x;      // give some random positioning
    y = _y;
    dim =  _dim;
    
    speedX = ofRandom(-1, 1);           // and random speed and direction
    speedY = ofRandom(-1, 1);
    
    
    
    color.set(232, 70, 46); // one way of defining digital color is by addressing its 3 components individually (Red, Green, Blue) in a value from 0-255, in this example we're setting each to a random value 232,68,86
}

void Ball::update(){
    if(x < 390 ){
        x = 390;
        speedX *= -1;
    } else if(x > 630){
        x = 630;
        speedX *= -1;
    }
    
    if(y < 300 ){
        y = 300;
        speedY *= -1;
    } else if(y > 500){
        y = 500;
        speedY *= -1;
    }
    
    x+=speedX;
    y+=speedY;
}

void Ball::draw(){
    ofSetColor(color);
    ofDrawCircle(x, y, dim);
}

