import sys,os
#下面的python模块需要事先装好,建议使用conda安装，其中forgi模块需要安装RNA模块，而RNA模块是viennaRNA中的一个模块
#python建议安装3.6版本的
#使用conda create -n rnaplot python=3.6
#pip install matplotlib
#pip install forgi
#conda install -c bioconda viennarna
import RNA
import matplotlib.pyplot as plt
import forgi.visual.mplotlib as fvm
import forgi
#需要处理的文件,这里可以直接在程序中写入当前目录下要处理的文件名称
input_file = 'test.txt'
out_file = 'test_out_RNA.png'

#RNA二级结构绘图函数

def secondary_structure_plot (input_file, out_file):
    #使用forgi模块中的load_rna函数，将需要处理的文件读入到程序中
    cg = forgi.load_rna(input_file,allow_many=False)
    fvm.plot_rna(cg, text_kwargs={"fontweight":"black"}, lighten=0.7,
             backbone_kwargs={"linewidth":3})
    plt.savefig(out_file)
    plt.show()

secondary_structure_plot(input_file,out_file)

