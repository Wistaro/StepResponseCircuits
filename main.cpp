#include <iostream.h>
#include <fstream.h>
#include "euler.h"
#include "Sources.h"
#include <stdio.h>

#define OUT_FILE "data_debug.txt"
#define NB_POINTS 1000
#define VBE 0.6

void main(){

	/*ENTREE*/
	float entree = 0;
	float temps = 0;
	float V0 = 1.0;
	float decallage = 0.0; 
	float periode = 100.0;
	float temps_haut = periode/2;
	float duree = temps_haut;

	
	//echelon input(decallage, V0);
	// rectangle input(periode,temps_haut,decallage,V0);
	//impulsion input(decallage,V0,duree);
	sinus input(periode,decallage,V0);
	//triangle input(periode,decallage,V0);


	/*SORTIE*/
	float sortie = 0;
	ofstream fichier;
	fichier.open(OUT_FILE, ios::out|ios::trunc);


	/*Initialisation des variables d'Euler*/
	float t0 = 0.0;
	float h0 = 1e-9;
	float u0 = 0;
	float u0p = 0;

	// ~ Circuit D ordre 2
	char ordre = 2;
	char nom_circuit = 'D';
	float R = 1.2;
	float C = 0.1e-6;
	float L = 10e-9;
	CircuitDEuler2 circuit(R,L,C,0,0,0,u0,0,0,0,u0p,h0,t0);

	// ~ Circuit B ordre 2	
	/*char ordre = 2;
	float R = 50;
	float L = 1e-6;
	float C = 0.1e-9;
	char nom_circuit = 'B';
	CircuitBEuler2 circuit(R,L,C,0,0,0,u0,0,0,0,u0p,h0,t0);*/
	

	// ~ Circuit A Ordre 1
	/*char nom_circuit = 'A';
	char ordre = 1;
	float R = 50;
	float C = 1e-9;
	CircuitAEuler circuit(R,C,0,0,0,u0,h0,t0);*/


	// ~ Circuit C Ordre 1
	/*char nom_circuit = 'C';
	char ordre = 1;
	float R1 = 36;
	float R2 = 180;
	float C = (float)1e-9;
	CircuitCEuler circuit(R1,R2,C,VBE, 0,0,0,u0,h0,t0);*/


	/*Test si le fichier de sortie est bon*/
	if(fichier.bad()) printf("\nErreur dans le fichier");
	
	printf("Calcul en cours du circuit %c..\n", nom_circuit);  

	/*Début du test*/
	for(int n = 0; n <= NB_POINTS; n++){
		
		entree = input.calc_Ve(n);
		temps = circuit.get_t();
		sortie = circuit.calcVs(entree);

		if(n>=1 && ordre>1) circuit.setVePrime(entree,input.calc_Ve(n-1));

		/*Ecriture dans le fichier*/
		fichier << temps << " "<< entree << " " << sortie <<endl;

	}

	printf("\nCalcul termine\n");
	fichier.close();

}