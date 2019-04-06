#include "Sources.h"
#include <stdio.h>
#include <math.h>

source::source(float decallage_user,float V0_user){

	decallage=decallage_user;
	V0=V0_user;
}
float source::calc_Ve(float temps){ return 1; }

periodique::periodique(float periode_user,float temps_haut_user,float decallage_user,float V0_user):source(decallage_user,V0_user){
	periode=periode_user;
	temps_haut=temps_haut_user;
}
periodique::periodique(float periode_user,float decallage_user,float V0_user):source(decallage_user,V0_user){}


aperiodique::aperiodique(float decallage_user,float V0_user, float duree_user):source(decallage_user, V0_user){
	duree=duree_user;
}
aperiodique::aperiodique(float decallage_user,float V0_user):source(decallage_user, V0_user){
	
}

//constructeurs signaux periodiques
sinus::sinus(float periode_user,float decallage_user,float V0_user):periodique(periode_user, decallage_user, V0_user){
}

triangle::triangle(float periode_user,float decallage_user,float V0_user):periodique(periode_user, decallage_user, V0_user){
}
rectangle::rectangle(float periode_user,float temps_haut_user,float decallage_user,float V0_user):periodique(periode_user, temps_haut_user, decallage_user, V0_user){
}

//constructeurs signaux aperiodiques
echelon::echelon(float decallage_user,float V0_user):aperiodique(decallage_user,V0_user){
}

impulsion::impulsion(float decallage_user,float V0_user,float duree_user):aperiodique(decallage_user,V0_user,duree_user){
}


float impulsion::calc_Ve(float temps){
	if(temps >= decallage && temps <= (decallage + duree)){
		return V0;
	}else{
		return 0.0;
	}


}

float echelon::calc_Ve(float temps){
	if(temps < decallage){
			return 0.0;
	}else{
		return V0;
	}
}

float rectangle::calc_Ve(float temps){

	int temps_modulo = (int)temps%(int)periode;


	if(temps_modulo >= decallage && temps_modulo <= temps_haut + decallage){
		return V0;
	
	}else{
		return 0.0;
	}

}

float sinus::calc_Ve(float temps){

	return sin(temps - decallage);

}

float triangle::calc_Ve(float temps){

	int temps_modulo = (int)temps%(int)periode;


	if(temps_modulo >= decallage && temps_modulo <= 0.5*periode + decallage){

		return temps_modulo*(2*V0/periode);
		
	
	}else{
		return V0-temps_modulo*(2*V0/periode);
	}

}