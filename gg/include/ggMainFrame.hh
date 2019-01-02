// ggMainFrame.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 16:46:43 2019 (+0800)
// Last-Updated: 三 1月  2 22:20:04 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 9
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
#include "TSystem.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class ggMainFrame : public TGMainFrame
{
public:
  ggMainFrame();
  virtual ~ggMainFrame();


  void Reset();
  void HandleReturn();
  
private:
  void MainFrame();
  
protected:
  TGTextButton      *fReset, *fExit;
  TGTextViewostream *fTextView;
  TGVerticalFrame   *fContents;
  TGHorizontalFrame *fButtons, *fCommandFrame;
  TGTextEntry       *fCommand;

  ggMatrix2 *ggmatrix2;
  TFile *fileraw;
  TH2I *ggm;
  TH1D *xe;


  
  ClassDef(ggMainFrame, 1);
};

#endif /* _GGMAINFRAME_H_ */

// 
// ggMainFrame.hh ends here
