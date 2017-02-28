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

void printGrid2(vector<vector<char>>fullGrid, int Width, int Height){
    
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            cout<<fullGrid.at(j)[i]<<" ";
        }
        cout<<endl;
    }
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
    char placeHolder= '-';
    
    // Continue iteration until the bottom of the grid is reached
    while(*agentLocY!=*pHeight-1){
        
        // check to see if agent is all the way left
        if(*agentLocX==0){
            
            while(*agentLocX!=*pWidth-1){
                
                *agentLocX=*agentLocX+1;
                
                if(*agentLocX==*goalLocX && *agentLocY==*goalLocY){
                cout<<"Congratulations, the agent found the goal at ("<< *agentLocX+1 <<","<<*pHeight-*agentLocY<<")"<<endl;
                    
                    // reprint grid given that the agent hopefully found goal
                    pFullGrid->clear();
                    for(int i=0;i<*pWidth;i++){
                        for(int j=0;j<*pHeight;j++){
                            pDepth->push_back(placeHolder);
                        }
                        pFullGrid->push_back(*pDepth);
                        pDepth->clear();
                    }
                    pFullGrid->at(*agentLocX)[*agentLocY]='A';
                    
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
                cout<<"Congratulations, the agent found the goal at ("<< *agentLocX+1 <<","<<*pHeight-*agentLocY<<")"<<endl;
                    
                    // reprint grid given that the agent hopefully found goal
                    pFullGrid->clear();
                    for(int i=0;i<*pWidth;i++){
                        for(int j=0;j<*pHeight;j++){
                            pDepth->push_back(placeHolder);
                        }
                        pFullGrid->push_back(*pDepth);
                        pDepth->clear();
                    }
                    pFullGrid->at(*agentLocX)[*agentLocY]='A';
                    
                    return 1000;
                    break;
                }
            }
            
        }
        
    }
    return 0;
};

int userPlay(vector<vector<char>>* pFullGrid, int* pWidth, int* pHeight , int* agentLocY, int* agentLocX, int* goalLocY, int* goalLocX){
    char movement;
    
    while(*agentLocX!=*goalLocX && *agentLocY!=*goalLocY){
        cout<<"Which way would you like to move? w = up, s = down, a = left, d = right."<<endl;
        cin>>movement;
        if(movement=='w'){
            if(*agentLocY==0){
                cout<<"No movement, try again. "<<endl;
            }
            else{
                //replace old location with place
                pFullGrid->at(*agentLocX)[*agentLocY]='-';
                
                // update angent location
                *agentLocY=*agentLocY-1;
                
                // replace new location with 'A'
                pFullGrid->at(*agentLocX)[*agentLocY]='A';
                //printGrid(pFullGrid, pWidth, pHeight);
               }
            
            // check agent location against goal and output success
            if(*agentLocX==*goalLocX && *agentLocY==*goalLocY){
                cout<<"Congratulations, you found the goal at ("<< *agentLocX+1 <<","<<*pHeight-*agentLocY<<")"<<endl;
                
                return 1000;
                break;
            }

        }
        else if(movement=='s'){
            if(*agentLocY==*pHeight-1){
                cout<<"No movement, try again. "<<endl;
            }
            else{
                //replace old location with place
                pFullGrid->at(*agentLocX)[*agentLocY]='-';
                
                // update angent location
                *agentLocY=*agentLocY+1;
                
                // replace new location with 'A'
                pFullGrid->at(*agentLocX)[*agentLocY]='A';
                //printGrid(pFullGrid, pWidth, pHeight);
            }
            
            // check agent location against goal and output success
            if(*agentLocX==*goalLocX && *agentLocY==*goalLocY){
                cout<<"Congratulations, you found the goal at ("<< *agentLocX+1 <<","<<*pHeight-*agentLocY<<")"<<endl;
                
                return 1000;
                break;
            }
        
        }
        else if(movement=='a'){
            if(*agentLocX==0){
                cout<<"No movement, try again. "<<endl;
            }
            else{
                //replace old location with place
                pFullGrid->at(*agentLocX)[*agentLocY]='-';
                
                // update angent location
                *agentLocY=*agentLocX-1;
                
                // replace new location with 'A'
                pFullGrid->at(*agentLocX)[*agentLocY]='A';
               // printGrid(pFullGrid, pWidth, pHeight);
            }
            
            // check agent location against goal and output success
            if(*agentLocX==*goalLocX && *agentLocY==*goalLocY){
                cout<<"Congratulations, you found the goal at ("<< *agentLocX+1 <<","<<*pHeight-*agentLocY<<")"<<endl;
                
                return 1000;
                break;
            }
            
        }
        else if(movement=='d'){
            if(*agentLocX==*pWidth-1){
                cout<<"No movement, try again. "<<endl;
            }
            else{
                //replace old location with place
                pFullGrid->at(*agentLocX)[*agentLocY]='-';
                
                // update angent location
                *agentLocY=*agentLocX+1;
                
                // replace new location with 'A'
                pFullGrid->at(*agentLocX)[*agentLocY]='A';
                //printGrid(pFullGrid, pWidth, pHeight);
            }
            
            // check agent location against goal and output success
            if(*agentLocX==*goalLocX && *agentLocY==*goalLocY){
                cout<<"Congratulations, you found the goal at ("<< *agentLocX+1 <<","<<*pHeight-*agentLocY<<")"<<endl;
                
                return 1000;
                break;
            }
            
        }
    
    }
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
    char check2;
    
    
    while(check !='n'){
    createGrid(&fullGrid, &depth, &gridWidth, &gridHeight, &agentLocY, &agentLocX, &goalLocY, &goalLocX);
    printGrid(&fullGrid, &gridWidth, &gridHeight);
        cout<<endl<<"Agent Y location: "<<gridHeight-agentLocY<<" Agent X location: "<<agentLocX +1<<endl<<endl;
        fullGrid.clear();
        
        cout<<"Would you like to test another grid? Come on... make it more difficult. (y/n) ";
        cin>>check;
        cout<<endl;
    }
    
    cout<<"Would you like the computer to find the goal? Press 'C'. "<< endl; cout<<"Or would you like to give it a try? Press 'U'."<<endl<<"Or would you like to exit the program? Enter 'N'."<<endl<< "enter C U or N: ";
    cin>>check2;
    cout<<endl;
    
    while(check2 != 'n' || check2 != 'N'){
    
    if(check2 =='C' || check2 =='c'){
    initializeStart(&fullGrid, &depth, &gridWidth, &gridHeight, &agentLocY, &agentLocX, &goalLocY, &goalLocX);
    lawnMowerCheck(&fullGrid, &depth, &gridWidth, &gridHeight , &agentLocY, &agentLocX, &goalLocY, &goalLocX);
    printGrid(&fullGrid, &gridWidth, &gridHeight);
        return 0;
    }
    
    else if(check2 =='u' || check2 =='U'){
    userPlay(&fullGrid, &gridWidth, &gridHeight ,&agentLocY, &agentLocX, &goalLocY, &goalLocX);
        return 0;
    }
        
    else if (check2=='n'||check2=='N'){
        return 0;
    }

    else{
        cout<<"Sorry, that was an invalid key, please try again. Enter 'U' or 'C', or if you're trying to quit, press 'N'. ";
        cin>>check2;
        cout<<endl;
        if(check2=='n'||check2=='N'){
            return 0;
        }
    }

    }
    return 0;
}


