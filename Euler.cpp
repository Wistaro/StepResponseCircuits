#include <stdio.h>
#include <math.h>
#include "euler.h"

SchemaNumerique::SchemaNumerique(float h_user,float t0_user){
	h = h_user;
	t = t0_user;
}

EquaDiffOrdre1::EquaDiffOrdre1(float tu_user, float tt_user, float cte_user, float u0_user, float h_user,float t0_user):SchemaNumerique(h_user,t0_user){
	tu = tu_user;
	tt = tt_user;
	cte = cte_user;
	u0 = u0_user;

}

Euler1::Euler1(float tu_user, float tt_user, float cte_user, float u0_user, float h_user,float t0_user):EquaDiffOrdre1(tu_user,tt_user, cte_user,  u0_user,  h_user,t0_user){
	u = u0;
}
void SchemaNumerique::calc_Un(float Ve){}
float SchemaNumerique::calcVs(float Ve){return 0.0; }
void SchemaNumerique::setVePrime(float Ven, float VenMoins1){}

void Euler1::calc_Un(float Ve){ //retourne Un+1 et tn+1 en fonction de un et tn 

//	printf("AVANT: u = %f et t = %f",u);

	u = u + h*(tu*u+tt*Ve+cte);

	t = t+h;
//	printf("u = %f, tu = %f, tt",u);

}

float Euler1::get_t(){
	return t;
}
float SchemaNumerique::get_h(){
	return h;
}
float Euler1::get_Un(){
	return u;
}


/*Circuit A*/
CircuitAEuler::CircuitAEuler(float R_user, float C_user, float tu_user, float tt_user, float cte_user, float u0_user, float h_user,float t0_user):Euler1(tu_user,tt_user,cte_user, u0_user,h_user, t0_user){
	R = R_user;
	C = C_user;
}

float CircuitAEuler::calcVs(float Ve){
		tu = -1/(R*C);
		cte = 0;
		tt=1/(R*C);
		Euler1::calc_Un(Ve); //compute the output using Euler	algo
		
		Vs = u;

		return Vs;
}

/*Circuit C*/
CircuitCEuler::CircuitCEuler(float R1_user, float R2_user, float C_user, float vbe_user, float tu_user, float tt_user, float cte_user, float u0_user, float h_user,float t0_user):Euler1(tu_user,tt_user,cte_user, u0_user,h_user, t0_user){
	R1 = R1_user;
	R2 = R2_user;
	C = C_user;
	vbe = vbe_user;
}

float CircuitCEuler::calcVs(float Ve){
	
		if(Ve>vbe){

				cte = -vbe/(R1*C);
				tt = 1/(R1*C);
				tu =  -1/(R1*C)-1/(R2*C);

			}else{

				cte = 0.0;
				tt = 0.0;
				tu = -1/(R2*C);

			}

		Euler1::calc_Un(Ve); //compute the output using Euler1	algo
		
		Vs = u;

		return Vs;
}



/*ORDRE 2*/
EquaDiffOrdre2::EquaDiffOrdre2(float tu_user, float tt_user, float cte_user, float u0_user, float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user):SchemaNumerique(h_user,t0_user){
	tu = tu_user;
	tt = tt_user;
	cte = cte_user;
	u0 = u0_user;
	tup = tup_user;
	ttp = ttp_user;
	ctep = ctep_user;
	u0p = u0p_user;

}

Euler2::Euler2(float tu_user, float tt_user, float cte_user, float u0_user, float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user):EquaDiffOrdre2(tu_user,tt_user, cte_user,  u0_user, tup_user,ttp_user,ctep_user,u0p_user, h_user,t0_user){
	u = u0;
	up=u0p;
	VePrime = 0;
}

void Euler2::calc_Un(float Ve){ //retourne Un+1 et tn+1 en fonction de un et tn 
	
	//printf("DEBUG %f / %f / %f / %f \n", up, tup, ttp, ctep);

	
	u = u + h*up;

	calc_Unp(Ve);
	
	//printf("DEBUG %f\n", u);
	//getchar();

	t = t+h;
	

}
void Euler2::calc_Unp(float Ve){ 
	
	//printf("AVANT up = %f", up);

	up = up + h*(tup*up+tu*u+tt*Ve+ttp*VePrime+cte);

	//printf("DEBUG %f / %f / %f / %f /%f \n", up, tup, ttp, ctep, h);
	//printf("APRES up = %f et h = %f", up,h);
	//getchar();


}

float Euler2::get_t(){
	return t;
}

float Euler2::get_Un(){
	return u;
}

void Euler2::setVePrime(float Ven, float VenMoins1){
	VePrime = (1/h)*(Ven - VenMoins1);

}
CircuitBEuler2::CircuitBEuler2(float R1_user, float L1_user, float C1_user, float tu_user, float tt_user, float cte_user, float u0_user, float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user):Euler2(tu_user,tt_user,cte_user,u0_user,tup_user,ttp_user,ctep_user,u0p_user,h_user,t0_user){
	R1 = R1_user;
	L1 = L1_user;
	C1 = C1_user;
}

float CircuitBEuler2::calcVs(float Ve){
		tu = -1/(L1*C1);
		tup = -R1/L1;
		tt = 1/(L1*C1);

		Euler2::calc_Un(Ve); //compute the output using Euler2	algo
		
		Vs = u;
		return Vs;
}

CircuitDEuler2::CircuitDEuler2(float R1_user, float L1_user, float C1_user, float tu_user, float tt_user, float cte_user, float u0_user, float tup_user, float ttp_user, float ctep_user, float u0p_user, float h_user,float t0_user):Euler2(tu_user,tt_user,cte_user,u0_user,tup_user,ttp_user,ctep_user,u0p_user,h_user,t0_user){
	R1 = R1_user;
	L1 = L1_user;
	C1 = C1_user;
}

float CircuitDEuler2::calcVs(float Ve){
		tu = -1/(L1*C1);
		tup = -1/(R1*C1);
		ttp = 1/(R1*C1);

		Euler2::calc_Un(Ve); //compute the output using Euler2	algo
		
		Vs = u;
		return Vs;
}