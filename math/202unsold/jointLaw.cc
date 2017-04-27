#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "includes/includes.hh"

int					varianceAndValues(double nbs[6][6])
{
  double				res1 = 0;
  double				Vres1 = 0;
  double				res2 = 0;
  double				Vres2 = 0;
  int					idx = 0;

  std::cout << "----------------------------------------" << std::endl;
  std::cout << "expected value of X:\t";
  for (int x=10;x<60;x+=10)
    {
      res1 += (nbs[0][idx] + nbs[1][idx] + nbs[2][idx] + nbs[3][idx] + nbs[4][idx]) * x;
      idx++;
    }
  printf("%.1f\n", res1);
  std::cout << "variance of X:\t\t";
  idx = 0;
  for (int x=10;x<60;x+=10)
    {
      Vres1 += (nbs[0][idx] + nbs[1][idx] + nbs[2][idx] + nbs[3][idx] + nbs[4][idx]) * pow(x, 2);
      idx++;
    }
  printf("%.1f\n", Vres1 - pow(res1, 2));


  std::cout << "expected value of Y:\t";
  idx = 0;
  for (int y=10;y<60;y+=10)
    {
      res2 += (nbs[idx][0] + nbs[idx][1] + nbs[idx][2] + nbs[idx][3] + nbs[idx][4]) * y;
      idx++;
    }
  printf("%.1f\n", res2);
  std::cout << "variance of Y:\t\t";
  idx = 0;
  for (int y=10;y<60;y+=10)
    {
      Vres2 += (nbs[idx][0] + nbs[idx][1] + nbs[idx][2] + nbs[idx][3] + nbs[idx][4]) * pow(y, 2);
      idx++;
    }
  printf("%.1f\n", Vres2 - pow(res2, 2));

  std::cout << "expected value of Z:\t";
  printf("%.1f\n", res1 + res2);
  printf("variance of Z:\t\t%.1f\n", ((Vres2 - pow(res2, 2)) + (Vres1 - pow(res1, 2))));
  std::cout << "----------------------------------------" << std::endl;
  return (0);
}

int					ZLaw(double nbs[6][6])
{
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "z\t20\t30\t40\t50\t60\t70\t80\t90\t100\ttotal" << std::endl;
  std::cout << "p(Z=z)\t";
  printf("%.3f\t%.3f\t%.3f\t", nbs[0][0], nbs[1][0] + nbs[0][1], nbs[0][2] + nbs[1][1] + nbs[2][0]);
  printf("%.3f\t", nbs[0][3] + nbs[1][2] + nbs[2][1] + nbs[3][0]);
  printf("%.3f\t", nbs[0][4] + nbs[1][3] + nbs[2][2] + nbs[3][1] + nbs[4][0]);
  printf("%.3f\t", nbs[1][4] + nbs[2][3] + nbs[3][2] + nbs[4][1]);
  printf("%.3f\t", nbs[2][4] + nbs[3][3] + nbs[4][2]);
  printf("%.3f\t%.3f\t", nbs[3][4] + nbs[4][3], nbs[4][4]);
  printf("1\n");
  varianceAndValues(nbs);
  return (0);
}

int					jointLaw(double a, double b)
{
  double				nbs[6][6];
  int					axex = 0;
  int					axey = 0;

  std::cout << "----------------------------------------" << std::endl;
  std::cout << "\tX=10\tX=20\tX=30\tX=40\tX=50\tY law" << std::endl;

  for (double y=10;y<60;y+=10)
    {
      axex = 0;
      std::cout << "Y=" << y << "\t";
      for (double x=10;x<60;x+=10)
	{
	  nbs[axey][axex] = (double)(((a - x) * (b - y)) / (( (5 * a) - 150) * ((5 * b) - 150)));
	  printf("%.3f\t", nbs[axey][axex]);
	  axex++;
	}
      nbs[axey][5] = nbs[axey][0] + nbs[axey][1] + nbs[axey][2] + nbs[axey][3] + nbs[axey][4];
      printf("%.3f\n", nbs[axey][5]);
      axey++;
    }
  axex = 0;
  std::cout << "X law\t";
  for (int i=0; i < 5; i++)
    {
      printf("%.3f\t",(double)(nbs[0][axex] + nbs[1][axex] + nbs[2][axex] + nbs[3][axex] + nbs[4][axex]));
      axex += 1;
    }
  std::cout << "1" << std::endl;
  ZLaw(nbs);
  return (0);
}
