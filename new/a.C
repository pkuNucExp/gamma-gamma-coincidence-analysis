#define gg_cxx
#include "gg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void gg::Loop()
{
   if (fChain == 0) return;
   Short_t nt;
   Short_t tx,ty,masst;

   TFile *f1=new TFile(Form("tt%d_%d.root",run1,run2),"RECREATE");
   f1->cd();
   TTree *opt1=new TTree("tree","tree");
   opt1->Branch("tx",&tx,"tx/S");
   opt1->Branch("ty",&ty,"ty/S");
   opt1->Branch("nt",&nt,"nt/S");
   opt1->Branch("masst",&masst,"masst/S");

   Short_t np,px,py,massp;
   TFile *f2=new TFile(Form("pp%d_%d.root",run1,run2),"RECREATE");
   f2->cd();
   TTree *opt2=new TTree("tree","tree");
   opt2->Branch("px",&px,"px/S");
   opt2->Branch("py",&py,"py/S");
   opt1->Branch("np",&np,"np/S");
   opt2->Branch("massp",&massp,"massp/S");

   Short_t nd,dx,dy,dgt;
   TFile *f3=new TFile(Form("dd%d_%d.root",run1,run2),"RECREATE");
   f3->cd();
   TTree *opt3=new TTree("tree","tree");
   opt3->Branch("dx",&dx,"dx/S");
   opt3->Branch("dy",&dy,"dy/S");
   opt1->Branch("nd",&nd,"nd/S");
   opt3->Branch("dgt",&dgt,"dgt/S");

   Short_t npx,ndy;
   TFile *f4=new TFile(Form("pd%d_%d.root",run1,run2),"RECREATE");
   f4->cd();
   TTree *opt4=new TTree("tree","tree");
   opt4->Branch("px",&px,"px/S");
   opt4->Branch("dy",&dy,"dy/S");
   opt4->Branch("npx",&npx,"npx/S");
   opt4->Branch("ndy",&ndy,"ndy/S");
   opt4->Branch("dgt",&dgt,"dgt/S");

   Short_t ntx,nddy;

   TFile *f5=new TFile(Form("td%d_%d.root",run1,run2),"RECREATE");
   f5->cd();
   TTree *opt5=new TTree("tree","tree");
   opt5->Branch("tx",&tx,"tx/S");
   opt5->Branch("dy",&dy,"dy/S");
   opt5->Branch("ntx",&ntx,"ntx/S");
   opt5->Branch("ndy",&nddy,"ndy/S");
   opt5->Branch("dgt",&dgt,"dgt/S");
   int ntt=0,ndd=0;
   Long64_t nentries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      float GGeT[1000],GGeP[1000],GGe[1000],GGt[1000];
      float GGed[1000],GGtd[1000];
      int nGG=0,nGGd=0;
      for(int i=0;i<nGam;i++) {
	if(Gdt[i]>-30 && Gdt[i]<30 && Gfom[i]<0.8 && Ge[i]<2000) {//prompt
	  GGeT[nGG]=GeT[i];
	  GGeP[nGG]=GeP[i];
	  GGe[nGG]=Ge[i];
	  GGt[nGG]=Gdt[i];
	  nGG++;
	}
	if(Gdt[i]>40 && Gfom[i]<0.8 && Ge[i]<2000) {//delayed
	  GGed[nGGd]=Ge[i];
	  GGtd[nGGd]=Gdt[i];
	  nGGd++;
	}
      }  
      if(nGG>1 && nGG<=4) {
	for(int i=0;i<nGG-1;i++){
	  for(int j=i+1;j<nGG;j++){
	    if(abs(GGt[i]-GGt[j])<20){//g-g
	      nt=nGG;
	      tx=GGeT[i];
	      ty=GGeT[j];
	      masst=MassT;
	      opt1->Fill();
	      tx=GGeT[j];
	      ty=GGeT[i];
	      opt1->Fill();
	      np=nGG;
	      px=GGeP[i];
	      py=GGeP[j];
	      massp=MassP;
	      opt2->Fill();
	      px=GGeP[j];
	      py=GGeP[i];
	      opt2->Fill();
	    }
	  }
	}
	}
  
     if(nGGd>=2) {
	for(int i=0;i<nGGd-1;i++){
	  for(int j=i+1;j<nGGd;j++){
	    if(abs(GGtd[i]-GGtd[j])<20){//g-g
	      nd=nGGd;
	      dx=(Short_t)GGed[i];
	      dy=(Short_t)GGed[j];
	      dgt=(Short_t)(GGtd[i]+GGtd[j])/2.;
              opt3->Fill();
	      dx=(Short_t)GGed[j];
	      dy=(Short_t)GGed[i];
	      opt3->Fill();
	      ndd++;
	    }
	  }
	}  
     }
      if(nGG>0 && nGG<=4 && nGGd>0) {//prompt-two fold, delay-one fold
	for(int i=0;i<nGG;i++){
	  for(int j=0;j<nGGd;j++){
	    ndy=nGGd;
	    nddy=nGGd;
	    ntx=nGG;
	    npx=nGG;
	    px=GGeP[i];
	    tx=GGeT[i];
	    dy=GGed[j];
	    dgt=GGtd[j];
	    opt4->Fill();
	    opt5->Fill();

	  }
	}
      } 

         
      if(jentry % 10000 == 0) {
	printf("Process %.2f \%, %dk / %dk\r",Double_t(jentry)/nentries*100.,
	       jentry/1000,nentries/1000);
	fflush(stdout);
      }
      
   }
   cout<<ntt<<" "<<ndd<<endl;
   f1->cd();
   opt1->Write();
   f1->Close();
   f2->cd();
   opt2->Write();
   f2->Close();
   f3->cd();
   opt3->Write();
   f3->Close();
   f4->cd();
   opt4->Write();
   f4->Close();
   f5->cd();
   opt5->Write();
   f5->Close();
 }
