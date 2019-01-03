// ggMainFrame.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 16:47:02 2019 (+0800)
// Last-Updated: 四 1月  3 10:57:20 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 31
// URL: http://wuhongyi.cn 

#include "ggMainFrame.hh"

ClassImp(ggMainFrame);
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ggMainFrame::ggMainFrame()
  : TGMainFrame(gClient->GetRoot())
{
  fileraw = NULL;
  ggmatrix2 = NULL;
  ggm = NULL;
  xe = NULL;
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  MainFrame();
}

ggMainFrame::~ggMainFrame()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ggMainFrame::MainFrame()
{
  SetCleanup(kDeepCleanup);

  // Contents
  fContents = new TGVerticalFrame(this);
  fButtons = new TGHorizontalFrame(fContents);

  // TextView
  fTextView = new TGTextViewostream(fContents, 500, 300);
  fContents->AddFrame(fTextView, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 0));

  fCommandFrame = new TGHorizontalFrame(fContents);
  fCommand = new TGTextEntry(fCommandFrame, (const char *)"", 20);
  fCommand->Connect("ReturnPressed()", "ggMainFrame", this, "HandleReturn()");
  fCommandFrame->AddFrame(new TGLabel(fCommandFrame, "Command: "),
			  new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 5, 5));
  fCommandFrame->AddFrame(fCommand, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  fContents->AddFrame(fCommandFrame, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));

  // The button for test
  fReset = new TGTextButton(fButtons, "&Reset");
  fReset->SetToolTipText("Press to clear the command entry\nand the TGTextView", 200);
  fReset->Connect("Clicked()", "ggMainFrame", this, "Reset()");
  fButtons->AddFrame(fReset, new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));

  fExit = new TGTextButton(fButtons, "&Exit");
  fExit->SetToolTipText("Terminate the application", 200);
  fButtons->AddFrame(fExit, new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));
  fExit->Connect("Pressed()", "TApplication", gApplication, "Terminate()");

  fContents->AddFrame(fButtons, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 0, 0, 0, 0));
  Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  DontCallClose();

  AddFrame(fContents, new TGLayoutHints(kLHintsTop | kLHintsExpandX | kLHintsExpandY));
  MapSubwindows();
  Resize(GetDefaultSize());

  SetWindowName("g-g coincidence analysis");
  MapRaised();
}

void ggMainFrame::Reset()
{
  fCommand->Clear();
  fTextView->Clear();

  if(fileraw != NULL) delete fileraw;
  TString fname="xia.root";//filename;
  fileraw = new TFile(fname);
  std::cout<<"Load ROOT file: "<<fname<<std::endl;

  *fTextView<<"Load ROOT file: "<<fname<<std::endl;

  xe = (TH1D*)fileraw->Get("TpjPeak");
  // xe->SetTitle(xe->GetName());
  ggm = (TH2I*)fileraw->Get("ggmat");
  // ggm->SetTitle(ggm->GetName());

  
  if(ggmatrix2 != NULL) delete ggmatrix2;
  ggmatrix2 = new ggMatrix2(ggm,xe);



  
}

void ggMainFrame::HandleReturn()
{
  std::string line;
  std::string command = fCommand->GetText();
  // *fTextView << gSystem->GetFromPipe(command.c_str()).Data() << std::endl;
  *fTextView<<command<<std::endl;

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // TODO

  if(ggmatrix2 == NULL) return;
  
  std::string flagcommand;
  
  std::stringstream ss(command);
  ss>>flagcommand;

  if(flagcommand=="nc" || flagcommand=="newcanvas")
    {
      // std::cout<<"Command: nc"<<std::endl;
      int ncy1 = 0;
      ss >> ncy1;
      if(ncy1 > 0)
	{
	  ggmatrix2->NewCanvas(ncy1);
	}
      else
	{
	  *fTextView<<"Invalid canvas number."<<std::endl;
	}
      
    }
  else if(flagcommand=="sr" || flagcommand=="setrange")
    {
      double ul = -1;
      double ur = -1;
      ss >> ul >> ur;
      if(ul < ur)
	{
	  ggmatrix2->SetXRangeUser(ul,ur);
	}
      else
	{
	  *fTextView<<"Invalid range."<<std::endl;
	}
      
    }
  else if(flagcommand=="g" || flagcommand=="gate")
    {
      std::cout<<"Command gate not defind."<<std::endl;
    }
  else if(flagcommand=="gm")
    {
      int mhit = 0;
      double ge[100];
      while(ss >> ge[mhit])
	{
	  std::cout<<"gate: "<<ge[mhit]<<std::endl;
	  mhit++;
	}
      std::cout<<"mhit: "<<mhit<<std::endl;

      switch(mhit)
	{
	case 1:
	  ggmatrix2->ShowGatedMulti(ge[0]);
	  break;
	case 2:
	  ggmatrix2->ShowGatedMulti(ge[0],ge[1]);
	  break;
	case 3:
	  ggmatrix2->ShowGatedMulti(ge[0],ge[1],ge[2]);
	  break;	  
	case 4:
	  ggmatrix2->ShowGatedMulti(ge[0],ge[1],ge[2],ge[3]);
	  break;
	case 5:
	  ggmatrix2->ShowGatedMulti(ge[0],ge[1],ge[2],ge[3],ge[4]);
	  break;
	case 6:
	  ggmatrix2->ShowGatedMulti(ge[0],ge[1],ge[2],ge[3],ge[4],ge[5]);
	  break;
	default:
	  *fTextView<<"Invalid gated."<<std::endl;
	}
      
    }
  else if(flagcommand=="tpj" || flagcommand=="totalproject")
    {
      ggmatrix2->ShowTotalProject();
    }
  else if(flagcommand=="snp")
    {
      int n = 0;
      ss >> n;
      if(n > 0)
	{
	  ggmatrix2->SetNPeaks(n);
	}
      else
	{
	  *fTextView<<"Invalid peaks number."<<std::endl;
	}
    }
  else if(flagcommand=="spw")
    {
      double ul = 10000;
      double ur = -10000;
      ss >> ul >> ur;
      if(ul < 0 && ur > 0)
	{
	  ggmatrix2->SetPeakWidth(ul,ur);
	}
      else
	{
	  *fTextView<<"Invalid peak width."<<std::endl;
	}
    }
  else if(flagcommand=="spt")
    {
      double thres = 100;
      ss >> thres;
      if(thres > 0 && thres <1)
	{
	  ggmatrix2->SetPeaksThreshold(thres);
	}
      else
	{
	  *fTextView<<"Invalid peak threshold."<<std::endl;
	}
    }
  else
    {
      *fTextView<<"Invalid command."<<std::endl;
    }
  
  
  

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  fTextView->ShowBottom();
  fCommand->Clear();
}

// 
// ggMainFrame.cc ends here
