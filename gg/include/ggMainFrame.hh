// ggMainFrame.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 三 1月  2 16:46:43 2019 (+0800)
// Last-Updated: 三 1月  2 16:54:57 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 3
// URL: http://wuhongyi.cn 

#ifndef _GGMAINFRAME_H_
#define _GGMAINFRAME_H_

#include "TGButton.h"
#include "TGButtonGroup.h"
#include "TGLabel.h"
#include "TGNumberEntry.h"
#include "TGTextViewStream.h"
#include "TApplication.h"
#include "TGFrame.h"
#include "TSystem.h"

class ggMainFrame : public TGMainFrame
{
public:
  ggMainFrame();
  virtual ~ggMainFrame();


  void Reset();
  void HandleReturn();
  
protected:
  TGTextButton      *fReset, *fExit;
  TGTextViewostream *fTextView;
  TGVerticalFrame   *fContents;
  TGHorizontalFrame *fButtons, *fCommandFrame;
  TGTextEntry       *fCommand;
  

  ClassDef(ggMainFrame, 1);
};

#endif /* _GGMAINFRAME_H_ */

// 
// ggMainFrame.hh ends here
