#include "VettoreLineare.hpp"
#include "Vettore.hpp"
#include "FunzioneVettoriale.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <stdio.h>

#include "argh.h"

#define pi 3.1415926535897932
#define nepier 2.718281828459045

using namespace std;

#define USAGE \
	programName << ": a C++ tool to solve the Lane-Emden equation." << endl << endl << \
	"Usage: " << endl << \
	programName << " -h|--help" << endl << \
	programName << " euler [options]" << endl << \
	programName << " rungekutta [options]" << endl  << \
	programName << " zero [options]" << endl << endl  << \
	"You must specify the index 'n' of the Lane-Emden equation to be resolved, " \
	"throughout the option '-n <index>' or '--index=<index>'." << endl << \
	"Run '" << programName << " <action-name> -h|--help' for all supported options." << endl

#define HELP_EULERO \
	"euler: solve the Lane-Emden equation using Euler method." << endl << endl << \
	"Usage: " << programName << " euler [options]" << endl << endl << \
	"Available options:" << endl << \
	"	-h, --help				Print this message." << endl << \
	"	-n <index>, --index=<index>	REQUIRED: Index of the Lane-Emden equation to be resolved. " << endl << \
	"	-s <step>, --step=<step>		Step measure to be used solving the differential equation."  << endl << \
	"	-b <begin>, --begin=<begin>	Beginning value of csi, where the algothims starts." << endl << \
	"	-e <end>, --end=<end>		Ending value of csi, where the algorithm ends." << endl

#define HELP_RUNGEKUTTA \
	"rungekutta: solve the Lane-Emden equation using Runge-Kutta method." << endl << endl << \
	"Usage: " << programName << " rungekutta [options]" << endl << endl << \
	"Available options:" << endl << \
	"	-h, --help				Print this message." << endl << \
	"	-n <index>, --index=<index>	REQUIRED: Index of the Lane-Emden equation to be resolved. " << endl << \
	"	-s <step>, --step=<step>		Step measure to be used solving the differential equation."  << endl << \
	"	-b <begin>, --begin=<begin>	Beginning value of csi, where the algothims starts." << endl << \
	"	-e <end>, --end=<end>		Ending value of csi, where the algorithm ends." << endl

#define HELP_ZERO \
	"zeros: gives the values of csi, dtheta/dcsi, ... in the zero of the Lane-Emden solution, " << endl << \
	"for the specified index n."<< endl << endl << \
	"Usage: " << programName << " zero  [options]" << endl << \
	"The method which will be used solving the equation is Runge-Kutta." << endl << endl << \
	"Available options:" << endl << \
	"	-h, --help				Print this message." << endl << \
	"	-n <index>, --index=<index>	REQUIRED: Index of the Lane-Emden equation to be considered. " << endl << \
	"	-s <step>, --step=<step>		Step measure to be used solving the differential equation."  << endl << \
	"	-b <begin>, --begin=<begin>	Beginning value of csi, where the algothims starts." << endl << \
	"	-e <end>, --end=<end>		Ending value of csi, where the algorithm ends." << endl


#define INDEX_NOT_PROVIDED \
	"You must provide the index 'n' of the Lane-Emden equation to be resolved! For example:" << endl << \
	"Usage: " << programName << " {euler|rungekutta|zero} --index=<index>  [options]" << endl << endl << \
	"Run '" << programName << "  -h|--help' to get the help message." << endl

int eulero(argh::parser cmdl);
int rungekutta(argh::parser cmdl);
int zero(argh::parser cmdl);
string fix(double in);

//void assert_close(double ,double );
//void test_program(VettoreLineare , Eulero , OscillatoreArmonico* );
int main(int argc, char ** argv){
	argh::parser cmdl;

	cmdl.add_params({
			"-n", "--index",
			"-s", "--step",
			"-b", "--begin",
			"-e", "--end",
			});

	cmdl.parse(argc, argv);
	const string programName = cmdl[0];
	const string actionName = cmdl[1];

	if (cmdl[{"-h", "--help"}]) {
		cout << USAGE;
		return 0;
	}

	if (actionName == "euler" && cmdl({"-n", "--index"})) { 
		return eulero(cmdl);
	} else if (actionName == "rungekutta" && cmdl({"-n", "--index"})) {
		return rungekutta(cmdl);
	} else if (actionName == "zero" && cmdl({"-n", "--index"})) {
		return zero(cmdl);
	} else if (cmdl[{"-h", "--help"}]) {
		cout << USAGE;
		return 0;
	} else if ( (actionName == "rungekutta" || actionName == "euler") && !cmdl({"-n", "--index"})) {
		cout << INDEX_NOT_PROVIDED;
		return 1;
	} else {
		cout << USAGE;
		return 1;
	}

	return 0;
}


int eulero(argh::parser cmdl){
	const string programName = cmdl[0];
	const string actionName = cmdl[1];

	if (cmdl[{"-h", "--help"}]) {
		cout << HELP_EULERO;
		return 0;
	}

	double n, h, csi_begin, csi_end;
	cmdl({"-n", "--index"}) >> n;
	cmdl({"-s", "--step"}, 0.001) >> h;
	cmdl({"-b", "--begin"}, 0.0001) >> csi_begin;
	cmdl({"-e", "--end"}, 5) >> csi_end;

	if(csi_begin<=0.0){
		cout << "The input value of csi_begin=" << csi_begin << 
			" must be >=0="<< endl;
		return 1;
	}else if (csi_begin > csi_end){
		cout << "The input value of csi_begin=" << csi_begin << 
			" must be < than csi_end="<< csi_end << endl;
		return 1;
	}else if(h > 0.3*(csi_end-csi_begin)){
		cout << "The input value of the step=" << h << 
			" must be <= than 0.3*(csi_end-csi_begin)="<< 
			0.3*(csi_end-csi_begin) << endl;
		return 1;
	}

	Eulero myEuler;
	LaneEmden* LE = new LaneEmden(n);
	int nstep = int(csi_end/h + 0.5);
	VettoreLineare x(2);
	x.setComponent(0, 1.);
	x.setComponent(1, 0.);

	ofstream uscita_Eulero;
	uscita_Eulero.open("Lane-Emden_Eulero_n=" + fix(n) +".dat");

	double csi = csi_begin;
	for(int i=0; i<nstep; i++){
		uscita_Eulero << i 
			<< "\t "  << csi 
			<< "\t " 	<< x.getComponent(0) 
			<< "\t " 	<< x.getComponent(1) 
			<< "\t "  << pow(x.getComponent(0), n)
			<< "\t "  << pow(csi, 2.0)*x.getComponent(1) 
			<< endl;
		x = myEuler.Passo(LE, x, h, csi);
		csi += h;
	}

	uscita_Eulero.close();
	uscita_Eulero.clear();
	return 0;
}

int rungekutta(argh::parser cmdl){

	const string programName = cmdl[0];
	const string actionName = cmdl[1];

	if (cmdl[{"-h", "--help"}]) {
		cout << HELP_RUNGEKUTTA;
		return 0;
	}

	double n, h, csi_begin, csi_end;
	cmdl({"-n", "--index"}) >> n;
	cmdl({"-s", "--step"}, 0.001) >> h;
	cmdl({"-b", "--begin"}, 0.0001) >> csi_begin;
	cmdl({"-e", "--end"}, 5) >> csi_end;

	if(csi_begin<=0.0){
		cout << "The input value of csi_begin=" << csi_begin << 
			" must be >=0="<< endl;
		return 1;
	}else if (csi_begin > csi_end){
		cout << "The input value of csi_begin=" << csi_begin << 
			" must be < than csi_end="<< csi_end << endl;
		return 1;
	}else if(h > 0.3*(csi_end-csi_begin)){
		cout << "The input value of the step=" << h << 
			" must be <= than 0.3*(csi_end-csi_begin)="<< 
			0.3*(csi_end-csi_begin) << endl;
		return 1;
	}

	RungeKutta myRK;
	LaneEmden* LE = new LaneEmden(n);
	int nstep = int(csi_end/h + 0.5);
	VettoreLineare x(2);
	x.setComponent(0, 1.);
	x.setComponent(1, 0.);
	ofstream uscita_RK;
	printf("%.6g", 13.2500 );  // 12.5 with 6 digit precision
	uscita_RK.open("Lane-Emden_RK_n=" + fix(n) + ".dat" );

	double csi = csi_begin;
	for(int i=0; i<nstep; i++){
		uscita_RK << i 
			<< "\t "  << csi 
			<< "\t " 	<< x.getComponent(0) 
			<< "\t " 	<< x.getComponent(1) 
			<< "\t "  << pow(x.getComponent(0), n)
			<< "\t "  << pow(csi, 2.0)*x.getComponent(1) 
			<< endl;
		x = myRK.Passo(LE, x, h, csi);
		csi += h;
	}

	uscita_RK.close();
	uscita_RK.clear();
	return 0;
}

int zero(argh::parser cmdl){

	const string programName = cmdl[0];
	const string actionName = cmdl[1];

	if (cmdl[{"-h", "--help"}]) {
		cout << HELP_ZERO;
		return 0;
	}

	double n, h, csi_begin, csi_end;
	cmdl({"-n", "--index"}) >> n;
	cmdl({"-s", "--step"}, 0.001) >> h;
	cmdl({"-b", "--begin"}, 0.0001) >> csi_begin;
	cmdl({"-e", "--end"}, 100) >> csi_end;

	if(csi_begin<=0.0){
		cout << "The input value of csi_begin=" << csi_begin << 
			" must be >=0"<< endl;
		return 1;
	}else if (csi_begin > csi_end){
		cout << "The input value of csi_begin=" << csi_begin << 
			" must be < than csi_end="<< csi_end << endl;
		return 1;
	}else if(h > 0.3*(csi_end-csi_begin)){
		cout << "The input value of the step=" << h << 
			" must be <= than 0.3*(csi_end-csi_begin)="<< 
			0.3*(csi_end-csi_begin) << endl;
		return 1;
	}

	RungeKutta myRK;
	LaneEmden* LE = new LaneEmden(n);
	int nstep = int(csi_end/h + 0.5);
	VettoreLineare x(2);
	x.setComponent(0, 1.);
	x.setComponent(1, 0.);

	double csi = csi_begin;
	double old_theta=0.0, new_theta=0.0;
	int NNN = 42; 
	int prec = (int) (-log10(h));
	for(int i=0; i<nstep; i++){
		if(x.getComponent(0)<=0.0){
			cout << endl;
			cout << "The precision that can be achieved with this step is of " 
				<< prec << " significant digits."<< endl << endl;
			cout << std::setw(NNN) << "input value of n = " << n << endl;
			cout << std::setw(NNN) << "csi_n = " << std::setprecision(prec) << csi << endl;
			cout << std::setw(NNN) << "theta(csi_n) = " << std::setprecision(prec) 
				<< x.getComponent(0)  << endl;
			cout << std::setw(NNN) << "dtheta/dcsi(csi_n) = " << std::setprecision(prec) 
				<< x.getComponent(1)  << endl;
			cout << std::setw(NNN) << "g_n = theta^n(csi_n) = " << std::setprecision(prec) 
				<< pow(x.getComponent(0), n)  << endl;
			double f_n = -pow(csi, 2.0)*x.getComponent(1);
			cout << std::setw(NNN) << "f_n = - csi_n^2 * dtheta/dcsi(csi_n) = " << std::setprecision(prec) 
				<< f_n  << endl;
			cout << std::setw(NNN) << "3 * f_n / csi_n^3 = " << std::setprecision(prec) <<
				- 3.0 * f_n / pow(csi, 3.0)    << endl;
			cout << std::setw(NNN) << "alpha_n = 1/(n+1) * (4*pi/f_n^2)^(1/3) = " << std::setprecision(prec) <<
				pow( 4.0*pi/f_n/f_n, 0.33333333)/(n+1.0)   << endl << endl;
			break;
		}
		x = myRK.Passo(LE, x, h, csi);
		csi += h;
	}
	return 0;
}


string fix(double in) {       
    string s = to_string(in);
    size_t dot = s.find_first_of('.'), last = s.find_last_not_of(".0");

    if (dot!=string::npos) return s.substr(0, max(dot,last+1));
    else return s;
}