# Biolab-RNApredict

## 1. Description

An easy, fast and  relatively accurate tool for users to predict the possible secondary structure of a RNA molecule.

## 2. Install

> As for normal predicting methods
>
> - Dynamic programming --version-1
> - Dynamic programming--version-2
> - Weight matching

Just do as follows:

```bash
make
```

This will build the relevant libraries

```bash
make install
```

This will install the product

***Tips for use: *** (the executable file named ***RNA***)

./RNA \<options\>  \<your input filename\>  \<your wanted output filename\>

- for options:
  - `-d1`: Dynamic1
  - `-d2`: Dynamic2
  - `-w`: Weight 

> However if you intend to use the Genetic Algorithm, we **strongly** suggested you run it on the server considering the memory bank factors!

Just get in to the `MPI_Genetic` directory, and do exactly the same procedure

```bash
make
make install
```

And you will get an executable file in the `bin` directory.

Then, simply run it on your individual server and enjoy it!

## 3. Other functions

We also provide you with a convenient python program to draw a **2-D graph** for your predicted sequence, but it may need to install some environmental packages to function normally. You can check the details in the manual.

## 4. Authors

This product is supported by:

- Runhan Li
- Ziyun Chen
- Songchi Zhou

***School of Life Science and Technology, Shanghai Jiao Tong University***

