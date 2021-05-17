#include <stdio.h>
#include <string.h>
#include "mylibrary.h" // Biblioteca criada com as fórmulas usadas no projeto

void gerar_chave(){
	int p, q, e;
	// Dois arquivos são abertos pra armazenar as chaves pública e privada
	FILE* publica = fopen("chave_publica.txt" , "w");
	FILE* privada = fopen("chave_privada.txt" , "w");

	printf("Digite o valor de P: ");
	scanf("%d", &p);
	printf("Digite o valor de Q: ");
	scanf("%d", &q);
	printf("Digite o valor de E: ");
	scanf("%d", &e);

	// É feita a verificação se P e Q são primos
	if(!primo(p) || !primo(q)){
		printf("P e/ou Q nao eh primo!!!\n");
		return;
	}
	// É feita a verificação se E e (p-1)(q-1) são coprimos
	if(!coprimos(e , (p-1)*(q-1))){
		printf("E e (P-1)*(Q-1) nao sao coprimos!!!\n");
		return;
	}

	// Armazena as chaves nos arquivos
	fprintf(publica, "n: %d\ne: %d", p*q, e);
	fprintf(privada, "p: %d\nq: %d\ne: %d\n", p, q, e);

	// Fecha os arquivos
	fclose(publica);
	fclose(privada);

	return;
}

void encriptar(){
	char texto[100];
	int n, e;
	// Abre o arquivo para armazenar a mensagem encriptada
	FILE* mensagem = fopen("mensagem_encriptada.txt" , "w");
	getchar();
	printf("Digite o texto a ser encriptado: ");
	fgets(texto, sizeof(texto), stdin);
	printf("Digite n: ");
	scanf("%d", &n);
	printf("Digite e: ");
	scanf("%d", &e);

	// Trata cada um dos caracteres e, depois de encriptados, os armazena no arquivo
	for(int i=0 ; i<strlen(texto) ; i++){
		if(texto[i] == ' '){
			fprintf(mensagem, "%d ", exponenciacao(28, e, n));
		}
		else{
			fprintf(mensagem, "%d ", exponenciacao(texto[i]-63, e, n) );
		}
	}

	return;
}

void desencriptar(){
	int p, q, e, original;
	long long int d, cifrada;
	// Abre os arquivos de mensagem encriptada e desencriptada
	FILE* mensagem = fopen("mensagem_encriptada.txt" , "r");
	FILE* desencriptada = fopen("mensagem_desencriptada.txt" , "w");

	printf("Digite o valor de P: ");
	scanf("%d", &p);
	printf("Digite o valor de Q: ");
	scanf("%d", &q);
	printf("Digite o valor de E: ");
	scanf("%d", &e);

	// Calcula o inverso de E
	d = inverso(e, (p-1)*(q-1));

	printf("O inverso eh: %lld\n", d);

	// Lê os valores da mensagem encriptada, converte
	// para a mensagem original e armazena-os em outro arquivo
	while(fscanf(mensagem , "%lld" , &cifrada) != EOF){
		original = exponenciacao(cifrada, d, (p*q));
		//printf("original: %d\n", original+63);
		if(original == 28){
			fprintf(desencriptada, "%c", ' ');
			printf(" ");
		}
		else{
			fprintf(desencriptada, "%c", original+63);
			printf("%c", original+63);
		}
	}
	// Fecha os arquivos
	fclose(mensagem);
	fclose(desencriptada);

	return;
}

int main(){
	int opcao;
	printf("Digite a opcao desejada\n");
	printf("1 Gerar chave\n2 Encriptar\n3 Desencriptar\n");
	scanf("%d", &opcao);

	if(opcao == 1){
		gerar_chave();
	}
	else if(opcao == 2){
		encriptar();
	}
	else if(opcao == 3){
		desencriptar();
	}
	else{
		printf("Opcao invalida!!!\n");
	}

	return 0;
}
