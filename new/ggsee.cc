// ggsee.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 五 1月 15 19:24:59 2021 (+0800)
// Last-Updated: 五 1月 15 20:23:13 2021 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 10
// URL: http://wuhongyi.cn 



#define DATAFORMAT_M4B 0
#define DATAFORMAT_ROOT 1
#define DATAFORMAT DATAFORMAT_ROOT //定义数据格式，选择 DATAFORMAT_M4B 或者 DATAFORMAT_ROOT


#if DATAFORMAT == DATAFORMAT_M4B//如果采用 m4b 格式数据，则修改以下定义
#define BINNUMBER 4096
#define ENERGYMAX 4096  //keV
#define FILENAME_M4B  "co59.m4b"
#elif DATAFORMAT == DATAFORMAT_ROOT//如果采用 root 格式数据，则修改以下定义
#define FILENAME_ROOT "187Tl.root"
#define ROOTTH2TYPE  TH2D  //可选择 TH2I TH2F TH2D
#define ROOTTH2NAME  "hg2"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 以下程序请勿修改
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"

#include <fstream>
#include <iostream>
#include <set>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TCanvas* c1;
TCanvas* c2;

TH2 *h2 = NULL;
TH2 *h22 = NULL;


void ggsee()
{



#if DATAFORMAT == DATAFORMAT_M4B
  h2 = new TH2D("h2","",BINNUMBER,0,ENERGYMAX,BINNUMBER,0,ENERGYMAX);
  uint data;
  std::ifstream readdata(FILENAME_M4B,std::ios::binary);
  for (int i = 1; i <= BINNUMBER; ++i)
    for (int j = 1; j <= BINNUMBER; ++j)
      {
	readdata.read((char*)&data,sizeof(uint));
	if(data > 0)
	  {
	    h2->SetBinContent(i,j,data);
	  }
      }
  readdata.close();
#elif DATAFORMAT == DATAFORMAT_ROOT
  TFile *fin=new TFile(FILENAME_ROOT);
  h2=(ROOTTH2TYPE*)fin->Get(ROOTTH2NAME);
  h2->ClearUnderflowAndOverflow();
#endif

  

  

}


void tpj()
{
  if(!c1) { c1 = new TCanvas("c1","g-g matrix"); }
  c1->cd();
  h2->Draw("colz");
  c1->Draw();
  c1->AddExec("pointflag","pointflag()");


  if(!c2) { c2 = new TCanvas("c2","c2"); }
}

void pointflag()
{
  int pe = gPad->GetEvent();
  if(pe != 11) return;
  gPad->GetCanvas()->FeedbackMode(kTRUE);



  TObject *select = gPad->GetSelected();
  if(!select) {return;}
  if (!select->InheritsFrom(TH1::Class())) {return;}

  
  int px = gPad->GetEventX();
  int py = gPad->GetEventY();


  float uxmin = gPad->GetUxmin();
  float uxmax = gPad->GetUxmax();
  float uymin = gPad->GetUymin();
  float uymax = gPad->GetUymax();
  int pxmin = gPad->XtoAbsPixel(uxmin);
  int pxmax = gPad->XtoAbsPixel(uxmax);
  int pymin = gPad->YtoAbsPixel(uymin);
  int pymax = gPad->YtoAbsPixel(uymax);
      
  Float_t upx = gPad->AbsPixeltoX(px);
  Float_t upy = gPad->AbsPixeltoY(py);

  
  std::cout<<"px: "<<upx<<"   py:"<<upy<<std::endl;

  c2->cd();
  if(h22!=NULL)
    {
      delete h22;
      h22 = NULL;
    }
  h22 = (ROOTTH2TYPE *)h2->Clone("h22");
  h22->GetXaxis()->SetRangeUser(upx-10,upx+10);
  h22->GetYaxis()->SetRangeUser(upy-10,upy+10);
  h22->Draw("surf2");

  c2->Modified();
  c2->Update();
  gSystem->ProcessEvents();
  
}



// 
// ggsee.cc ends here















