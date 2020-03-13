#include <iostream>
#include <cassert>

#include "TROOT.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TString.h"
#include "TStyle.h"
#include "TList.h"
#include "TMinuit.h"
#include "TVirtualFitter.h"
#include <TSystem.h>

#define th_ph_optimize false
#define y_optimize false
#define dp_optimize true

#include "ROpticsOpt.h"
//#include "SaveCanvas.C"

using namespace std;

class ROpticsOpt;

ROpticsOpt * opt;
UInt_t NPara = 0;
Double_t OldMatrixArray[1000] = {-99}; //NPara
Bool_t freepara[10000] = {kFALSE}; //NPara

UInt_t MaxDataPerGroup = 100;

TString DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/Sieve.Full.test_reform";


typedef void (*PTRFCN)(Int_t &, Double_t *, Double_t &, Double_t*, Int_t);
PTRFCN myfcn = NULL;

void myfcn1(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
    //compute the sum of squares of dth

    assert(opt);
    assert(opt->fCurrentMatrixElems);

    opt->Array2Matrix(par);
    f = opt->SumSquareDTh();

    return;
}

void myfcn2(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
    //compute the sum of squares of dph

    assert(opt);
    assert(opt->fCurrentMatrixElems);

    opt->Array2Matrix(par);
    f = opt->SumSquareDPhi();

    return;
}

void myfcn3(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
    //compute the sum of squares of dtgy

    assert(opt);
    assert(opt->fCurrentMatrixElems);

    opt->Array2Matrix(par);
    f = opt->SumSquareDTgY();

    return;
}

void myfcn4(Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
    //compute the sum of squares of dp

    assert(opt);
    assert(opt->fCurrentMatrixElems);

    opt->Array2Matrix(par);
    f = opt->SumSquareDp();

    return;
}

void DoMinTP(TString SourceDataBase, TString DestDataBase, UInt_t MaxDataPerGroup = 200)
{
    // minimize with root

    assert(opt);
    assert(opt->fCurrentMatrixElems);
    
    opt->LoadDataBase(SourceDataBase);
    NPara = opt->Matrix2Array(OldMatrixArray, freepara);
    opt->LoadRawData(DataSource, (UInt_t) - 1, MaxDataPerGroup);
    opt->PrepareSieve();
    opt->Print();
    
#if th_ph_optimize  
                                          
    TVirtualFitter::SetDefaultFitter("Minuit"); //default is Minuit
    TVirtualFitter *fitter = TVirtualFitter::Fitter(NULL, NPara);
    fitter->SetFCN(myfcn);

    for (UInt_t i = 0; i < NPara; i++) {
      //      cout<<"i:"<<i<<endl;
        Double_t absold = TMath::Abs(OldMatrixArray[i]);
        Double_t abslimit = absold > 0 ? absold * 10000 : 10000;

        fitter->SetParameter(i, Form("TMatrix%03d", i), OldMatrixArray[i], absold > 0 ? absold / 10 : 0.1, -abslimit, abslimit);
        // fitter->SetParameter(1,"asdf",0,0,0,0);

        if (!freepara[i]) fitter->FixParameter(i);
    }

    fitter->Print();
    cout << fitter->GetNumberFreeParameters() << " Free  / " << fitter->GetNumberTotalParameters() << " Parameters\n";

    assert(opt->fNRawData > 0);
    assert(NPara > 0);
    assert(fitter->GetNumberFreeParameters() > 0);
    assert(fitter->GetNumberTotalParameters() == NPara);

    Double_t arglist[1] = {0};
    fitter->ExecuteCommand("MIGRAD", arglist, 0);
    
#endif                   
                 
    opt->Print();
    opt->SaveDataBase(DestDataBase); 
    opt->SaveNewDataBase(Form("%s",DestDataBase.Data()));

    opt->SumSquareDTh();
    opt->SumSquareDPhi();
    
    TCanvas * c1 = opt->CheckSieve(-1);
    c1->Print(DestDataBase+".Sieve.Opt.png", "png");
    c1->Print(DestDataBase+".Sieve.Opt.eps", "eps");
    
    //    TCanvas * c2 = opt->CheckSieveAccu(-1);
    //    c2->Print(DestDataBase + ".TpAccu.Opt.png", "png");
    //    c2->Print(DestDataBase + ".TpAccu.Opt.eps", "eps");

#if th_ph_optimize
    delete fitter;
#endif    
}

void DoMinY(TString SourceDataBase, TString DestDataBase, UInt_t MaxDataPerGroup = 100)
{
    // minimize with root

    assert(opt);
    assert(opt->fCurrentMatrixElems);

    opt->LoadDataBase(SourceDataBase);
    NPara = opt->Matrix2Array(OldMatrixArray, freepara);
    cout<<"NPara:"<<NPara<<endl;
    opt->LoadRawData(DataSource, (UInt_t) - 1, MaxDataPerGroup);
    opt->PrepareVertex();

    opt->Print();

#if y_optimize                                  
    TVirtualFitter::SetDefaultFitter("Minuit"); //default is Minuit
    TVirtualFitter *fitter = TVirtualFitter::Fitter(NULL, NPara);
    fitter->SetFCN(myfcn);

    for (UInt_t i = 0; i < NPara; i++) {
        Double_t absold = TMath::Abs(OldMatrixArray[i]);
        Double_t abslimit = absold > 0 ? absold * 10000 : 10000;

        fitter->SetParameter(i, Form("TMatrix%03d", i), OldMatrixArray[i], absold > 0 ? absold / 10 : 0.1, -abslimit, abslimit);
        // fitter->SetParameter(1,"asdf",0,0,0,0);

        if (!freepara[i]) fitter->FixParameter(i);
    }

    fitter->Print();
    cout << fitter->GetNumberFreeParameters() << " Free  / " << fitter->GetNumberTotalParameters() << " Parameters\n";
    //    cout<<"NPara:"<<NPara<<endl;

    assert(opt->fNRawData > 0);
    assert(NPara > 0);
    assert(fitter->GetNumberFreeParameters() > 0);
    assert(fitter->GetNumberTotalParameters() == NPara);
    
    Double_t arglist[1] = {0};
    fitter->ExecuteCommand("MIGRAD", arglist, 0);
#endif
                               
    opt->Print();
    opt->SaveDataBase(DestDataBase);
    opt->SaveNewDataBase(Form("%s",DestDataBase.Data()));

    opt->SumSquareDTgY();

    TCanvas * c1 = opt->CheckVertex();
    c1->Print(DestDataBase + ".Vertex.Opt.png", "png");

#if y_optimize
    delete fitter;
#endif
}

void DoMinDp(TString SourceDataBase, TString DestDataBase, UInt_t MaxDataPerGroup = 200)
{
    // minimize with root

    assert(opt);
    assert(opt->fCurrentMatrixElems);

    cout << "Optimizing for dp\n";
    opt->fCurrentMatrixElems = &(opt->fDMatrixElems);

    opt->LoadDataBase(SourceDataBase);
    NPara = opt->Matrix2Array(OldMatrixArray, freepara);
    opt->LoadRawData(DataSource, (UInt_t) - 1, MaxDataPerGroup);
    opt->PrepareSieve(); // used for calculate the Realth and Realph. Those two will be used for calculated the Real Dp in the Dp Optimization
    opt->PrepareDp();

    //compensate bias due to dp event selections
    // 	opt->fArbitaryDpKinShift[0] = 2.786177e-05;
    // 	opt->fArbitaryDpKinShift[1] = 8.168538e-05;
    // 	opt->fArbitaryDpKinShift[2] = 5.299596e-05;
    // 	opt->fArbitaryDpKinShift[3] = 3.175602e-05;
    // 	opt->fArbitaryDpKinShift[4] = 9.519830e-05;

    opt->fArbitaryDpKinShift[0] = 0.;
    opt->fArbitaryDpKinShift[1] = 0.;
    opt->fArbitaryDpKinShift[2] = 0.;
    opt->fArbitaryDpKinShift[3] = 0.;

//    opt->fArbitaryDpKinShift[0] = 2.649891e-05;
//    opt->fArbitaryDpKinShift[1] = -1.457213e-04;
//    opt->fArbitaryDpKinShift[2] = 2.037271e-04;
//    opt->fArbitaryDpKinShift[3] = -1.493965e-04;

    opt->Print();


#if dp_optimize

    TVirtualFitter::SetDefaultFitter("Minuit"); //default is Minuit
    TVirtualFitter *fitter = TVirtualFitter::Fitter(NULL, NPara);

    fitter->SetFCN(myfcn);

    for (UInt_t i = 0; i < NPara; i++) {
        Double_t absold = TMath::Abs(OldMatrixArray[i]);
        Double_t abslimit = absold > 0 ? absold * 10000 : 10000;

        fitter->SetParameter(i, Form("TMatrix%03d", i), OldMatrixArray[i], absold > 0 ? absold / 10 : 0.1, -abslimit, abslimit);
        // fitter->SetParameter(1,"asdf",0,0,0,0);

        if (!freepara[i]) fitter->FixParameter(i);
    }

   fitter->Print();
    cout << fitter->GetNumberFreeParameters() << " Free  / " << fitter->GetNumberTotalParameters() << " Parameters\n";

    assert(opt->fNRawData > 0);
    assert(NPara > 0);
    assert(fitter->GetNumberFreeParameters() > 0);
    assert(fitter->GetNumberTotalParameters() == NPara);

    Double_t arglist[2] = {1000,0.01};
    fitter->ExecuteCommand("MIGRAD", arglist, 2);
#endif         

    opt->Print();
    opt->SaveDataBase(DestDataBase);
    opt->SaveNewDataBase(Form("%s",DestDataBase.Data()));
    opt->SumSquareDp();
//    opt->CheckDp();
//    opt->CheckDpGlobal();
//    TCanvas * c1 = opt->CheckDp();
//    TCanvas * c1 = opt->CheckDp_test();
    TCanvas * c2 = opt->CheckDp_test2();
//    c1->Print(DestDataBase + ".Dp.Opt.png", "png");
#if dp_optimze
    delete fitter;
#endif

}

void PlotDataBase(TString DatabaseFileName, UInt_t MaxDataPerGroup = 1000)
{
    opt = new ROpticsOpt();

    assert(opt);

    gStyle->SetOptStat(0);

    opt->LoadDataBase(DatabaseFileName);
    opt->Print();

    opt->LoadRawData(DataSource, (UInt_t) - 1, MaxDataPerGroup);

    opt->PrepareSieve();
    //opt->PrepareDp();

    //opt->SumSquareDTh(kTRUE);
    //opt->SumSquareDPhi(kTRUE);
    //opt->SumSquareDp(kTRUE);

    TCanvas * c1 = opt->CheckSieve();
    c1->Print(DatabaseFileName + ".Sieve.png", "png");
 

   //TCanvas * c1 = opt->CheckDpGlobal();
    //c1->Print(DatabaseFileName + ".Dp.png","png");

    delete opt;
}

void ROpticsOptScript(TString select, TString SourceDataBase, TString DestDataBase="")
{
    opt = new ROpticsOpt();

    Int_t s = 0;
    if (select == "theta") s = 1;
    if (select == "phi") s = 2;
    if (select == "y") s = 3;
    if (select == "delta") s = 4;

    TString autoDestDatabase;
    if(DestDataBase==""){
    	DestDataBase= SourceDataBase + "." + select;
    }

    // debug infor, debug infor

    gStyle->SetOptStat(0);

    switch (s) {
    case 1:
        cout << "Optimizing for Theta\n";
        myfcn = myfcn1;
        opt->fCurrentMatrixElems = &(opt->fTMatrixElems);
        DoMinTP(SourceDataBase, DestDataBase, 500);
        break;
    case 2:
        cout << "Optimizing for Phi\n";
        myfcn = myfcn2;
        opt->fCurrentMatrixElems = &(opt->fPMatrixElems);
        DoMinTP(SourceDataBase, DestDataBase, 500);
        break;
    case 3:
        cout << "Optimizing for Y\n";
        myfcn = myfcn3;
        opt->fCurrentMatrixElems = &(opt->fYMatrixElems);
        DoMinY(SourceDataBase, DestDataBase, 200000);
        break;
    case 4:
        cout << "Optimizing for Delta\n";
        myfcn = myfcn4;
        opt->fCurrentMatrixElems = &(opt->fDMatrixElems);
        DoMinDp(SourceDataBase, DestDataBase, 200000);
        break;
    default:
        break;
    }

    gSystem->Exec(Form("cp -vf %s %s.source", SourceDataBase.Data(), DestDataBase.Data()));
    //    gSystem->Exec(Form("cp -vf log %s.log", DestDataBase.Data()));

    delete opt;

    return;
}
