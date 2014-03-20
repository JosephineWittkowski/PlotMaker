#ifndef PLOTMAKER_H
#define PLOTMAKER_H

#include <iostream>
#include <string>
#include <vector>

#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TGraphAsymmErrors.h"

using namespace std;

class PlotMaker {

  // Public
  public:

    /// \brief Constructor
    PlotMaker();
    /// \brief Constructor
    ~PlotMaker();

    /// \brief Set-Get Functions for input ROOT file
    void           setInputFile(TString arg) { m_inputFile = arg ; }; 
    TString        getInputFile(           ) { return m_inputFile; };
    
    /// \brief Set-Get Functions for input *signal* ROOT file
    void           setInputFileSignal(TString arg) { m_inputFileSignal = arg ; }; 
    TString        getInputFileSignal(           ) { return m_inputFileSignal; };

    /// \brief Set-Get Functions for sample list 
    void           setSampleList(vector<string> arg) { m_sampleList = arg;  };
    vector<string> getSampleList(         ) { return m_sampleList; };       
    
    /// \brief Set-Get Functions for sample list 
    void           SetFakeSampleList(vector<string> arg) { m_fakesampleList = arg;  };
    vector<string> getFakeSampleList(      ) { return m_fakesampleList; };          
    
    
      

    /// \brief Set-Get Functions for signal list 
    void           setSignalList(vector<string> arg) { m_signalList = arg;  };
    vector<string> getSignalList(                  ) { return m_signalList; };
 
    /// \brief Set-Get Functions for systematics list
    void           setMCSystematicsList(vector<string> arg) { m_MCsystematicsList = arg;  };
    vector<string> getMCSystematicsList(                  ) { return m_MCsystematicsList; };
    
    /// \brief Set-Get Functions for fake systematics list
    void           setFakeSystematicsList(vector<string> arg) { m_fakesystematicsList = arg;  };
    vector<string> getFakeSystematicsList(                  ) { return m_fakesystematicsList; };

    /// \brief Set-Get Functions for bin values list
    void           setBinValuesList(vector<string> arg) { m_binValuesList = arg;  };
    vector<string> getBinValuesList(                  ) { return m_binValuesList; };

    /// \brief Set-Get Functions for GeV Flag
    void           setGeVFlag(bool arg) { m_converToGeV = arg;  };
    bool           getGeVFlag(        ) { return m_converToGeV; };         
    
    /// \brief Set-Get Functions for WZ Flag
    void           setWZFlag(bool arg) { m_addWZuncert = arg;  };
    bool           getWZFlag(        ) { return m_addWZuncert; };
    
    /// \brief Set-Get Functions for WZ Flag
    void           setDataBlindCut(float arg) { m_dataBlindCut = arg;  };
    bool           getDataBlindCut(        ) { return m_dataBlindCut; };  
    
    /// \brief Set-Get Functions larger/smaller data blinding cut
    void           setLargerSmaller(string arg) { m_largersmaller = arg;  };
    string           getLargerSmaller(        ) { return m_largersmaller; };  
    
    
    
    

    /// \brief Main Function that plots and saves histograms
    void           generatePlot(TString channel,TString region,TString variable);

    /// \brief Function to add overflow to last bin
    void           addOverFlowToLastBin(TH1* arg);

    /// \brief Function to get central histogmras
    void           getHistograms(TFile* input, TString varToPlot, TString cutToApply, TString dataBlindCut, TH1D* histos[], TString variation, vector<string> inputList);

    /// \brief Function to add overflow to last bin
    void           convertErrorsToPoisson(TH1* inputHisto, TGraphAsymmErrors* outputGraph);

    /// \brief Function to build the ratio's error band
    void           buildRatioErrorBand(TGraphAsymmErrors* input, TGraphAsymmErrors* output, int w_ZVIndex);
    
    /// \brief Function to get fake up dn histograms
    void GetFakeSys(vector<TH1D*> &w_fakeUpDnHistograms, TString w_observable, TString w_cut, TString w_dataBlindCut);
    

  // Private
  private:

    TFile*         m_inputROOTFile;
    TFile*         m_signalROOTFile;
    TString        m_inputFile;
    TString        m_inputFileSignal;
    vector<string> m_sampleList;
    vector<string> m_fakesampleList;
    vector<string> m_signalList;
    vector<string> m_MCsystematicsList;
    vector<string> m_fakesystematicsList;
    vector<string> m_binValuesList;
    bool           m_converToGeV;
    bool           m_addWZuncert;
    float          m_dataBlindCut;
    string m_largersmaller;
    TH1D* m_fakeHistogram;
    TH1D* m_ZVHistogram;
    bool m_dbg;
    bool m_eventyield;
    double m_WZSysUncert;
};

#endif 
