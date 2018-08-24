#include <iostream>
int ana_AC_root(){

  //gStyle->SetOptLogy(1);

  // ======= TTree ============//
  TFile *fin = new TFile("rootfiles/ac2_ch1.root","read");
  TTree *tin=(TTree*)fin->Get("tree");
  double AC_npe_sum;
  tin->SetBranchAddress("AC_npe_sum",&AC_npe_sum); 
  const int n = tin->GetEntries();
  //  cout<<"bin number is "<<n<<endl;
  
  //=== TCUT Defined ================= //

  //  TCut cut_adc = "trig_adc_b[1]>1000 && AC_adc_b>800.";
  TCut cut_adc = "AC_npe_b>1. && AC_npe_t>1.";

  //============================= //

int bin;
    double xmax,xmin;
  bin=600;
  xmin=-10.;
  xmax=50.;
  TH1F *hist =new TH1F("hist","hist",bin,xmin,xmax);
  TH1F *hist_cut=new TH1F("hist_cut","hist_cut",bin,xmin,xmax);
  TH1F *hist_sum=new TH1F("hist_sum","hist_sum",bin,xmin,xmax);
  tin->Project("hist_cut","AC_npe_sum",cut_adc);
  tin->Project("hist_sum","AC_npe_sum");
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



  for(int j=0;j<num;j++){
    th[j]=j;
    rate[j]=0;
    num_th[j]=0;
    num_tot[j]=0;
  
  for(int i=0;i<n;i++){
   tin->GetEntry(i);
     hist->Fill(AC_npe_sum);
     num_tot[j]=num_tot[j]+1;
    if(AC_npe_sum>=th[j]){
         num_th[j]=num_th[j]+1;
     }
  
}
  yth=num_th[j];
  ytot=num_tot[j];
 rate[j]=yth/ytot;
  

  }

  
  TCanvas *c1=new TCanvas("c1","c1");
  c1->Divide(1,3);
  c1->cd(1);
   TGraph *gth = new TGraph(num,th,rate);
    gth->GetXaxis()->SetRangeUser(0,30);
    gth->Draw();
    c1->cd(2);

    hist->Draw();

    //========= Fit NPE histgram ========== //

    // TF1 *fnpe=new TF1("fnpe","gaus",xmin,xmax);
    hist->Fit("gaus","","",0.,30.);
   
    c1->cd(3);
    hist_cut->Draw();
    hist_sum->Draw("same");
    hist_cut->Fit("gaus","","",0.,30.);
    hist_sum->Fit("gaus","","",0.,30.);

    //===== Integral of Hist ==========//
    
    int nxbin,xminbin,xmaxbin,nxbin_cut,xminbin_cut,xmaxbin_cut,xminbin_sum,xmaxbin_sum;
    nxbin=hist->GetXaxis()->GetNbins();
     xminbin=hist->GetXaxis()->GetXmin();
    //  xminbin= hist->FindBin(0);
    xmaxbin=hist->GetXaxis()->GetXmax();

    /*
    nxbin_cut=hist_cut->GetXaxis()->GetNbins();
    xminbin_cut=hist_cut->GetXaxis()->GetXmin();
    xmaxbin_cut=hist_cut->GetXaxis()->GetXmax();

    // nxbin_cut=hist_cut->GetXaxis()->GetNbins();
    xminbin_sum=hist_sum->GetXaxis()->GetXmin();
    xmaxbin_sum=hist_sum->GetXaxis()->GetXmax();

    double xcut_min,xcut_max,xsum_min,xsum_max;
    xcut_min=hist_cut->GetXminimum();
    xcut_max=hist_cut->GetXmaximum();
    xsum_min=hist_sum->GetMinimum();
    xsum_max=hist_sum->GetXmaximum();
    cout<<"xminbin_cut is "<<xminbin_cut<<endl;
    cout<<"xmaxbin_cut is "<<xminbin_cut<<endl;
    cout<<"xmin_cut is "<<xcut_min<<endl;
    cout<<"xmax_cut is "<<xcut_max<<endl;


    cout<<"xminbin_sum is "<<xminbin_sum<<endl;
    cout<<"xmaxbin_sum is "<<xminbin_sum<<endl;
    */


    double inte,inte_cut,inte_sum;
    inte= hist->Integral(xminbin,xmaxbin);
    inte_cut=hist_cut->Integral(xminbin_cut,xmaxbin_cut);
    inte_sum=hist_sum->Integral(xminbin_sum,xmaxbin_sum);
    double inte_err,inte_cut_err,inte_tot_err,inte_sum_err;
    inte_err=sqrt(inte);
    inte_cut_err=sqrt(inte_cut);
    inte_sum_err=sqrt(inte_sum);
    // inte_tot_err=1./inte_err+1./inte_cut_err;
   inte_tot_err=1./inte_sum_err+1./inte_cut_err;
   cout<<"integral hist "<<inte<<endl;
    cout<<"integral hist_sum  "<<inte_sum<<endl;
    cout<<"integral hist_cut  "<<inte_cut<<endl;

    cout<<"integral hist error "<<inte_err<<endl;
    cout<<"integral hist_sum error "<<inte_sum_err<<endl;
    cout<<"integral hist_cut error "<<inte_cut_err<<endl;
    cout<<"integral total error "<<inte_tot_err<<endl;
     return 0;
}









