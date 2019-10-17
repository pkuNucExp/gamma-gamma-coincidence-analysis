// cube.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 10月 13 14:23:09 2019 (+0800)
// Last-Updated: 日 10月 13 15:33:28 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 3
// URL: http://wuhongyi.cn 

#ifndef _CUBE_H_
#define _CUBE_H_

#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TFile.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class cube
{
public:
  cube(int bin, double max_e);
  virtual ~cube();

  void Fill(double ex,double ey,double ez);
  void Save(int run);
  
private:
  int BINNUMBER;
  double MAXENERGY;


  TH1I *hg3x;//Pi
  TH2I *hg3xy;//Mij
  TH2I **hg3xyz;//z文件号，fill (x,y)

};

#endif /* _CUBE_H_ */
// 
// cube.hh ends here
