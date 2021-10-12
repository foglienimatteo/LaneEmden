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
    - [Output file](#output-file)
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
./Lane_Emden {euler/rungekutta} [options]
```

The command `euler` tells the program to solve the differential equation with the Euler method, while `rungekutta` with the classic Runge-Kutta one. You have to specify which between these two algorithms must be used.

The actual available options, for both `euler` and `rungekutta` commands, are the following:
- `-h, --help`: print the help message;
- `-n <index>, --index=<index>`	REQUIRED: set the index of the Lane-Emden equation to be resolved;
- `-s <step>, --step=<step>`: set the step measure to be used solving the differential equation;
- `-b <begin>, --begin=<begin>`: set the beginning value of `ξ`, where the algothims starts;
- `-e <end>, --end=<end>`: set the ending value of `ξ`, where the algorithm ends;

### Output file

Depending on the algorithm choosen, the output file (saved in the `build` directory) will be `Lane-Emden_Eulero_n=<index>.dat` or `Lane-Emden_RK_n=<index>.dat`.
For each of these files, the output data are organized in 6 columns; from left to right, they are:
- the iteration index of the algorithm `i=0,1,2,...`
- the corresponding `ξ` value
- the function value in that point, i.e. `θ(ξ)`
- the first function derivate in that point, i.e. `θ'(ξ)`
- the concentration parameter `g_0` at `ξ_0=ξ`;
-  the parameter `f_0` at `ξ_0=ξ`;

In a table form, the data are disposed like this: 

|![i](rsc/i.svg)  | ![xi](rsc/xi.svg) |![theta](rsc/theta_of_xi.svg)  | ![thetap](rsc/dtheta-dxi_of_xi.svg) | ![g_0](rsc/g_0.svg)  | ![f_0](rsc/f_0.svg) |
|--------------|--------------|-------------|-------------|-------------|-------------|
|0   |    0.0001	| 0	          |0	          |0.9999	|0             |
|1   |	0.00011	| 0	          |1e-05	     |0.99989  |1.21e-13      |
|2   |	0.00012	| 1e-10	     |1.81818e-05	|0.99988	|2.61818e-13   |
|3   |	0.00013	| 2.81818e-10	|2.51515e-05	|0.99987	|4.25061e-13   |
|... |	...       | ...	     | ...	     |...	     |...           |

Here we rememeber the  definition of `g_0` and `f_0`:

|![g_0](rsc/g_0_definition.svg) |  | | |  | ![f_0](rsc/f_0_definition.svg) |
|--------------|-|-|-|-|--------------|


### Visualization of the data

In the main directory, it is provided a JupyterLab Notebook, called `Lane-Emden.ipynb`, where the skeleton of the data plotting and analysis is provided.
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

