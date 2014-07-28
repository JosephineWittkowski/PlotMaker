#ifndef REGIONCUTS_H
#define REGIONCUTS_H

#include <map>
#include "boost/assign.hpp"
#include "TString.h"
#include "Rtypes.h"

using namespace std;

typedef map<TString, TString> TS2TSMap;
typedef map<TString, int>     ColorMap;

/// \brief Region Cut Definitions
TS2TSMap RegionCuts = boost::assign::map_list_of 
("SR_EE_play"  , "*(isEE)") 

("SR_EE_1j"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>=30000. && lept2Pt>=20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>=55000. && mlj<=90000. && Ht>=200000.)")

("SR_EE_1jNOmlj"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht>200000.)")

("SR_EE_1jmlj"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht>200000. && mlj>=90000.)")

("SR_EE_1jNOHt"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>=30000. && lept2Pt>=20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>=55000. && mlj<=90000.)")

("SR_EE_1jNOmljNOHt"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000.)")

("SR_EE_1jNOmljHt"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht<=200000. )")

("SR_EE_1jVR0"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)))")

("SR_EE_1jVR1"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1)")

("SR_EE_1jVR1lept1Pt"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt<=30000.)")

("SR_EE_1jVR1lept2Pt"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept2Pt<=20000.)")

("SR_EE_1jVR0mlj"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && mlj>=90000.)")

("SR_EE_1jVR0Ht"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && Ht<=200000.)")

("SR_EE_1jVR0metRel"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel<=55000.)")

("SR_EE_23j"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mljj<120000. && mtmax>110000.)")

("SR_EE_23jmljj"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mljj>=120000. && mtmax>110000.)")

("SR_EE_23jNOmljj"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mtmax>110000.)")

("SR_EE_23jNOmtmax"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mljj<120000. )")

("SR_EE_23jNOmljjmtmax"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mtmax<=110000.)")

("SR_EE_23jNOmljjNOmtmax"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000.)")

("SR_EE_23jVR0"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)))")

("SR_EE_23jVR1"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3))")

("SR_EE_23jVR1lept1Pt"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt<=30000.)")

("SR_EE_23jVR1lept2Pt"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept2Pt<=20000.)")

("SR_EE_23jVR0mljj"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && mljj>=120000.)")

("SR_EE_23jVR0mtmax"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && mtmax<=110000.)")

("SR_EE_23jVR0metRel"    , "*((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel<=30000.)")

("SR_EE_"    , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && mlj<90000. && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mljj<120000. && mtmax>110000.))")

("SR_EE_mtmax"    , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mtmax>110000.))")

("SR_EE_Ht"    , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000.))")

("SR_EE_METrel"    , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000.) || ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000.))")

("SR_EE_leptPt"    , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.))) || ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.))))")

("SR_EE_ZVeto"    , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.))) || ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.))))")

("SR_EE_Njets"    , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1) || ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3)))")

("SR_MM_1j"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mlj<90000. && Ht>200000. && mtmax>110000.)")

("SR_MM_1jmlj"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000. && mlj>=90000.)")

("SR_MM_1jNOmlj"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.)")

("SR_MM_1jNOHt"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mlj<90000. && mtmax>110000.)")

("SR_MM_1jNOmljHt"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht<=200000. && mtmax>110000.)")

("SR_MM_1jNOmljNOHt"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mtmax>110000.)")

("SR_MM_1jtest"     , "*(1)")

("SR_MM_1jVR0"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. )")

("SR_MM_1jVR1"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 )")

("SR_MM_1jVR1lept1Pt"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt<=30000 )")

("SR_MM_1jVR1lept2Pt"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept2Pt<=20000 )")

("SR_MM_1jVR0mlj"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && mlj>=90000.)")

("SR_MM_1jVR0Ht"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && Ht<=200000.)")

("SR_MM_1jVR0deltaEtaLl"     , "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl>=1.5 || deltaEtaLl<=-1.5) )")

("SR_MM_23j", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mljj<120000. && Ht>200000.)")

("SR_MM_23jmljj", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mljj>=120000. && Ht>200000.)")

("SR_MM_23jNOmljj", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.  && eventNumber!=451609)")

("SR_MM_23jNOHt", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mljj<120000. )")

("SR_MM_23jNOmljjHt", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht<=200000.)")

("SR_MM_23jNOmljjNOHt", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5))")

("SR_MM_23jVR0", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && eventNumber!=451609)")

("SR_MM_23jVR1", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3))")

("SR_MM_23jVR1lept1Pt", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt<=30000)")

("SR_MM_23jVR1lept2Pt", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept2Pt<=30000)")

("SR_MM_23jVR0mljj", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && mljj>=120000)")

("SR_MM_23jVR0Ht", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000.  && Ht<=200000.)")

("SR_MM_23jVR0deltaEtaLl", "*((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl>=1.5 || deltaEtaLl<=-1.5))")

("SR_MM_"     , "*(((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mlj<90000. && Ht>200000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mljj<120000. && Ht>200000.) )")

("SR_MM_mtmax"     , "*(((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.) )")

("SR_MM_Ht"     , "*(((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.) )")

("SR_MM_deltaEtaLl"     , "*(((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5)) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5)) )")

("SR_MM_leptPt"     , "*(((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000.) )")

("SR_MM_Njets"     , "*(((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 ) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3)) )")

("SR_EM_1j", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mlj<90000. && Ht>200000. && mtmax>110000.)")

("SR_EM_1jmlj", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mlj>=90000. && Ht>200000. && mtmax>110000.)")

("SR_EM_1jNOmlj", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.)")

("SR_EM_1jNOmtmax", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mlj<90000. && Ht>200000.)")

("SR_EM_1jNOmljmtmax", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax<=110000.)")

("SR_EM_1jNOmljNOmtmax", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.)")

("SR_EM_1jVR0", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. )")

("SR_EM_1jVR1", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1)")
("SR_EM_1jVR1lept1Pt", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt<=30000.)")
("SR_EM_1jVR1letp2Pt", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept2Pt<=30000.)")

("SR_EM_1jVR0mlj", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && mlj>=90000.)")

("SR_EM_1jVR0mtmax", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && mtmax<=110000.)")

("SR_EM_1jVR0deltaEtaLl", "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl>=1.5 || deltaEtaLl<=-1.5))")

("SR_EM_23j"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mljj<120000. && Ht>200000. && mtmax>110000.)")

("SR_EM_23jmljj"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000. && mljj>=120000.)")

("SR_EM_23jNOmljj"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.)")

("SR_EM_23jNOmtmax"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mljj<120000. && Ht>200000.)")

("SR_EM_23jNOmljjmtmax"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax<=110000.)")


("SR_EM_23jNOmljjNOmtmax"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.)")

("SR_EM_23jVR0"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000.)")

("SR_EM_23jVR1"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3))")

("SR_EM_23jVR1lept1Pt"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt<=30000.)")

("SR_EM_23jVR1letp2Pt"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept2Pt<=30000.)")

("SR_EM_23jVR0mljj"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && mljj>=120000.)")

("SR_EM_23jVR0mtmax"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && mtmax<=110000.)")

("SR_EM_23jVR0deltaEtaLl"      , "*((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl>=1.5 || deltaEtaLl<=-1.5))")


("SR_EM_", "*(((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mlj<90000. && Ht>200000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mljj<120000. && Ht>200000. && mtmax>110000.))")

("SR_EM_mtmax", "*(((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.))")

("SR_EM_Ht", "*(((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.))")

("SR_EM_deltaEtaLl", "*(((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5)) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5)))")

("SR_EM_leptPt", "*(((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. ))")

("SR_EM_Njets", "*(((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3)))")


("SR_1jNOmlj"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.) )")

("SR_1jNOmtmax"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht>200000. && mlj<90000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mlj<90000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mlj<90000.) )")

("SR_1jNOHt"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && mlj<90000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mtmax>110000. && mlj<90000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mtmax>110000. && mlj<90000.) )")

("SR_1jmlj"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) & L2METrel>55000. && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.) && mlj>=90000.)")

("SR_1jVR0"       , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)))   ||   ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. )   ||   ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000. )  )")

("SR_1jVR1"       , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1)   ||   ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 )   ||   ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1)  )")

("SR_1jVR1lept1Pt"       , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt<=30000.)   ||   ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt<=30000.)   ||   ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt<=30000.)  )")

("SR_1jVR1lept2Pt"       , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept2Pt<=30000.)   ||   ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept2Pt<=30000. )   ||   ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1&& lept2Pt<=30000. )  )")

("SR_1jVR0mlj"       , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.))  && mlj>=90000.)   ||   ((!isOS || L2qFlipWeight!=1.0) && isMUMU && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>20000.  && mlj>=90000.)   ||   ((!isOS || L2qFlipWeight!=1.0) && isEMU  && L2nCentralLightJets==1 && lept1Pt>30000. && lept2Pt>30000.  && mlj>=90000.)  )")


("SR_23jNOmljj"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.  && eventNumber!=451609) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.) ) ")

("SR_23jNOmtmax"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mljj<120000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.  && eventNumber!=451609    && mljj<120000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mljj<120000.) ) ")

("SR_23jNOHt"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mtmax>110000. && mljj<120000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && eventNumber!=451609 && mljj<120000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && mtmax>110000. && mljj<120000.) ) ")

("SR_23jmljj"      , "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && L2METrel>30000. && mtmax>110000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && (deltaEtaLl<1.5 && deltaEtaLl>-1.5) && Ht>200000. && mtmax>110000.)  && mljj>=120000.)")


("SR_23jVR0"	, "*(( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.))) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000.  && eventNumber!=451609) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000.)))")

("SR_23jVR1"	, "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3)) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3)) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3)) )")

("SR_23jVR1lept1Pt"	, "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt<=30000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt<=30000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt<=30000.) )")

("SR_23jVR1lept2Pt"	, "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept2Pt<=30000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept2Pt<=30000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept2Pt<=30000.) )")

("SR_23jVR0mljj"	, "*( ((!isOS || L2qFlipWeight!=1.0) && isEE   && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>20000. && !(L2Mll>(91200.-10000.) && L2Mll<(91200.+10000.)) && mljj>=120000.) || ((!isOS || L2qFlipWeight!=1.0) && isMUMU && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && mljj>=120000.) || ((!isOS || L2qFlipWeight!=1.0) && isEMU  && (L2nCentralLightJets==2 || L2nCentralLightJets==3) && lept1Pt>30000. && lept2Pt>30000. && mljj>=120000.) )")
;





/// \brief Sample Colors
ColorMap SampleColors = boost::assign::map_list_of ("Data"  , (int)kBlack    )
                                                   ("WW"  , (int)kRed+1    )
                                                   ("ZV"    , (int)kAzure+4  )
                                                   ("Zjets" , (int)kOrange-2 )
                                                   ("Top"    , (int)kSpring+1 )
                                                   ("Higgs" , (int)kYellow-9 )
						   ("SameSign" , (int)kAzure+4 )
						   ("ChargeFlip" , (int)kSpring+1 )
                                                   ("Fakes" , (int)kGray     );
// 						   ("130.0_0.0", (int)kPink+7);

/// \brief Sample Names
TS2TSMap SampleNames = boost::assign::map_list_of ("Data"  , "Data 2012"    )
                                                  ("Top"  , "t#bar{t} + Wt")
                                                  ("WW"    , "WW"           )
                                                  ("Zjets" , "Z+jets"       )
                                                  ("ZV"    , "ZV"           )
                                                  ("Higgs" , "Higgs"        )
                                                  ("Fakes" , "Fake leptons" )
						  ("SameSign" , "SameSign" )
						  ("ChargeFlip" , "ChargeFlip" )
						  ("signal1", "(m_{#tilde{#chi}_{2}^{0}},m_{#tilde{#chi}_{1}^{#pm}, #tilde{#chi}_{1}^{0}}) = (130,0) GeV");


/// \brief Define the variables
TS2TSMap VariableNames = boost::assign::map_list_of ("Ht"   , "Ht"         )
						    ("lept1Pt", "lept1Pt")
						    ("lept2Pt", "lept2Pt")
						    ("lept1Eta", "lept1Eta")
						    ("lept2Eta", "lept2Eta")						    
						    ("deltaEtaLl", "deltaEtaLl")
						    ("eventNumber", "eventNumber")
						    ("jet1Pt", "jet1Pt")
						    ("jet2Pt", "jet2Pt")
						    ("jet3Pt", "jet3Pt")
                                                    ("mtmax"   , "mtmax"       )
                                                    ("L2METrel", "L2METrel"    )
                                                    ("mtllmet"  , "mtllmet"     )
                                                    ("ptl2"  , "lept2Pt"     )
                                                    ("met"   , "MET"         )
                                                    ("ptll"  , "L2dileptonpt")
                                                    ("mlj", "mlj"    )
                                                    ("mljj"   , "mljj"       );

#endif
