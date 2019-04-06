/*CLASSE MERE SOURCE*/
class source{
protected:
	float V0,decallage;

public:
	source(float decallage_user,float V0_user);	
	virtual float calc_Ve(float temps);
	//~source();
};
/*CLASSE FILLE NIVEAU 1: PERIODIQUE*/
class periodique: public source {
protected:
	float periode,temps_haut;
public:
	periodique(float periode_user,float temps_haut_user,float decallage_user,float V0_user);
	periodique(float periode_user,float decallage_user,float V0_user);
	//~periodique();
};

/*CLASSE FILLE NIVEAU 1: APERIODIQUE*/
class aperiodique: public source {
protected:
	float duree;
public:
	aperiodique(float decallage_user,float V0_user, float duree_user); //constructeur 1
	aperiodique(float decallage_user,float V0_user); //constructeur 2
};
//////////////////////////////////////
//////////////////////////////////////
/*CLASSE FILLE NIVEAU 2: ECHELON (APERIODIQUE)*/
class echelon: public aperiodique {
public: 
	float decallage_user;
	echelon(float decallage_user,float V0_user);
	virtual float calc_Ve(float temps);
	
};
/*CLASSE FILLE NIVEAU 2: IMPULSION (APERIODIQUE)*/
class impulsion: public aperiodique {
public:
	impulsion(float decallage_user,float V0_user,float duree_user);
	virtual float calc_Ve(float temps);
};
/*CLASSE FILLE NIVEAU 2: RECTANGLE (PERIODIQUE)*/
class rectangle: public periodique {
public:
	rectangle(float periode_user,float temps_haut_user,float decallage_user,float V0_user);
	virtual float calc_Ve(float temps);
};
/*CLASSE FILLE NIVEAU 2: TRIANGLE (APERIODIQUE)*/
class triangle: public periodique {
public:
	triangle(float periode_user,float decallage_user,float V0_user);
	virtual float calc_Ve(float temps);
	
};
/*CLASSE FILLE NIVEAU 2: SINUS (APERIODIQUE)*/
class sinus: public periodique {
public:
	sinus(float periode_user,float decallage_user,float V0_user);
	virtual float calc_Ve(float temps);
	
};
