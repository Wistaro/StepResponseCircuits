class  SchemaNumerique{
protected:
	float h; //pas de calcul
	float t; //temps
	float t0; //temps initial
public:
	SchemaNumerique(float h_user,float t0_user);
	virtual void calc_Un(float Vd);
	virtual float calcVs(float Ve); //calcule la sortie 
	float get_h();
	virtual void setVePrime(float Ven, float VenMoins1);

};
class EquaDiffOrdre1:public SchemaNumerique{
protected :
	float u0; //condition initiales
	float tu,tt, cte; // f(u,t) = tu*u(t) + tt*t + cte
	float u;

public: 
	EquaDiffOrdre1(float tu_user, float tt_user, float cte_user, float u0_user, float h_user,float t0_user);

};

class  Euler1: public EquaDiffOrdre1{

public: 
	Euler1(float tu_user, float tt_user, float cte_user, float u0_user, float h_user,float t0_user);
	void calc_Un( float Ve); //calcule un
	float get_Un(); //getter
	float get_t(); //getter

};
 
class CircuitAEuler: public Euler1{
	
protected: 
	float R;
	float C;
	float Vs;

public:
	CircuitAEuler (float R_user, float C_user, float tu_user, float tt_user, float cte_user, float u0_user, float h_user, float t0_user);
	float calcVs(float Ve);


};
class CircuitCEuler: public Euler1{
	
protected: 
	float R1;
	float R2;
	float C;
	float vbe;
	float Vs;

public:
	CircuitCEuler (float R1_user, float R2_user, float C_user, float vbe_user, float tu_user, float tt_user, float cte_user, float u0_user, float h_user, float t0_user);
	float calcVs(float Ve);

};


/*ORDRE 2*/
class EquaDiffOrdre2:public SchemaNumerique{
protected :
	float u0; //condition initiales
	float u0p; //condition de Newman
	float tu,tt, cte; // f(u,t) = tu*u(t) + tt*t + cte
	float tup, ttp, ctep; //f'(u',t) = tup*u'(t) + ttp*t + ctep
	float u;
	float up;

public: 
	EquaDiffOrdre2(float tu_user, float tt_user, float cte_user, float u0_user,float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user);

};

class  Euler2: public EquaDiffOrdre2{
protected:
	float VePrime;
	float ve_avant;


public: 
	Euler2(float tu_user, float tt_user, float cte_user, float u0_user, float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user);
	void calc_Un( float Ve); //calcule un
	void calc_Unp( float Ve); //calcule un_prime

	float get_Un(); //getter
	float get_t(); //getter
	void setVePrime(float Ven, float VenMoins1);

};

class CircuitBEuler2: public Euler2{
protected: 
	float R1;
	float L1;
	float C1;
	float Vs;

public:
	CircuitBEuler2(float R1_user, float L1_user, float C1_user, float tu_user, float tt_user, float cte_user, float u0_user, float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user);
	float calcVs(float Ve);
};
class CircuitDEuler2: public Euler2{
protected: 
	float R1;
	float L1;
	float C1;
	float Vs;

public:
	CircuitDEuler2(float R1_user, float L1_user, float C1_user, float tu_user, float tt_user, float cte_user, float u0_user, float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user);
	float calcVs(float Ve);
};