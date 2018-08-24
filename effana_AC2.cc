// HKS AC NPE Efficiency analysis macro Aug 2018 //
// Cosmic ray test June 2018 at ESB in JLab     //
 
#include <iostream>
int effana_AC2(){

  //gStyle->SetOptLogy(1);

  // ======= TTree ============//
  TFile *fin = new TFile("rootfiles/ac2_ch1.root","read");
  TTree *tin=(TTree*)fin->Get("tree");
  double AC_npe_sum;
  tin->SetBranchAddress("AC_npe_sum",&AC_npe_sum); 
  const int n = tin->GetEntries();
  

  //=================================== //
  //===== TCUT Defined ================= //
  //==================================== //
  TCut cut_ac = "AC_npe_t>1.0";
  //TCut cut_ac = "AC_npe_b>1.0";  
  //TCut cut_ac = "AC_npe_t>1.0 ||  AC_npe_b>1.0"; 
  //TCut cut_ac = "AC_npe_t>1.0 &&  AC_npe_b>1.0"; 

  //==== AC2 Ch1 Cut Condition ===========//
  TCut cut_trig = "trig_adc_t[1]>900 && trig_adc_t[0]>900. && trig_adc_b[0]>800. && trig_adc_b[1]>800. && trig_time_t[1]< 263.5 && trig_time_b[0]<262. && trig_time_b[1]>260. && trig_time_b[1]<262. ";
   //===== AC2 Ch2 Cut Condition ========== //
  TCut cut_trig2 ="trig_adc_t[0]<2000. && trig_adc_t[0]>800. && trig_adc_t[1]>900. && trig_adc_b[0]>700. && trig_adc_b[0]<1500. && trig_adc_b[1]>700. && trig_time_t[1]>261.5 &&trig_time_t[1]<263.5 && trig_time_b[0]>260.5 && trig_time_b[0]<262. && trig_time_b[1]>260. && trig_time_b[1]<262.";
 
  //===== AC2 Ch3 Cut Condition ========== //
  TCut cut_trig3="trig_adc_t[0]>850. && trig_adc_t[0]<1800. && trig_adc_t[1]>900. && trig_adc_b[0]>700. &&  trig_adc_b[0]<1500. && trig_adc_b[1]>800. && trig_time_t[1]>262. && trig_time_t[1]<263.5 && trig_time_b[0]>260. && trig_time_b[0]<262. && trig_time_b[1]>260. && trig_time_b[1]<262.0";
 
  //===== AC2 Ch4 Cut Condition ========== //
  TCut cut_trig4 = "trig_adc_b[0]>700. && trig_adc_b[1]>800. && trig_adc_t[0]>800. && trig_adc_t[1]>800. && trig_time_t[1]>262. && trig_time_t[1]<263.5 && trig_time_b[0]>260.5 && trig_time_b[0]<262. && trig_time_b[1]>260. && trig_time_b[1]<262.";
  
//====== AC2 ch5 Cut Condition ========== //
  TCut cut_trig5 ="trig_adc_t[0]>800. && trig_adc_t[0]<2000 && trig_adc_t[1]>800. && trig_adc_b[0]>700.  && trig_adc_b[1]>800. && trig_time_t[1]>261.5 && trig_time_t[1]<263.2 && trig_time_b[0]>260.5 && trig_time_b[0]<262.0 && trig_time_b[1]>260. && trig_time_b[1]<262.";
 
 //====== AC2 ch6 Cut Condition ========== //
  TCut cut_trig6 ="trig_adc_t[0]>800. && trig_adc_t[0]<2000 && trig_adc_t[1]>800. && trig_adc_t[1]<3000. && trig_adc_b[0]>700. && trig_adc_b[0]<2000. && trig_adc_b[1]<2000. && trig_adc_b[1]>800. && trig_time_t[1]>261.5 && trig_time_t[1]<263.5 && trig_time_b[0]<262. && trig_time_b[1]>260/5 && trig_time_b[1]>260. && trig_time_b[1]<262.0";

//====== AC2 ch7 Cut Condition ========== //
  TCut cut_trig7 ="trig_adc_t[0]<2000 && trig_adc_t[0]>800.  && trig_adc_t[1]<2500. && trig_adc_t[1]>800. && trig_adc_b[0]<2000. && trig_adc_b[0]>650. && trig_adc_b[1]<2000. && trig_adc_b[1]>800. && trig_time_t[1]>261.5 && trig_time_t[1]<263.5 && trig_time_b[0]>260. && trig_time_b[0]<262. && trig_time_b[1]>260. && trig_time_b[1]<262."; 
  

 int bin;
  double xmax,xmin;
  bin=600;
  xmin=-10.;
  xmax=50.;
  TH1F *hist =new TH1F("hist","hist",bin,xmin,xmax);
  TH1F *hist_cut=new TH1F("hist_cut","hist_cut",bin,xmin,xmax);
  TH1F *hist_sum=new TH1F("hist_sum","hist_sum",bin,xmin,xmax);
  TH1F *hist_ac=new TH1F("hist_ac","hist_ac",bin,xmin,xmax);
  TH1F *hist_ac_cut=new TH1F("hist_ac_cut","hist_ac",bin,xmin,xmax);
  tin->Project("hist_cut","AC_npe_sum",cut_trig);
  tin->Project("hist_sum","AC_npe_sum");
  tin->Project("hist_ac","AC_npe_sum", cut_ac);
  tin->Project("hist_ac_cut","AC_npe_sum",cut_trig && cut_ac);

  double rate[1000];
  double rate_err[1000];
  //====== Parameter Of Threshold ========= //
  double th[1000]; //Threshold 
  // th=0; 
  double sum_tot[1000],sum_th[1000];
  double ytot,yth;
  int num_th[1000],num_tot[1000],num;
  num=100;
  //===================================== //


  TCanvas *c0=new TCanvas("c0","c0");
  c0->Divide(2,2);
  c0->cd(1);
  hist->SetLineColor(0);
  hist_cut->SetLineColor(1);
  hist_ac->SetLineColor(2);
  hist_ac_cut->SetLineColor(3); 
  hist_sum->Draw();
  hist_cut->Draw("same");
  c0->cd(2);
  hist_ac->Draw();
  hist_ac_cut->Draw("same");
  c0->cd(3);
    hist_sum->Draw();
  hist_ac->Draw("same");
  c0->cd(4);
  hist_cut->Draw();
  hist_ac_cut->Draw("same");
  TCanvas *c1=new TCanvas("c1","c1");
  hist_cut->Draw();
  hist_ac_cut->Draw("same");
    //===== Integral of Hist ==========//
    
    int nxbin,xminbin,xmaxbin,nxbin_cut,xminbin_cut,xmaxbin_cut,xminbin_sum,xmaxbin_sum,xminbin_ac,xmaxbin_ac;
    nxbin=hist->GetXaxis()->GetNbins();
    xminbin=hist->GetXaxis()->FindBin(xmin);
    xmaxbin=hist->GetXaxis()->FindBin(xmax);

    double inte,inte_cut,inte_sum,inte_ac,inte_ac_cut;
    inte= hist->Integral(xminbin,xmaxbin);
    inte_cut=hist_cut->Integral(xminbin,xmaxbin);
    inte_sum=hist_sum->Integral(xminbin,xmaxbin);
    inte_ac=hist_ac->Integral(xminbin,xmaxbin);
    inte_ac_cut=hist_ac_cut->Integral(xminbin,xmaxbin);
    double inte_err,inte_cut_err,inte_tot_err,inte_sum_err,inte_ac_err,inte_ac_cut_err,inte_tot_cut_err;
    inte_err=sqrt(inte);
    inte_cut_err=sqrt(inte_cut);
    inte_sum_err=sqrt(inte_sum);
    inte_ac_err=sqrt(inte_ac);
    inte_ac_cut_err=sqrt(inte_ac_cut);
    inte_tot_cut_err=sqrt(pow(inte_ac_cut_err,2)+pow(inte_ac_cut/inte_cut*inte_cut_err,2))/inte_cut;

    inte_tot_err=sqrt(pow(inte_ac_err,2)+pow(inte_ac/inte_sum*inte_err,2))/inte_sum;


    //========================================//
    //=============== Coment out =============//
    //========================================//

    cout<<"integral hist_ac "<<inte_ac<<endl;
    cout<<"integral hist_sum  "<<inte_sum<<endl;
    cout<<"integral hist_cut  "<<inte_cut<<endl;
    cout<<"integral hist_ac_cut "<<inte_ac_cut<<endl;
    cout<<"NO cut efficiency is "<<inte_ac/inte_sum<<endl;
    cout<<"Cut efficiency is "<<inte_ac_cut/inte_cut<<endl;
    cout<<"integral hist_ac error "<<inte_ac_err<<endl;
    cout<<"integral hist_sum error "<<inte_sum_err<<endl;
    cout<<"integral hist_cut error "<<inte_cut_err<<endl;
    cout<<"integral total error "<<inte_tot_err<<endl;
    cout<<"integral total cut error "<<inte_tot_cut_err<<endl;
    
   return 0;
}









