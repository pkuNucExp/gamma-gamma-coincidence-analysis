// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 六 4月 19 09:14:41 2014 (+0800)
// Last-Updated: 三 1月  2 17:00:17 2019 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 165
// URL: http://wuhongyi.cn 

#include "TRint.h"
#include "TObject.h"

#include "ggMainFrame.hh"
using namespace std;

int main(int argc, char *argv[])
{
   // Create an interactive ROOT application
   TRint *theApp = new TRint("Rint", &argc, argv);

   //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

   new ggMainFrame();

   //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
   // and enter the event loop...
   theApp->Run();
   delete theApp;

  return 0;
}

// 
// main.cc ends here
