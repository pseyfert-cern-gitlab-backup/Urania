from ROOT import *
import cPickle

def list_values(input_dict, typeData):
  print '\n####################################'
  print '########### Fit case: ' + str(typeData) + ' '+'#'*(13-len(str(typeData)))
  print '####################################\n'
  keys = input_dict.keys()
  keys.sort()
  for m in keys:
    print ' '*(5-len(str(m)))+' ***** A1 mass = '+str(m)+' GeV/c2 *****'
    print '| Nsig  | CLs    | CLb    | CLsb   |'# Check |'
    keys_ns = input_dict[m].keys()
    keys_ns.sort()
    for ns in keys_ns:
      #CLs, CLb, CLsb = input_dict[m][ns][0], input_dict[m][ns][1], input_dict[m][ns][2]
      #check  = round((CLsb/CLb)/CLs,3)
      CLs, CLb, CLsb = round(input_dict[m][ns][0], 3), round(input_dict[m][ns][1], 3), round(input_dict[m][ns][2], 3)
      print '| '+ str(ns) + ' '*(6-len(str(ns)))+'| ' + str(CLs) + ' '*(7-len(str(CLs)))+'| ' + str(CLb) + ' '*(7-len(str(CLb)))+'| ' + str(CLsb) + ' '*(7-len(str(CLsb)))+'|'# + str(check) + '   |'

def create_plot(input_dict, mass, typeData):
  nPoints = len(input_dict.keys())
  CLs_gr, CLb_gr = TGraph(nPoints), TGraph(nPoints)
  CLs_ls, CLb_ls = [], []
  keys = input_dict.keys()
  keys.sort()
  for index in range(nPoints):
    nsig     = keys[index]
    CLs, CLb = input_dict[nsig][0], input_dict[nsig][1]
    CLs_ls.append(CLs)
    CLb_ls.append(CLb)
    if index==0:
      CLs_gr.SetPoint(index, nsig, CLs)
      CLb_gr.SetPoint(index, nsig, CLb)
    CLs_gr.SetPoint(index+1, nsig, CLs)
    CLb_gr.SetPoint(index+1, nsig, CLb)
  CLs_gr.SetLineColor(kBlue)
  CLs_gr.SetMarkerColor(kBlue)
  CLs_gr.SetMarkerStyle(20)
  CLs_gr.SetMarkerSize(1)
  CLb_gr.SetLineColor(kRed)
  CLb_gr.SetMarkerColor(kRed)
  CLb_gr.SetMarkerStyle(22)
  CLb_gr.SetMarkerSize(1)
  hAux = TH2F('hAux', 'Upper limits for M(A_{1}^{0})='+str(mass)+' GeV/c^{2};Signal candidates;CLs (CLb)', 100, min(input_dict.keys())-5., max(input_dict.keys())+5., 100, 0., 1.)#100, min(CLs_ls)*0.95, max(CLb_ls)*1.05)
  lAux = TLegend(0.7,0.65,0.9,0.85)
  lAux.SetBorderSize(0)
  lAux.SetFillStyle(0)
  lAux.AddEntry(CLs_gr, 'CLs', 'P')
  lAux.AddEntry(CLb_gr, 'CLb', 'P')
  cAux = TCanvas()
  gStyle.SetOptStat('')
  cAux.SetGrid()
  hAux.Draw()
  CLs_gr.Draw('same, LP')
  CLb_gr.Draw('same, LP')
  lAux.Draw('same')
  cAux.Print('plots_'+str(typeData)+'/CLs_plot_'+str(mass)+'_'+str(typeData)+'.pdf')

file_nsig  = 'output_CLs_HPT.nsig'
typeData   = 'HPT'
input_nsig = cPickle.load(file(file_nsig))
list_values(input_nsig, typeData)
for mass in input_nsig.keys():
  create_plot(input_nsig[mass], mass, typeData)

file_nsig  = 'output_CLs_normal.nsig'
typeData   = 'normal'
input_nsig = cPickle.load(file(file_nsig))
list_values(input_nsig, typeData)
for mass in input_nsig.keys():
  create_plot(input_nsig[mass], mass, typeData)
