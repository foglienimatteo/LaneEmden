#include "FunzioneVettoriale.hpp"


LaneEmden:: LaneEmden(double N){
	n = N;
}
LaneEmden:: LaneEmden(){
	n = 1.;
}

LaneEmden:: ~LaneEmden(){}

double LaneEmden:: getEsponente() const{return n;}
void LaneEmden:: setEsponente(double N){n = N;}

VettoreLineare LaneEmden::Eval(VettoreLineare& y, double csi){
	VettoreLineare f(y.getDimension());
	f.setComponent(0, y.getComponent(1));
	f.setComponent(1, -  pow(y.getComponent(0),n) - 2 * y.getComponent(1)/csi );
	return f;
}


Eulero::Eulero(){}

Eulero::~Eulero(){}

VettoreLineare Eulero::Passo(FunzioneVettorialeBase* f, VettoreLineare& y0, double h, double t)const{
	VettoreLineare y = y0 + (f->Eval(y0,t))*h;
	return y;
}

RungeKutta::RungeKutta(){}

RungeKutta::~RungeKutta(){}

VettoreLineare RungeKutta::Passo(FunzioneVettorialeBase* f, VettoreLineare& y0, double h, double t) const {
	int dim = y0.getDimension();
	VettoreLineare k1(dim), k2(dim), k3(dim), k4(dim);

	k1 = f->Eval(y0, t);
	VettoreLineare p = y0 + k1*(h/2.);
	k2 = f->Eval(p, t+h/2.);
	p = y0 + k2*(h/2.);
	k3 = f->Eval (p, t+h/2.);
	p = y0 + k3*h;
	k4 = f->Eval (p, t+h);

	VettoreLineare y = y0 + (k1 + k2*2.+ k3*2. + k4)*(h/6.);
	return y;
}
