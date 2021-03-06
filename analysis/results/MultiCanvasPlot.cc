void MultiCanvasPlot(){
	TFile* f_G4 = new TFile("VetoOn-6coll/G4spectrum2hits.root","READ");
	TH1F* hist_G4 = (TH1F*) f_G4->Get("S2hits");
	hist_G4->SetDirectory(0);
	f_G4->Close();
	
	TFile* f_Elena = new TFile("Elena/Histos_6coll_BKGsubt.root","READ");
	TH1F* hist_Elena = (TH1F*) f_Elena->Get("2hit_spectrum_tot");
	hist_Elena->SetDirectory(0);
	f_Elena->Close();
	
	
	hist_Elena->Rebin(8);
	hist_G4->Rebin(8);
	hist_Elena->SetLineColor(kRed);
	hist_G4->SetLineColor(kBlue);
	
	
	TCanvas* c1 = new TCanvas();
	c1->SetLogy();
	c1->SetTicks(1,1);
	hist_Elena->Draw("HISTE");
	hist_G4->Draw("SAMES");
	
	hist_Elena->GetXaxis()->SetRangeUser(0,2000);
	
	
	
	
	TPad *pad2 = new TPad("pad2","",0.12,0.11,0.62,0.61);
	pad2->SetFillStyle(4000); //will be transpare
	pad2->Draw();
	pad2->cd();
	gPad->SetLogy();
	gPad->SetTicks(1,1);
	TH1F *h1 = (TH1F*)hist_Elena->Clone("h1");
	TH1F *h2 = (TH1F*)hist_G4->Clone("h2");

	h1->GetXaxis()->SetRangeUser(0,100);
	h1->GetXaxis()->SetLabelSize(0.05);
	h1->GetYaxis()->SetLabelSize(0.05);
	h1->SetTitle("");
	h1->SetXTitle("");
	h1->SetYTitle("");
	h1->SetStats(kFALSE);

	h1->Draw("HISTE");
	h2->Draw("SAME");

}
