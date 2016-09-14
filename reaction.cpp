#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#define width 5
#define height 5
#define dU 0.1
#define dW 0.05
#define alphaU 0.055
#define alphaW 0.055
#define muU 0.062
#define muW 0.062
#define f 0.055
#define k 0.062
#define dT 1

using namespace std;

double T = 0;

struct cell{
  double u,w;
};

cell grid[width][height];
cell next[width][height];




void initialize()
{
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      {
        grid[i][j].u = 1;
        grid[i][j].w = 0;
        next[i][j].u = 1;
        next[i][j].w = 0;
      }
  for (int i = 1; i < 3; i++)
    for (int j = 1; j < 3; j++)
      {
	grid[i][j].u = 1;
	grid[i][j].w = 0.1;
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
        fprintf(fin,"%lf ", grid[i][j].u);
      fprintf (fin,"\n");
    }
  fclose(fin);
}

void next_generation()
{
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      {
        grid[i][j].u = next[i][j].u;
        grid[i][j].w = next[i][j].w;
      }

}


double laplaceU(int x, int y)
{
  double sumU = -4*grid[x][y].u;
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
      sumU += grid[pX][pY].u;
    }

  return sumU;

}

double laplaceW(int x,int y)
{
  double sumW = -4*grid[x][y].w;
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
      sumW += grid[pX][pY].w;
    }
  return sumW;
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
            double U = grid[x][y].u;
            double W = grid[x][y].w;
            next[x][y].u = U + dU*laplaceU(x,y) + alphaU*U/(U+W) -  muU*U*(1+k*(U+W));
            next[x][y].w = W + dW*laplaceW(x,y) + alphaW*W - muW*W*(1+k*(U+W));

          }
      //      next_generation();
      printMap(T);
      next_generation();
    }
  return 0;
}
