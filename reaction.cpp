#include <stdio.h>
#include <string> 
#include <stdlib.h>
#include <sstream>
#include <string.h>
#define width 200
#define height 200
#define dA 1
#define dB 0.5
#define f 0.055
#define k 0.062
#define dT 1

using namespace std;

double T = 0;

struct cell{
  double a,b;
};

cell grid[width][height];
cell next[width][height];




void initialize()
{
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      {
	grid[i][j].a = 1;
	grid[i][j].b = 0;
	next[i][j].a = 1;
	next[i][j].b = 0;
       }
  for (int i = 100; i < 110; i++)
    for (int j = 100; j < 110; j++)
      grid[i][j].b = 1;
}

void printMap(int t)
{
  //char buffer [33];
  //itoa (t,buffer,10);
  stringstream ss;
  ss << t;
  string str = ss.str();
  FILE *fin = fopen(("./output/"+str+".txt").c_str(),"w+");
    for (int i = 0; i < width; i++)
      {
      for (int j = 0; j < height; j++)
	fprintf(fin,"%lf ", grid[i][j].b);
      fprintf (fin,"\n");
      } 
    fclose(fin);
}

void next_generation()
{
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      {
        grid[i][j].a = next[i][j].a;
	grid[i][j].b = next[i][j].b;
      }

}


double laplaceA(int x, int y)
{
  double sumA = 0;
  sumA+=grid[x][y].a * -1;
  sumA+=grid[x-1][y].a * 0.2;
  sumA+=grid[x+1][y].a * 0.2;
  sumA+=grid[x][y+1].a * 0.2;
  sumA+=grid[x][y-1].a * 0.2;
  sumA+=grid[x+1][y+1].a * 0.05;
  sumA+=grid[x-1][y+1].a * 0.05;
  sumA+=grid[x+1][y-1].a * 0.05;
  sumA+=grid[x-1][y-1].a * 0.05;
  return sumA;

}

double laplaceB(int x,int y)
{

  double sumB = 0;
  sumB+=grid[x][y].b * -1;
  sumB+=grid[x-1][y].b * 0.2;
  sumB+=grid[x+1][y].b * 0.2;
  sumB+=grid[x][y+1].b * 0.2;
  sumB+=grid[x][y-1].b * 0.2;
  sumB+=grid[x+1][y+1].b * 0.05;
  sumB+=grid[x-1][y+1].b * 0.05;
  sumB+=grid[x+1][y-1].b * 0.05;
  sumB+=grid[x-1][y-1].b * 0.05;

  return sumB;
}

int main()
{
  initialize();
  
  while(T <= 10)
    {
      T = T + dT;
      for (int x = 1; x < width-1; x++)
	for (int y = 1; y < height-1; y++)
	  {
	    double a = grid[x][y].a;
	    double b = grid[x][y].b;
	    next[x][y].a = a + dA*laplaceA(x,y) - a*b*b +  f*(1-a);
	    next[x][y].b = b + dB*laplaceB(x,y) + a*b*b - (k+f)*b;
		    
	  }
      next_generation();
      printMap(T);
    }
  return 0;
}
