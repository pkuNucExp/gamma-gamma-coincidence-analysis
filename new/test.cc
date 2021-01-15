// test.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 1月  5 13:53:07 2021 (+0800)
// Last-Updated: 二 1月  5 13:54:10 2021 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 1
// URL: http://wuhongyi.cn 

void test()
{
  int run1 = 100;
  int run2 = 101;
  
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

// 
// test.cc ends here










