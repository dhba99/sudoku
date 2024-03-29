#ifndef CREADOR_CPP
#define CREADOR_CPP
#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <time.h>
#include <iomanip>
#include <cassert>
#include <math.h>
#include <cstring>
#include <stack>
#include <chrono>
#include <algorithm>
#include <random>
#include "resolucionador.cpp"

#define F first
#define S second

using namespace std;

#define SCI static_cast<int>
#define ENDL cout << endl;

static char tt[9][9];
static pair<char,bool> def[9][9];

void imprimir(char tablero[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)    cout <<right <<setw(3)<< (int)tablero[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void imprimirPS(int possibleValues[9][9][9],int i1){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)    cout <<right <<setw(3)<< possibleValues[i][j][i1]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void generate(){

    //srand(time(NULL));
    
    char tablero[9][9];
    char possibleValues[9][9][10];
    memset(tablero,0,sizeof(tablero));
    memset(possibleValues,true,sizeof(possibleValues));
    // for(int i=0;i<9;++i){
    //     for(int j=0;j<9;++j){
    //         possibleValues[i][j][0]=9;
    //     }
    // }
    
    for(int i1=0;i1<9;i1++){
        int value=i1+1;
        for(int i2=0;i2<9;i2++){
            int posibleValues=0;
            int tmpR=(int)(floor(i2/3)*3);
            int tmpC=i2%3*3;
            for(int i3=0;i3<9;i3++){
                //Checkeo inicial para eliminar el valor
                if(tablero[tmpR + i3/3][tmpC+i3%3]==value){
                    tablero[tmpR + i3/3][tmpC+i3%3]=0;
                }
                if(possibleValues[tmpR + i3/3][tmpC+i3%3][i1]!=-1)
                    possibleValues[tmpR + i3/3][tmpC+i3%3][i1]=true;
                }
                for(int j1=0;j1<9;j1++){
                    for(int j2=0;j2<9;j2++){
                        if(tablero[j1][j2]==value){
                            for(int j3=0;j3<9;j3++){
                                if(possibleValues[j1][j3][i1]!=-1){
                                    possibleValues[j1][j3][i1]=false;
                                }
                                if(possibleValues[j3][j2][i1]!=-1){
                                    possibleValues[j3][j2][i1]=false;
                                } 
                            }
                        }
                    }
                }

            for(int i3=0;i3<9;i3++){
                if(tablero[tmpR + i3/3][tmpC+i3%3]!=0)    continue;
                if(possibleValues[tmpR + i3/3][tmpC+i3%3][i1]!=true) continue;   
                ++posibleValues;
            }

            if(posibleValues==0){
                for(int i3=0;i3<9;i3++){
                    if(tablero[tmpR + i3/3][tmpC+i3%3]==value){
                        tablero[tmpR + i3/3][tmpC+i3%3]=0;
                    }
                    possibleValues[tmpR + i3/3][tmpC+i3%3][i1]=true;
                }
                if(i2==0){
                    for(int i3=0;i3<9;i3++){
                        if(tablero[(((8)/3)*3) + i3/3][(i2-1)%3*3+i3%3]==value-1){
                            tablero[(((8)/3)*3) + i3/3][(i2-1)%3*3+i3%3]=0;
                        }
                    }
                    i1-=1;
                    i2=7;
                    --value;
                    continue;
                }else{
                    for(int i3=0;i3<9;i3++){
                        if(tablero[(((i2-1)/3)*3) + i3/3][(i2-1)%3*3+i3%3]==value){
                            tablero[(((i2-1)/3)*3) + i3/3][(i2-1)%3*3+i3%3]=0;
                        }
                    }
                    for(int j1=0;j1<9;j1++){
                        for(int j2=0;j2<9;j2++){
                            if(tablero[j1][j2]==value){
                                for(int j3=0;j3<9;j3++){
                                   if(possibleValues[j1][j3][i1]!=-1){
                                        possibleValues[j1][j3][i1]=false;
                                   }
                                   if(possibleValues[j3][j2][i1]!=-1){
                                        possibleValues[j3][j2][i1]=false;
                                   }
                                   
                                }
                            }
                        }
                    }
                    i2-=2;
                    continue;
                }
            }

            //Elegir aleatoreamente la celda del cuadrado
            int r = rand()%posibleValues+1;
            posibleValues=0;

            for(int i4=0;i4<9;i4++){
                if(tablero[tmpR+ i4/3][tmpC+i4%3]!=0)    continue;
                
                if(possibleValues[tmpR+ i4/3][tmpC+i4%3][i1]!=true) continue; 
                ++posibleValues;
                
                if(posibleValues==r){
                    int hr=tmpR + i4/3;
                    int hc=tmpC + i4%3;
                    tablero[hr][hc] = value;
                    for(int i5=0;i5<9;i5++){
                        if(possibleValues[hr][i5][i1]!=-1){
                            possibleValues[hr][i5][i1]=false;
                        }
                        if(possibleValues[i5][hc][i1]!=-1){
                            possibleValues[i5][hc][i1]=false;
                        }
                    }
                    possibleValues[hr][hc][i1]=-1;
                    break;
                }
            }
        }
    }
    //despues activar
    //imprimir(tablero);
    for(int ix=0;ix<9;++ix){
        for(int jx=0;jx<9;jx++){
            tt[ix][jx] = tablero[ix][jx];

        }
    }
}


void main11(int d){

    //int d=2;
    srand(time(NULL));
    int diff=0;
    if(d==1){
        diff=25+ rand()%11;
        //diff=1;
    }else if(d==2){
        diff=40 + rand()%11;
    }else if(d==3){
        diff=55 + rand()%1;
    }
    

    for(int im=0;;im++){
        generate();
        int tempTablero[9][9];
        for(int ix=0;ix<9;++ix){
            for(int jx=0;jx<9;++jx){
                tablero[ix][jx]=(int)tt[ix][jx];
                tempTablero[ix][jx]=tablero[ix][jx];
            }
        }

        int rix,rjx,temp;

        stack<pair<pair<int,int>,int>> vals;

        std::random_device rd;
        std::mt19937 g(rd());

        bool negs[9][9]={false};
        memset(negs,0,sizeof(negs));

	    //cambiar la dificultad
        for(int i=0;i<diff;++i){
            cout<<"Vamos "<<i+1<<endl;
            vector<pair<pair<int,int>,bool>> x;

            for(int ix=0;ix<9;++ix){
                for(int jx=0;jx<9;++jx){
                    tablero[ix][jx]=(int)tempTablero[ix][jx];
                    if(negs[ix][jx]) continue;
                    if(tablero[ix][jx]!=0) x.push_back({{ix,jx},false});
                }
            }

            shuffle(x.begin(),x.end(),g);

            cout<<"Tamaño de X: "<<x.size()<<endl;
            for(int ix=0;ix<9;++ix){
                for(int jx=0;jx<9;++jx){
                    cout <<right <<setw(3)<< (int)tempTablero[ix][jx]<<" ";
                }
                cout<<endl;
            }

            bool found=false;
            for(size_t j=0;j<x.size();++j){
                rix=x[j].first.first;
                rjx=x[j].first.second;
                
                temp=(int)tablero[rix][rjx];
                tablero[rix][rjx]=0;
                if(main1()!=1){
                    for(int ix=0;ix<9;++ix){
                        for(int jx=0;jx<9;++jx){
                            tablero[ix][jx]=(int)tempTablero[ix][jx];
                        }
                    }
                }else{
                    vals.push({{rix,rjx},temp});
                    tempTablero[rix][rjx]=0;
                    found=true;
                    break;
                }

            }
            
            if(!found){
                auto elem = vals.top();
                vals.pop();
                tempTablero[elem.F.F][elem.F.S]=elem.S;
                negs[elem.F.F][elem.F.S]=true;
                i-=2; 
            } 

            // int te;
            // cin>>te;

            
        }


        for(int ix=0;ix<9;++ix){
            for(int jx=0;jx<9;++jx){
                def[ix][jx].first=(int)tt[ix][jx];
                def[ix][jx].second=(int)tempTablero[ix][jx];
                cout <<right <<setw(3)<< (int)tempTablero[ix][jx]<<" ";
                //tablero[ix][jx]=(int)tt[ix][jx];
            }
            cout<<endl;
        }
        break;


    }

    
}

#endif
