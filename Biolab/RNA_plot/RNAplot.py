
import sys,os
import RNA
import matplotlib.pyplot as plt
import forgi.visual.mplotlib as fvm
import forgi

input_file = 'test.txt'
out_file = 'test_out_RNA.png'

def secondary_structure_plot (input_file, out_file):
    
    cg = forgi.load_rna(input_file,allow_many=False)
    fvm.plot_rna(cg, text_kwargs={"fontweight":"black"}, lighten=0.7,
             backbone_kwargs={"linewidth":3})
    plt.savefig(out_file)
    plt.show()

secondary_structure_plot(input_file,out_file)

