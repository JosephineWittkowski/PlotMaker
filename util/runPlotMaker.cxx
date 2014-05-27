#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <vector>

#include "TwoLeptonEWKPlotter/PlotMaker.h"

//set setInputFile, setInputFileSignal to correct paths

//regions: chose from list in PlotMakerDefs.h

//set variable to plot

//set binning

//activate all systematics. Attention: systematics for XS and GEN are added correlated (linearly). Systematics for fake are treated differently but added uncorrelated in the endl

//dataBlindCut: how should data be blinded?

//show_Data: set to false when looking into SignalRegion or if there is no cut on the variable but signal contamination is too high.

//convertToGeV: set to true except for jet1Pt, jet2Pt, jet3Pt and of course eta distributions

//set m_dbg, m_eventyield and m_table in PlotMaker.cxx
  
//in /cmt, make -f Makefile.RootCore; runPlotMaker


using namespace std;

void tokenizeString(string input, vector<string> &result);
void help();

/// \brief Main Function
int main(int argc, char** argv)
{
  // Read user inputs
  string channels     = "none"                               ; vector<string> channelList   ;
  string regions      = "SR_EE_1j"; vector<string> regionList    ;
  string variables    = "Ht"                              ; vector<string> variableList  ;
  string samples      = 
//   "ZV,WW,Top,Zjets,Higgs,Data"; 
// "SameSign,ChargeFlip,Data";
"SameSign,ChargeFlip,Higgs,Data";
  vector<string> sampleList    ;
  string fakesamples  = "Fakes"; vector<string> fakesampleList    ;
  string signal       = "130.0_0.0"			    ; vector<string> signalList;
  string binValues    = "1, 0, 400"                         ; vector<string> binValueList  ;
   string MCsystematics  = 
//    "IDDOWN";
  "EESZUP,EESZDOWN,EERUP,EERDOWN,EESLOWUP,EESLOWDOWN,EESMATUP,EESMATDOWN,EESPSUP,EESPSDOWN,IDUP,IDDOWN,JESUP,JESDOWN,MSUP,MSDOWN,SCALESTUP,SCALESTDOWN,JER,RESOST,syst_BJETUP,syst_BJETDOWN,syst_CJETUP,syst_CJETDOWN,syst_BKGMETHODUP,syst_BKGMETHODDOWN,syst_BMISTAGUP,syst_BMISTAGDOWN,syst_ETRIGREWUP,syst_ETRIGREWDOWN,syst_MTRIGREWUP,syst_MTRIGREWDOWN,syst_ESFUP,syst_ESFDOWN,syst_MEFFUP,syst_MEFFDOWN"; 
  vector<string> MCsystematicList;
  string MCsystematicsCorrBg = 
//   "";
  "syst_XSUP,syst_XSDOWN,syst_GENUP,syst_GENDOWN"; 
  vector<string> MCsystematicCorrBgList;
  
  string fakesystematics =   "ELREUP,ELREDOWN,MUREUP,MUREDOWN,ELFRUP,ELFRDOWN,MUFRUP,MUFRDOWN,ELFRACDOWN,ELFRACUP,MUFRACDOWN,MUFRACUP";
  vector<string> fakesystematicList;
  
  float dataBlindCut = -1.;
  string largerSmaller = "";
//   largerSmaller = " >= "; dataBlindCut = 90000.; //mlj
//     largerSmaller = " >= "; dataBlindCut = 120000.; // mljj

//     largerSmaller = " <= "; dataBlindCut = 200000.; // Ht
//     largerSmaller = " <= "; dataBlindCut = 220000.; // Ht MM 23 jets
//       largerSmaller = " <= "; dataBlindCut = 100000.; // mtmax
//         largerSmaller = " <= "; dataBlindCut = 110000.; // mtmax EM
//         largerSmaller = " <= "; dataBlindCut = 120000.; // mWWT = mtllmet
//         largerSmaller = " <= "; dataBlindCut = 30000.; // lept1Pt
//         largerSmaller = " <= "; dataBlindCut = 20000.; // lept2Pt
//         largerSmaller = " <= "; dataBlindCut = 30000.; // lept2Pt MM 23 jets
//           largerSmaller = " <= "; dataBlindCut = 30000.; // metRel
//             largerSmaller = " >= "; dataBlindCut = 0.; // showData everywhere
//             largerSmaller = " >= "; dataBlindCut = 1.5; // deltaEtaLl
  
  //
//   deltaEtaLl      L2METrel   lept1Eta  lept2Eta  jet1Pt  jet2Pt  jet3Pt 
  bool show_Data = false;
  bool   convertToGeV = true;
   

  for(int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--channels") == 0)
      channels     = argv[++i];
    else if (strcmp(argv[i], "--regions") == 0)
      regions      = argv[++i];
    else if (strcmp(argv[i], "--variables") == 0)
      variables    = argv[++i];
    else if (strcmp(argv[i], "--mcsystematics") == 0)
      MCsystematics  = argv[++i];
    else if (strcmp(argv[i], "--samples") == 0)
      samples      = argv[++i];
    else if (strcmp(argv[i], "--binValues") == 0)
      binValues    = argv[++i];
    else if (strcmp(argv[i], "--isGeV") == 0)
      convertToGeV = true;
    else {
      help();
      return 0; 
    }
  } // end of user inputs loop

  // Print
  cout << "=======================================================" << endl;
  cout << "Running PlotMaker w/ arguments:"                         << endl;
  cout << "=======================================================" << endl;
  cout << "Channels        = " << channels     << endl;
  cout << "Regions         = " << regions      << endl;
  cout << "Variables       = " << variables    << endl;
  cout << "MC Systematics     = " << MCsystematics  << endl;
  cout << "Fake Systematics     = " << fakesystematics  << endl;
  cout << "Samples         = " << samples      << endl;
  cout << "Signal         = " << signal      << endl;
  cout << "Bin Values      = " << binValues    << endl;
  cout << "Convert to GeV  = " << convertToGeV << endl;
  cout << "show data: " << show_Data << endl;
  cout << "=======================================================" << endl;

  // Tokenize inputs
  tokenizeString(channels   ,channelList   );
  tokenizeString(regions    ,regionList    );
  tokenizeString(variables  ,variableList  );
  tokenizeString(MCsystematics,MCsystematicList);
  tokenizeString(MCsystematicsCorrBg,MCsystematicCorrBgList);
  tokenizeString(fakesystematics, fakesystematicList);
  tokenizeString(samples    ,sampleList    );
  tokenizeString(fakesamples  ,fakesampleList  );
  tokenizeString(signal    ,signalList    );
  tokenizeString(binValues  ,binValueList  );
  
  

  // Plot and Save
  PlotMaker* plots = new PlotMaker();
  plots->setInputFile("/data/etp/jwittkowski/hft_processed_May_20/20140520/SSBG8TeV.root");
  plots->setInputFileSignal("/data/etp/jwittkowski/hft_processed_May_20/20140520/SSWH8TeV.root");
  plots->setSignalList     (signalList    );
  plots->setSampleList     (sampleList    );
  plots->SetFakeSampleList (fakesampleList);
  plots->setMCSystematicsList(MCsystematicList);
  plots->setMCSystematicsCorrBgList(MCsystematicCorrBgList);
  plots->setFakeSystematicsList(fakesystematicList);
  plots->setBinValuesList  (binValueList  );
  plots->setGeVFlag        (convertToGeV  );
  plots->setDataBlindCut   (dataBlindCut);
  plots->setLargerSmaller(largerSmaller);
  plots->setShowData(show_Data);

  // Loop over all combinations
  for(unsigned ii = 0; ii < channelList.size(); ++ii) {
    for(unsigned jj = 0; jj < regionList.size(); ++jj) {
      for(unsigned kk = 0; kk < variableList.size(); ++kk) {

        TString ch = ""; ch.Form("%s",channelList.at(ii).c_str() );
        TString rg = ""; rg.Form("%s",regionList.at(jj).c_str()  );
        TString vr = ""; vr.Form("%s",variableList.at(kk).c_str());

        plots->generatePlot(ch,rg,vr); 

      } // end of variable loop
    } // end of region loop
  } // end of channel loop

  return 0;
}

/// \brief Tokinize the string
void tokenizeString(string input, vector<string> &result) {

  for(unsigned int i=0,n; i<input.length(); i=n+1)
  {
    n = input.find_first_of(',',i);
    // This crap doesn't work in slc6 bugger 32/64 bit is being mixed somehow
    //if (n == string::npos) {
    if (n == 4294967295 || n == 18446744073709551615) {
        n = input.length();
    }
    string tmp = input.substr(i,n-i);
    result.push_back(tmp);
  }

}

/// \brief Print some help information to the user
void help()
{
   cout << "   Options: "                                                     << endl;
   cout << "   --channels    channels to be plotted"                          << endl;
   cout << "                 currently implemented ee/mm/em"                  << endl;
   cout << "                 default is mm"                                   << endl;

   cout << "   --regions     regions to be plotted "                          << endl;
   cout << "                 currently implemented all mT2 SR/CRs"            << endl;
   cout << "                 default is SRpremT2"                             << endl;

   cout << "   --variables   variables to be plotted "                        << endl;
   cout << "                 currently implemented mT2, metRel, met, ptl1, ptl2, ptll, mll, mjj" << endl;
   cout << "                 default is mT2"                                  << endl;

   cout << "   --systematics systematics to be added to the error band"       << endl;
   cout << "                 currently only Tree based systematics"           << endl;

   cout << "   --samples     samples to be included in the plot"              << endl;
   cout << "                 currently implemented Higgs, Fakes, ZV, Zjets, ttst, WW, Data (default)" << endl;
   cout << "                 order is preserved for the stack"                << endl;

   cout << "   --binValues   follows the logic: nbin,xmin,xmax"               << endl;
   cout << "                 default is 20,0,200"                             << endl;

   cout << "   --isGeV       converts variable into GeV"                      << endl;
   cout << "                 default is true"                                 << endl;          
}
