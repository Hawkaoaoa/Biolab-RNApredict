% BIOLAB-RNAPREDICT(1) biolab 1.0.0
%Group 4
%June 2020

# NAME
biolab - predict RNA secondary structure

# Get Start
git clone https://github.com/Hawkaoaoa/Biolab-RNApredict
cd Biolab-RNApredict
ls
cd Biolab
make:build a static library
make install:generate an executable file(/bin/RNA)
cd bin
./RNA [Option] [Input Filename] [Output Filename]
make clean

# SYNOPSIS
./RNA [*-d1d2w*] [Input Filename] [Output Filename]

# DESCRIPTION
This document describes the **biolab** software.**biolab** predict RNA secondary structure with Nussinov algorithm, genetic algorithm and weight matching algorithm.By inputing an input file storing RNA sequences,**biolab** can output a file with predicted RNA secondary structure presented in Dot-Bracket Notion.

# OPTIONS
**-d1**
:use the Nussinov algorithm to predict(traceback version1).
**-d2**
:use the Nussinov algorithm to predict(traceback version2).
**-w**
:use the weight matching algorithm.

# EXAMPLES
./RNA -d1 input.txt output.txt
:use the Nussinov algorithm(traceback with linked list) to predict the RNA sequences stored in input.txt.The result is stored in /bin/output.txt.
./RNA -w RNA.txt res
:use the weight matching algorithm to predict the RNA sequences stored in RNA.txt.The result is stored in /bin/res.
We strongly recommend you run the genetic algorithm on the server, otherwise it may fail due to computer memory limitations.Here is an example of run genetic algorithm in torque.
`#PBS -S /bin/bash`
`#PBS -N <sc_519111910094>`
`#PBS -o ${PBS_JOBID}.o`
`#PBS -e ${PBS_JOBID}.e`
`#PBS -q cpuq`
`#PBS -l nodes=1:ppn=40`
`#PBS -r y`
cd ${PBS_O_WORKDIR}
mpirun -np 40 /home/ug2019/ug519111910094/test/Biolab-RNApredict/Biolab/bin/RNA input.txt

# EXIT VALUES
**0**
:Success

**-1**
:miss command line arguments,wrong options or wrong input file.

# BUGS
Tests have shown that git clone is prone to failure due to network problems. 

# TIPS
The software includes a Python program that can draw RNA secondary structures based on the predicted results, but it requires the user to have the plug-in installed on the system in advance.
Here are the details:
The following Python modules need to be installed in advance and are recommended to be installed using Conda, where the Forgi module needs to be installed with the RNA module, which is one of the modules in Viennarna.
Python recommends installing version 3.6
conda create-n rnaplot python=3.6
pip install matplotlib
pip install forgi
conda install -c bioconda viennarna

Or you can draw the structure on http://rna.tbi.univie.ac.at/forna/

# COPYRIGHT
Copyrtight © 2021 Group4. This is free software: you are free to change and redistribute it. There is NO WARRANITY, to the extent permitted by law.



