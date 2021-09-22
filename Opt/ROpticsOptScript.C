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
#include "ROpticsOpt.h"

#define th_ph_optimize true
#define y_optimize true
#define dp_optimize true


//#include "SaveCanvas.C"

using namespace std;

class ROpticsOpt;

ROpticsOpt * opt;
UInt_t NPara = 0;
Double_t OldMatrixArray[1000] = {-99}; //NPara
Bool_t freepara[10000] = {kFALSE}; //NPara

UInt_t MaxDataPerGroup = 100;


//TString DataSource =   "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/RHRS_data/Sieve.Full.thetaphi.f51";
TString DataSource =   "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptData/CRex_RHRS/averageVersion/average/sieve.average.f51";


// theta phi Y data set Sieve.test.average.thetaphi.f51
TString thetaPhiOptSource= "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptData_2021/PRex_RHRS/OptData/thetaphi/Sieve.average.f51";
TString thetaPhiTestSource="/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptData_2021/PRex_RHRS/OptData/largeDataSet/Sieve.Full_LargeDataSet.f51";

// Dp optimization dataset
TString DpOptSource="";
TString DpTestSource="";

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

inline std::string getFilePath(const std::string & s){
    char sep = '/';
#ifdef _WIN32
    sep = '\\';
#endif
    size_t i = s.rfind(sep, s.length());
    if(i != std::string::npos){
        return(s.substr(0, i+1));
    }
    return("");
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

    std::cout<<"Run summary"<<std::endl;
    std::cout<<"\t dataset::"<<DataSource.Data()<<std::endl;
#if th_ph_optimize
    delete fitter;
#endif    
}

// new function used for pass the
void AutoDoMinTP(TString SourceDataBase, TString DestDataBase, UInt_t MaxDataPerGroup = 200, Bool_t doFit=true)
{
    // load the test data set and load the test data set seperately
    if (doFit){
        // load the Optimization database
        if(!thetaPhiOptSource.IsNull()){
            DataSource = thetaPhiOptSource;
        }
    }else{
        // load the test database
        if(!thetaPhiTestSource.IsNull()){
            DataSource = thetaPhiTestSource;
        }
    }

    //minimize with root
    assert(opt);
    assert(opt->fCurrentMatrixElems);

    opt->LoadDataBase(SourceDataBase);
    NPara = opt->Matrix2Array(OldMatrixArray, freepara);
    opt->LoadRawData(DataSource, (UInt_t) - 1, MaxDataPerGroup);
    opt->PrepareSieve();
    opt->Print();


    if (doFit){
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


        TString SourceDataBasePath=getFilePath(DestDataBase.Data());

        opt->Print();
        opt->SaveDataBase(DestDataBase);
        opt->SaveNewDataBase(Form("%s",DestDataBase.Data()));

        opt->SumSquareDTh();
        opt->SumSquareDPhi();

        TCanvas * c1 = opt->CheckSieve(-1,SourceDataBasePath.Data());
        c1->Print(DestDataBase+".Sieve.Opt.png", "png");
        c1->Print(DestDataBase+".Sieve.Opt.eps", "eps");
        std::cout<<"\t dataset::"<<DataSource.Data()<<std::endl;
        delete fitter;
    }else{
        TString SourceDataBasePath=getFilePath(DestDataBase.Data());
        opt->Print();
        opt->SaveDataBase(DestDataBase);
        opt->SaveNewDataBase(Form("%s",DestDataBase.Data()));
        opt->SumSquareDTh();
        opt->SumSquareDPhi();

        TCanvas * c1;
        //= opt->CheckSieve(-1,SourceDataBasePath.Data());
        if(doFit){
            c1 = opt->CheckSieve(-1,SourceDataBasePath.Data());
        }else{
            TString savefolder=Form("%s/%s",SourceDataBasePath.Data(),basename(DataSource.Data()));
            mkdir(savefolder.Data(),0777);
            c1 = opt->CheckSieve(-1,savefolder.Data());
        }
        c1->Print(DestDataBase+".Sieve.Opt.png", "png");
        c1->Print(DestDataBase+".Sieve.Opt.eps", "eps");
        std::cout<<"\t dataset::"<<DataSource.Data()<<std::endl;
    }
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

    opt->fArbitaryDpKinShift[0] = 0.;//-0.5*1.86177e-05;//;/5.86177e-05;
    opt->fArbitaryDpKinShift[1] = 0.;
    opt->fArbitaryDpKinShift[2] = 0.;
    opt->fArbitaryDpKinShift[3] = 0.;
    opt->fArbitaryDpKinShift[4] = 0.;

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
    TCanvas * c1 = opt->CheckDp_test2();
//    c1->Print(DestDataBase + ".Dp.Opt.png", "png");
    c1->Draw();
#if dp_optimze
    delete fitter;
#endif

}

void AutoDoMinDp(TString SourceDataBase, TString DestDataBase="", UInt_t MaxDataPerGroup = 200, Bool_t doOptmization=true)
{
	// extract the base name of the string
	if (doOptmization){
		//DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/Sieve.Full.Mom.f51_reform";
		//DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/RHRS_data/Sieve.Full.Mom.f51";
		//DataSource = "/home/newdriver/Storage/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/RHRS_large_diff_events/Sieve.Full.Mom.f51";
//		DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/RHRS_GroundOnly/SameEvt/Sieve.Full.Mom.f51_reform";
//		DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/RHRS_mean/Sieve.Full.Mom.f51";
		DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptData/CRex_RHRS/averageVersion/average/sieve.average.f51";
	}else{
//		DataSource="/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/LargeDataSetEndQuanter/Sieve.full.LargetDataset.Top.0.75.f51";
//		DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/LargeDataseTopQauter/Sieve.full.LargetDataset.Top.0.25.f51";
		    DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/RHRS_data/Sieve.full.largeDataset.f51";
//		    DataSource = "/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/asciReform/SieveReform/Sieve.full.largeDataset.f51_reform";
	}

	TString SourceDataBasePath=getFilePath(DestDataBase.Data());
	if (DestDataBase.IsNull()){
		DestDataBase=Form("%s_resultDelta",SourceDataBase.Data());
	}

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

    opt->fArbitaryDpKinShift[0] = 0.;
    opt->fArbitaryDpKinShift[1] = 0.;
    opt->fArbitaryDpKinShift[2] = 0.;
    opt->fArbitaryDpKinShift[3] = 0.;
    opt->Print();


if (doOptmization){
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
    Double_t arglist[2] = {1000,0.001};
    fitter->ExecuteCommand("MIGRAD", arglist, 2);
}

    opt->Print();
    opt->SaveDataBase(DestDataBase);
    opt->SaveNewDataBase(Form("%s",DestDataBase.Data()));
    opt->SumSquareDp();      // recalculate the matrix project parameter

	if (doOptmization) {
		TCanvas *c2 = opt->CheckDp_test2(SourceDataBasePath.Data());
//    delete fitter;
	} else {
		TCanvas *c1 = opt->CheckDp_test(SourceDataBasePath.Data());
	}

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

void ROpticsOptScript(TString select, TString SourceDataBase, TString DestDataBase)
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


//void ROpticsOptScript(Bool_t doFit,TString select, TString SourceDataBase, TString DestDataBase)
//{
//    opt = new ROpticsOpt();
//
//    Int_t s = 0;
//    if (select == "theta") s = 1;
//    if (select == "phi") s = 2;
//    if (select == "y") s = 3;
//    if (select == "delta") s = 4;
//
//    TString autoDestDatabase;
//    if(DestDataBase==""){
//    	DestDataBase= SourceDataBase + "." + select;
//    }
//
//    // debug infor, debug infor
//
//    gStyle->SetOptStat(0);
//
//    switch (s) {
//    case 1:
//        cout << "Optimizing for Theta\n";
//        myfcn = myfcn1;
//        opt->fCurrentMatrixElems = &(opt->fTMatrixElems);
//        DoMinTP(SourceDataBase, DestDataBase, 500);
//        break;
//    case 2:
//        cout << "Optimizing for Phi\n";
//        myfcn = myfcn2;
//        opt->fCurrentMatrixElems = &(opt->fPMatrixElems);
//        DoMinTP(SourceDataBase, DestDataBase, 500);
//        break;
//    case 3:
//        cout << "Optimizing for Y\n";
//        myfcn = myfcn3;
//        opt->fCurrentMatrixElems = &(opt->fYMatrixElems);
//        DoMinY(SourceDataBase, DestDataBase, 200000);
//        break;
//    case 4:
//        cout << "Optimizing for Delta\n";
//        myfcn = myfcn4;
//        opt->fCurrentMatrixElems = &(opt->fDMatrixElems);
//        AutoDoMinDp(SourceDataBase, DestDataBase, 200000,doFit);
//        break;
//    default:
//        break;
//    }
//    //gSystem->Exec(Form("cp -vf %s %s.source", SourceDataBase.Data(), DestDataBase.Data()));
//    //    gSystem->Exec(Form("cp -vf log %s.log", DestDataBase.Data()));
//    delete opt;
//    return;
//
//}


//_____________________________________________________________________________________________
// new function
//_____________________________________________________________________________________________
void ROpticsOptScript(Bool_t doFit,TString select, TString SourceDataBase, TString DestDataBase)
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
//        DoMinTP(SourceDataBase, DestDataBase, 500);
            AutoDoMinTP(SourceDataBase, DestDataBase, 500,doFit);
            break;
        case 2:
        {
            cout << "Optimizing for Phi\n";
            myfcn = myfcn2;
            opt->fCurrentMatrixElems = &(opt->fPMatrixElems);
            if (doFit){
                AutoDoMinTP(SourceDataBase, DestDataBase, 500,doFit);
            } else{
                std::map<UInt_t,TString> thetaPhiTestList;
                UInt_t runDp0List[]={21363,21364,21365,21366,21368,21369,21370,21380,21381};//
                for(int i =0; i < (sizeof(runDp0List)/sizeof(UInt_t)); i ++){
                    TString testfilename=Form("/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptData_2021/PRex_RHRS/OptData/largeDataSet/Sieve._%d_p4.f51_reform",runDp0List[i]);
                    if (!gSystem->AccessPathName(testfilename.Data()))
                    {
                        thetaPhiTestSource=testfilename.Data();
                        AutoDoMinTP(SourceDataBase, DestDataBase, 500,doFit);
                        std::cout<<thetaPhiTestSource.Data()<<std::endl;
                    }
                }
            }

            break;
        }
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
            AutoDoMinDp(SourceDataBase, DestDataBase, 200000,doFit);
            break;
        default:
            break;
    }
    //gSystem->Exec(Form("cp -vf %s %s.source", SourceDataBase.Data(), DestDataBase.Data()));
    //    gSystem->Exec(Form("cp -vf log %s.log", DestDataBase.Data()));
    delete opt;
    return;

}
