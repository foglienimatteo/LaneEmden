# Lane-Emden

<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-1-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

![Operating Systems](https://img.shields.io/badge/OS-Linux%20%7C%20MacOS%20%7C%20Windows-lightgrey)
![License](https://img.shields.io/github/license/cosmofico97/LaneEmden)
![Pulls](https://img.shields.io/github/issues-pr/cosmofico97/LaneEmden)
![Top Language](https://img.shields.io/github/languages/top/cosmofico97/LaneEmden)
![Version](https://img.shields.io/github/v/release/cosmofico97/LaneEmden)
![Commits](https://img.shields.io/github/commit-activity/m/cosmofico97/LaneEmden)
![Size](https://img.shields.io/github/repo-size/cosmofico97/LaneEmden)

Lane-Emden is a simple C++ program that solves the Lane-Emden differential equation

![Lane-Emden_equation](rsc/Lane-Emden_equation.svg)

for an arbitrary input value of the index `n` with two possible algorithms: Euler and classic Runge-Kutta. The output file `Lane-Emden_Eulero_n=<index>.dat`/`Lane-Emden_RK_n=<index>.dat` contains also the values of the first derivate `θ'(ξ)` , concentration parameter `g_0` and `f_0`.
This data may be easily visualize thanks to the Jupyter Notebook files:
- `Lane-Emden.ipynb`, which analyses deeply a given input dataset;
- `Lane-Emden_confronti_vari_esponenti.ipynb`, which compares various datasets with different index values;
- `Lane-Emden_confronto_Eulero-RK.ipynb`, which compares a dataset obtained with Euler algorithm with another obtained with Runge-Kutta one.

## Table of contents
- [Lane-Emden](#lane-emden)
  - [Table of contents](#table-of-contents)
    - [Requirements](#requirements)
    - [Installation](#installation)
    - [Usage](#usage)
    - [Options and output for `euler` and `rungekutta`](#options-and-output-for-euler-and-rungekutta)
    - [Options for `zero`](#options-for-zero)
    - [Options and output for `zerosfunc`](#options-and-output-for-zerosfunc)
    - [Visualization of the data](#visualization-of-the-data)
  - [Mathematical treatment](#mathematical-treatment)
  - [License](#license)
  - [Contributors ✨](#contributors-)


### Requirements

In order to build the software from the source code here provided, you will need:
* [`cmake`](https://cmake.org/) (version >= 3.12);
* A `C++17` compiler;

This project uses the header-only [`Argh!`](https://github.com/adishavit/argh) library, which is already included in this repository in `include/argh.h`;therefore, you do not need to install it on your system.

### Installation

First of all, copy the source code provided in this repository on your OS. You may clone the repository where it is built in, running in the command line
```bash
git clone https://github.com/cosmofico97/LaneEmden
```
or download the source code from the webpage https://github.com/cosmofico97/LaneEmden.


Hereafter, run the following shell commands from the project directory:
```bash
mkdir build
cd build
cmake ..
make
```
The executable file `Lane_Emden` is generated in the `build` directory.

### Usage

In order to execute the `Lane_Emden` file (inside the `build` directory), the syntax is the standar one:
```bash
./Lane_Emden {euler|rungekutta|zero|zerosfunc} [options]
```

 - `euler` solve the differential equation with the Euler method;
 - `rungekutta` solve the differential equation with the classic Runge-Kutta method;
 - `zero` solve the differential equation with the classic Runge-Kutta method (not other methods avaiable for this command) and print to the standard output the resulting values of `ξ`, `θ'(ξ)`, ... in the zero of the numerical solution obtained; no output files are produced;
 - `zerosfunc` solve the differential equation with the classic Runge-Kutta method (not other methods avaiable for this command) and creates an output file with the resulting values of `ξ`, `θ'(ξ)`, ... in the zero of the numerical solution for a subset of `n` values inside `[0,5)`.

You must specify the index `n` of the Lane-Emden equation to be resolved (throughout the option `-n <index>` or `--index=<index>`) for the commands `euler`-`rungekutta`-`zero` (because they operate on THAT SPECIFIC Lane-Emden equation), but not for `zerosfunc` (because it operates on the interval `n \in [0, 5)`).



### Options and output for `euler` and `rungekutta`

The actual available options, for `euler` and `rungekutta` commands, are the following:
- `-h, --help`: print the help message;
- `-n <index>, --index=<index>`	REQUIRED: set the index of the Lane-Emden equation to be resolved;
- `-s <step>, --step=<step>`: set the step measure to be used solving the differential equation;
- `-b <begin>, --begin=<begin>`: set the beginning value of `ξ`, where the algothims starts;
- `-e <end>, --end=<end>`: set the ending value of `ξ`, where the algorithm ends;

Depending on the algorithm choosen, the output file (saved in the `build` directory) will be `Lane-Emden_Eulero_n=<index>.dat` or `Lane-Emden_RK_n=<index>.dat`.
For each of these files, the output data are organized in 8 columns; from left to right, they are:
- the iteration index of the algorithm `i=0,1,2,...`;
- the corresponding `ξ` value;
- the function value in that point, i.e. `θ(ξ)`;
- the first function derivate in that point, i.e. `θ'(ξ)`;
- the concentration parameter `g(ξ)`;
- the parameter `f(ξ)`;
- the parameter `h(ξ)`;
- the parameter `α(ξ)`;

In a table form, the data are disposed like this: 

|![i](rsc/i.svg)  | ![xi](rsc/xi.svg) |![theta](rsc/theta_of_xi.svg)  | ![thetap](rsc/dtheta-dxi_of_xi.svg) | ![g_csi](rsc/g_csi.svg)  | ![f_csi](rsc/f_csi.svg) | ![h_csi](rsc/h_csi.svg)  | ![alpha_csi](rsc/alpha_csi.svg) |
|--------------|--------------|-------------|-------------|-------------|-------------|-------------|-------------|
|0	 |  0.0001	 |  1	         |    0   	      | 1	 |    -0 |  0 | 	0 | 	 inf |	 
|1	 |  0.0011	 |  1	         |  -0.000175084	| 1	 |  2.11852e-10 	 |  -0.477502 	 | 6.54207e+06 |	 
|2	 |  0.0021	 |  0.999999	 |  -0.000643578	 |1	 |2.83818e-09 	 |-0.919396 	 |1.15978e+06 |	 
|3	 |  0.0031	 |  0.999998	 |  -0.00100734	 |1	 |9.68052e-09 	 |-0.974843 | 511844 |	 
|4	 |  0.0041	 |  0.999997	 |  -0.0013518	 |1	 |2.27237e-08 	 |-0.989119 	 | 289790 |	 
|... |	...       | ...	     | ...  |...	 |... |...  |...      |

Here we rememeber the definition of `g_csi`, `f_csi`, `h_csi` e `alpha_csi`:

|![g_csi](rsc/g_csi_definition.svg) | | | ![f_csi](rsc/f_csi_definition.svg) |
|--------------|-|-|--------------|
|![h_csi](rsc/h_csi_definition.svg) | | | ![alpha_csi](rsc/alpha_csi_definition.svg) |



### Options for `zero`

The actual available options, for the `zero` command, are the following:
- `-h, --help`: print the help message;
- `-n <index>, --index=<index>`	REQUIRED: set the index of the Lane-Emden equation to be resolved;
- `-s <step>, --step=<step>`: set the step measure to be used solving the differential equation;
- `-b <begin>, --begin=<begin>`: set the beginning value of `ξ`, where the algothims starts;
- `-e <end>, --end=<end>`: set the ending value of `ξ`, where the algorithm ends;
- `-m <min>, --min=<min>`: value of theta considered sufficiently close to zero (from up) where the algorithm must stop; it's better to set values not less than `1e-5`, because the algorithm becomes more and more unstable for certain values of `n` when the numerical solution approaches to zero.



### Options and output for `zerosfunc` 

The actual available options, for the `zerosfunc` command, are the following:
- `-h, --help`: print the help message;
- `-s <step>, --step=<step>`: set the step measure to be used solving the differential equation;
- `-b <begin>, --begin=<begin>`: set the beginning value of `ξ`, where the algothims starts;
- `-e <end>, --end=<end>`: set the ending value of `ξ`, where the algorithm ends;
- `-sn <index_step>, --index_step=<index_step>`: set the step which will be used to sample the index `n` of the Lane-Emden equation;
- `-m <min>, --min=<min>`: value of theta considered sufficiently close to zero (from up) where the algorithm must stop; it's better to set values not less than `1e-5`, because the algorithm becomes more and more unstable for certain values of `n` when the numerical solution approaches to zero.

The output file (saved in the `build` directory) will be `Lane-Emden_Eulero_zerosfunc.dat`.
The output data are organized in 9 columns; from left to right, they are:
- the iteration index of the algorithm `i` where the zero is placed;
- the value of the index `n`;
- the corresponding `ξ_n` value;
- the function value in that point, i.e. `θ(ξ_n)`;
- the first function derivate in that point, i.e. `θ'(ξ_n)`;
- the concentration parameter `g_n = g(ξ_n)`;
- the parameter `f_n = f(ξ_n)`;
- the parameter `h_n = h(ξ_n)`;
- the parameter `α_n = α(ξ_n)`;

In a table form, the data are disposed like this: 

|![i](rsc/i.svg)  | ![n](rsc/n.svg) |![xi_n](rsc/xi_n.svg) |![theta_n](rsc/theta_of_xi_n.svg)  | ![thetap_n](rsc/dtheta-dxi_of_xi_n.svg) | ![g_n](rsc/g_n.svg)  | ![f_n](rsc/f_n.svg) | ![h_n](rsc/h_n.svg)  | ![alpha_n](rsc/alpha_n.svg) |
|--------------|--------------|-------------|-------------|-------------|-------------|-------------|-------------|-------------|
|2449 	 |0 	 |2.4491 	 |0.000318203 	 |-0.816367 	 |1 	 |4.89664 	 |-1 	 |0. |806253 |	 
|2454 	 |0.01 	 |2.4541 	 |0.000631585 	 |-0.807695 	 |0.928976 	 |4.86443 	 |-0.987362 	 |0.80179 	| 
|2459 	 |0.02 	 |2.4591 	 |0.000958193 	 |-0.799185 	 |0.87022 	 |4.83281 	 |-0.974972 	 |0.797389 	 |
|2465 	 |0.03 	 |2.4651 	 |0.00050677 	 |-0.790996 	 |0.796424 	 |4.80666 	 |-0.962633 	 |0.792508 |	 
|2470 	 |0.04 	 |2.4701 	 |0.000867039 	 |-0.782751 	 |0.754261 	 |4.77587 	 |-0.950671 	 |0.788258 |
|... |	... |...      | ...	     | ...  |...	 |... |...  |...      |

Here we rememeber the definition of `g_n`, `f_n`, `h_n` e `alpha_n`:

|![g_n](rsc/g_n_definition.svg) | | | ![f_n](rsc/f_n_definition.svg) |
|--------------|-|-|--------------|
|![h_n](rsc/h_n_definition.svg) | | | ![alpha_n](rsc/alpha_n_definition.svg) |


### Visualization of the data

In the main directory, there are 4 JupyterLab Notebooks:
- `Lane-Emden.ipynb`, where the skeleton of the data plotting and analysis is provided, for an arbitrary value of `n`;
- `Lane-Emden-zerosfunc.ipynb`, where the zeros for a subset of `n` values inside `[0, 5)` are plotted and analysed;
- `Lane-Emden_confronto_vari_esponenti.ipynb`, where solutions for various `n` values are compared;
- `Lane-Emden_confronto_Eulero-RK.ipynb`, where are compared Euler and Runge-Kutta methods.
  
Unfortunately, the notous curl in the `p_0/p_s` vs `(R_0/R_s)^3` does not appear clearly, probably for a computational mistake somewhere in the source code.  


## Mathematical treatment

The original equation can be rewrited in this simple system:

![LE_system](rsc/LE_system.svg)

So, with the basic treatment of the differential equation numerical solutions:

![LE_system](rsc/LE_num-system.svg)

## License

Lane-Emden is free software, and it is released under version 3 of the [GNU General Public License](https://www.gnu.org/licenses/gpl-3.0.html).



## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/teozec"><img src="https://avatars.githubusercontent.com/u/44500371?v=4" width="100px;" alt=""/><br /><sub><b>Matteo Zeccoli Marazzini</b></sub></a><br /><a href="#ideas-Matteo-Zeccoli-Marazzini" title="Ideas, Planning, & Feedback">🤔</a> <a href="#tool-Matteo-Zeccoli-Marazzini" title="Tools">🔧</a></td>
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!

