#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#include <math.h>

// Função que realiza exponenciação modular rápida
long long int expo(long long int base, int e, long long int m, int i){
	long long int resto = 1;
	
	// Desloca o primeiro bit de 1(um) i vezes
	if(e & (1<<i)) resto = (resto * base) % m;
	base = (base*base) % m;

	// O "i" vai somente ate a quantidade de bits de bits(32)
	i++;
	if (i<32) resto=(resto*expo(base,e,m,i))%m;

	return resto;
}

/* Função auxiliar de exponenciação. Poupa a passagem de um
   parametro onde for chamada para realizar a exponenciação*/
int exponenciacao(int base, int expoente, long long int modulo){
	return expo(base, expoente, modulo, 0);
}

// Funcao que busca o inverso de "e"
int inverso(int e, int mod){
	int i=0;
	for (i ; i<mod ; i++){
		if((e*i)%mod == 1) return i;
	}

	return -1;
}

// Função que verifica se dois numeros são coprimos
int coprimos(int x, int y){
	if(x%y == 1) return 1;
	if(x%y == 0) return 0;
	return coprimos(y , x%y);
}

// Funcao que verifica se um número é primo
int primo(int n){
	for (int i = 2; i < sqrt(n); i++)
		if(n%i == 0) return 0;

	return 1;
}

#endif
