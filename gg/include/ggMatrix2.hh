// ggMatrix2.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 20:30:18 2019 (+0800)
// Last-Updated: 三 1月  2 22:21:35 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 11
// URL: http://wuhongyi.cn 

#ifndef _GGMATRIX2_H_
#define _GGMATRIX2_H_

#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ggMatrix2
{
public:
  ggMatrix2(TH2 *gm,TH1 *gs);
  virtual ~ggMatrix2();

  void ShowTotalProject();
  void NewCanvas(int ncy1);
  
  void SetNoPeaks(int n);// eg: 30
  void SetPeakWidth(double left,double right);// eg: -3 3
  void SetPeaksThreshold(double thres);//eg: 0.05
  void SetXRangeUser(double xmin,double xmax);

  void PeaksFlag(TH1 *hh);
private:
  TH1 *gTpj;
  TH2 *gMat;
  
  TCanvas *ca[1000];
  int ic = -1;//canvas id
  int ih = 0;
  int ncy = 1;//number of windows in y axis

  int NoPeaks;
  double PeakWidthLeft;
  double PeakWidthRight;

  double PeaksThreshold;
  double UserMinX,UserMaxX;
  
  
  int gBinX,gMinX,gMaxX;
  int gBinY,gMinY,gMaxY;
  
};

#endif /* _GGMATRIX2_H_ */
// 
// ggMatrix2.hh ends here
