#include "TRandom3.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"


void SetRatioErr(TH1F*TotalBkg, TH1F*Pred, TGraphAsymmErrors &Closure,
                 int nBins = 4 , double lowerBound = 100. , double upperBound = 900.){
    double binWidth = (upperBound-lowerBound)/nBins;
    TRandom3 rand;
    TH1F*hratio=new TH1F("hratio", "", 100,0.0, 3.);
    TH2F* kappaDist = new TH2F("kappaDist","kappaDist",nBins,lowerBound,upperBound,1000,0.,5.);
    kappaDist->Reset();
    for( int m=1; m<=nBins; ++m){
        for(int i=0; i<1000; ++i){
            float num=rand.Gaus(TotalBkg->GetBinContent(m),TotalBkg->GetBinError(m));
            float den=rand.Gaus(Pred->GetBinContent(m),Pred->GetBinError(m));
            if(TotalBkg->GetBinError(m)<0.00001 && TotalBkg->GetBinContent(m)<0.0001){
                num=1.0;
                den=rand.Gaus(Pred->GetBinContent(m),Pred->GetBinError(m));
                den=1.0+den;
            }
            if(TotalBkg->GetBinCenter(m)<upperBound)kappaDist->Fill(TotalBkg->GetBinCenter(m),num/den);
            else kappaDist->Fill(upperBound-1.,num/den);
        }
        TH1D*METBinKappa=(TH1D*)kappaDist->QuantilesX(0.5, "METBinKappa");
        TH1D*METBinKappaUncUp=(TH1D*)kappaDist->QuantilesX(0.5+0.34, "METBinKappaUnc");
        TH1D*METBinKappaUncDn=(TH1D*)kappaDist->QuantilesX(0.5-0.34, "METBinKappaUnc");
        float RatioErrorUp=fabs(METBinKappaUncUp->GetBinContent(m)-METBinKappa->GetBinContent(m));
        float RatioErrorDn=METBinKappa->GetBinContent(m)-METBinKappaUncDn->GetBinContent(m);
        Closure.SetPoint(m-1, TotalBkg->GetBinCenter(m), METBinKappa->GetBinContent(m));
        Closure.SetPointError(m-1, binWidth/2., binWidth/2., RatioErrorDn,RatioErrorUp);
        if(m==4) Closure.SetPointError(m-1, binWidth/2.,binWidth/2., RatioErrorDn,RatioErrorUp);
        std::cout<<"Mean: "<<METBinKappa->GetBinContent(m)<<" +/- "<< RatioErrorUp<<std::endl;
    }

}