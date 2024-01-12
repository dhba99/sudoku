#ifndef RESOLUCIONADOR_CPP
#define RESOLUCIONADOR_CPP

#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <chrono>
#include <list>
using namespace std;

static int tablero[9][9]={  {0,0,0,5,0,0,6,8,0},
                            {1,0,8,0,4,0,0,0,0},
                            {0,3,0,0,7,0,0,0,2},
                            {0,0,6,0,0,0,0,2,0},
                            {0,4,0,0,0,5,0,0,0},
                            {2,0,0,0,0,0,4,0,0},
                            {0,8,0,0,0,0,0,6,3},
                            {0,0,0,9,0,1,0,0,0},
                            {0,0,2,0,3,0,9,5,0}};
signed char psV[9][9][10];
int solutions;

void deletePosibilities(int,int,int);
void undoPosibilities(int,int,int);
void printNow();

void generateSudoku(){
    memset(tablero,0,sizeof(tablero));
    memset(psV,true,sizeof(psV));
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            for(int k=0;k<9;++k){
                cout << psV[i][j][k]<<endl;
            }
        }
    }
}

int solveSudoku(){

    int solutions=0;
    int firstx=0,firsty=0;

    bool forward=true;
    memset(psV,0,sizeof(psV));

    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(tablero[i][j]!=0){
                psV[i][j][0]=-1;
                deletePosibilities(i,j,tablero[i][j]);
            }
        }
    }

    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            //cout<<i<<j<<endl;
            // if(tablero[8][7]!=0){
            //     printNow();
            //     int bb; cin>>bb;
            // }
            // if(tablero[8][7]!=0){cout<<"llego aca"<<endl;}
            if(i==8&&j==8){
                ++solutions;
                if(solutions>=2){
                    return 2;
                }
                forward=false;
                j-=2;
                continue;
                // if(tablero[firstx][firsty]==8){
                //     forward=true;
                // }
            }
            //if(tablero[8][7]!=0){cout<<"llego aca"<<endl;}
            if(psV[i][j][0]==-1){
                if(forward){
                    continue;
                }else{
                    if(j==firsty&&i==firstx){
                        i=8;j=8;
                         continue;
                    }
                    if(j==0&&i!=0){
                        j=7;
                        i-=1;
                        continue;
                    }else{
                        j-=2;
                        continue;
                    }
                }
            }

            forward=true;
            
            int val=-1;
            if(tablero[i][j]==0){
                for(int k=1;k<=9;++k){
                    if(psV[i][j][k]<0){
                        --psV[i][j][k];
                    }
                }
            }else{
                undoPosibilities(i,j,tablero[i][j]);
                tablero[i][j]=0;
            }
            
            for(int k=1;k<=9;++k){
                if(psV[i][j][k]==0){
                    val=k;
                    --psV[i][j][k];
                    break;
                }
            }
            
            if(val==-1){
                if(i==firstx&&j==firsty){
                    i=8;j=8;continue; //No hay solucion
                }
                for(int k=1;k<=9;++k){
                    ++psV[i][j][k];
                }
                forward=false;
                if(j==0){
                    j=7;
                    i-=1;
                    continue;
                }else{
                    j-=2;
                    continue;
                }   
            }

            deletePosibilities(i,j,val);
            
            tablero[i][j]=val;


            // if(tablero[0][0]==2){
            //     printNow();
            //     cout<<"Soluciones "<<solutions<<endl;
            //     int s;
            //     cin>>s;

            // }
            
        }

    }


    if(solutions==0){
        cout<<"El sudoku no tiene solucion"<<endl;
    }else if(solutions==1){
        cout<<"El sudoku tiene solucion unica"<<endl;
    }else{
        cout<<"El sudoku tiene "<<solutions<<" soluciones"<<endl;
    }
    return solutions;
}


bool isValid(int x,int y,int value){
    for(int i=0;i<9;++i){
        if(tablero[x][i]==value)                    return false;
        if(tablero[i][y]==value)                    return false;
        if(tablero[x-x%3+i/3][y-y%3+i%3]==value)    return false;
    }
    return true;
}

void undoPosibilities(int x,int y,int value){
    for(int i=0;i<9;++i){
        if(psV[x][i][value]!=1){
            ++psV[x][i][value];
        }
        if(psV[i][y][value]!=1){
            ++psV[i][y][value];
        }
        if(psV[x-x%3+i/3][y-y%3+i%3][value]!=1){
            if(x-x%3+i/3!=x&&y-y%3+i%3!=y){
                ++psV[x-x%3+i/3][y-y%3+i%3][value];
            }
        }
    }
    //en prueba
        psV[x][y][value]-=1;
}

void deletePosibilities(int x,int y,int value){
    for(int i=0;i<9;++i){
        if(psV[x][i][value]!=1){
            --psV[x][i][value];
            // if(psV[x][i][value]==-1)
            // --psV[x][i][0];
        }
        // //Debug
        //     if(y==6){
        //         cout<<endl;
        //         for(int i1=0;i1<9;++i1){
        //             cout<< (int)psV[0][6][i1+1]<<" ";
        //         }
        //         cout<<endl;
        //     }
        if(psV[i][y][value]!=1){
            --psV[i][y][value];
            // if(psV[i][y][value]==-1)
            // --psV[i][y][0];
        }
        if(psV[x-x%3+i/3][y-y%3+i%3][value]!=1){
            if(x-x%3+i/3!=x&&y-y%3+i%3!=y){
                --psV[x-x%3+i/3][y-y%3+i%3][value];

            }
            // if(psV[x-x%3+i/3][y-y%3+i%3][value]==-1)
            // --psV[x-x%3+i/3][y-y%3+i%3][0];
        }
    }
        //en prueba
        psV[x][y][value]+=1;
}

void printNow(){
    for(int i1=0;i1<9;i1++){
        for(int j1=0;j1<9;j1++){
            cout <<right <<setw(3)<< tablero[i1][j1]<<" ";
        }   
        cout<<endl;
    }
}

void updatePossibilities(){
    memset(psV,true,sizeof(psV));
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            psV[i][j][0]=9;
            if(tablero[i][j]!=0){
                deletePosibilities(i,j,tablero[i][j]);
            }
        }
    }
}

int main1(){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    return solveSudoku();
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_double.count() << "ms\n";
    
}

// int main(){
//     main1();
// }
#endif
