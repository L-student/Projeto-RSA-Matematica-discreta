#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#include <math.h>

// Função que realiza exponenciação modular rápida
long long int expo(long long int base, int e, long long int m, int i){
	long long int resto = 1;
	if(e & (1<<i) ){ // Desloca o primeiro bit de 1(um) i vezes
		resto = base % m;
	}
	base = (base*base)%m;
	if (i<31){ // O "i" vai somente ate a quantidade de bits de bits(32)
		resto=(resto*expo(base,e,m,i+1))%m;
	}
	return resto;
}

/* Função auxiliar de exponenciação. Poupa a passagem de um
   parametro onde for chamada para realizar a exponenciação*/
long long int exponenciacao(int base, int expoente, long long int modulo){
	return expo(base, expoente, modulo, 0);
}

// Funcao que busca o inverso de "e"
int inverso(int e, int mod){
	for (int i = 0; i<mod ; i++){
		if((e*i)%mod == 1){
			return i;
		}
	}
	return -1;
}

// Função que verifica se dois numeros são coprimos
int coprimos(int x, int y){
	if(x%y == 1){
		return 1;
	}else if(x%y == 0){
		return 0;
	}else{
		return coprimos(y , x%y);
	}
}

// Funcao que verifica se um número é primo
int primo(int n){
	for (int i = 2; i < sqrt(n); i++){
		if(n%i == 0){
			return 0;
		}
	}

	return 1;
}

#endif