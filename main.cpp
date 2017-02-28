//
//  main.cpp
//  Hw_2
//
//  Created by Cooper Richardson on 2/27/17.
//  Copyright © 2017 Cooper Richardson. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <assert.h>
#include <random>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <time.h>
using namespace std;


#define crRand (double)rand()/RAND_MAX

void createGrid(vector<vector<char>>* pFullGrid, vector<char>* pDepth, int* pWidth, int* pHeight, int* agentLocY, int* agentLocX, int* goalLocY, int* goalLocX){
    
    srand(time(NULL));
    
    // Input length and width of gridworld from user
cout<<"How wide would you like your grid to be? ";
    cin>>*pWidth;
    cout<< endl;
    cout<<"How tall would you like your grid to be? ";
    cin>>*pHeight;
    cout<< endl;
    
    // Create gridworld given user inputs
    char placeHolder= '-';
    for(int i=0;i<*pWidth;i++){
        for(int j=0;j<*pHeight;j++){
            pDepth->push_back(placeHolder);
        }
        pFullGrid->push_back(*pDepth);
        pDepth->clear();
    }
    
    // Place Agent and Goal in created grid world
    *agentLocY = rand()% *pHeight;
    *agentLocX = rand()% *pWidth;
    pFullGrid->at(*agentLocX)[*agentLocY]='A';
    *goalLocY = rand()%*pHeight;
    *goalLocX= rand()% *pWidth;
    pFullGrid->at(*goalLocX)[*goalLocY]='G';
    
        // If agent and goal are in same location, relocate
    while( *agentLocY == *goalLocY && *agentLocX == *goalLocX ){
        *agentLocY = rand()%*pHeight;
        *agentLocX = rand()% *pWidth;
        pFullGrid->at(*agentLocX)[*agentLocY]='A';
        *goalLocY = rand()%*pHeight;
        *goalLocX= rand()% *pWidth;
        pFullGrid->at(*goalLocX)[*goalLocY]='G';
    }
};

void printGrid(vector<vector<char>>* pFullGrid, int* pWidth, int* pHeight){
    for(int i=0;i<*pHeight;i++){
        for(int j=0;j<*pWidth;j++){
            cout<<pFullGrid->at(j)[i]<<" ";
        }
        cout<<endl;
    }
};

void move( vector<vector<char>>* pFullGrid, int* pWidth, int* pHeight , char* direction, int* agentLocY, int* agentLocX, int* goalLocY, int* goalLocX){
    
};

void initializeStart( vector<vector<char>>* pFullGrid, vector<char>* pDepth, int* pWidth, int* pHeight , int* agentLocY, int* agentLocX, int* goalLocY, int* goalLocX){
    while(*agentLocY!=0){
        *agentLocY=*agentLocY-1;
    }
    while(*agentLocX!=0){
        *agentLocX=*agentLocX-1;
    }
    
    char placeHolder= '-';
    for(int i=0;i<*pWidth;i++){
        for(int j=0;j<*pHeight;j++){
            pDepth->push_back(placeHolder);
        }
        pFullGrid->push_back(*pDepth);
        pDepth->clear();
    }
    pFullGrid->at(*goalLocX)[*goalLocY]='G';
    pFullGrid->at(*agentLocX)[*agentLocY]='A';
};


int lawnMowerCheck(vector<vector<char>>* pFullGrid, vector<char>* pDepth, int* pWidth, int* pHeight , int* agentLocY, int* agentLocX, int* goalLocY, int* goalLocX){
    
    // Continue iteration until the bottom of the grid is reached
    while(*agentLocY!=*pHeight-1){
        
        // check to see if agent is all the way left
        if(*agentLocX==0){
            
            while(*agentLocX!=*pWidth-1){
                
                *agentLocX=*agentLocX+1;
                
                if(*agentLocX==*goalLocX && *agentLocY==*goalLocY){
                    cout<<"Congratulations, the goal was found at "<<*pHeight-*agentLocY<<" in the Y direction, and "<< *agentLocX+1<<" in the X direction."<<endl;
                    return 1000;
                    break;
                }
            }
        
        }
        
        //check to see if agent is all the way right
        else if(*agentLocX==*pWidth-1){
            *agentLocY=*agentLocY+1;
            
            while(*agentLocX!=0){
                *agentLocX=*agentLocX-1;
                
                if(*agentLocX==*goalLocX && *agentLocY==*goalLocY){
                    cout<<"Congratulations, the goal was found at "<<*pHeight-*agentLocY<<" in the Y direction, and "<< *agentLocX+1<<" in the X direction."<<endl;
                    return 1000;
                    break;
                }
            }
            
        }
        
    }
    // reprint grid given that the agent hopefully found goal
    char placeHolder= '-';
    for(int i=0;i<*pWidth;i++){
        for(int j=0;j<*pHeight;j++){
            pDepth->push_back(placeHolder);
        }
        pFullGrid->push_back(*pDepth);
        pDepth->clear();
    }
    pFullGrid->at(*goalLocX)[*goalLocY]='G';
    pFullGrid->at(*agentLocX)[*agentLocY]='A';
    return 0;
};


int main() {

    vector<vector<char>> fullGrid;
    vector<char> depth;
    int gridWidth;
    int gridHeight;
    int agentLocY;
    int agentLocX;
    int goalLocY;
    int goalLocX;
    char check;
    
    
    while(check !='n'){
    createGrid(&fullGrid, &depth, &gridWidth, &gridHeight, &agentLocY, &agentLocX, &goalLocY, &goalLocX);
    printGrid(&fullGrid, &gridWidth, &gridHeight);
        cout<<endl<<"Agent Y location: "<<gridHeight-agentLocY<<" Agent X location: "<<agentLocX +1<<endl<<endl;
        fullGrid.clear();
        
        cout<<"Would you like to test another grid? Come on... make it more difficult. (y/n) ";
        cin>>check;
        cout<<endl;
    }
    initializeStart(&fullGrid, &depth, &gridWidth, &gridHeight, &agentLocY, &agentLocX, &goalLocY, &goalLocX);
    printGrid(&fullGrid, &gridWidth, &gridHeight);
    lawnMowerCheck(&fullGrid, &depth, &gridWidth, &gridHeight , &agentLocY, &agentLocX, &goalLocY, &goalLocX);
    printGrid(&fullGrid, &gridWidth, &gridHeight);
    
    
    return 0;
}
