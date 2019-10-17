// cube.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 10月 13 14:23:25 2019 (+0800)
// Last-Updated: 日 10月 13 15:38:47 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 11
// URL: http://wuhongyi.cn 

#include "cube.hh"
#include <iostream>

cube::cube(int bin, double max_e)
{
  BINNUMBER = bin;
  MAXENERGY = max_e;


  hg3x = new TH1I("cube_hg3x","total projection spectrum for hg3xyz",BINNUMBER,0.0,MAXENERGY);
  hg3xy = new TH2I("cube_hg3xy","x-y projection of hg3xyz",BINNUMBER,0,MAXENERGY,BINNUMBER,0.0,MAXENERGY);

  hg3xyz = new TH2I *[BINNUMBER];
  for (int i = 0; i < BINNUMBER; ++i)
    {
      hg3xyz[i] = new TH2I(TString::Format("cube_%04d",i).Data(),"",BINNUMBER,0.0,MAXENERGY,BINNUMBER,0.0,MAXENERGY);
    }
}

cube::~cube()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void cube::Fill(double ex,double ey,double ez)
{
  if(ex<MAXENERGY && ey<MAXENERGY && ez<MAXENERGY)
    {
      hg3x->Fill(ex);
      hg3xy->Fill(ex,ey);
      hg3xyz[int(ez/MAXENERGY*BINNUMBER)]->Fill(ex,ey);
    }
}


void cube::Save(int run)
{
  TFile *cubesave;
  
  cubesave = new TFile(TString::Format("cube_R%04d.root",run).Data(),"RECREATE");
  if(!cubesave->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
  hg3x->Write();
  hg3xy->Write();
  cubesave->Close();

  for (int i = 0; i < BINNUMBER; ++i)
    {
      cubesave = new TFile(TString::Format("cube_%04d_R%04d.root",i,run).Data(),"RECREATE");
      if(!cubesave->IsOpen())
	{
	  std::cout<<"Can't open root file"<<std::endl;
	}
      hg3xyz[i]->Write();
      cubesave->Close();
    }
  
}


// 
// cube.cc ends here
