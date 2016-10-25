#ifndef STACKHISTHELPER_H
#define STACKHISTHELPER_H

#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <map>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TPad.h"
#include "TLine.h"
#include "TString.h"
#include "TLegend.h"
#include "TMatrix.h"
#include "TMatrixDEigen.h"
#include "TDecompSVD.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TGraphAsymmErrors.h"
#include "TVectorD.h"
#include "TLatex.h"
#include "TF1.h"
#include "TEfficiency.h"

class StackHistHelper
{
private:
  std::vector<TH1*> vHist;

public:
  StackHistHelper() {};

  void addHist(TH1* h)
  {
    TH1* hStack = (TH1*)h->Clone( TString(h->GetName()) + "_Stack" );

    if( vHist.size() != 0 ) hStack->Add( vHist[vHist.size()-1] );
    vHist.push_back(hStack);
  }

  void addHistFromFileWithPrefix(TFile* file, TString histname, std::vector<TString> vPrefix)
  {
    for(unsigned int iPrefix=0; iPrefix<vPrefix.size(); iPrefix++) {
      TH1* h = (TH1*)file->Get(histname + vPrefix[iPrefix]);
      addHist(h);
    }
  }

  unsigned int getHistSize() { return vHist.size(); }

  TH1* getHist(unsigned int nbr, bool reverse=true)
  {
    if( nbr >= vHist.size() ) return NULL;

    if( reverse ) {
      return vHist[ vHist.size()-1-nbr ];
    }

    return vHist[nbr];
  }

  
};


#endif