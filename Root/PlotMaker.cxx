//////////////////////////////////////////////////////////////////////////////////////////
// \project:    ATLAS Experiment at CERN's LHC
// \package:    TwoLeptonEWKPlotter
// \class:      PlotMaker
// \file:       $Id: PlotMaker.cxx 91354 2013-05-22 12:48:03Z amete $
// \author:     Alaettin.Serhan.Mete@cern.ch
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
  for(unsigned int i=0; i<m_systematicsList.size(); ++i) {                          
    cout << m_systematicsList.at(i) << " ";
  }
  cout << endl;
  
  cout << "PlotMaker::INFO   Included signal : ";
  for(unsigned int i=0; i<m_signalList.size(); ++i) {                          
    cout << m_signalList.at(i) << " ";
  }
  cout << endl;

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

  // Append Channel to the Cut
//   if(channel.EqualTo("ee"))
//     cut.Append("&&isEE");
//   else if(channel.EqualTo("em"))
//     cut.Append("&&isEMU");
//   else if(channel.EqualTo("mm"))
//     cut.Append("&&isMUMU");
//   else if(!channel.EqualTo("all")) {
//     cerr << "PlotMaker::ERROR   Unknown channel " << channel << endl;
//     return;
//   }

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
  
  // Build the legend
  TLegend* legend        = new TLegend(0.7,0.6,0.9,0.9);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  // Get signal histograms
  TH1D    *histograms_signal[m_signalList.size()];
  getHistograms(m_signalROOTFile, observable, cut, histograms_signal,"CENTRAL", m_signalList);
  
  //set style for signal sample(s)
  for(unsigned int i=0; i<m_signalList.size(); ++i) {
    histograms_signal[i]->SetLineWidth(2);
    histograms_signal[i]->SetLineColor(kPink+7);
    histograms_signal[i]->SetLineStyle(5);
    legend->AddEntry(histograms_signal[i],SampleNames["signal1"],"l");
//     cout << " content for " << m_signalList.at(i) << " = " << histograms_signal[i]->Integral() << endl;  
  }
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////
  
  // Get the central histograms 
  TH1D    *histograms[m_sampleList.size()];
  getHistograms(m_inputROOTFile, observable, cut, histograms,"CENTRAL", m_sampleList);
  
  

  // Massage the Data and add MC to SM stack 
  TGraphAsymmErrors *Data = new TGraphAsymmErrors();
  THStack *stackBg        = new THStack("stackBg","Standard Model");
  THStack *stackMCBg        = new THStack("stackMCBg","MC Standard Model");
  int      dataIndex      = -1; 
  int 	   FakesIndex     = -1;

  for(unsigned int i=0; i<m_sampleList.size(); ++i) {
    // Add to stack if background
    if(m_sampleList.at(i) == "Fakes") FakesIndex = i;
    
    if(m_sampleList.at(i)!="Data"){
      stackBg->Add(histograms[i]);
      if(m_sampleList.at(i)!="Fakes") stackMCBg->Add(histograms[i]);
      cout << m_sampleList.at(i) << " NOMINAL= " << histograms[i]->Integral(0, -1) << endl;
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
//   cout << "MC stack content = " << ((TH1*)(stackBg->GetStack()->Last()))->Integral() << endl;
  

  




  // Add Data
  legend->AddEntry(Data,SampleNames["Data"],"p");

  // Add SM Background
  for(int i=m_sampleList.size()-1; i>-1 ; --i) {
    if(m_sampleList.at(i)!="Data")
      legend->AddEntry(histograms[i],SampleNames[m_sampleList.at(i)],"f");
  }
  

  

  ////////////////////////////////////////////////////////////////////////////////////////
  // HERE SHOULD COME THE SYSTEMATICS LOOP

  // Get Total MC Histo
  TH1D* stackHistoMCBg = (TH1D*) stackMCBg->GetStack()->Last();

  TGraphAsymmErrors* nominalAsymErrors = TH1TOTGraph(stackHistoMCBg);
  nominalAsymErrors->SetMarkerSize(0);
  nominalAsymErrors->SetLineWidth(2);
  nominalAsymErrors->SetFillStyle(3004);
  nominalAsymErrors->SetFillColor(kBlack);
  cout << "only statistical error on MC stackHistoMCBg (excl Fakes):" << endl;
  for(int bin=0; bin < nominalAsymErrors->GetN(); bin++){ 
    cout << "bin " << bin <<  " EYhigh()= " << nominalAsymErrors->GetEYhigh()[bin] << endl;
    cout << "bin " << bin <<  " EYlow()=  " << nominalAsymErrors->GetEYlow()[bin] << endl;
  }


  // Add SM Bkg. to the legend
  legend->AddEntry(nominalAsymErrors,"Bkg. Uncert.","f"); 

  // Loop over and add the Tree based systematics
  TH1D* totalSysHistoMcBg = (TH1D*) stackHistoMCBg->Clone();
  totalSysHistoMcBg->Reset();
  TH1D* totalSysHistoFakes = (TH1D*) stackHistoMCBg->Clone();
  totalSysHistoFakes->Reset();
//   totalSysHistoMcBg == NULL;
//   if(totalSysHistoMcBg==NULL) cout << "totalSysHistoMcBg==NULL" << endl;
  TGraphAsymmErrors* transientMcBg; 
  TGraphAsymmErrors* transientFakes; 

  cout << "histograms[FakesIndex]->Integral()= " << histograms[FakesIndex]->Integral() << endl;
  TGraphAsymmErrors*  AsymmErrorsFake = TH1TOTGraph(histograms[FakesIndex]);
  cout << "only statistical error on Fakes:" << endl;
    for(int bin=0; bin < AsymmErrorsFake->GetN(); bin++){ 
    cout << "bin " << bin <<  " EYhigh()= " << AsymmErrorsFake->GetEYhigh()[bin] << endl;
    cout << "bin " << bin <<  " EYlow()=  " << AsymmErrorsFake->GetEYlow()[bin] << endl;
  }
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;

  TH1D    *sysHistograms[m_sampleList.size()];
  int McBgIndex = -1;
  for(unsigned int i=0; i < m_systematicsList.size(); ++i) {
    cout << m_systematicsList.at(i) << endl;

    // Retrieve the histograms
    getHistograms(m_inputROOTFile, observable, cut, sysHistograms, m_systematicsList.at(i), m_sampleList);

    // Loop over samples and add to total systematics histo
    for(unsigned int j=0; j < m_sampleList.size(); ++j) {
      

      if(m_sampleList.at(j) != "Fakes"){
// 	cout << "! Fakes" << endl;
	if(sysHistograms[j]!=NULL){
	  cout << m_sampleList.at(j) << " sys Integral " << sysHistograms[j]->Integral(0,-1) << endl;
	  totalSysHistoMcBg->Add(sysHistograms[j]);
	  McBgIndex = j;
// 	  cout << "added to totalSysHistoMcBg" << endl;	  
	}
	else if ( m_sampleList.at(j) != "Data") {
	  cout << "PlotMaker::WARNING   Cannot find TTree for systematics " << 
		  m_systematicsList.at(i) << " for sample " << m_sampleList.at(j)  << endl;
	}
      }
    }


    // Add to the band:
    
    //All MC BG (correlated-> use TH1D, linear) SYS (uncorrelated -> use myAddtoBand(), squared)
    if(McBgIndex>=0){
      transientMcBg = TH1TOTGraph(totalSysHistoMcBg);
      cout << "myAddtoBand for McBg:" << endl;
      myAddtoBand(transientMcBg,nominalAsymErrors);
      totalSysHistoMcBg->Reset();
      McBgIndex = -1;
    }

    //All Fake SYS (uncorrelated -> use myAddtoBand(), squared)
    if(FakesIndex>=0 && sysHistograms[FakesIndex]!=NULL){

      totalSysHistoFakes = sysHistograms[FakesIndex];
//       cout << "Fakes sys Integral " << sysHistograms[FakesIndex]->Integral(0,-1) << endl;
//       cout << "AsymmErrorsFake->Integral()= " << AsymmErrorsFake->Integral() << endl;
      transientFakes = TH1TOTGraph(totalSysHistoFakes);
      cout << "myAddtoBand for Fakes:" << endl;
      myAddtoBand(transientFakes,AsymmErrorsFake);     
//       FakesIndex = -1;
      totalSysHistoFakes->Reset();
    }
//     cout << m_systematicsList.at(i) << " Integral= "  << totalSysHistoMcBg->Integral() << endl;

  }
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "add MCbg and fakes errors:" << endl;
  myTGraphErrorsAdd(nominalAsymErrors,AsymmErrorsFake);



  ////////////////////////////////////////////////////////////////////////////////////////
  // Draw the canvas
  TCanvas* canvas = new TCanvas("canvas","canvas",500,500);
  TPad*    topPad = new TPad("pTop","pTop",0,0.2,1,1);
  TPad*    botPad = new TPad("pBot","pBot",0,0.0,1,0.3);
  topPad->Draw();
  botPad->Draw();

  // Top Pad
  topPad               ->cd();
  topPad               ->SetBottomMargin(0.15);
  histograms[dataIndex]->Draw("p");
//   cout << "data content= " << histograms[dataIndex]->Integral() << endl;
  stackBg              ->Draw("hists same");
  nominalAsymErrors    ->Draw("same && E2");
  Data                 ->Draw("same && p");
  histograms_signal[0]->Draw("hists same");
  legend               ->Draw();

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
  else if( variable.EqualTo("metRel") ) {
    xlabel = "E_{T}^{miss,rel} [GeV]";
  }
  else if( variable.EqualTo("mtmax") ) {
    xlabel = "max(m_{T}(l0), m_{T}(l1)) [GeV]";
  }
  else if( variable.EqualTo("ptl1") ) {
    xlabel = "p_{T,l1} [GeV]";
  }
  else if( variable.EqualTo("mWWT") ) {
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
  histograms[dataIndex]->GetXaxis()->SetLabelSize(0.03);
  histograms[dataIndex]->GetYaxis()->SetTitle(ylabel); 
//   histograms[dataIndex]->GetYaxis()->SetRangeUser(2.e-2,1000*pow(10,ceil(log(histograms[dataIndex]->GetMaximum())/log(10))));
    histograms[dataIndex]->GetYaxis()->SetRangeUser(2.e-2,histograms[dataIndex]->GetMaximum()*10);

  gPad->RedrawAxis();
//   gPad->SetLogy(1);

  // Decoration
  char annoyingLabel1[100] = "#bf{#it{ATLAS}} Internal", annoyingLabel2[100] = "#scale[0.6]{#int} L dt = 20.3 fb^{-1}  #sqrt{s} = 8 TeV";
  myText(0.20,0.88,kBlack,annoyingLabel1);
  myText(0.20,0.80,kBlack,annoyingLabel2);

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
  ratio_original->GetXaxis()->SetLabelSize(0.1);
  ratio_original->GetXaxis()->SetLabelOffset(0.02);
  ratio_original->GetXaxis()->SetTitleSize(0.12);
  ratio_original->GetXaxis()->SetTitleOffset(1.);
  ratio_original->GetYaxis()->SetRangeUser(0,2);
  ratio_original->GetYaxis()->SetLabelSize(0.1);
  ratio_original->GetYaxis()->SetTitleSize(0.12);
  ratio_original->GetYaxis()->SetTitleOffset(0.5);
  ratio_original->GetYaxis()->SetNdivisions(5);

  // Build the ratio's error band
  TGraphAsymmErrors* ratioBand   = new TGraphAsymmErrors( *nominalAsymErrors ); 
  buildRatioErrorBand(nominalAsymErrors,ratioBand);

  // Get the ratio
  // For Data/MC only use the statistical error for data
  // because we explicitly draw the MC error band
  TGraphAsymmErrors* nominalAsymErrorsNoError = new TGraphAsymmErrors( *nominalAsymErrors );
  for(int i=1; i<=nominalAsymErrorsNoError->GetN(); ++i) {
    nominalAsymErrorsNoError->SetPointError(i-1,0,0,0,0);
  }
  TGraphAsymmErrors* ratio_raw = myTGraphErrorsDivide(Data,nominalAsymErrorsNoError);
  TGraphAsymmErrors* ratio     = new TGraphAsymmErrors();

  double x1=0; double y1=0; unsigned int newIndex = 0.;
  for(int kk=0; kk<ratio_raw->GetN(); ++kk){
    ratio_raw->GetPoint(kk, x1,y1);
    if(x1 > 0. && y1 > 0.) {
      ratio->SetPoint(newIndex, x1, y1);
      ratio->SetPointError(newIndex, ratio_raw->GetErrorXlow(kk), ratio_raw->GetErrorXhigh(kk), ratio_raw->GetErrorYlow(kk), ratio_raw->GetErrorYhigh(kk));
//       cout << "xlow " << ratio_raw->GetErrorXlow(kk) << " xhigh " <<  ratio_raw->GetErrorXhigh(kk) << " ylow " << ratio_raw->GetErrorYlow(kk) << " yhigh " <<  ratio_raw->GetErrorYhigh(kk) << endl;
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
  ratio         ->Draw("same && P");
  gPad          ->SetGridy(1);

  TString plotName = channel + "_" + region + "_" + variable + "_test.pdf" ;
  TString plotNameeps = channel + "_" + region + "_" + variable + "_test.eps" ;
  //plotName = dirOut + "/" + plotName;
  canvas->SaveAs(plotName);
  canvas->SaveAs(plotNameeps);

  // Delete unnecessary stuff to open up memory
  //delete[] histograms;
  //delete[] sysHistograms;
  delete Data;
  delete stackBg;
  delete nominalAsymErrors;
  delete nominalAsymErrorsNoError;
  delete ratioBand;
  delete ratio_original;
  delete ratio_raw;
  delete ratio;
  delete totalSysHistoMcBg;
  delete legend;
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
  for(int i=1; i<=histo->GetNbinsX(); i++){
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
void PlotMaker::getHistograms(TFile* input, TString varToPlot, TString cutToApply, TH1D* histos[], TString variation, vector<string> inputList)
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
//       cout << "Data, histos[i] set to NULL" << endl;
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
      if(inputList == m_sampleList){      
	//MC BACKGROUND
	if(inputList.at(i) != "Fakes" ){
	  if(variation.EqualTo("CENTRAL")){
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += "CENTRAL";
	  }
	  if(variation.Contains("ELFR") || variation.Contains("ELRE") || variation.Contains("MUFR") || variation.Contains("MURE")){
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += "CENTRAL";
	  }
	  else{
	    treeName.Form("%s_",inputList.at(i).c_str()); 
	    treeName += variation;
	  }
// 	  cout << "MC background " << inputList.at(i) << " treeName= " << treeName << endl;
	}
	//FAKE BACKGROUND
	if(inputList.at(i) == "Fakes"){
	  if(variation.EqualTo("CENTRAL")){
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
	  cout << "Fake background " << inputList.at(i) << " treeName= " << treeName << endl;
	}
      }
      //SIGNAL
      else{
	treeName = ""; treeName.Form("SSWH8TeV_%s_",m_signalList.at(i).c_str()); treeName += variation;
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
     
//       sys weights:

// syst_BKGMETHODUP
// syst_BKGMETHODDOWN
// syst_ETRIGREWUP
// syst_ETRIGREWDOWN 
// syst_MTRIGREWUP
// syst_MTRIGREWDOWN 
// syst_BJETUP
// syst_BJETDOWN 
// syst_XSUP
// syst_XSDOWN
      
    //use eventweight for nominal (CENTRAL) and most sytematic variations.
    TString weight = "eventweight";
    
    if(inputList.at(i) == "Data"){
      if(cutToApply.Contains("L2nCentralLightJets==2")==1){
	if(m_converToGeV)
	  tree->Draw( varToPlot + "/1000.>>temp" , weight + cutToApply + "&&  mljj>120000.");
	else
	  tree->Draw( varToPlot + ">>temp"       , weight + cutToApply + "&& mljj>120000.");
      }
      else{
      if(m_converToGeV)
	tree->Draw( varToPlot + "/1000.>>temp" , weight + cutToApply );
      else
	tree->Draw( varToPlot + ">>temp"       , weight + cutToApply + "&& Ht<200000.");
      }
    }
    else{
      if(m_converToGeV)
	tree->Draw( varToPlot + "/1000.>>temp" , weight + cutToApply );
      else
	tree->Draw( varToPlot + ">>temp"       , weight + cutToApply);
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
void PlotMaker::buildRatioErrorBand(TGraphAsymmErrors* input, TGraphAsymmErrors* output) 
{
  output->SetMarkerSize(0);
  for(int bin=0; bin < output->GetN(); bin++){ 
    output->GetY()[bin] = 1.; 
    cout << "EYhigh= " << input->GetEYhigh()[bin] << " / " << input->GetY()[bin] << endl; 
    if( input->GetY()[bin] > 0.0001 ) {
      
      output->GetEYhigh()[bin]=input->GetEYhigh()[bin]/input->GetY()[bin]; 
    }
   else 
      output->GetEYhigh()[bin]= 0.; 
   cout << "EYlow=  " << input->GetEYlow()[bin] << " / " << input->GetY()[bin] << endl;
   if( input->GetY()[bin] > 0.0001 ){ 
     
      output->GetEYlow()[bin]=input->GetEYlow()[bin]/input->GetY()[bin]; 
   }
   else 
      output->GetEYlow()[bin]= 0.; 
//    if( output->GetEYlow()[bin] > 1. ) 
//      output->GetEYlow()[bin] = 1.; 
//    if( output->GetEYhigh()[bin] > 1. ) 
//      output->GetEYhigh()[bin] = 1.; 
  }
}
