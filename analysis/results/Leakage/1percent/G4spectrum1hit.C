{
//=========Macro generated from canvas: G4spectrum1hit/G4spectrum1hit
//=========  (Tue Dec  3 16:24:46 2013) by ROOT version5.34/09
   TCanvas *G4spectrum1hit = new TCanvas("G4spectrum1hit", "G4spectrum1hit",11,36,700,500);
   G4spectrum1hit->SetHighLightColor(2);
   G4spectrum1hit->Range(0,0,1,1);
   G4spectrum1hit->SetFillColor(0);
   G4spectrum1hit->SetBorderMode(0);
   G4spectrum1hit->SetBorderSize(2);
   G4spectrum1hit->SetLogy();
   G4spectrum1hit->SetGridx();
   G4spectrum1hit->SetGridy();
   G4spectrum1hit->SetFrameBorderMode(0);
   
   TH1F *S1hit = new TH1F("S1hit","G4 spectrum, 1 hit events",120,0,120);
   S1hit->SetBinContent(18,1.0625);
   S1hit->SetBinContent(19,2.799342);
   S1hit->SetBinContent(20,2.148026);
   S1hit->SetBinContent(21,1.618421);
   S1hit->SetBinContent(22,1.226974);
   S1hit->SetBinContent(23,0.7861842);
   S1hit->SetBinContent(24,0.6052632);
   S1hit->SetBinContent(25,0.4342105);
   S1hit->SetBinContent(26,0.3881579);
   S1hit->SetBinContent(27,0.2138158);
   S1hit->SetBinContent(28,0.2039474);
   S1hit->SetBinContent(29,0.1907895);
   S1hit->SetBinContent(30,0.1907895);
   S1hit->SetBinContent(31,0.1447368);
   S1hit->SetBinContent(32,0.1907895);
   S1hit->SetBinContent(33,0.1776316);
   S1hit->SetBinContent(34,0.194079);
   S1hit->SetBinContent(35,0.2171053);
   S1hit->SetBinContent(36,0.2171053);
   S1hit->SetBinContent(37,0.3388158);
   S1hit->SetBinContent(38,0.3289474);
   S1hit->SetBinContent(39,0.4111842);
   S1hit->SetBinContent(40,0.4835526);
   S1hit->SetBinContent(41,0.4703947);
   S1hit->SetBinContent(42,0.5394737);
   S1hit->SetBinContent(43,0.5230263);
   S1hit->SetBinContent(44,0.7401316);
   S1hit->SetBinContent(45,0.7236842);
   S1hit->SetBinContent(46,0.8421053);
   S1hit->SetBinContent(47,0.9243421);
   S1hit->SetBinContent(48,0.9144737);
   S1hit->SetBinContent(49,1.075658);
   S1hit->SetBinContent(50,1.111842);
   S1hit->SetBinContent(51,1.161184);
   S1hit->SetBinContent(52,1.276316);
   S1hit->SetBinContent(53,1.230263);
   S1hit->SetBinContent(54,1.138158);
   S1hit->SetBinContent(55,1.378289);
   S1hit->SetBinContent(56,1.328947);
   S1hit->SetBinContent(57,1.266447);
   S1hit->SetBinContent(58,1.200658);
   S1hit->SetBinContent(59,1.236842);
   S1hit->SetBinContent(60,1.246711);
   S1hit->SetBinContent(61,1.220395);
   S1hit->SetBinContent(62,1.148026);
   S1hit->SetBinContent(63,0.9967105);
   S1hit->SetBinContent(64,1.003289);
   S1hit->SetBinContent(65,0.9868421);
   S1hit->SetBinContent(66,0.9703947);
   S1hit->SetBinContent(67,0.8092105);
   S1hit->SetBinContent(68,0.8355263);
   S1hit->SetBinContent(69,0.7269737);
   S1hit->SetBinContent(70,0.6217105);
   S1hit->SetBinContent(71,0.6940789);
   S1hit->SetBinContent(72,0.4473684);
   S1hit->SetBinContent(73,0.5131579);
   S1hit->SetBinContent(74,0.5);
   S1hit->SetBinContent(75,0.3782895);
   S1hit->SetBinContent(76,0.3848684);
   S1hit->SetBinContent(77,0.2664474);
   S1hit->SetBinContent(78,0.2993421);
   S1hit->SetBinContent(79,0.2993421);
   S1hit->SetBinContent(80,0.2269737);
   S1hit->SetBinContent(81,0.1611842);
   S1hit->SetBinContent(82,0.1644737);
   S1hit->SetBinContent(83,0.1907895);
   S1hit->SetBinContent(84,0.1052632);
   S1hit->SetBinContent(85,0.125);
   S1hit->SetBinContent(86,0.0625);
   S1hit->SetBinContent(87,0.03289474);
   S1hit->SetBinContent(88,0.06907894);
   S1hit->SetBinContent(89,0.03289474);
   S1hit->SetBinContent(90,0.02960526);
   S1hit->SetBinContent(91,0.03289474);
   S1hit->SetBinContent(92,0.02960526);
   S1hit->SetBinContent(93,0.009868421);
   S1hit->SetBinContent(94,0.02302632);
   S1hit->SetBinContent(95,0.01315789);
   S1hit->SetBinContent(96,0.01644737);
   S1hit->SetBinContent(97,0.009868421);
   S1hit->SetBinContent(98,0.009868421);
   S1hit->SetBinContent(99,0.006578947);
   S1hit->SetBinContent(100,0.006578947);
   S1hit->SetBinContent(102,0.006578947);
   S1hit->SetBinContent(107,0.003289474);
   S1hit->SetBinContent(108,0.003289474);
   S1hit->SetEntries(15010);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   S1hit->SetLineColor(ci);
   S1hit->GetXaxis()->SetTitle("Energy (keV)");
   S1hit->GetXaxis()->CenterTitle(true);
   S1hit->GetXaxis()->SetLabelFont(42);
   S1hit->GetXaxis()->SetLabelSize(0.035);
   S1hit->GetXaxis()->SetTitleSize(0.035);
   S1hit->GetXaxis()->SetTitleFont(42);
   S1hit->GetYaxis()->SetTitle("Events/bin/s");
   S1hit->GetYaxis()->CenterTitle(true);
   S1hit->GetYaxis()->SetLabelFont(42);
   S1hit->GetYaxis()->SetLabelSize(0.035);
   S1hit->GetYaxis()->SetTitleSize(0.035);
   S1hit->GetYaxis()->SetTitleFont(42);
   S1hit->GetZaxis()->SetLabelFont(42);
   S1hit->GetZaxis()->SetLabelSize(0.035);
   S1hit->GetZaxis()->SetTitleSize(0.035);
   S1hit->GetZaxis()->SetTitleFont(42);
   S1hit->Draw("");
   
   TH1F *S1hitsRing0 = new TH1F("S1hitsRing0","G4 spectrum ring 0, 1 hit events",120,0,120);
   S1hitsRing0->SetBinContent(18,0.9539474);
   S1hitsRing0->SetBinContent(19,2.608553);
   S1hitsRing0->SetBinContent(20,1.934211);
   S1hitsRing0->SetBinContent(21,1.473684);
   S1hitsRing0->SetBinContent(22,1.125);
   S1hitsRing0->SetBinContent(23,0.7171053);
   S1hitsRing0->SetBinContent(24,0.5361842);
   S1hitsRing0->SetBinContent(25,0.3782895);
   S1hitsRing0->SetBinContent(26,0.3223684);
   S1hitsRing0->SetBinContent(27,0.1578947);
   S1hitsRing0->SetBinContent(28,0.1677632);
   S1hitsRing0->SetBinContent(29,0.1381579);
   S1hitsRing0->SetBinContent(30,0.1480263);
   S1hitsRing0->SetBinContent(31,0.08552632);
   S1hitsRing0->SetBinContent(32,0.1381579);
   S1hitsRing0->SetBinContent(33,0.1151316);
   S1hitsRing0->SetBinContent(34,0.1447368);
   S1hitsRing0->SetBinContent(35,0.1381579);
   S1hitsRing0->SetBinContent(36,0.1348684);
   S1hitsRing0->SetBinContent(37,0.256579);
   S1hitsRing0->SetBinContent(38,0.1842105);
   S1hitsRing0->SetBinContent(39,0.2697369);
   S1hitsRing0->SetBinContent(40,0.3519737);
   S1hitsRing0->SetBinContent(41,0.3421053);
   S1hitsRing0->SetBinContent(42,0.3980263);
   S1hitsRing0->SetBinContent(43,0.3519737);
   S1hitsRing0->SetBinContent(44,0.5493421);
   S1hitsRing0->SetBinContent(45,0.5756579);
   S1hitsRing0->SetBinContent(46,0.6184211);
   S1hitsRing0->SetBinContent(47,0.6677632);
   S1hitsRing0->SetBinContent(48,0.6677632);
   S1hitsRing0->SetBinContent(49,0.8125);
   S1hitsRing0->SetBinContent(50,0.8157895);
   S1hitsRing0->SetBinContent(51,0.9046053);
   S1hitsRing0->SetBinContent(52,1.009868);
   S1hitsRing0->SetBinContent(53,0.9342105);
   S1hitsRing0->SetBinContent(54,0.8618421);
   S1hitsRing0->SetBinContent(55,1.128289);
   S1hitsRing0->SetBinContent(56,1.065789);
   S1hitsRing0->SetBinContent(57,0.9539474);
   S1hitsRing0->SetBinContent(58,0.9177632);
   S1hitsRing0->SetBinContent(59,0.9144737);
   S1hitsRing0->SetBinContent(60,1);
   S1hitsRing0->SetBinContent(61,0.9835526);
   S1hitsRing0->SetBinContent(62,0.9111842);
   S1hitsRing0->SetBinContent(63,0.7960526);
   S1hitsRing0->SetBinContent(64,0.7927632);
   S1hitsRing0->SetBinContent(65,0.7598684);
   S1hitsRing0->SetBinContent(66,0.7598684);
   S1hitsRing0->SetBinContent(67,0.6480263);
   S1hitsRing0->SetBinContent(68,0.7335526);
   S1hitsRing0->SetBinContent(69,0.5690789);
   S1hitsRing0->SetBinContent(70,0.4967105);
   S1hitsRing0->SetBinContent(71,0.5756579);
   S1hitsRing0->SetBinContent(72,0.3552631);
   S1hitsRing0->SetBinContent(73,0.430921);
   S1hitsRing0->SetBinContent(74,0.3914474);
   S1hitsRing0->SetBinContent(75,0.305921);
   S1hitsRing0->SetBinContent(76,0.3092105);
   S1hitsRing0->SetBinContent(77,0.2039474);
   S1hitsRing0->SetBinContent(78,0.2269737);
   S1hitsRing0->SetBinContent(79,0.2302632);
   S1hitsRing0->SetBinContent(80,0.194079);
   S1hitsRing0->SetBinContent(81,0.1381579);
   S1hitsRing0->SetBinContent(82,0.1381579);
   S1hitsRing0->SetBinContent(83,0.1578947);
   S1hitsRing0->SetBinContent(84,0.08552632);
   S1hitsRing0->SetBinContent(85,0.1052632);
   S1hitsRing0->SetBinContent(86,0.04605263);
   S1hitsRing0->SetBinContent(87,0.02960526);
   S1hitsRing0->SetBinContent(88,0.0625);
   S1hitsRing0->SetBinContent(89,0.02631579);
   S1hitsRing0->SetBinContent(90,0.02631579);
   S1hitsRing0->SetBinContent(91,0.02302632);
   S1hitsRing0->SetBinContent(92,0.01973684);
   S1hitsRing0->SetBinContent(93,0.009868421);
   S1hitsRing0->SetBinContent(94,0.01973684);
   S1hitsRing0->SetBinContent(95,0.01315789);
   S1hitsRing0->SetBinContent(96,0.01315789);
   S1hitsRing0->SetBinContent(97,0.003289474);
   S1hitsRing0->SetBinContent(98,0.009868421);
   S1hitsRing0->SetBinContent(99,0.006578947);
   S1hitsRing0->SetBinContent(100,0.006578947);
   S1hitsRing0->SetBinContent(102,0.006578947);
   S1hitsRing0->SetEntries(12036);

   ci = TColor::GetColor("#0000ff");
   S1hitsRing0->SetLineColor(ci);
   S1hitsRing0->GetXaxis()->SetTitle("Energy (keV)");
   S1hitsRing0->GetXaxis()->CenterTitle(true);
   S1hitsRing0->GetXaxis()->SetLabelFont(42);
   S1hitsRing0->GetXaxis()->SetLabelSize(0.035);
   S1hitsRing0->GetXaxis()->SetTitleSize(0.035);
   S1hitsRing0->GetXaxis()->SetTitleFont(42);
   S1hitsRing0->GetYaxis()->SetTitle("Events/bin/s");
   S1hitsRing0->GetYaxis()->CenterTitle(true);
   S1hitsRing0->GetYaxis()->SetLabelFont(42);
   S1hitsRing0->GetYaxis()->SetLabelSize(0.035);
   S1hitsRing0->GetYaxis()->SetTitleSize(0.035);
   S1hitsRing0->GetYaxis()->SetTitleFont(42);
   S1hitsRing0->GetZaxis()->SetLabelFont(42);
   S1hitsRing0->GetZaxis()->SetLabelSize(0.035);
   S1hitsRing0->GetZaxis()->SetTitleSize(0.035);
   S1hitsRing0->GetZaxis()->SetTitleFont(42);
   S1hitsRing0->Draw("sames");
   
   TH1F *S1hitsRing1 = new TH1F("S1hitsRing1","G4 spectrum ring 1, 1 hit events",120,0,120);
   S1hitsRing1->SetBinContent(18,0.01973684);
   S1hitsRing1->SetBinContent(19,0.01644737);
   S1hitsRing1->SetBinContent(20,0.009868421);
   S1hitsRing1->SetBinContent(21,0.009868421);
   S1hitsRing1->SetBinContent(22,0.009868421);
   S1hitsRing1->SetBinContent(23,0.006578947);
   S1hitsRing1->SetBinContent(24,0.003289474);
   S1hitsRing1->SetBinContent(25,0.006578947);
   S1hitsRing1->SetBinContent(27,0.003289474);
   S1hitsRing1->SetBinContent(29,0.006578947);
   S1hitsRing1->SetBinContent(30,0.006578947);
   S1hitsRing1->SetBinContent(33,0.006578947);
   S1hitsRing1->SetBinContent(35,0.003289474);
   S1hitsRing1->SetBinContent(36,0.003289474);
   S1hitsRing1->SetBinContent(37,0.003289474);
   S1hitsRing1->SetBinContent(38,0.003289474);
   S1hitsRing1->SetBinContent(39,0.009868421);
   S1hitsRing1->SetBinContent(40,0.009868421);
   S1hitsRing1->SetBinContent(41,0.01315789);
   S1hitsRing1->SetBinContent(42,0.009868421);
   S1hitsRing1->SetBinContent(43,0.02302632);
   S1hitsRing1->SetBinContent(44,0.01973684);
   S1hitsRing1->SetBinContent(45,0.003289474);
   S1hitsRing1->SetBinContent(46,0.02302632);
   S1hitsRing1->SetBinContent(47,0.01973684);
   S1hitsRing1->SetBinContent(48,0.01644737);
   S1hitsRing1->SetBinContent(49,0.04276316);
   S1hitsRing1->SetBinContent(50,0.02302632);
   S1hitsRing1->SetBinContent(51,0.03618421);
   S1hitsRing1->SetBinContent(52,0.02302632);
   S1hitsRing1->SetBinContent(53,0.01973684);
   S1hitsRing1->SetBinContent(54,0.03618421);
   S1hitsRing1->SetBinContent(55,0.02631579);
   S1hitsRing1->SetBinContent(56,0.01973684);
   S1hitsRing1->SetBinContent(57,0.02302632);
   S1hitsRing1->SetBinContent(58,0.01644737);
   S1hitsRing1->SetBinContent(59,0.02302632);
   S1hitsRing1->SetBinContent(60,0.02960526);
   S1hitsRing1->SetBinContent(61,0.01973684);
   S1hitsRing1->SetBinContent(62,0.01644737);
   S1hitsRing1->SetBinContent(63,0.02302632);
   S1hitsRing1->SetBinContent(64,0.006578947);
   S1hitsRing1->SetBinContent(65,0.01973684);
   S1hitsRing1->SetBinContent(66,0.01315789);
   S1hitsRing1->SetBinContent(67,0.01644737);
   S1hitsRing1->SetBinContent(68,0.009868421);
   S1hitsRing1->SetBinContent(69,0.006578947);
   S1hitsRing1->SetBinContent(70,0.01973684);
   S1hitsRing1->SetBinContent(71,0.01315789);
   S1hitsRing1->SetBinContent(72,0.003289474);
   S1hitsRing1->SetBinContent(73,0.006578947);
   S1hitsRing1->SetBinContent(74,0.01315789);
   S1hitsRing1->SetBinContent(75,0.006578947);
   S1hitsRing1->SetBinContent(77,0.006578947);
   S1hitsRing1->SetBinContent(78,0.01315789);
   S1hitsRing1->SetBinContent(79,0.003289474);
   S1hitsRing1->SetBinContent(81,0.003289474);
   S1hitsRing1->SetBinContent(83,0.003289474);
   S1hitsRing1->SetBinContent(86,0.003289474);
   S1hitsRing1->SetBinContent(87,0.003289474);
   S1hitsRing1->SetEntries(248);

   ci = TColor::GetColor("#ff0000");
   S1hitsRing1->SetLineColor(ci);
   S1hitsRing1->GetXaxis()->SetTitle("Energy (keV)");
   S1hitsRing1->GetXaxis()->CenterTitle(true);
   S1hitsRing1->GetXaxis()->SetLabelFont(42);
   S1hitsRing1->GetXaxis()->SetLabelSize(0.035);
   S1hitsRing1->GetXaxis()->SetTitleSize(0.035);
   S1hitsRing1->GetXaxis()->SetTitleFont(42);
   S1hitsRing1->GetYaxis()->SetTitle("Events/bin/s");
   S1hitsRing1->GetYaxis()->CenterTitle(true);
   S1hitsRing1->GetYaxis()->SetLabelFont(42);
   S1hitsRing1->GetYaxis()->SetLabelSize(0.035);
   S1hitsRing1->GetYaxis()->SetTitleSize(0.035);
   S1hitsRing1->GetYaxis()->SetTitleFont(42);
   S1hitsRing1->GetZaxis()->SetLabelFont(42);
   S1hitsRing1->GetZaxis()->SetLabelSize(0.035);
   S1hitsRing1->GetZaxis()->SetTitleSize(0.035);
   S1hitsRing1->GetZaxis()->SetTitleFont(42);
   S1hitsRing1->Draw("sames");
   
   TH1F *S1hitsRing2 = new TH1F("S1hitsRing2","G4 spectrum ring 2, 1 hit events",120,0,120);
   S1hitsRing2->SetBinContent(19,0.003289474);
   S1hitsRing2->SetBinContent(20,0.003289474);
   S1hitsRing2->SetBinContent(25,0.003289474);
   S1hitsRing2->SetBinContent(26,0.003289474);
   S1hitsRing2->SetBinContent(28,0.003289474);
   S1hitsRing2->SetBinContent(31,0.006578947);
   S1hitsRing2->SetBinContent(33,0.003289474);
   S1hitsRing2->SetBinContent(34,0.003289474);
   S1hitsRing2->SetBinContent(36,0.003289474);
   S1hitsRing2->SetBinContent(37,0.003289474);
   S1hitsRing2->SetBinContent(39,0.006578947);
   S1hitsRing2->SetBinContent(41,0.003289474);
   S1hitsRing2->SetBinContent(43,0.003289474);
   S1hitsRing2->SetBinContent(44,0.003289474);
   S1hitsRing2->SetBinContent(46,0.006578947);
   S1hitsRing2->SetBinContent(47,0.006578947);
   S1hitsRing2->SetBinContent(49,0.003289474);
   S1hitsRing2->SetBinContent(50,0.006578947);
   S1hitsRing2->SetBinContent(51,0.003289474);
   S1hitsRing2->SetBinContent(52,0.003289474);
   S1hitsRing2->SetBinContent(53,0.009868421);
   S1hitsRing2->SetBinContent(54,0.006578947);
   S1hitsRing2->SetBinContent(55,0.003289474);
   S1hitsRing2->SetBinContent(56,0.006578947);
   S1hitsRing2->SetBinContent(57,0.009868421);
   S1hitsRing2->SetBinContent(58,0.009868421);
   S1hitsRing2->SetBinContent(59,0.003289474);
   S1hitsRing2->SetBinContent(60,0.003289474);
   S1hitsRing2->SetBinContent(61,0.01315789);
   S1hitsRing2->SetBinContent(62,0.003289474);
   S1hitsRing2->SetBinContent(64,0.003289474);
   S1hitsRing2->SetBinContent(65,0.01315789);
   S1hitsRing2->SetBinContent(67,0.003289474);
   S1hitsRing2->SetBinContent(70,0.003289474);
   S1hitsRing2->SetBinContent(71,0.006578947);
   S1hitsRing2->SetBinContent(72,0.009868421);
   S1hitsRing2->SetBinContent(73,0.003289474);
   S1hitsRing2->SetBinContent(75,0.003289474);
   S1hitsRing2->SetBinContent(79,0.003289474);
   S1hitsRing2->SetEntries(61);

   ci = TColor::GetColor("#00ff00");
   S1hitsRing2->SetLineColor(ci);
   S1hitsRing2->GetXaxis()->SetTitle("Energy (keV)");
   S1hitsRing2->GetXaxis()->CenterTitle(true);
   S1hitsRing2->GetXaxis()->SetLabelFont(42);
   S1hitsRing2->GetXaxis()->SetLabelSize(0.035);
   S1hitsRing2->GetXaxis()->SetTitleSize(0.035);
   S1hitsRing2->GetXaxis()->SetTitleFont(42);
   S1hitsRing2->GetYaxis()->SetTitle("Events/bin/s");
   S1hitsRing2->GetYaxis()->CenterTitle(true);
   S1hitsRing2->GetYaxis()->SetLabelFont(42);
   S1hitsRing2->GetYaxis()->SetLabelSize(0.035);
   S1hitsRing2->GetYaxis()->SetTitleSize(0.035);
   S1hitsRing2->GetYaxis()->SetTitleFont(42);
   S1hitsRing2->GetZaxis()->SetLabelFont(42);
   S1hitsRing2->GetZaxis()->SetLabelSize(0.035);
   S1hitsRing2->GetZaxis()->SetTitleSize(0.035);
   S1hitsRing2->GetZaxis()->SetTitleFont(42);
   S1hitsRing2->Draw("sames");
   
   TLegend *leg = new TLegend(0,0,0,0,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("S1hit","All units","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("S1hitsRing0","Ring 0 unit","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("S1hitsRing1","Ring 1 unit","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("S1hitsRing2","Ring 2 unit","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   G4spectrum1hit->Modified();
   G4spectrum1hit->cd();
   G4spectrum1hit->SetSelected(G4spectrum1hit);
}
