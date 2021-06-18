// test.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 1月  5 13:53:07 2021 (+0800)
// Last-Updated: 日 1月 24 20:50:18 2021 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

TFile *filew = new TFile("output.root","RECREATE");//"RECREATE" "READ"
if(!filew->IsOpen())
  {
    std::cout<<"Can't open root file"<<std::endl;
  }

// filew->ls("");
// filew = tree->GetCurrentFile();
// filew->cd();
// TObject->Write();
// TH1D *h = (TH1D*)filew->Get("name");
// TH1D *h; filew->GetObject("name", h);
filew->Close();


TTree *tree = new TTree("t","Hongyi Wu Data");
// TTree *tree = (TTree*)rootfile->Get("t");


// Branch / write
// int mhit;
// int hitdata[1024];
// tree->Branch("mhit",&mhit,"mhit/I");
// tree->Branch("hitdata",&hitdata,"hitdata[mhit]/I");

// file = tree->GetCurrentFile();
tree->Fill();//loop
// tree->Write();

// tree->GetEntries();//获取entry数
// tree->Print("");// "all" friend trees are also printed. "toponly" only the top level branches are printed. "clusters" information about the cluster of baskets is printed.    T.Print("xxx*") will print all branches with name starting with "xxx".

// Branch / read
// Event *event = 0;  //event must be null or point to a valid object it must be initialized
// tree->SetBranchAddress("event",&event);
// tree->GetEntry( /*int*/);


// 
// test.cc ends here










