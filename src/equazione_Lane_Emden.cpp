#include "VettoreLineare.hpp"
#include "Vettore.hpp"
#include "FunzioneVettoriale.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include<fstream>
#include <cmath>

#define pi 3.141592653589

using namespace std;

//void assert_close(double ,double );
//void test_program(VettoreLineare , Eulero , OscillatoreArmonico* );

int main(int argc, char ** argv){
	if(argc!=5){
		cerr << "Tipo di input: " << argv[0];
		cerr << " <passo_di_integrazione> <csi_iniziale> <csi_finale> <esponente>" << endl;
		return -1;
	}

	double h = atof(argv[1]);
	double csi = atof(argv[2]);
	double csi_max = atof(argv[3]);
	double n = atof(argv[4]);

	Eulero myEulero;
	RungeKutta myRK;

	LaneEmden* LE = new LaneEmden(n);

	int nstep = int(csi_max/h + 0.5);

	VettoreLineare x_Eulero(2);
	x_Eulero.setComponent(0, 1.);
	x_Eulero.setComponent(1, 0.);

	VettoreLineare x_RK(2);
	x_RK.setComponent(0, 1.);
	x_RK.setComponent(1, 0.);

	//test_program(x,myEuler,LE);

	ofstream uscita_Eulero;
	uscita_Eulero.open("LaneEmden_Eulero.dat");
	ofstream uscita_RK;
	uscita_RK.open("LaneEmden_RK.dat");

	for(int i=0; i<nstep; i++){
		uscita_Eulero << i << "\t "  << csi << "\t " << x_Eulero.getComponent(0) << endl;
		uscita_RK << i << "\t "  << csi << "\t " << x_RK.getComponent(0) << endl;
		x_Eulero = myEulero.Passo(LE, x_Eulero, h, csi);
		x_RK = myRK.Passo(LE, x_RK, h, csi);
		csi += h;
	}

	uscita_Eulero.close();
	uscita_Eulero.clear();
	uscita_RK.close();
	uscita_RK.clear();

	return 0;
}
