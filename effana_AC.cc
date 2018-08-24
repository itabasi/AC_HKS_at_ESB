#include <iostream>
int effana_AC(){

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
  TCut cut_trig = "trig_adc_t[1]>900 && trig_adc_t[0]>900. && trig_adc_b[0]>800. && trig_adc_b[1]>800. && trig_time_t[1]< 263.5 && trig_time_b[0]<262. && trig_time_b[1]>260. && trig_time_b[1]<262. ";
 
 TCut cut_ac = "AC_npe_b>1.0 && AC_npe_t>1.0";
  //============================= //

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

  double y[10000],yac[10000];


  for(int k=0;k<bin+1;k++){



  }




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





  TCanvas *c0=new TCanvas("c0","c0");
  hist->SetLineColor(0);
  hist_cut->SetLineColor(1);
  hist_ac->SetLineColor(2);
  hist_ac_cut->SetLineColor(3); 
  hist_sum->Draw();
  hist_cut->Draw("same");
  hist_ac->Draw("same");
  hist_ac_cut->Draw("same");

  TCanvas *c1=new TCanvas("c1","c1");
// c1->Divide(1,3);
  /* c1->cd(1);
   TGraph *gth = new TGraph(num,th,rate);
    gth->GetXaxis()->SetRangeUser(0,30);
    gth->Draw();
  */    
//    c1->cd(2);
  hist_cut->Draw();
  hist_ac_cut->Draw("same");
 
  // hist->Draw();
    /*
    //========= Fit NPE histgram ========== //
   double inte_ph,inte_total;
 
     TF1 *fnpe=new TF1("fnpe","gaus",xmin,xmax);
     hist_sum->Fit("fnpe","","",xmin,xmax);
     TF1 *func_tot=hist_sum->GetFunction("fnpe");
     inte_total=func_tot->Integral(xmin,xmax);
   
    TF1 *fph=new TF1("fph","gaus",-5.,2.);
    hist_sum->Fit("fph","+","",-5.,2.);
    TF1 *func_ph =hist_sum->GetFunction("fph");
     inte_ph=func_ph->Integral(xmin,xmax);
    */
     /*
    cout<<"inte_ph is "<<inte_ph<<endl; 
    cout<<"inte_total is "<<inte_total<<endl;
    cout<<"efficiency is "<<(inte_total-inte_ph)/inte_total<<endl;
     */
    /*
    c1->cd(3);
    hist_cut->Draw();
    hist_sum->Draw("same");
    hist_cut->Fit("gaus","","",0.,30.);
    hist_sum->Fit("gaus","","",0.,30.);
    */

    //===== Integral of Hist ==========//
    
    int nxbin,xminbin,xmaxbin,nxbin_cut,xminbin_cut,xmaxbin_cut,xminbin_sum,xmaxbin_sum,xminbin_ac,xmaxbin_ac;
    nxbin=hist->GetXaxis()->GetNbins();
    xminbin=hist->GetXaxis()->FindBin(xmin);
    xmaxbin=hist->GetXaxis()->FindBin(xmax);
    /*
    xminbin_cut=hist_cut->GetXaxis()->GetXmin();
    xmaxbin_cut=hist_cut->GetXaxis()->GetXmax();
    xminbin_sum=hist_sum->GetXaxis()->GetXmin();
    xmaxbin_sum=hist_sum->GetXaxis()->GetXmax();
    xminbin_ac=hist_ac->GetXaxis()->GetXmin();
    xmaxbin_ac=hist_ac->GetXaxis()->GetXmax();
    */

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
    inte_tot_cut_err=1./inte_ac_cut_err+1./inte_cut_err;
    inte_tot_err=1./inte_ac_err+1./inte_err;
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
    
    
   return 0;
}









