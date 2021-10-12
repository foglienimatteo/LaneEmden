#ifndef FunzioneVettoriale_hpp
#define FunzioneVettoriale_hpp

#include "VettoreLineare.hpp"

class FunzioneVettorialeBase{
public:
	virtual VettoreLineare Eval(VettoreLineare& y, double t) = 0;
};



class EquazioneDifferenzialeBase{
public:
	virtual VettoreLineare Passo(FunzioneVettorialeBase* f, VettoreLineare& y0, double h, double t)const = 0;
};



class LaneEmden: public FunzioneVettorialeBase{
public:
	LaneEmden(double );
	LaneEmden();

	~LaneEmden();

	double getEsponente() const;
	void setEsponente(double );

	virtual VettoreLineare Eval(VettoreLineare& y, double csi);

protected:
	double n;
};



class Eulero: public EquazioneDifferenzialeBase{
public:
	Eulero();

	~Eulero();

	virtual VettoreLineare Passo(FunzioneVettorialeBase* f, VettoreLineare& y0, double h, double t)const;
};

class RungeKutta: public EquazioneDifferenzialeBase{
public:
	RungeKutta();

	~RungeKutta();

	virtual VettoreLineare Passo(FunzioneVettorialeBase* f, VettoreLineare& y0, double h, double t) const;
};

#endif /* FunzioneVettoriale_hpp */
