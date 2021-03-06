//////////////////////////////////////////////////////////////////////////////////////////
// \project:    ATLAS Experiment at CERN's LHC
// \package:    TwoLeptonEWKPlotter
// \class:      PlotMaker
// \file:       $Id: PlotMaker.cxx 91354 2013-05-22 12:48:03Z amete $
// \author:     Alaettin.Serhan.Mete@cern.ch, jwittkow@cern.ch
// \history:    N/A 
// 
// Copyright (C) 2013 University of California, Irvine
//////////////////////////////////////////////////////////////////////////////////////////

#include "TwoLeptonEWKPlotter/AtlasStyle.h"
#include "TwoLeptonEWKPlotter/AtlasLabels.h"
#include "TwoLeptonEWKPlotter/AtlasUtils.h"
#include "TwoLeptonEWKPlotter/PlotMaker.h"
#include "TwoLeptonEWKPlotter/PlotMakerDefs.h"

#include "TTree.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TArrow.h"

#include <stdlib.h> 

/// \brief Constructor
PlotMaker::PlotMaker()
{
  ////////////////////////////////////////////////////////////////////////////////////////
  // Set ATLAS Style
  SetAtlasStyle();
}

/// \brief Constructor
PlotMaker::~PlotMaker() 
{

}

/// \brief Main Function that plots and saves histograms
void PlotMaker::generatePlot(TString channel, TString region, TString variable)
{
  
  m_dbg = false;
  m_eventyield = true;
  m_table = false;
  
  string DataBlindCut;
  string AnD = " && ";
  DataBlindCut.append(AnD);
  DataBlindCut.append(variable);
  DataBlindCut.append(m_largersmaller);
  char buffer[20];
  sprintf(buffer, "%f", m_dataBlindCut);
  DataBlindCut.append(buffer);
  TString finalDataBlindCut = "";
//   if(m_dataBlindCut>0.) finalDataBlindCut = DataBlindCut;

  //for printing the table based on HFT's:
  TString cutflowstage = "\\mlj{} , \\mljj{}";
  if(region.Contains("_mtmax")) cutflowstage = "\\mtmax{}";
  if(region.Contains("_Ht")) cutflowstage = "\\meff{}";
  if(region.Contains("_METrel")) cutflowstage = "\\metrel{}";
  if(region.Contains("_leptPt")) cutflowstage = "\\ptlead{} , \\ptsubl{}";
  if(region.Contains("_deltaEtaLl")) cutflowstage = "\\dEtall{}";
  if(region.Contains("_ZVeto")) cutflowstage = "$Z$ veto";
  if(region.Contains("_Njets")) cutflowstage = "1-3 central jets";
  


  ////////////////////////////////////////////////////////////////////////////////////////
  // Print information
  cout << "PlotMaker::INFO   Now plotting" << 
          " channel "    << channel  <<
          " region "     << region   <<
          " variable "   << variable << endl;

  cout << "PlotMaker::INFO   Included samples     : ";
  for(unsigned int i=0; i<m_sampleList.size(); ++i) {                          
    cout << m_sampleList.at(i) << " ";
  }
  cout << endl;

  cout << "PlotMaker::INFO   Included systematics : ";

  //only now append the systematics which are correlated to make sure that they will be processed after the uncorrelated systematics
  m_MCsystematicsList.insert(m_MCsystematicsList.end(), m_MCsystematicsCorrBgList.begin(), m_MCsystematicsCorrBgList.end());
  for(unsigned int i=0; i<m_MCsystematicsList.size(); ++i) {                          
    cout << m_MCsystematicsList.at(i) << " ";
  }
  cout << endl;
  
  cout << "PlotMaker::INFO   Included fakesystematics : ";
  for(unsigned int i=0; i<m_fakesystematicsList.size(); ++i) {                          
    cout << m_fakesystematicsList.at(i) << " ";
  }
  cout << endl;
  
  cout << "PlotMaker::INFO   Included signal : ";
  for(unsigned int i=0; i<m_signalList.size(); ++i) {                          
    cout << m_signalList.at(i) << " ";
  }
  cout << endl;
  
  cout << "finalDataBlindCut= " << finalDataBlindCut << endl;

  ////////////////////////////////////////////////////////////////////////////////////////
  // Open the input ROOT file
  if(m_inputROOTFile == NULL) {
    m_inputROOTFile = new TFile(m_inputFile);
  }
  if(!m_inputROOTFile->IsOpen()) {
    cerr << "PlotMaker::ERROR   Cannot read ROOT file " << m_inputFile << endl;
    return;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////
  // Open the input ROOT file
  if(m_signalROOTFile == NULL) {
    m_signalROOTFile = new TFile(m_inputFileSignal);
  }
  if(!m_signalROOTFile->IsOpen()) {
    cerr << "PlotMaker::ERROR   Cannot read signal ROOT file " << m_inputFileSignal << endl;
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////
  // Find the Region Cut
  TString cut = RegionCuts[region];
  if(cut.Length()==0) {
    cerr << "PlotMaker::ERROR   Unknown region " << region << endl;
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////
  // Find the variable in the Ntuple
  TString observable = VariableNames[variable];
  if(observable.Length()==0) {
    cerr << "PlotMaker::ERROR   Unknown variable " << variable << endl;
    return;
  }

  ////////////////////////////////////////////////////////////////////////////////////////
  // Read the bin values set by the user and intialize the temporary histogram
  if(m_binValuesList.size()!=3) {
    cerr << "PlotMaker::ERROR   Wrong Bin Value List Size " << m_binValuesList.size() << endl;
    return;
  }
  int binWidth = ( atoi(m_binValuesList.at(2).c_str()) - atoi(m_binValuesList.at(1).c_str()) ) / atoi(m_binValuesList.at(0).c_str()); 
  
  // Build the legendL
  TLegend* legendL        = new TLegend(0.57,0.72,0.77,0.92);
  legendL->SetBorderSize(0);
  legendL->SetFillColor(0);
  legendL->SetTextFont(42);
  legendL->SetTextSize(0.035);
  
    // Build the legendR
  TLegend* legendR        = new TLegend(0.775,0.76,0.92,0.92);
  legendR->SetBorderSize(0);
  legendR->SetFillColor(0);
  legendR->SetTextFont(42);
  legendR->SetTextSize(0.035);
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  std::cout.precision(2);
  cout << fixed;
  // Get signal histogram(s)
  TH1D    *histograms_signal[m_signalList.size()];
  getHistograms(m_signalROOTFile, observable, cut, finalDataBlindCut, histograms_signal,"CENTRAL", m_signalList);
  if(m_eventyield) cout << "region " << region << " \\\\" << endl;
  //set style for signal sample(s)
  double error_signal = 0.;
  for(unsigned int i=0; i<m_signalList.size(); ++i) {
    histograms_signal[i]->SetLineWidth(4);
    histograms_signal[i]->SetLineColor(kPink+7);
    histograms_signal[i]->SetLineStyle(5);
    
    histograms_signal[i]->IntegralAndError(0,-1,error_signal);
    if(m_eventyield) cout << "Signal : " << histograms_signal[i]->Integral(0,-1) << " +\- " << error_signal << " \\\\" << endl;  
  }
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  
  // Get the central (nominal) histograms 
  TH1D    *histograms[m_sampleList.size()];
  getHistograms(m_inputROOTFile, observable, cut, finalDataBlindCut, histograms,"CENTRAL", m_sampleList);
  
  // Get the central (nominal) fake histogram
  TH1D    *fakehistograms[m_fakesampleList.size()];
  getHistograms(m_inputROOTFile, observable, cut, finalDataBlindCut, fakehistograms,"CENTRAL", m_fakesampleList);
  if(m_fakesampleList.size()>0) m_fakeHistogram = (TH1D*) fakehistograms[0]->Clone();
  
  

  // Massage the Data and add MC to SM stack 
  TGraphAsymmErrors *Data = new TGraphAsymmErrors();
  //one stack for ALL bg...
  THStack *stackBg        = new THStack("stackBg","Standard Model");
  //...and one for MC bg, only
  THStack *stackMCBg        = new THStack("stackMCBg","MC Standard Model");
  int      dataIndex      = -1; 
  int 	   ZVIndex	  = -1;
  int 	   SSIndex	  = -1;
  
  
  if(m_table) cout << "Requirement on & ";
  for(unsigned int i=0; i<m_sampleList.size(); ++i) {
      if(m_table && (m_sampleList.at(i)!="Data")) cout << m_sampleList.at(i) << " & " ;
  }
  double error_on_integral = 0.;
  if(m_table) cout << " Fake & ($m_{\\neutralino{2}}, m_{\\chargino{1}, \\neutralino{1}}$)=(130,0)~GeV \\\\" << endl;
  if(m_table) cout << "\\hline " << endl;
  if(m_table) cout << cutflowstage << " & " ;
  for(unsigned int i=0; i<m_sampleList.size(); ++i) {
    // Add to stack if background
    if((m_dbg || m_eventyield) && (m_sampleList.at(i)!="Data" || (/*m_dataBlindCut>-1. &&*/ m_show_data))) cout << m_sampleList.at(i) << " : " << histograms[i]->Integral(0, -1) << " \\\\" << endl;
    if(m_table && (m_sampleList.at(i)!="Data")) histograms[i]->IntegralAndError(0, -1, error_on_integral);
    if(m_table && (m_sampleList.at(i)!="Data")) cout << histograms[i]->IntegralAndError(0, -1, error_on_integral) << " $\\pm$ " << error_on_integral;;
    if(m_table && i < m_sampleList.size()-2  && (m_sampleList.at(i)!="Data")) cout << " & ";
    
    if(m_sampleList.at(i)!="Data"){
      if(m_sampleList.at(i)=="ZV"){
	ZVIndex = i;
	m_ZVHistogram =  (TH1D*) histograms[i]->Clone();
      }
      if(m_sampleList.at(i)=="SameSign"){
	SSIndex = i;
	m_SSHistogram =  (TH1D*) histograms[i]->Clone();
      }
      stackBg->Add(histograms[i]);
      if(m_sampleList.at(i)!="Fakes") stackMCBg->Add(histograms[i]);
      
      if(m_dbg){
	for(int bin=1; bin<histograms[i]->GetNbinsX()+1; bin++){
	  cout << m_sampleList.at(i) << " NOMINAL= " << histograms[i]->GetBinContent(bin) << endl;
	}
      }
    }
    else {
      dataIndex = i;
      histograms[i]->SetMarkerSize(0);
      histograms[i]->SetLineWidth(0);
      histograms[i]->SetLineColor(0);
      // Convert data errors to Poisson
      convertErrorsToPoisson(histograms[i],Data);
      Data->SetMarkerSize(1.2);
      Data->SetMarkerStyle(20);
      Data->SetLineWidth(2);
    }
  }
  if(m_show_data) legendL->AddEntry(Data,SampleNames["Data"],"p");
  for(unsigned int i=0; i<m_fakesampleList.size(); ++i) {
    stackBg->Add(fakehistograms[i]);
//     cout << "stackBg->Add(fakehistograms[i]);" << endl;
    if(m_dbg || m_eventyield) cout << m_fakesampleList.at(i) << " : " << fakehistograms[i]->Integral(0, -1) << " \\\\" << endl;
    if(m_table) fakehistograms[i]->IntegralAndError(0, -1, error_on_integral);
    if(m_table) cout << " & " << fakehistograms[i]->IntegralAndError(0, -1, error_on_integral) << " $\\pm$ " << error_on_integral;
    legendL->AddEntry(fakehistograms[i],SampleNames["Fakes"],"f");
  }
  
  for(unsigned int i=0; i<m_signalList.size(); ++i) {
    if(m_table) histograms_signal[i]->IntegralAndError(0, -1, error_on_integral);
    if(m_table) cout << " & " <<  histograms_signal[i]->IntegralAndError(0, -1, error_on_integral) << " $\\pm$ " << error_on_integral << " \\\\" << endl;  
  } 

  // Add SM Background to legendL
  for(int i=0; i<m_sampleList.size() ; i++) {
    if(m_sampleList.at(i)!="Data")
      
      if(i<2)legendL->AddEntry(histograms[i],SampleNames[m_sampleList.at(i)],"f");
      else legendR->AddEntry(histograms[i],SampleNames[m_sampleList.at(i)],"f");
      if(i==3)legendL->AddEntry(histograms_signal[0],SampleNames["signal1"],"l");
      
  }
    

  

  ////////////////////////////////////////////////////////////////////////////////////////
  // Treatment of systematic errors. 
  // uncorrelated: add squared. correlated: add linarly.
  // 1) loop over all sys errors and weighted event yields for MC bg, add to totalSysHistoBg (linear, stack, ==> correlated!)
  // 1a) XS and GEN: add in quadrature
  // 2) add for each individual sys the difference to the nominal value to yhigh or ylow with myAddtoBandSquaredUncorr. Original TGraphAsymmErrors 'nominalAsymErrorsMCBg': deduced from MC stack histo -> includes statistical error of all MC histos.
  // 3) to include stat error of fake histos, use myTGraphErrorsAdd() method to add fake_histo (= stat errors) to 'nominalAsymErrorsMCBg'.
  // 4) for fakes, don't consider stat error any more (already included!). Loop over each bin for all fake sys and add difference to nominal event yield to yhigh or ylow. 
  // 4) for fakes, don't consider stat error any more (already included!). Loop over each bin for all fake sys and add difference to nominal event yield to yhigh or ylow (in GetFakeSys() method)
  // 5) use again myAddtoBandSquaredUncorr method. 'nominalAsymErrorsMCBg' now inlcudes all background (MC + fake !) -> add other bg contributions to fake_up and fake_dn histos before calling the method.
  // 6) final error includes stats of MC bg, stats of fake bg, sys of MC bg and sys of fake bg. Everything is added squared (uncorrelated) except for individual MC bg components or simply adding EE, EM and MM if wanted. ('regions and processes' are correlated. Everything else is uncorrelated. )

  // Get Total MC Histo
  TH1D* stackHistoBg = (TH1D*) stackBg->GetStack()->Last();

  TGraphAsymmErrors* nominalAsymmErrorsBg = TH1TOTGraph(stackHistoBg);
  nominalAsymmErrorsBg->SetMarkerSize(0);
  nominalAsymmErrorsBg->SetLineWidth(2);
  nominalAsymmErrorsBg->SetFillStyle(3004);
  nominalAsymmErrorsBg->SetFillColor(kBlack);
  
  TH1D* stackHistoMCBg; 

//   if there is MC bg to be included:
  TGraphAsymmErrors* nominalAsymErrorsMCBg;
  if(m_sampleList.size()>1){
//     cout << "in if(m_sampleList.size()>1){" << endl;
    stackHistoMCBg = (TH1D*) stackMCBg->GetStack()->Last();
    nominalAsymErrorsMCBg = TH1TOTGraph(stackHistoMCBg);
  }
  else{
    //else: use an empty TGraphAsymmErrors, based on stackBg
    stackHistoMCBg = stackHistoBg;
    stackHistoMCBg->Reset();
    nominalAsymErrorsMCBg = TH1TOTGraph(stackHistoMCBg);
  }
  
  if(m_dbg) cout << "nominalAsymErrorsMCBg->GetY()[0]= " << nominalAsymErrorsMCBg->GetY()[0] << endl;
  nominalAsymErrorsMCBg->SetMarkerSize(0);
  nominalAsymErrorsMCBg->SetLineWidth(2);
  nominalAsymErrorsMCBg->SetFillStyle(3004);
  nominalAsymErrorsMCBg->SetFillColor(kBlack);
  
  if(m_dbg){
    cout << "only statistical error on MC stackHistoMCBg (excl Fakes):" << endl;
    for(int bin=0; bin < nominalAsymErrorsMCBg->GetN(); bin++){ 
      cout << "bin " << bin << " Y= " << nominalAsymErrorsMCBg->GetY()[bin] <<  " + " << nominalAsymErrorsMCBg->GetEYhigh()[bin] << " - " << nominalAsymErrorsMCBg->GetEYlow()[bin] << endl;
    }
  
    if(m_fakesampleList.size()>0){
      TGraphAsymmErrors*  AsymmErrorsFake = TH1TOTGraph(m_fakeHistogram);
      cout << "only statistical error on Fakes:" << endl;
	for(int bin=0; bin < AsymmErrorsFake->GetN(); bin++){ 
	  cout << "bin " << bin << " Y= " << AsymmErrorsFake->GetY()[bin] <<  " + " << AsymmErrorsFake->GetEYhigh()[bin] << " - " << AsymmErrorsFake->GetEYlow()[bin] << endl;
      }
    }
    cout << "only statistical error on all backgrounds:" << endl;
    for(int bin=0; bin < nominalAsymmErrorsBg->GetN(); bin++){ 
      cout << "bin " << bin << " Y= " << nominalAsymmErrorsBg->GetY()[bin] <<  " + " << nominalAsymmErrorsBg->GetEYhigh()[bin] << " - " << nominalAsymmErrorsBg->GetEYlow()[bin] << endl;
  }
  
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
  }


  // Add SM Bkg. to the legendL
  legendR->AddEntry(nominalAsymErrorsMCBg,"Bkg. Uncert.","f"); 
  

  // 1) loop over all sys errors and weighted event yields for MC bg, add to totalSysHistoBg (linear, stack, ==> correlated!)
  TH1D* totalSysHistoBg = (TH1D*) stackHistoMCBg->Clone();
  totalSysHistoBg->Reset();  
  //for adding the individual sys histo to the previous ones:
  TGraphAsymmErrors* transientMcBg;
  TH1D    *sysHistograms[m_sampleList.size()];
  
  for(unsigned int i=0; i < m_MCsystematicsList.size(); ++i) {
//     cout << "loop over systematics MC" << endl;

    // Retrieve the syshistograms
    getHistograms(m_inputROOTFile, observable, cut, finalDataBlindCut, sysHistograms, m_MCsystematicsList.at(i), m_sampleList);

    // Loop over samples and add to total systematics histo
    for(unsigned int j=0; j < m_sampleList.size(); ++j) {      

      if(m_sampleList.at(j) != "Fakes"){
	if(sysHistograms[j]!=NULL){
	  
	  if(m_dbg){ 
	    for(int k=1; k<sysHistograms[j]->GetNbinsX()+1; k++){
	      cout << "sysHistograms[j]->GetBinContent( " << k << ")= " << sysHistograms[j]->GetBinContent(k) << " histograms[j]->GetBinContent(" << k << ")= " << histograms[j]->GetBinContent(k) << endl;
	    }
	  }
	  
// 	  if(m_dbg) cout << m_sampleList.at(j) << " " << m_MCsystematicsList.at(i) << " Integral " << sysHistograms[j]->Integral(0,-1) << " diff " << fabs(sysHistograms[j]->Integral(0,-1) - histograms[j]->Integral(0, -1)) << endl;
	  
	  
//####################################################################################################################################3	  
	  //if XS or GEN: add error quadratically by looping over all bins, not linearly like with TH1D->Add()
	  if(m_MCsystematicsList.at(i) == "syst_XSUP" || m_MCsystematicsList.at(i) == "syst_XSDOWN"|| m_MCsystematicsList.at(i) == "syst_GENUP" || m_MCsystematicsList.at(i) == "syst_GENDOWN"){
	    double totalSysHistoBgYield = 0.;
	    for(int k=1; k<sysHistograms[j]->GetNbinsX()+1; k++){
	      
	      //save what was in there already before:
	      totalSysHistoBgYield = totalSysHistoBg->GetBinContent(k);

	      totalSysHistoBg->SetBinContent( k, sqrt(pow(totalSysHistoBgYield,2) + pow(sysHistograms[j]->GetBinContent(k) - histograms[j]->GetBinContent(k),2)) );
	    }
	  }
	  
//####################################################################################################################################3	  
	  else{
// 	    if(m_dbg) cout << "totalSysHistoBg->Add(sysHistograms[j]);" << endl;
	    totalSysHistoBg->Add(sysHistograms[j]);
	    
	  }

	}
	else if ( m_sampleList.at(j) != "Data") {
	  cout << "PlotMaker::WARNING   Cannot find TTree for systematics " << 
		  m_MCsystematicsList.at(i) << " for sample " << m_sampleList.at(j)  << endl;
	}
      }
      if(m_dbg) cout << "for " << m_sampleList.at(j) << " totalSysHistoBg->Integral(0,-1)= " << totalSysHistoBg->Integral(0,-1) << endl;
    }

    //2) add for each individual sys the difference to the nominal value to yhigh or ylow with myAddtoBandSquaredUncorr. Original TGraphAsymmErrors 'nominalAsymErrorsMCBg': deduced from stack histo -> includes statistical error of all MC histos.
    
    //All MC BG (correlated-> use TH1D, linear) SYS (uncorrelated -> use myAddtoBandSquaredUncorr(), squared)

      if(m_MCsystematicsList.at(i) == "syst_XSUP" || m_MCsystematicsList.at(i) == "syst_GENUP"){
	for(int k=1; k<stackHistoMCBg->GetNbinsX()+1; k++){
	  if(m_dbg) cout << "totalSysHistoBg->SetBinContent( k, totalSysHistoBg->GetBinContent(k) + stackHistoMCB->GetBinContent(k)); " << totalSysHistoBg->GetBinContent(k) + stackHistoMCBg->GetBinContent(k) << endl;
	  totalSysHistoBg->SetBinContent( k, totalSysHistoBg->GetBinContent(k) + stackHistoMCBg->GetBinContent(k));
	}
      }
      
      if(m_MCsystematicsList.at(i) == "syst_XSDOWN"|| m_MCsystematicsList.at(i) == "syst_GENDOWN"){
	for(int k=1; k<stackHistoMCBg->GetNbinsX()+1; k++){
	  if(m_dbg)cout << "totalSysHistoBg->SetBinContent( k, stackHistoMCBg->GetBinContent(k) - totalSysHistoBg->GetBinContent(k)); " << stackHistoMCBg->GetBinContent(k) - totalSysHistoBg->GetBinContent(k) << endl;
	  totalSysHistoBg->SetBinContent( k, stackHistoMCBg->GetBinContent(k) - totalSysHistoBg->GetBinContent(k));
	}
      }
      transientMcBg = TH1TOTGraph(totalSysHistoBg);
      myAddtoBandSquaredUncorr(transientMcBg,nominalAsymErrorsMCBg);
      totalSysHistoBg->Reset();

  }
  
  if(m_dbg) cout << "nominalAsymErrorsMCBg->GetY()[0]= " << nominalAsymErrorsMCBg->GetY()[0] << endl;
  
  // 3) to include stat error of fake histos, use myTGraphErrorsAdd() method to add fake_histo (= stat errors) to 'nominalAsymErrorsMCBg'.
    if(m_fakesampleList.size() > 0){
      TGraphAsymmErrors* nominalAsymmErrorsFake = TH1TOTGraph(m_fakeHistogram);
      //   add in quadrature the  statistical errors:
      myTGraphErrorsAdd(nominalAsymErrorsMCBg,nominalAsymmErrorsFake );
      if(m_dbg) cout << "after adding fake stat error: nominalAsymErrorsMCBg->GetY()[0]= " << nominalAsymErrorsMCBg->GetY()[0] << endl;
      vector<TH1D*> FakeUpDnHistograms;
      TH1D* sys0 = (TH1D*) m_fakeHistogram->Clone();
      TH1D* sys1 = (TH1D*) m_fakeHistogram->Clone();
      sys0->Reset();
      sys1->Reset();
      FakeUpDnHistograms.push_back(sys0);
      FakeUpDnHistograms.push_back(sys1);
      
      // 4) for fakes, don't consider stat error any more (already included!). Loop over each bin for all fake sys and add difference to nominal event yield to yhigh or ylow (in GetFakeSys() method)
      GetFakeSys(FakeUpDnHistograms, observable, cut, finalDataBlindCut);
      if(m_dbg){
	for(int i=1; i<FakeUpDnHistograms[0]->GetNbinsX()+1; i++){
	  if(m_dbg) cout << "FakeUpDnHistograms[0]->GetBinContent(i)= " << FakeUpDnHistograms[0]->GetBinContent(i) << endl;
	  if(m_dbg) cout << "FakeUpDnHistograms[1]->GetBinContent(i)= " << FakeUpDnHistograms[1]->GetBinContent(i) << endl;
	}
      }
      totalSysHistoBg->Reset();

      if(m_dbg) cout << "totalSysHistoBg->Integral(0,-1)= " << totalSysHistoBg->Integral(0,-1) << endl;
    
      for(uint i=0; i<FakeUpDnHistograms.size(); i++){//loop fake UP/DN

	for(uint imc=0; imc<m_sampleList.size(); imc++){
  	if(m_sampleList.at(imc) == "Data") continue;
	  TH1D* _hsys = histograms[imc];
	  totalSysHistoBg->Add(_hsys);
	}
	if(m_dbg) cout << "totalSysHistoBg->Integral(0,-1)= " << totalSysHistoBg->Integral(0,-1) << endl;

	totalSysHistoBg->Add(FakeUpDnHistograms[i]); //Add the fake sys
	// 5) use again myAddtoBandSquaredUncorr method. 'nominalAsymErrorsMCBg' now inlcudes all background (MC + fake !) -> add other bg contributions to fake_up and fake_dn histos before calling the method.
	TGraphAsymmErrors* transientFake = TH1TOTGraph(totalSysHistoBg);   //Mem leak!!!
	myAddtoBandSquaredUncorr(transientFake,nominalAsymErrorsMCBg); //100 uncorrelated sys - add in quad to the other MC bkg sys
	totalSysHistoBg->Reset();
      }
    }
    
    if(m_dbg) cout << "nominalAsymErrorsMCBg->GetY()[0]= " << nominalAsymErrorsMCBg->GetY()[0] << endl;
  

// 6) final error includes stats of MC bg, stats of fake bg, sys of MC bg and sys of fake bg. Everything is added squared (uncorrelated) except for individual MC bg components or simply adding EE, EM and MM if wanted. ('regions and processes' are correlated. Everything else is uncorrelated. )

    
    if(m_dbg) cout << "nominalAsymErrorsMCBg->GetY()[0]= " << nominalAsymErrorsMCBg->GetY()[0] << endl;


  ////////////////////////////////////////////////////////////////////////////////////////
  // Draw the canvas
  TCanvas* canvas = new TCanvas("canvas","canvas",700,500);
  TPad*    topPad = new TPad("pTop","pTop",0,0.23,1,1);
  TPad*    botPad = new TPad("pBot","pBot",0,0.0,1,0.31);
  topPad->Draw();
  botPad->Draw();

  // Top Pad
  topPad               ->cd();
  if(m_show_data) topPad               ->SetBottomMargin(0.13);
  else topPad               ->SetBottomMargin(0.13);

  if(m_show_data){
    histograms[dataIndex]->Draw("p");

    stackBg              ->Draw("hists same");
    nominalAsymErrorsMCBg    ->Draw("same && E2");
    Data                 ->Draw("same && p");
    histograms_signal[0]->Draw("hists same");
    legendL               ->Draw();
    legendR               ->Draw();
  }
  else{
    histograms_signal[0]->Draw("hists");
    stackBg              ->Draw("hists same");
    nominalAsymErrorsMCBg    ->Draw("same E2");
    histograms_signal[0]->Draw("hists same");
    
    legendL               ->Draw();
    legendR               ->Draw();
  }
  
  TArrow* arrow;
  if(!variable.Contains("Eta")) arrow = new TArrow(m_dataBlindCut/1000.,0,m_dataBlindCut/1000.,histograms[dataIndex]->GetMaximum()/1.2,0.03,"<|");
  else arrow = new TArrow(m_dataBlindCut,0,m_dataBlindCut,histograms[dataIndex]->GetMaximum()/1.5,0.03,"<|");
  arrow->SetLineWidth(6);
  arrow->SetAngle(40);
  arrow->SetLineColor(kRed);
  arrow->SetFillColor(kRed);
  arrow->SetLineWidth(3);
  if(m_dataBlindCut > 0.)arrow->Draw("");

  // Set a few fancy labels and set axis ranges
  TString ylabel = "";
  ylabel.Form("Events /%i",binWidth);
  if(m_converToGeV)
    ylabel.Append(" GeV");
  TString xlabel = "";

  if( variable.EqualTo("Ht") ) {
    xlabel = "H_{T} [GeV]";
  }
  else if( variable.EqualTo("mlj") ) {
    xlabel = "m_{lj} [GeV]";
  }
  else if( variable.EqualTo("mljj") ) {
    xlabel = "m_{ljj} [GeV]";
  }
  else if( variable.EqualTo("L2METrel") ) {
    xlabel = "E_{T}^{miss,rel} [GeV]";
  }
  else if( variable.EqualTo("mtmax") ) {
    xlabel = "m_{T}^{max}[GeV]";
  }
  else if( variable.EqualTo("ptl1") ) {
    xlabel = "p_{T,l1} [GeV]";
  }
  else if( variable.EqualTo("mtllmet") ) {
    xlabel = "m_{T}(WW) [GeV]";
  }
  else if( variable.EqualTo("ptll") ) {
    xlabel = "p_{T,ll} [GeV]";
  }
  else {
    xlabel = variable;
  }
  histograms[dataIndex]->GetXaxis()->SetTitle(xlabel); 
  histograms[dataIndex]->GetXaxis()->SetLabelOffset(1.2); 
//   histograms[dataIndex]->GetXaxis()->SetLabelSize(0.03);
  histograms[dataIndex]->GetYaxis()->SetTitle(ylabel); 
  histograms[dataIndex]->GetYaxis()->SetLabelSize(0.05); 
  histograms[dataIndex]->GetYaxis()->SetTitleSize(0.05);
  //if not plotting data, another histogram is the first one to plot and will be used as reference for SetRangeUser (and only this one, other don't have influence on the range...).
  if(m_show_data) histograms[dataIndex]->GetYaxis()->SetRangeUser(2.e-2,histograms[dataIndex]->GetMaximum()*2.0); //*1000 if logscale
  else histograms_signal[0]->GetYaxis()->SetRangeUser(2.e-2,stackMCBg->GetMaximum()*3.5);

//   gPad->SetLogy(1);

  // Decoration
  char annoyingLabel1[100] = "#bf{#it{ATLAS}} Internal", annoyingLabel2[100] = "#scale[0.6]{#int} L dt = 20.3 fb^{-1} #sqrt{s} = 8 TeV";
  myText(0.19,0.88,kBlack,annoyingLabel1);
  myText(0.19,0.80,kBlack,annoyingLabel2);
  topPad->RedrawAxis();
  // Bottom Pad
  botPad->cd();
  botPad->SetBottomMargin(0.3);

  // Dummy ratio histogram to set the scale and titles, etc.
  // I don't really like this part
  TH1D* ratio_original = (TH1D*) histograms[dataIndex]->Clone();
  ratio_original->Reset();
  ratio_original->SetMarkerSize(1.2);
  ratio_original->SetMarkerStyle(20);
  ratio_original->SetLineColor(kBlack);
  ratio_original->SetLineWidth(2);
  ratio_original->GetXaxis()->SetTitle(xlabel);
  ratio_original->GetYaxis()->SetTitle("Data/SM");
  ratio_original->GetXaxis()->SetLabelSize(0.05/0.31*0.77);
  ratio_original->GetXaxis()->SetLabelOffset(0.02);
  ratio_original->GetXaxis()->SetTitleSize(0.05/0.31*0.77);
  ratio_original->GetXaxis()->SetTitleOffset(1.);
  ratio_original->GetYaxis()->SetRangeUser(0,2);
  ratio_original->GetYaxis()->SetLabelSize(0.05/0.31*0.77);
  ratio_original->GetYaxis()->SetTitleSize(0.05/0.31*0.77);
  ratio_original->GetYaxis()->SetTitleOffset(0.5);
  ratio_original->GetYaxis()->SetNdivisions(5);

  // Build the ratio's error band: Use (bg stat + sys errors) divided by bin content (nominal yield). 
  TGraphAsymmErrors* ratioBand   = new TGraphAsymmErrors( *nominalAsymErrorsMCBg ); 
  if(m_dbg) cout << "m_MCsystematicsList.size()= " << m_MCsystematicsList.size() << endl;
  if(m_eventyield) cout << "Total = " << ((TH1*)(stackBg->GetStack()->Last()))->Integral(0,-1) ;
  buildRatioErrorBand(nominalAsymErrorsMCBg, ratioBand, ZVIndex);

  // Get the ratio
  // For the ratio points, only use the statistical error for data because we explicitly draw the MC error band -> Set Error of 'nominalAsymErrorsMCBg' to 0 in 'nominalAsymErrorsMCBgNoError'
  TGraphAsymmErrors* nominalAsymErrorsMCBgNoError = new TGraphAsymmErrors( *nominalAsymErrorsMCBg );
  for(int i=1; i<nominalAsymErrorsMCBgNoError->GetN()+1; ++i) {
    nominalAsymErrorsMCBgNoError->SetPointError(i-1,0,0,0,0);
  }
  TGraphAsymmErrors* ratio_raw = myTGraphErrorsDivide(Data,nominalAsymErrorsMCBgNoError);
  TGraphAsymmErrors* ratio     = new TGraphAsymmErrors();

  double x1=0; double y1=0; unsigned int newIndex = 0.;
  for(int kk=0; kk<ratio_raw->GetN(); ++kk){
    ratio_raw->GetPoint(kk, x1,y1);
    if(y1 > 0.) {
      ratio->SetPoint(newIndex, x1, y1);
      if(m_dbg) cout << " point " << kk << " y1= " << y1 << " ratio_raw->GetErrorYlow(kk)= " << ratio_raw->GetErrorYlow(kk) << " ratio_raw->GetErrorYhigh(kk)= " << ratio_raw->GetErrorYhigh(kk) << endl;
      ratio->SetPointError(newIndex, ratio_raw->GetErrorXlow(kk), ratio_raw->GetErrorXhigh(kk), ratio_raw->GetErrorYlow(kk), ratio_raw->GetErrorYhigh(kk));
      newIndex++;
    }
  }
  ratio->SetMarkerSize(1.2);
  ratio->SetMarkerStyle(20);
  ratio->SetLineColor(kBlack);
  ratio->SetLineWidth(2);

  // Make the line at 1 for the ratio plot
  TLine *line = new TLine(histograms[dataIndex]->GetXaxis()->GetXmin(),1,histograms[dataIndex]->GetXaxis()->GetXmax(),1);
  line->SetLineColor(kRed);
  line->SetLineStyle(7);

  // Draw
  ratio_original->Draw();
  ratioBand     ->Draw("same && E2");
  line          ->Draw();
  if(m_show_data) ratio         ->Draw("same && P");
  gPad          ->SetGridy(1);
  gPad->RedrawAxis();


  TString plotName = "/data/etp3/jwittkow/analysis_SUSYTools_03_04_SusyNt_01_16/pics_KinematicPlotter/kinematics_" + region + "_" + variable + "_July_10_cosmetics.pdf" ;
  TString plotNameeps = "/data/etp3/jwittkow/analysis_SUSYTools_03_04_SusyNt_01_16/pics_KinematicPlotter/kinematics_" + region + "_" + variable + "_July_10_cosmetics.eps" ;
  //plotName = dirOut + "/" + plotName;
  canvas->SaveAs(plotName);
  canvas->SaveAs(plotNameeps);

  // Delete unnecessary stuff to open up memory
  //delete[] histograms;
  //delete[] sysHistograms;
  delete Data;
  delete stackBg;
  delete nominalAsymErrorsMCBg;
  delete nominalAsymErrorsMCBgNoError;
  delete ratioBand;
  delete ratio_original;
  delete ratio_raw;
  delete ratio;
  delete totalSysHistoBg;
  delete legendL;
  delete legendR;
  delete canvas;

  return;
}

/// \brief Function to add overflow to last bin
void PlotMaker::addOverFlowToLastBin(TH1* histo) {

  // Find last bin
  int lastBin          = histo->GetXaxis()->GetNbins();

  // Read values
  double lastBinValue  = histo->GetBinContent(lastBin);
  double lastBinError  = histo->GetBinError(lastBin);
  double overFlowValue = histo->GetBinContent(lastBin+1); 
  double overFlowError = histo->GetBinError(lastBin+1);

  // Set Values    
  histo->SetBinContent(lastBin+1,0);
  histo->SetBinError(lastBin+1,0);
  histo->SetBinContent(lastBin,lastBinValue+overFlowValue);
  histo->SetBinError(lastBin,sqrt(lastBinError*lastBinError+overFlowError*overFlowError));

}

/// \brief Function to add overflow to last bin
void PlotMaker::convertErrorsToPoisson(TH1* histo, TGraphAsymmErrors* graph) 
{
  // Needed variables
  double value = 0;
  double error_poisson_up   = 0;
  double error_poisson_down = 0;
  double alpha = 0.158655, beta = 0.158655; // 68%

  // loop over bins and overwrite values
  for(int i=1; i<histo->GetNbinsX()+1; i++){
    value = histo->GetBinContent(i);
    if(value!=0) {
      error_poisson_up     = 0.5*TMath::ChisquareQuantile(1-beta,2*(value+1)) - value; 
      error_poisson_down   = value - 0.5*TMath::ChisquareQuantile(alpha,2*value);
      graph->SetPoint(i-1, histo->GetBinCenter(i), value);
      graph->SetPointError(i-1, 0., 0. , error_poisson_down, error_poisson_up);
    }
    else{
      graph->SetPoint(i-1, histo->GetBinCenter(i), 0.);
      graph->SetPointError(i-1, 0., 0., 0., 0.);
    }
  }
}

/// \brief Function to get higstograms
void PlotMaker::getHistograms(TFile* input, TString varToPlot, TString cutToApply, TString dataBlindCut, TH1D* histos[], TString variation, vector<string> inputList)
{
  // Initialize the temp histogram
  TH1D *temp = new TH1D("temp","temp",atof(m_binValuesList.at(0).c_str()),
                                      atof(m_binValuesList.at(1).c_str()),
                                      atof(m_binValuesList.at(2).c_str())); 
  temp->Sumw2();
  
  // Here is the loop over samples
  for(unsigned int i=0; i<inputList.size(); ++i) {
    // Return NULL if systematics and Data
    if( (inputList.at(i) == "Data") && !variation.EqualTo("CENTRAL") ) {
      histos[i] = NULL;
      continue;
    }

    
    // Define variables internal to the loop
    TString treeName = "";
    //DATA
    if(inputList.at(i) == "Data"){
      treeName.Form("%s_",inputList.at(i).c_str()); 
      treeName += "CENTRAL";
//       cout << "Data " << inputList.at(i) << " treeName= " << treeName << endl;
    }
    else{
      //BACKGROUND
      if(inputList == m_sampleList || inputList == m_fakesampleList){      
	//MC BACKGROUND
	if(inputList.at(i) != "Fakes" ){
// 	  cout << "variation.Contains(syst)= " << variation.Contains("syst") << endl;
	  if(variation.EqualTo("CENTRAL") || variation.Contains("syst")){
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += "CENTRAL";
// 	    cout <<  "treeName= " << treeName << endl;
	  }
	  else if(variation.Contains("ELFR") || variation.Contains("ELRE") || variation.Contains("MUFR") || variation.Contains("MURE")){
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += "CENTRAL";
// 	    cout <<  "treeName= " << treeName << endl;
	  }
	  else{
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += variation;
// 	    cout <<  "treeName= " << treeName << endl;
	  }
// 	  cout << "MC background " << inputList.at(i) << " treeName= " << treeName << endl;
	}
	//FAKE BACKGROUND
	if(inputList.at(i) == "Fakes"){
	  if(variation.EqualTo("CENTRAL") || variation.Contains("syst")){
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += "CENTRAL";
	  }
	  if(variation.Contains("ELFR") || variation.Contains("ELRE") || variation.Contains("MUFR") || variation.Contains("MURE")){
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += variation;
	  }
	  else{
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += "CENTRAL";
	  }
// 	  cout << "Fake background " << inputList.at(i) << " treeName= " << treeName << endl;
	}
      }
      //SIGNAL
      if(inputList == m_signalList){
	treeName = ""; 
	if(variation.Contains("syst")){ 
	  treeName.Form("SSWH8TeV_%s_",m_signalList.at(i).c_str()); treeName += "CENTRAL";
	}
	else{
	  treeName.Form("SSWH8TeV_%s_",m_signalList.at(i).c_str()); treeName += variation;
	}
// 	cout << "signal " << inputList.at(i) << " treeName= " << treeName << endl;
      }
    }
//       cout << inputList.at(i) << " " << variation << " treeName= " << treeName << endl;    
    TString histoName = ""; histoName.Form("histo_%s",inputList.at(i).c_str());

    // Get the TTree - continue the loop if not found 
    TTree* tree = (TTree*) input->Get(treeName);
    if(tree == NULL) {
      cout << "PlotMaker::WARNING   Cannot find TTree w/ name " << treeName << " " << inputList.at(i) << " " << variation << endl;
      histos[i] = NULL;
      continue;
    }
     
      
    //use eventweight for nominal (CENTRAL) and most sytematic variations. Else use weight == variation.
    TString weight = " * eventweight";
    TString additionalWeight = "1";
    if(variation.Contains("syst")) additionalWeight= variation;
//     else weight = variation;
//     if(m_dbg) cout << "weight= " << weight << endl;
    //eventually additional cut for data to blind it in SR.
//     cout << "additionalWeight + weight + cutToApply + dataBlindCut= " << additionalWeight + weight + cutToApply + dataBlindCut << endl;
    if(inputList.at(i) == "Data"){
      if(cutToApply.Contains("L2nCentralLightJets==2")==1){
	if(m_converToGeV)
	  tree->Draw( varToPlot + "/1000.>>temp" , additionalWeight + weight + cutToApply + dataBlindCut/* + "&& mljj>120000."*/);
	else
	  tree->Draw( varToPlot + ">>temp"       , additionalWeight + weight + cutToApply + dataBlindCut);
      }
      else{
      if(m_converToGeV)
	tree->Draw( varToPlot + "/1000.>>temp" , additionalWeight + weight + cutToApply + dataBlindCut/* + "&& mlj>90000." */);
      else
	tree->Draw( varToPlot + ">>temp"       , additionalWeight + weight + cutToApply + dataBlindCut);
      }
    }
    else{
      if(m_converToGeV){
	tree->Draw( varToPlot + "/1000.>>temp" , additionalWeight + weight + cutToApply );
//       	cout << "cutToApply= " << cutToApply << endl;
      }
      else
	tree->Draw( varToPlot + ">>temp"       , additionalWeight + weight + cutToApply);
    }

    // Clone and beautify
    histos[i] = (TH1D*) temp->Clone();
    histos[i]->SetName(histoName);
    histos[i]->SetTitle(histoName);
    histos[i]->SetLineWidth(2);
    histos[i]->SetLineColor(kBlack);
    histos[i]->SetFillColor(SampleColors[inputList.at(i)]);

    // Add the overflow to the last bin
    addOverFlowToLastBin(histos[i]);

    delete tree;
  } // end of loop over samples

  temp->Reset();
  delete temp;
}

/// \brief Function to build the ratio's error band
void PlotMaker::buildRatioErrorBand(TGraphAsymmErrors* input, TGraphAsymmErrors* output, int w_ZVIndex) 
{
  
  output->SetMarkerSize(0);
  float EYHigh = 0.;
  float EYLow = 0.;
  for(int bin=0; bin < output->GetN(); bin++){ 
    if(m_dbg) cout << "bin " << bin << " ratio " << input->GetY()[bin] << endl;
    output->GetY()[bin] = 1.; 
    
    if( fabs(input->GetY()[bin]) > 0.0001 ) {
      output->GetEYhigh()[bin]=input->GetEYhigh()[bin] /input->GetY()[bin]; 
      if(m_dbg || m_eventyield) cout << "$^{+ " << input->GetEYhigh()[bin]  << "} "; 
      EYHigh += input->GetEYhigh()[bin];
    }
   else 
      output->GetEYhigh()[bin]= 0.; 
   
   if( fabs(input->GetY()[bin]) > 0.0001 ){

      output->GetEYlow()[bin]=input->GetEYlow()[bin]/input->GetY()[bin]; 
      if(m_dbg || m_eventyield) cout << "_{- " << input->GetEYlow()[bin]  << "}$ \\\\" << endl;     
      EYLow += input->GetEYlow()[bin];
      
   }
   else 
      output->GetEYlow()[bin]= 0.; 
  }
  if(m_dbg || m_eventyield) cout << "$^{+ " << EYHigh  << "} _{- " << EYLow << "}$ \\\\" << endl;   
}

  void PlotMaker::GetFakeSys(vector<TH1D*> &w_fakeUpDnHistograms, TString w_observable, TString w_cut, TString w_dataBlindCut){
  
    if(m_dbg) cout << "m_fakeHistogram->Integral(0,-1)= " << m_fakeHistogram->Integral(0,-1) << endl;
    TH1D* fake_histo_up = (TH1D*) m_fakeHistogram->Clone();
    TH1D* fake_histo_dn = (TH1D*)m_fakeHistogram->Clone();
    //if no fake sys given, reset the fake sys histos :
    fake_histo_up->Reset();
    fake_histo_dn->Reset();
    if(m_dbg) cout << "fakes:" << endl;
    for(int bin=1; bin<m_fakeHistogram->GetNbinsX()+1; ++bin){
//       if(m_dbg) cout << "bin " << bin-1 << endl;
      float stat = pow(m_fakeHistogram->GetBinError(bin),2);//stat err
      float err_up = 0; 
      float err_dn = 0;
      float bc = m_fakeHistogram->GetBinContent(bin);
      if(m_dbg) cout << "bc= " << bc << endl;
	
      for(unsigned int i=0; i < m_fakesystematicsList.size(); ++i) {	
	if(m_dbg) cout << "m_fakesystematicsList.at(i)= " << m_fakesystematicsList.at(i) << endl;
	TH1D    *fakesysHistograms[m_sampleList.size()];
	

	getHistograms(m_inputROOTFile, w_observable, w_cut, w_dataBlindCut, fakesysHistograms, m_fakesystematicsList.at(i), m_fakesampleList);

	float shift = fakesysHistograms[0]->GetBinContent(bin);
	if(m_dbg) cout << "shift= " << shift << endl;
	if(shift > bc) err_up += pow(shift-bc,2);
	else           err_dn += pow(shift-bc,2);
	if(m_dbg) cout << "err_up= " << sqrt(err_up) << " err_dn= " << sqrt(err_dn) << endl;
	fake_histo_up->SetBinContent(bin, sqrt(err_up));
	fake_histo_dn->SetBinContent(bin, sqrt(err_dn));
	
      }
    }
    
    fake_histo_up->Add(m_fakeHistogram);
    
    TH1D* _htmp = (TH1D*) m_fakeHistogram->Clone();
    _htmp->Add(fake_histo_dn,-1);
    fake_histo_dn->Reset();
    fake_histo_dn->Add(_htmp); 
    _htmp->Delete();
    w_fakeUpDnHistograms[0] = fake_histo_up;
    w_fakeUpDnHistograms[1] = fake_histo_dn;
    
    //if no fake sys given, reset the fake sys histos :
//     if(!m_fakesystematicsList.size()>0){
//       w_fakeUpDnHistograms[0] = m_fakeHistogram;
//       w_fakeUpDnHistograms[1] = m_fakeHistogram;
//     }
    if(m_dbg) cout << "fake_histo_up->Integral()= " << fake_histo_up->Integral() << endl;
    if(m_dbg) cout << "fake_histo_dn->Integral()= " << fake_histo_dn->Integral() << endl;

      

  }
