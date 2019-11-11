#include "InputR.h"
#include "SaveCanvas.C"

#include "TH1.h"
#include "TH2.h"
#include <TFile.h>
#include "TTree.h"
#include <TCut.h>
#include <TCutG.h>
#include "TSpectrum.h"
#include <TSystem.h>
#include "TApplication.h"
#include "iostream"
#include "TChain.h"
#include "TCanvas.h"
#include <string>
#include "TObjString.h"
#include <fstream>
#include <TLine.h>
#include <TIterator.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Work Directory
//////////////////////////////////////////////////////////////////////////////
//TString WorkDir = "/Users/tong/Tritium_analysis/optics/Sieve/";
TString WorkDir = "./Result/SieveCodeTest/";

//////////////////////////////////////////////////////////////////////////////
// Define Files
//////////////////////////////////////////////////////////////////////////////
TString RootDir = "/home/newdriver/Storage/Research/PRex_Experiment/prex_analyzer/optReplay/Result/OptFolder/";

// Dp & Sieve
TString RootFile_Dp_m4;
TString RootFile_Dp_m3;
TString RootFile_Dp_m2;
TString RootFile_Dp_m1 = "prexRHRS_20826_-1.root prexRHRS_20826_-1_1.root prexRHRS_20826_-1_2.root";
TString RootFile_Dp_0  = "prexRHRS_20827_-1.root prexRHRS_20827_-1_1.root prexRHRS_20827_-1_2.root prexRHRS_20827_-1_3.root";
TString RootFile_Dp_p1 = "prexRHRS_20825_-1.root prexRHRS_20825_-1_1.root prexRHRS_20825_-1_2.root prexRHRS_20825_-1_3.root prexRHRS_20825_-1_4.root prexRHRS_20825_-1_5.root";
TString RootFile_Dp_p2 = "prexRHRS_20801_-1.root ";
TString RootFile_Dp_p3;
TString RootFile_Dp_p4;

TString RootFile_Sieve = "prexRHRS_20798.root";

TString RootFile_Dp = RootFile_Dp_0;

//TString RootFile_Vertex = RootFile_Sieve;

TString SourceRootFile = RootFile_Dp;


//////////////////////////////////////////////////////////////////////////////
// Define Cuts
//////////////////////////////////////////////////////////////////////////////
Bool_t UseVertexCut = kFALSE;
//Bool_t UseDpCut = kTRUE;
Bool_t UseDpCut = kFALSE;
Bool_t UseHDpCut = kFALSE;

//select the centrol whole for the Dp optimization
Bool_t UseDp_SieveCut=kTRUE;

// Switch for Plot Cuts
// 0  : general cuts
// 1  : foil cuts
// 2  : dp cuts
// 3  : dp cuts + foil cuts

UInt_t PlotCut = 0;

//TCut GeneralSieveCut = "abs(R.gold.p-0.94737)<=0.0025"; //20826
//TCut GeneralSieveCut = "abs(R.gold.p-0.94743)<=0.0025"; //20825
//TCut GeneralSieveCut = "abs(R.gold.p-0.947295)<=0.0025"; //20827
TCut GeneralSieveCut = "abs(R.gold.p-0.95)<=0.011439";
TCut GeneralCut =GeneralSieveCut+ "R.tr.n==1 && R.vdc.u1.nclust==1&& R.vdc.v1.nclust==1 && R.vdc.u2.nclust==1 && R.vdc.v2.nclust==1 && R.gold.dp<1 && R.gold.dp > -0.1 && fEvtHdr.fEvtType==1";

//////////////////////////////////////////////////////////////////////////////
// Settings
//////////////////////////////////////////////////////////////////////////////
Float_t xlowlimit = -0.14, xuplimit = 0.06;
Float_t ylowlimit = -0.06, yuplimit = 0.07;
Float_t fthlowlimit = -0.03, fthuplimit = 0.03;
Float_t fphlowlimit = -0.04, fphuplimit = 0.06;

Float_t dplowlimit = -0.1, dpuplimit = 0.1;
Float_t thlowlimit = -0.06, thuplimit = 0.05;
Float_t phlowlimit = -0.03, phuplimit = 0.02;
Float_t vzlowlimit = -0.12, vzuplimit = 0.12;

int nFoil = 1;

TString RootFileName;
TString CutSuf = ".FullCut.root";
TString CutDescFileSufVertex = ".VertexCut.cut";
TString CutDescFileSufDp = ".DpCut.cut";
TString CutDescFileSufSieve = ".SieveCut.%d_%d.cut";



TChain* LoadRootFiles();
//////////////////////////////////////////////////////////////////////////////
// Cut Tools
//////////////////////////////////////////////////////////////////////////////
/*
//////////////////////////////////////////////////////////////////////////////
// Cut Vertex, Used for multi-target foil case. Not used in PRex
/////////////////////////////////////////////////////////////////////////////
void CutVertex(int overwrite = 0) {

    TChain *T = LoadRootFiles();

    TString CutFileName = WorkDir + RootFileName + CutSuf;
    TString CutDescName = WorkDir + RootFileName + CutDescFileSufVertex;

    cerr << "cp -vf " + CutFileName + " " + CutFileName + ".old" << endl;
    gSystem->Exec("cp -vf " + CutFileName + " " + CutFileName + ".old");

    fstream cutdesc(CutDescName, ios_base::out);
    assert(cutdesc.is_open());

    TFile *f1 = new TFile(CutFileName, "UPDATE");
    assert(f1);

    // Define Canvas
    TCanvas* c3 = new TCanvas("c3", "ReactZ Cuts", 900, 900);
    TH2F* h3 = new TH2F("h3", "Tg_Z vs. Tg ph", 400, phlowlimit, phuplimit, 400, vzlowlimit, vzuplimit);
    //    TH2F* h3 = new TH2F("h3", "Tg_ph vs. R.tr.vz",  400, vzlowlimit, vzuplimit, 400, phlowlimit, phuplimit);
    assert(h3);

    // Choose the foil you want to make cut
    for (int FoilID = 0; FoilID < nFoil; FoilID++) {
        TCut DrawCut = GeneralCut;

	T->Draw("R.tr.vz:R.tr.tg_ph>>h3", DrawCut, "COLZ");
	//	T->Draw("R.tr.tg_ph:R.tr.vz>>h3", DrawCut, "COLZ");
	c3->Update();
        
        cout << "Testing " << Form("fcut_R_%d", FoilID) << endl;
        TCutG* cutg = (TCutG*)gROOT->FindObject(Form("fcut_R_%d", FoilID)); //looking for old cut definition
        
        if(!cutg || overwrite){
            cout << "Making cut " << Form("fcut_R_%d", FoilID) << endl;

            cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG
            c3->Update();
	    
            cutg->SetName(Form("fcut_R_%d", FoilID)); //
	    cutg->SetVarX("R.tr.tg_ph");
	    cutg->SetVarY("R.tr.vz");
	    //	    cutg->SetVarY("R.tr.tg_ph");
	    //           cutg->SetVarX("R.tr.vz");

            cout << "done!" << endl;
        }
        else{
            cout << Form("fcut_R_%d", FoilID) << " is found, using old one" << endl;
	    }

        cutg->SetLineColor(kMagenta);
        cutg->SetLineWidth(2);
        cutg->Draw("PL");
        c3->Update();

        // output cut to disk
        cutg->Write("", TObject::kOverwrite); // Overwrite old cut

        cout << "Log to " << CutDescName << endl;

        cutdesc << Form("fcut_R_%d", FoilID) << " && " << (const char*)GeneralCut << endl;

        SaveCanvas(c3, WorkDir + RootFileName + Form(".fcut_R_%d", FoilID), kFALSE);
    }

    f1->Write();
    f1->ls();
    cutdesc.close();
}
/////////////////////////////////////////////////////////////////////////////
void CutVertex_Dp(int overwrite = 0) {


    TChain *T = LoadRootFiles();

    TString CutFileName = WorkDir + RootFileName + CutSuf;
    TString CutDescName = WorkDir + RootFileName + CutDescFileSufVertex;

    cerr << "cp -vf " + CutFileName + " " + CutFileName + ".old" << endl;
    gSystem->Exec("cp -vf " + CutFileName + " " + CutFileName + ".old");

    fstream cutdesc(CutDescName, ios_base::out);
    assert(cutdesc.is_open());

    TFile *f1 = new TFile(CutFileName, "UPDATE");
    assert(f1);

    // Define Canvas
    TCanvas* c3 = new TCanvas("c3", "ReactZ Cuts", 900, 900);
    TH2F* h3 = new TH2F("h3", "Tg_Z vs. Tg ph", 400, phlowlimit, phuplimit, 400, vzlowlimit, vzuplimit);
    //    TH1F *h3 = new TH1F("h3","Tg_Z",400,vzlowlimit,vzuplimit);
    assert(h3);

    // Choose the foil you want to make cut
    for (int FoilID = 0; FoilID < nFoil; FoilID++) {
        TCut DrawCut = GeneralCut;

	T->Draw("R.tr.vz:R.tr.tg_ph>>h3", DrawCut, "COLZ");
	//	T->Draw("R.tr.vz>>h3", DrawCut, "COLZ");
	c3->Update();
        
        cout << "Testing " << Form("fcut_R_%d", FoilID) << endl;
        TCutG* cutg = (TCutG*)gROOT->FindObject(Form("fcut_R_%d", FoilID)); //looking for old cut definition
        
        if(!cutg || overwrite){
            cout << "Making cut " << Form("fcut_R_%d", FoilID) << endl;

            cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG
            c3->Update();
	    
            cutg->SetName(Form("fcut_R_%d", FoilID)); //
	    cutg->SetVarX("R.tr.tg_ph");
	    cutg->SetVarY("R.tr.vz");

            cout << "done!" << endl;
        }
        else{
            cout << Form("fcut_R_%d", FoilID) << " is found, using old one" << endl;
	    }

        cutg->SetLineColor(kMagenta);
        cutg->SetLineWidth(2);
        cutg->Draw("PL");
        c3->Update();

        // output cut to disk
        cutg->Write("", TObject::kOverwrite); // Overwrite old cut

        cout << "Log to " << CutDescName << endl;

        cutdesc << Form("fcut_R_%d", FoilID) << " && " << (const char*)GeneralCut << endl;

        SaveCanvas(c3, WorkDir + RootFileName + Form(".fcut_R_%d", FoilID), kFALSE);
    }

    f1->Write();
    f1->ls();
    cutdesc.close();
}
*/


///////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
void CutDp(int overwrite = 0)
{
    TChain *T = LoadRootFiles();

    TString CutFileName = WorkDir + RootFileName + CutSuf;
    TString CutDescName = WorkDir + RootFileName + CutDescFileSufDp;

    cerr << "cp -vf " + CutFileName + " " + CutFileName + ".old" << endl;
    gSystem->Exec("cp -vf " + CutFileName + " " + CutFileName + ".old");

    fstream cutdesc(CutDescName, ios_base::out);
    assert(cutdesc.is_open());

    TFile *f1 = new TFile(CutFileName, "UPDATE");
    assert(f1);

    TCanvas *c4 = new TCanvas("c4","dp Cuts",900,900);
    TH2F *h4 = new TH2F("h4", "Tg th vs. Tg dp", 400, -0.05, 0.05, 400, -0.1,0.1);
    //TH2F *h4 = new TH2F("h4", "Tg th vs. Tg dp", 400, dplowlimit, dpuplimit, 400, thlowlimit, thuplimit);
    assert(h4);

    for(int FoilID = 0; FoilID < nFoil; FoilID++){
        TCut DrawCut = GeneralCut;
        if(UseVertexCut){
            DrawCut = TCut(Form("fcut_R_%d", FoilID));
            (TCutG*)gROOT->FindObject(Form("fcut_R_%d", FoilID));
        }
        
	T->Draw("R.tr.tg_th:R.tr.tg_dp>>h4", DrawCut, "COLZ");
        c4->Update();

        cout << "Testing " << Form("dpcut_R_%d", FoilID) << endl;
        TCutG *cutg = (TCutG*)gROOT->FindObject(Form("dpcut_R_%d", FoilID));

        if(!cutg || overwrite){
            cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG
            c4->Update();

            cutg->SetName(Form("dpcut_R_%d", FoilID));
            // set axises' name
            cutg->SetVarX("R.tr.tg_dp");
            cutg->SetVarY("R.tr.tg_th");
            cout << "done!" << endl;
        }
        else {
            cout << Form("dpcut_R_%d", FoilID) << " is found, using old one" << endl;
        }

        cutg->SetLineColor(kMagenta);
        cutg->SetLineWidth(2);
        cutg->Draw("PL");
        c4->Update();

        cutg->Write("",TObject::kOverwrite); // Overwrite old cut

        cout << "Log to " << CutDescName << endl;

        if(UseVertexCut){
            cutdesc << Form("fcut_R_%d", FoilID) << " && ";
        }
        cutdesc << Form("dpcut_R_%d", FoilID) << " && " << (const char*)GeneralCut << endl;

        SaveCanvas(c4, WorkDir + RootFileName + Form(".dpcut_R_%d", FoilID), kFALSE);
    }

    f1->Write();
    f1->ls();
    cutdesc.close();
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
void CutDp_Sieve(int FoilID = 0, int col = 6, int overwrite = 0) {

    TChain *T = LoadRootFiles();

    TString CutFileName = WorkDir + RootFileName + CutSuf;
    TString TempString(Form(CutDescFileSufSieve.Data(), FoilID, col));
    TString PlotDir(RootFileName + Form(".hcut_R_%d_%d/", FoilID, col));
    TString CutDescName = WorkDir + RootFileName + TempString;

    cerr << "cp -vf " + CutFileName + " " + CutFileName + ".old" << endl;
    gSystem->Exec("cp -vf " + CutFileName + " " + CutFileName + ".old");
    gSystem->Exec("mkdir -vp " + WorkDir + PlotDir);

    fstream cutdesc(CutDescName, ios_base::out);
    assert(cutdesc.is_open());

    TFile *f1 = new TFile(CutFileName, "UPDATE");
    assert(f1);

    TCanvas *c5 = new TCanvas("c5","PlotSieve",900,900);
    TH2F *h5 = new TH2F("h5", "Tg th vs. Tg ph", 1000, -0.04, 0.02, 1000, -0.06, 0.04);
    assert(h5);

//    TCut DrawCut = GeneralCut;
    TCut DrawCut = GeneralSieveCut;

/*
    if(UseVertexCut){
        DrawCut = DrawCut + TCut(Form("fcut_R_%d", FoilID));
        (TCutG*)gROOT->FindObject(Form("fcut_R_%d", FoilID));
    }
    if(UseDpCut){
        DrawCut = DrawCut + TCut(Form("dpcut_R_%d", FoilID));
        (TCutG*)gROOT->FindObject(Form("dpcut_R_%d", FoilID));
    }
*/

    T->Draw("R.tr.tg_th:R.tr.tg_ph>>h5", DrawCut, "COLZ");
    gPad->SetGrid();
    c5->Update();

    int nhol = 0;
    cout << "How many holes in this No." << col << " column?" << endl;
    cin >> nhol;
    if(nhol < 0)return;
    cout << "min hole id : ";
    int rmin = -1;
    cin >> rmin;
    if(rmin < 0)return;


    for(int i = 0; i < rmin; i++)

    	cutdesc << "fEvtHdr.fRun==0" << endl;
    //make cuts for each holes from begin number
    for(int row = rmin; row < rmin + nhol; row++){
        cout << "Testing " << Form("DpSievecut_R_%d_%d_%d", FoilID, col, row) << endl;
	TCutG* cutg = (TCutG*)gROOT->FindObject(Form("DpSievecut_R_%d_%d_%d", FoilID, col, row));

        if(!cutg || overwrite){
            if(cutg)cutg->Delete();

	    cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG

            c5->Update();

            cutg->SetName(Form("DpSievecut_R_%d_%d_%d", FoilID, col, row));
            // set axises' name
            cutg->SetVarX("R.tr.tg_ph");
            cutg->SetVarY("R.tr.tg_th");
            cout << "done!" << endl;
        }
        else {
            cout << Form("DpSievecut_R_%d_%d_%d", FoilID, col, row) << " is found, using old one" << endl;
        }

        cutg->SetLineColor(kMagenta);
        cutg->SetLineWidth(2);
        cutg->Draw("PL");
        c5->Update();

        cutg->Write("", TObject::kOverwrite); // Overwrite old cut


        cout << "Log to " << CutDescName << endl;

        cutdesc << Form("DpSievecut_R_%d_%d_%d", FoilID, col, row) << " && ";

        cutdesc << (const char*)GeneralCut << endl;
    }

    //    for(int i = rmin + nhol; i < 7; i++)
    for(int i = rmin + nhol; i < NSieveRow; i++)
        cutdesc << "fEvtHdr.fRun==0" << endl;

    gSystem->Exec("rm -f " + WorkDir + PlotDir + RootFileName + Form(".hcut_R_%d_%d_*", FoilID, col) + ".*");
    SaveCanvas(c5, WorkDir + PlotDir + RootFileName + Form(".hcut_R_%d_%d_%d", FoilID, col, nhol), kFALSE);

    f1->Write();
    f1->ls();
    cutdesc.close();
}


//////////////////////////////////////////////////////////////////////////////
// Phi-Dp
//////////////////////////////////////////////////////////////////////////////
void CutDp_Dp(int overwrite = 0)
{
    TChain *T = LoadRootFiles();

    TString CutFileName = WorkDir + RootFileName + CutSuf;
    TString CutDescName = WorkDir + RootFileName + CutDescFileSufDp;

    cerr << "cp -vf " + CutFileName + " " + CutFileName + ".old" << endl;
    gSystem->Exec("cp -vf " + CutFileName + " " + CutFileName + ".old");

    fstream cutdesc(CutDescName, ios_base::out);
    assert(cutdesc.is_open());

    TFile *f1 = new TFile(CutFileName, "UPDATE");
    assert(f1);

    TCanvas *c4 = new TCanvas("c4","dp Cuts",900,900);
    //TH2F *h4 = new TH2F("h4", "Tg ph vs. Tg dp", 400, dplowlimit, dpuplimit, 400, phlowlimit, phuplimit);
    TH2F *h4 = new TH2F("h4", "Tg ph vs. Tg dp", 400, -0.04, 0.04, 400, phlowlimit, phuplimit);

    assert(h4);

    for(int FoilID = 0; FoilID < nFoil; FoilID++){
        TCut DrawCut = GeneralCut;
        if(UseVertexCut){
            DrawCut = TCut(Form("fcut_R_%d", FoilID));
            (TCutG*)gROOT->FindObject(Form("fcut_R_%d", FoilID));
        }
        // cut on Sieve, select the centrol hole
        if(UseDp_SieveCut){
            DrawCut = TCut(Form("DpSievecut_R_%d_6_1", FoilID));
            (TCutG*)gROOT->FindObject(Form("DpSievecut_R_%d_6_1", FoilID));

        }
        

	T->Draw("R.tr.tg_ph:R.tr.tg_dp>>h4", DrawCut, "COLZ");
    c4->Update();

        cout << "Testing " << Form("dpcut_R_%d", FoilID) << endl;
        TCutG *cutg = (TCutG*)gROOT->FindObject(Form("dpcut_R_%d", FoilID));

        if(!cutg || overwrite){
            cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG
            c4->Update();

            cutg->SetName(Form("dpcut_R_%d", FoilID));
            // set axises' name
            cutg->SetVarX("R.tr.tg_dp");
            cutg->SetVarY("R.tr.tg_ph");
            cout << "done!" << endl;
        }
        else {
            cout << Form("dpcut_R_%d", FoilID) << " is found, using old one" << endl;
        }

        cutg->SetLineColor(kMagenta);
        cutg->SetLineWidth(2);
        cutg->Draw("PL");
        c4->Update();

        cutg->Write("",TObject::kOverwrite); // Overwrite old cut

        cout << "Log to " << CutDescName << endl;

        if(UseVertexCut){
            cutdesc << Form("fcut_R_%d", FoilID) << " && ";
        }
        cutdesc << Form("dpcut_R_%d", FoilID) << " && " << (const char*)GeneralCut << endl;

        SaveCanvas(c4, WorkDir + RootFileName + Form(".dpcut_R_%d", FoilID), kFALSE);

    }

    f1->Write();
    f1->ls();
    cutdesc.close();
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
void CutSieve(int FoilID = 0, int col = 6, int overwrite = 0) {

    TChain *T = LoadRootFiles();

    TString CutFileName = WorkDir + RootFileName + CutSuf;
    TString TempString(Form(CutDescFileSufSieve.Data(), FoilID, col));
    TString PlotDir(RootFileName + Form(".hcut_R_%d_%d/", FoilID, col));
    TString CutDescName = WorkDir + RootFileName + TempString;

    cerr << "cp -vf " + CutFileName + " " + CutFileName + ".old" << endl;
    gSystem->Exec("cp -vf " + CutFileName + " " + CutFileName + ".old");
    gSystem->Exec("mkdir -vp " + WorkDir + PlotDir);

    fstream cutdesc(CutDescName, ios_base::out);
    assert(cutdesc.is_open());
    
    TFile *f1 = new TFile(CutFileName, "UPDATE");
    assert(f1);
    
    TCanvas *c5 = new TCanvas("c5","PlotSieve",900,900);
    TH2F *h5 = new TH2F("h5", "Tg th vs. Tg ph", 1000, phlowlimit, phuplimit, 1000, thlowlimit, thuplimit);
    assert(h5);

//    TCut DrawCut = GeneralCut;
    TCut DrawCut = GeneralSieveCut;

    if(UseVertexCut){
        DrawCut = DrawCut + TCut(Form("fcut_R_%d", FoilID));
        (TCutG*)gROOT->FindObject(Form("fcut_R_%d", FoilID));
    }
    if(UseDpCut){
        DrawCut = DrawCut + TCut(Form("dpcut_R_%d", FoilID));
        (TCutG*)gROOT->FindObject(Form("dpcut_R_%d", FoilID));
    }

    T->Draw("R.tr.tg_th:R.tr.tg_ph>>h5", DrawCut, "COLZ");
    gPad->SetGrid();
    c5->Update();

    //c5->Modified();
    //    TCanvas *cth = new TCanvas("cth","cth");
    //    T->Draw("L.tr.tg_th>>hth", DrawCut);
    //    TCanvas *cph = new TCanvas("cph","cph");
    //    T->Draw("L.tr.tg_ph>>hph", DrawCut);

    int nhol = 0;
    cout << "How many holes in this No." << col << " column?" << endl;
    cin >> nhol;
    if(nhol < 0)return;
    cout << "min hole id : ";
    int rmin = -1;    
    cin >> rmin;
    if(rmin < 0)return;

//    Double_t ph_peak[7]={.0, 2.e-2, 1.e-2, -0.03e-2, -1.07e-2, -2.08e-2};
//    Double_t th_peak[7]={.0, -4.01e-2, -1.93e-2, 0.3e-2, 2.52e-2, 4.55e-2};
//    Double_t ph_width = 1.1*0.003;
//    Double_t th_width = 1.3*0.005;

    for(int i = 0; i < rmin; i++)
        cutdesc << "fEvtHdr.fRun==0" << endl;
    //make cuts for each holes from begin number
    for(int row = rmin; row < rmin + nhol; row++){
        cout << "Testing " << Form("hcut_R_%d_%d_%d", FoilID, col, row) << endl;
	TCutG* cutg = (TCutG*)gROOT->FindObject(Form("hcut_R_%d_%d_%d", FoilID, col, row));

        if(!cutg || overwrite){
            if(cutg)cutg->Delete();
 
	    cutg = (TCutG*)(TVirtualPad::Pad()->WaitPrimitive("CUTG", "CutG")); // making cut, store to CUTG

	    
	    //cutg = new TCutG("cutg",4);
	    //cutg->SetVarX("x");
	    //cutg->SetVarY("y");
	   
	    //cutg->SetPoint(0,ph_peak[col]-ph_width+0.001*(row-3)/2.,th_peak[row]-th_width);
	    //cutg->SetPoint(1,ph_peak[col]+ph_width+0.001*(row-3)/2,th_peak[row]-th_width);
	    //cutg->SetPoint(2,ph_peak[col]+ph_width+0.001*(row-3)/2,th_peak[row]+th_width);
	    //cutg->SetPoint(3,ph_peak[col]-ph_width+0.001*(row-3)/2,th_peak[row]+th_width);
	    //cutg->SetPoint(4,ph_peak[col]-ph_width+0.001*(row-3)/2,th_peak[row]-th_width);

            c5->Update();

            cutg->SetName(Form("hcut_R_%d_%d_%d", FoilID, col, row));
            // set axises' name
            cutg->SetVarX("R.tr.tg_ph");
            cutg->SetVarY("R.tr.tg_th");
            cout << "done!" << endl;
        }
        else {
            cout << Form("hcut_R_%d_%d_%d", FoilID, col, row) << " is found, using old one" << endl;
        }

        cutg->SetLineColor(kMagenta);
        cutg->SetLineWidth(2);
        cutg->Draw("PL");
        c5->Update();

        cutg->Write("", TObject::kOverwrite); // Overwrite old cut

        if(UseHDpCut){
            TCanvas *c6 = new TCanvas("c6", Form("dp in col %d row %d", col+1, row+1), 800, 600);
            TH1F *h6 = new TH1F("h6", "dp", 200, dplowlimit, dpuplimit);
            assert(h6);

            c6->cd();

            TCut DpDrawCut = DrawCut + Form("hcut_R_%d_%d_%d", FoilID, col, row);
            (TCutG*)gROOT->FindObject(Form("hcut_R_%d_%d_%d", FoilID, col, row));
            T->Draw("R.tr.tg_dp>>h6", DpDrawCut);
            c6->Update();

            h6->Smooth(10);

            TSpectrum *s = new TSpectrum(5);
            Int_t nfound = s->Search(h6, 2, "", 0.10);
            c6->Update();

            double_t *xpeaks = s->GetPositionX();
            double_t *ypeaks = s->GetPositionY();

            cout << "Found " << nfound << " peaks in the dp plots:" << endl;
            for (int k=0; k<nfound; k++) {
                cout << k + 1 << "\t" << xpeaks[k] << "\t" << ypeaks[k] << endl;
            }
            cout << "Which peak is the C elastic peak?" << endl;

            Int_t npeak;
            cin >> npeak;

            if(npeak==0){
                cout << "No Data in this hole" << endl;
                cutdesc << "fEvtHdr.fRun==0" << endl;
                
                SaveCanvas(c6, WorkDir + PlotDir + RootFileName + Form(".hdpcut_R_%d_%d_%d", FoilID, col, row), kFALSE);
                c5->cd();

                continue;
            }
            else{
                cout << "Will use peak No " << npeak << " to generate cut file" << endl;

                Int_t idx;
                h6->GetBinWithContent(ypeaks[npeak-1],idx,0,400,ypeaks[npeak-1]*0.1);

                Double_t lowthr, hithr;
                for (Int_t k=idx; k<400; k++) {
                    if (h6->GetBinContent(k)<ypeaks[npeak-1]*0.5) {
                        hithr = h6->GetBinCenter(k);
                        break;
                    }
                }
                for (Int_t k=idx; k>0; k--) {
                    if (h6->GetBinContent(k)<ypeaks[npeak-1]*0.5) {
                        lowthr = h6->GetBinCenter(k);
                        break;
                    }
                }

                cout << lowthr << "<R.tr.tg_dp<" << hithr << endl;

                TLine *l1 = new TLine(lowthr,0,lowthr,h6->GetMaximum());
                TLine *l2 = new TLine(hithr,0,hithr,h6->GetMaximum());

                l1->SetLineStyle(1);
                l1->SetLineColor(2);
                l2->SetLineStyle(1);
                l2->SetLineColor(2);
                
                l1->Draw();
                l2->Draw();

                c6->Update();
                SaveCanvas(c6, WorkDir + PlotDir + RootFileName + Form(".hdpcut_R_%d_%d_%d", FoilID, col, row), kFALSE);

                c5->cd();

                cutdesc << Form("(R.tr.tg_dp>%7.5f && R.tr.tg_dp<%7.5f) && ", lowthr, hithr);
            }
        }
        
        cout << "Log to " << CutDescName << endl;

        cutdesc << Form("hcut_R_%d_%d_%d", FoilID, col, row) << " && ";
        if(UseVertexCut){
            cutdesc << Form("fcut_R_%d", FoilID) << " && ";
        }
        if(UseDpCut)
            cutdesc << Form("dpcut_R_%d", FoilID) << " && ";
        cutdesc << (const char*)GeneralCut << endl;
    }

    //    for(int i = rmin + nhol; i < 7; i++)
    for(int i = rmin + nhol; i < NSieveRow; i++)
        cutdesc << "fEvtHdr.fRun==0" << endl;
    
    gSystem->Exec("rm -f " + WorkDir + PlotDir + RootFileName + Form(".hcut_R_%d_%d_*", FoilID, col) + ".*");
    SaveCanvas(c5, WorkDir + PlotDir + RootFileName + Form(".hcut_R_%d_%d_%d", FoilID, col, nhol), kFALSE);

    f1->Write();
    f1->ls();
    cutdesc.close();
}

//////////////////////////////////////////////////////////////////////////////
TChain* LoadRootFiles()
{
    gStyle->SetOptStat("ne");

    // set the limite for the plot
    if(SourceRootFile == RootFile_Dp_m4){
        dplowlimit=-0.05;dpuplimit=-0.01;
    }
    if(SourceRootFile == RootFile_Dp_m3){
        dplowlimit=-0.04;dpuplimit=-0.025;
        xlowlimit=-0.14-0.40;xuplimit=0.06-0.40;
    }
    if(SourceRootFile == RootFile_Dp_m2){
        dplowlimit=-0.05;dpuplimit=0.01;
	//        xlowlimit=-0.14-0.24;xuplimit=0.06-0.24;
    }
    if(SourceRootFile == RootFile_Dp_m1){
        dplowlimit=-0.02;dpuplimit=-0.005;
        xlowlimit=-0.14-0.14;xuplimit=0.06-0.14;
    }
    if(SourceRootFile == RootFile_Dp_0){
        dplowlimit=-0.04;dpuplimit=0.03;
    }
    if(SourceRootFile == RootFile_Dp_p1){
        dplowlimit=0.00;dpuplimit=0.015;
        xlowlimit=-0.14+0.13;xuplimit=0.06+0.13;
    }
    if(SourceRootFile == RootFile_Dp_p2){
        dplowlimit=-0.02;dpuplimit=0.04;
	//        xlowlimit=-0.14+0.26;xuplimit=0.06+0.26;
    }
    if(SourceRootFile == RootFile_Dp_p3){
        dplowlimit=0.02;dpuplimit=0.035;
        xlowlimit=-0.14+0.38;xuplimit=0.06+0.38;
    }
    if(SourceRootFile == RootFile_Dp_p4){
        dplowlimit=0.0;dpuplimit=0.055;
    }

    char s[1024] ;
    strcpy(s,SourceRootFile.Data());
    const char *d = " ";
    char* sub;
    TList Files;

    sub=strtok(s,d);
    if(sub){
        RootFileName = TString(sub);
    }
    while(sub){
        Files.Add(new TObjString(sub));
        sub=strtok(NULL,d);
    }

    TIter next(&Files);
    TObjString* rootfile;
    TChain *T = new TChain("T");
    Int_t n=0;

    while((rootfile = (TObjString*)next())){
        T->Add(RootDir + rootfile->GetString());
        cout << "Open " <<rootfile->GetString() << endl;
    }

    return T;
}

//#include "plot_R.C"
