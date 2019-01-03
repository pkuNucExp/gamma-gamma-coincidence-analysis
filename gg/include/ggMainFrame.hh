// ggMainFrame.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 16:46:43 2019 (+0800)
// Last-Updated: 四 1月  3 16:46:38 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 15
// URL: http://wuhongyi.cn 

#ifndef _GGMAINFRAME_H_
#define _GGMAINFRAME_H_

#include "ggMatrix2.hh"

#include "TGButton.h"
#include "TGButtonGroup.h"
#include "TGLabel.h"
#include "TGNumberEntry.h"
#include "TGTextViewStream.h"
#include "TApplication.h"
#include "TGFrame.h"
#include "TGFileDialog.h"

#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"

#include <iostream> 
#include <sstream>
#include <cstring>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ggMainFrame : public TGMainFrame
{
public:
  ggMainFrame();
  virtual ~ggMainFrame();


  void Reset();
  void LoadFile();
  void HandleReturn();
  
private:
  void MainFrame();
  
protected:
  TGTextButton      *fLoad;

  
  TGTextButton      *fReset, *fExit;
  TGTextViewostream *fTextView;
  TGVerticalFrame   *fContents;
  TGHorizontalFrame *fButtons, *fCommandFrame;
  TGTextEntry       *fCommand;

  ggMatrix2 *ggmatrix2;
  TFile *fileraw;
  TH2I *ggm;
  TH1D *xe;

  // static TString gFileDir;
  TString gRootFileName;
  
  ClassDef(ggMainFrame, 1);
};

#endif /* _GGMAINFRAME_H_ */

// 
// ggMainFrame.hh ends here
