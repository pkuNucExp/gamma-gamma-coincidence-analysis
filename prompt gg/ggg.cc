// ggg.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 10月 14 16:46:13 2019 (+0800)
// Last-Updated: 四 10月 17 18:17:40 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 20
// URL: http://wuhongyi.cn 

int xmin;
int xmax;//range for hist
int npeaks;//number of peaks for TSpectrum

/*
TCanvas *ca[1000];
int ic=-1;//canvas id
int icy=1;
int ncy=1;//number of windows in y axia
*/


void setxrange(int xmin1=0, int xmax1=4096){ xmin=xmin1; xmax=xmax1;};
void setnpeaks(int npeaks1=35) {npeaks=npeaks1;};
void newcanvas(int ncy=1);
void peaks(TH1 *h, Double_t thres=0.05);

Double_t getv(TH2I *h,int i, int j)
{
  return h->GetBinContent(i,j);
}

Double_t getv(TH1I *h,int i)
{
  return h->GetBinContent(i);
}

void ggg(Double_t gy, Double_t gz)
{
  Double_t gw = 3;
  
  TFile * cube = new TFile("cube.root");
  TH2I *hg3xy = (TH2I*)cube->Get("cube_hg3xy");//Mij
  TH1I *hg3x = (TH1I*)cube->Get("cube_hg3x");//Pi
  TH1I *hg3xb;//bi

  TSpectrum *sa = new TSpectrum(200);
  hg3xb = (TH1I*)sa->Background(hg3x,8,"nosmoothing same");

  // hg3x->Draw();
  // hg3xb->Draw("same");
  int bin = hg3x->GetNbinsX();
  // cout<<"bin: "<<bin<<endl;
  int iy1 = hg3x->FindBin(gy-gw);
  int iy2 = hg3x->FindBin(gy+gw);
  int iz1 = hg3x->FindBin(gz-gw);
  int iz2 = hg3x->FindBin(gz+gw); 
  // cout<<iy1<<" "<<iy2<<" "<<iz1<<" "<<iz2<<endl;

  int start = iz1>=1?iz1-1:0;
  int stop = iz2<bin?iz2-1:bin-1;
  TFile * file;
  TH2I *hgxy = (TH2I*)hg3xy->Clone("hgxy");
  hgxy->Reset();
  for (int i = start; i <= stop; ++i)
    {
      file = new TFile(TString::Format("cube_%04d.root",i).Data());
      TH2I *hxy = (TH2I*)file->Get(TString::Format("cube_%04d",i).Data());
      hgxy->Add(hxy,1);
      file->Close();
      // cout<<hgxy->GetEntries()<<endl;
    }
  // cout<<"start: "<<start<<"  stop: "<<stop<<endl;

  TH1D* hg = hgxy->ProjectionX("hg",iy1,iy2);
  TH1D *hgb = (TH1D*)hg->Clone("hgb");
  hgb->Reset();
  Double_t T,Mij,Mjk,Mik,Pi,Pj,Pk,bi,bj,bk,Bijk;
  T = hg3x->Integral();
  for(int i = 1; i<=bin; i++)
    for(int j = iy1; j<=iy2; j++)
      for(int k=iz1; k<=iz2; k++)
	{
	  Mij = getv(hg3xy,i,j);
	  Mik = getv(hg3xy,i,k);
	  Mjk = getv(hg3xy,j,k);
	  Pi = getv(hg3x,i);
	  Pj = getv(hg3x,j);
	  Pk = getv(hg3x,k);	
	  bi = getv(hg3xb,i);
	  bj = getv(hg3xb,j);
	  bk = getv(hg3xb,k);	
	  Bijk = (Mij*bk+Mik*bj+Mjk*bi)/T+(-Pi*bj*bk-bi*Pj*bk-bi*bj*Pk+bi*bj*bk)/T/T;
	  hgb->Fill(hgb->GetBinCenter(i),Bijk);
	}

  hgb->Sumw2(0);
  hg->Add(hgb,-1);
  hg->Draw();
  setxrange();
  setnpeaks();
   peaks(hg);
  // hgxy->Draw("colz");
  // hg->Draw();
  // hgb->Draw("same");
}


/*
void newcanvas(int ncy1=1)
{
  ic++;
  ncy=ncy1;
  double w=800;
  double h=800;
  if(ncy1==1)h=400;
  ca[ic]=new TCanvas(Form("ca%i",ic),Form("canvas%i",ic),w,h);
  ca[ic]->Divide(1,ncy);
  for(int i=1;i<=ncy;i++) {
    ca[ic]->GetPad(i)->SetBottomMargin(0.05);
    ca[ic]->GetPad(i)->SetTopMargin(0.07);
    ca[ic]->GetPad(i)->SetLeftMargin(0.05);
    ca[ic]->GetPad(i)->SetRightMargin(0.05);
  }
*/



void peaks(TH1 *h, Double_t thres)
{
  double x0=h->GetBinLowEdge(h->GetNbinsX());
  double x1=h->GetBinLowEdge(0);
  if(xmin<x1) xmin=x1;
  if(xmax>x0) xmax=x0;
  std::cout<<xmin<<std::endl;
  std::cout<<xmax<<std::endl;
  h->SetAxisRange(xmin,xmax,"X");
  double ymin=h->GetBinContent(h->GetMinimumBin());
  double ymax=h->GetBinContent(h->GetMaximumBin())*1.3;
  if(ymin<0) ymin=0.01;
  //cout<<ic<<" "<<icy<<" "<<h->GetName()<<"  ["<<h->GetTitle()<<"]"<<endl;
  h->SetAxisRange(xmin,xmax,"X");  
  h->Sumw2(0);
  h->SetLineColor(kBlue);
  h->SetFillColor(kCyan);
  TSpectrum *s=new TSpectrum(500);					  
  h->SetAxisRange(ymin,ymax,"Y");
  h->SetStats(0);
  Int_t nfound=100;
  Int_t nloop=0;
   while(nloop<50){
    nfound=s->Search(h,2,"",thres);
    if(nfound>npeaks) thres += 0.005;
    else thres -= 0.005;
    if(thres<0 || abs(nfound-npeaks)<3 ) break;
    nloop++;
    }
   cout<<nfound<<" "<<npeaks<<endl;
  TPolyMarker *pm=(TPolyMarker *)
                      h->GetListOfFunctions()->FindObject("TPolyMarker");
  pm->SetMarkerStyle(32);
  pm->SetMarkerColor(kGreen);
  pm->SetMarkerSize(0.4);
  Double_t *xpeaks=s->GetPositionX();
  Double_t *ypeaks=s->GetPositionY();
  for(int j=0;j<nfound;j++) {
   stringstream ss;
   ss<<xpeaks[j];
   TString s1=ss.str();
   TLatex *tex=new TLatex(xpeaks[j],ypeaks[j],s1);
   tex->SetTextFont(13);
   tex->SetTextSize(20);
   tex->SetTextAlign(12);
   tex->SetTextAngle(90);
   tex->SetTextColor(kRed);
   tex->Draw();
   }
}

// 
// ggg.cc ends here
