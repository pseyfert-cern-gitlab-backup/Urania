from ROOT import *

gROOT.ProcessLine('.x lhcbStyle.C')

f = TFile('/home3/miguel.ramos/scratchTuples/K0Smumu/2012/Kspipi_MC2012_mcMatch_MVA.root')
t = f.Get('DecayTree')

canvas = TCanvas('c', 'c')

NBINS = 100
MIN   = 420
MAX   = 520

t.Draw('KS0_massMM>>hmm(%i, %d, %d)'%(NBINS, MIN, MAX), 'KS0_L0Global_TIS && KS0_Hlt1Phys_TIS && KS0_Hlt2Phys_TIS')
t.Draw('KS0_massPP>>hpp(%i, %d, %d)'%(NBINS, MIN, MAX), 'KS0_L0Global_TIS && KS0_Hlt1Phys_TIS && KS0_Hlt2Phys_TIS')

hmm.SetLineColor(kRed)
hmm.SetLineStyle(kDashed)
hpp.SetLineColor(kBlue)
hpp.SetLineStyle(kSolid)

hpp.GetXaxis().SetTitle('Reconstructed K_{S}^{0} mass [MeV/c^{2}]')
ct = ((MAX-MIN)/NBINS)
if int(ct) == ct:
    c = '%i'
else:
    c = '%.2f'
hpp.GetYaxis().SetTitle(('Candidates / (' + c + ' MeV/c^{2})') %ct)

legend = TLegend(0.2, 0.7, 0.4, 0.9)
legend.AddEntry(hpp, '#pi^{+}#pi^{-} hypothesis', 'L')
legend.AddEntry(hmm, '#mu^{+}#mu^{-} hypothesis', 'L')
legend.SetTextFont(132)#lhcb
legend.SetTextSize(0.06)#lhcb

lhcb = TPaveText(0.6, 0.8, 0.9, 0.9, 'NDC')
lhcb.AddText('LHCb Preliminary')
lhcb.SetFillColor( kWhite )
lhcb.SetBorderSize( 0 )

hpp.GetYaxis().SetRangeUser(1, 1e5)

hpp.Draw()
hmm.Draw('SAME')
lhcb.Draw('SAME')
legend.Draw('SAME')
canvas.SetLogy()
canvas.Update()
canvas.Print('ksmass.pdf')
