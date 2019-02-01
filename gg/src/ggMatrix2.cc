// ggMatrix2.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 20:30:37 2019 (+0800)
// Last-Updated: 日 1月  6 22:49:37 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 55
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

void ggMatrix2::SetNPeaks(int n)
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

int ggMatrix2::GetNPeaks()
{
  return NoPeaks;
}
double ggMatrix2::GetPeaksThreshold()
{
  return PeaksThreshold;
}
void ggMatrix2::GetPeakWidth(double &left,double &right)
{
  left = PeakWidthLeft;
  right =PeakWidthRight;
}
void ggMatrix2::GetXRangeUser(double &xmin,double &xmax)
{
  xmin = UserMinX;
  xmax = UserMaxX;
}

void ggMatrix2::ShowTotalProject()
{
  NewCanvas(1);

  ca[ic]->cd(1);
  TString sname = TString::Format("%s_%i",gTpj->GetName(),ih++);
  gTpj->SetBinContent(0,0);
  gTpj->SetBinContent(gTpj->GetNbinsX()+1,0);
  TH1D *h = (TH1D*)gTpj->Clone(sname);
  // h->SetTitle(xe->GetTitle());
  PeaksFlag(h,"TpjPeak");
  SetXRangeUser(-1,-1);
}

void ggMatrix2::ShowGated(double ge, int icy)
{
  if(icy > ncy) icy = ncy;
  ca[ic]->cd(icy);

  // TODO 需要优化bin的取值舍入
  int gatel = gBinY*(ge+PeakWidthLeft-gMinY)/(gMaxY-gMinY);
  int gater = gBinY*(ge+PeakWidthRight-gMinY)/(gMaxY-gMinY);

  TH1D *ha = (TH1D*)gMat->ProjectionX(TString::Format("%s_%i","Gated",ih++).Data(),gatel,gater);
  ha->SetBinContent(0,0);
  ha->SetBinContent(ha->GetNbinsX()+1,0);

  PeaksFlag(ha,TString::Format("Gated on ge=%0.1f,bin %d to %d",ge,gatel,gater));
}

void ggMatrix2::ShowGatedMulti(double ge1,double ge2,double ge3,double ge4, double ge5,double ge6)
{
  int npad = 0;
  double ge[6] = {ge1,ge2,ge3,ge4,ge5,ge6};
  for(int i=0;i<6;i++) 
    if(ge[i]>1) npad++;
  NewCanvas(npad);
  for(int i=0;i<npad;i++)
    ShowGated(ge[i],i+1);
}

void ggMatrix2::NewCanvas(int ncy1)
{
  ic++;
  ncy = ncy1;
  double w = 800;
  double h = 800;
  if(ncy1 == 1) h = 400;
  ca[ic] = new TCanvas(TString::Format("ca%i",ic).Data(),TString::Format("canvas%i",ic).Data(),w,h);
  // ca[ic] = new TRootCanvas(cca[ic],TString::Format("acanvas%i",ic).Data(),w,h);
  // ca[ic]->Connect("Closed()","ggMatrix2",this,"CanvasClose()");
  // ca[ic]->Connect("CloseWindow()","ggMatrix2",this,"CanvasClose()");
  // ca[ic]->InitWindow();
  // ca[ic]->Show();
  
  ca[ic]->Divide(1,ncy);
  for(int i = 1; i <= ncy; i++)
    {
      ca[ic]->GetPad(i)->SetBottomMargin(0.04);
      ca[ic]->GetPad(i)->SetTopMargin(0.04);
      ca[ic]->GetPad(i)->SetLeftMargin(0.05);
      ca[ic]->GetPad(i)->SetRightMargin(0.05);
    }
}

void ggMatrix2::PeaksFlag(TH1 *h,TString st)
{
  h->SetAxisRange(UserMinX,UserMaxX,"X");
  // hh->Print("all");
  double ymin = h->GetMinimum();
  double ymax = h->GetMaximum()*1.3;
  if(ymin < 0) ymin = 0.01;
  // std::cout<<"a "<<h->GetMaximum()<<std::endl;
  h->SetTitle("");

  h->Sumw2(0);
  h->SetLineColor(kBlue);
  h->SetFillColor(kCyan);
  TSpectrum *s = new TSpectrum(500);
  h->SetAxisRange(ymin,ymax,"Y");
  h->SetStats(0);
  Int_t nfound = 100;
  Int_t nloop = 0;
  while(nloop < 50)
    {
      nfound=s->Search(h,2,"",PeaksThreshold);
      if(nfound > NoPeaks) PeaksThreshold += 0.005;
      else PeaksThreshold -= 0.005;
      if(PeaksThreshold<0 || TMath::Abs(nfound-NoPeaks)<3 ) break;
      nloop++;
    }
  // cout<<nfound<<" peaks have been found."<<endl;
  TPolyMarker *pm=(TPolyMarker *)
    h->GetListOfFunctions()->FindObject("TPolyMarker");
  // std::cout<<"pm:"<<pm<<std::endl;
  pm->SetMarkerStyle(32);
  pm->SetMarkerColor(kGreen);
  pm->SetMarkerSize(0.4);
  Double_t *xpeaks = s->GetPositionX();
  Double_t *ypeaks = s->GetPositionY();
  for(int j = 0; j < nfound; j++)
    {
    std::stringstream ss;
    ss<<xpeaks[j];
    TString s1=ss.str();
    TLatex *tex = new TLatex(xpeaks[j],ypeaks[j],s1);
    tex->SetTextFont(13);
    tex->SetTextSize(13);
    tex->SetTextAlign(12);
    tex->SetTextAngle(90);
    tex->SetTextColor(kRed);
    tex->Draw();
  }

  if(st != "")
    {
      TLatex *ltx=new TLatex();
      ltx->SetNDC(kTRUE);
      ltx->SetTextColor(1);
      ltx->SetTextFont(22);
      ltx->SetTextSize(0.05);
      ltx->DrawLatex(0.5,0.9,st.Data());
      delete ltx;
    }
}

void ggMatrix2::CanvasClose()
{
  std::cout<<"close canvas test."<<std::endl;
}

// 
// ggMatrix2.cc ends here
