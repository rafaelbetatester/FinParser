#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#define width 5
#define height 5
#define dA 0.1
#define dB 0.05
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
  for (int i = 1; i < 3; i++)
    for (int j = 1; j < 3; j++)
      {
	grid[i][j].b = 1;
	grid[i][j].a = 0.1;
      }

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
  double sumA = -4*grid[x][y].a;
  int dX[] = {1,1,-1,-1};
  int dY[] = {1,-1,1,-1};
  for (int i = 0; i < 4; i ++)
    {
      int pX = x + dX[i];
      int pY = y + dY[i];
      if (pX < 0 || pX >= width)
        pX = 2*x - pX;
      if (pY < 0 || pY >= height)
        pY = 2*y - pY;
      sumA += grid[pX][pY].a;
    }

  return sumA;

}

double laplaceB(int x,int y)
{
  double sumB = -4*grid[x][y].b;
  int dX[] = {1,-1,0,0};
  int dY[] = {0,0,1,-1};
  for (int i = 0; i < 4; i ++)
    {
      int pX = x + dX[i];
      int pY = y + dY[i];
      if (pX < 0 || pX >= width)
        pX = 2*x - pX;
      if (pY < 0 || pY >= height)
        pY = 2*y - pY;
      sumB += grid[pX][pY].b;
    }
  return sumB;
}

int main()
{
  initialize();

  while(T <= 1000)
    {
      T = T + dT;
      for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
          {
            double a = grid[x][y].a;
            double b = grid[x][y].b;
            next[x][y].a = a + dA*laplaceA(x,y) - a*b*b +  f*(1-a);
            next[x][y].b = b + dB*laplaceB(x,y) + a*b*b - (k+f)*b;

          }
      //      next_generation();
      printMap(T);
      next_generation();
    }
  return 0;
}
