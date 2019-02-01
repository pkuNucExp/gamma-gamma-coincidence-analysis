// ggMatrix2.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 20:30:18 2019 (+0800)
// Last-Updated: 日 1月  6 22:49:37 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 29
// URL: http://wuhongyi.cn 

#ifndef _GGMATRIX2_H_
#define _GGMATRIX2_H_

#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"
#include "TSpectrum.h"
#include "TPolyMarker.h"
#include "TLatex.h"
#include "TMath.h"
// #include "TRootCanvas.h"

#include <iostream> 
#include <sstream> 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ggMatrix2
{
public:
  ggMatrix2(TH2 *gm,TH1 *gs);
  virtual ~ggMatrix2();

  void ShowTotalProject();
  void ShowGated(double ge, int icy=1);
  void ShowGatedMulti(double ge1,double ge2 = 0,double ge3 = 0,double ge4 = 0, double ge5 = 0,double ge6 = 0);
  void NewCanvas(int ncy1);
  
  void SetNPeaks(int n);// eg: 30
  void SetPeakWidth(double left,double right);// eg: -3 3
  void SetPeaksThreshold(double thres);//eg: 0.05
  void SetXRangeUser(double xmin,double xmax);


  int GetNPeaks();
  double GetPeaksThreshold();
  void GetPeakWidth(double &left,double &right);
  void GetXRangeUser(double &xmin,double &xmax);

  
  void PeaksFlag(TH1 *h,TString st = "");

  void CanvasClose();
private:
  TH1 *gTpj;
  TH2 *gMat;
  
  TCanvas *ca[1000];
  // TRootCanvas *ca[1000];
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
