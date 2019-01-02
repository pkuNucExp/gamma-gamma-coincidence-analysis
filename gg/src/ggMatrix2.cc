// ggMatrix2.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 20:30:37 2019 (+0800)
// Last-Updated: 三 1月  2 22:26:34 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 14
// URL: http://wuhongyi.cn 

#include "ggMatrix2.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ggMatrix2::ggMatrix2(TH2 *gm,TH1 *gs)
{
  gTpj = gs;
  gMat = gm;

  NoPeaks = 30;
  PeakWidthLeft = -3;
  PeakWidthRight = 3;
  PeaksThreshold = 0.05;

  
  gBinX = gMat->GetNbinsX();
  gBinY = gMat->GetNbinsY();
  gMinX = gMat->GetXaxis()->GetXmin();
  gMaxX = gMat->GetXaxis()->GetXmax();
  gMinY = gMat->GetYaxis()->GetXmin();
  gMaxY = gMat->GetYaxis()->GetXmax();

  UserMinX = gMinX;
  UserMaxX = gMaxX;
}

ggMatrix2::~ggMatrix2()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ggMatrix2::SetNoPeaks(int n)
{
  // TODO 添加参数合理性判断
  NoPeaks = n;
}

void ggMatrix2::SetPeakWidth(double left,double right)
{
  // TODO 添加参数合理性判断
  PeakWidthLeft = left;
  PeakWidthRight = right;
}

void ggMatrix2::SetPeaksThreshold(double thres)
{
  // TODO 添加参数合理性判断
  PeaksThreshold = thres;
}


void ggMatrix2::SetXRangeUser(double xmin,double xmax)
{
  if(xmin < 0 || xmax < 0)
    {
      UserMinX = gMinX;
      UserMaxX = gMaxX;
    }
  else
    {
      UserMinX = xmin;
      UserMaxX = xmax;
    }
}


void ggMatrix2::ShowTotalProject()
{
  NewCanvas(1);

  ca[ic]->cd(1);
  TString sname = TString::Format("%s_%i",gTpj->GetName(),ih++);
  TH1D *h = (TH1D*)gTpj->Clone(sname);
  // h->SetTitle(xe->GetTitle());
  // peaks(h);
  PeaksFlag(h);
  SetXRangeUser(-1,-1);
}

void ggMatrix2::NewCanvas(int ncy1)
{
  ic++;
  ncy = ncy1;
  double w = 800;
  double h = 800;
  if(ncy1 == 1) h = 400;
  ca[ic] = new TCanvas(TString::Format("ca%i",ic).Data(),TString::Format("canvas%i",ic).Data(),w,h);
  ca[ic]->Divide(1,ncy);
  for(int i = 1; i <= ncy; i++)
    {
      ca[ic]->GetPad(i)->SetBottomMargin(0.04);
      ca[ic]->GetPad(i)->SetTopMargin(0.04);
      ca[ic]->GetPad(i)->SetLeftMargin(0.05);
      ca[ic]->GetPad(i)->SetRightMargin(0.05);
    }
}

void ggMatrix2::PeaksFlag(TH1 *hh)
{
  // TString sname=Form("%s_%i",hh->GetName(),ih++);
  // // double x0=hh->GetBinLowEdge(hh->GetNbinsX());
  // // double x1=hh->GetBinLowEdge(0);
  // // if(xmin<x1) xmin=x1;
  // // if(xmax>x0) xmax=x0;
  // // hh->SetAxisRange(xmin,xmax,"X");
  // // hh->Print("all");
  // double ymin=hh->GetMinimum();
  // double ymax=hh->GetMaximum()*1.3;
  // if(ymin<0) ymin=0.01;
  // cout<<"a "<<hh->GetMaximum()<<endl;
  // TH1D *h=(TH1D*)hh->Clone(sname);
  // h->SetTitle("");
  // h->SetAxisRange(xmin,xmax,"X");
  // h->Sumw2(0);
  // h->SetLineColor(kBlue);
  // h->SetFillColor(kCyan);
  // TSpectrum *s=new TSpectrum(500);
  // h->SetAxisRange(ymin,ymax,"Y");
  // h->SetStats(0);
  // Int_t nfound=100;
  // Int_t nloop=0;
  // while(nloop<50){
  //   nfound=s->Search(h,2,"",PeaksThreshold);
  //   if(nfound>npeaks) PeaksThreshold += 0.005;
  //   else PeaksThreshold -= 0.005;
  //   if(PeaksThreshold<0 || abs(nfound-npeaks)<3 ) break;
  //   nloop++;
  // }
  // // cout<<nfound<<" peaks have been found."<<endl;
  // TPolyMarker *pm=(TPolyMarker *)
  //   h->GetListOfFunctions()->FindObject("TPolyMarker");
  // cout<<"pm:"<<pm<<endl;
  // pm->SetMarkerStyle(32);
  // pm->SetMarkerColor(kGreen);
  // pm->SetMarkerSize(0.4);
  // Double_t *xpeaks=s->GetPositionX();
  // Double_t *ypeaks=s->GetPositionY();
  // for(int j=0;j<nfound;j++) {
  //   stringstream ss;
  //   ss<<xpeaks[j];
  //   TString s1=ss.str();
  //   TLatex *tex=new TLatex(xpeaks[j],ypeaks[j],s1);
  //   tex->SetTextFont(13);
  //   tex->SetTextSize(13);
  //   tex->SetTextAlign(12);
  //   tex->SetTextAngle(90);
  //   tex->SetTextColor(kRed);
  //   tex->Draw();
  // }
}


// 
// ggMatrix2.cc ends here
