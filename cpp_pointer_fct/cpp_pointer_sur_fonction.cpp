#include <bits/stdc++.h> 
using namespace std;

int add(int x, int y){return x+y;}
int sub(int x, int y){return x-y;}
int operation (int x, int y,int (*function)(int,int)){return function(x,y);}
int operation2(int x, int y,std::function<int(int, int)> function){return function(x,y);}

int main()
{
    std::cout <<"Values 1 & 3. Pointer function: Add:"<<operation (1,3,&add)<<" Sub:"<<operation (1,3,&sub) << std::endl;
    std::cout <<"Values 1 & 3. std::function   : Add:"<<operation2(1,3,&add)<<" Sub:"<<operation2(1,3,&sub) << std::endl;
}
