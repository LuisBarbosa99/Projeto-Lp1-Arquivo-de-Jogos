#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
		
	struct Jogos{
		char genero[100], titulo[100], plataforma[100];
		int ano_lancamento, codigo;
		float preco;
	};
	
	void Ler_banco_de_dados(){ //serve para pegar os dados passados para o arquivo txt e alocar em variáveis
		char titdb[100], gendb[100], platdb[100];
		int coddb,anodb,cont=0,i=0;
		float precodb;
		struct Jogos jogo[cont];
		FILE *banco_dados;
		
		banco_dados=fopen("Banco_de_dados.txt","r");
		while( (fscanf(banco_dados,"%s %i %s %s %i %f \n", &titdb, &coddb, &gendb, &platdb, &anodb, &precodb))!=EOF ) {
			strcpy(jogo[cont].titulo, titdb);
			jogo[cont].codigo= coddb;
			strcpy(jogo[cont].genero, gendb);
			strcpy(jogo[cont].plataforma,platdb);	
			jogo[cont].ano_lancamento=anodb;
			jogo[cont].preco=precodb;
			cont++;
			i++;
		}
		fclose(banco_dados);
	}
		
	void Abrir_banco_de_dados(){ //tem a função de abrir o arquivo a ser utilizado pelo programa
		FILE *banco_dados;
		if(fopen("Banco_de_dados.txt","r")==NULL){
			printf("\tBanco de dados nao encontrado. Criando novo banco de dados.\t\n");
			banco_dados=fopen("Banco_de_dados.txt","w");
			fclose(banco_dados);
		}
	}
   
	void Salvar_banco_de_dados(struct Jogos jogo){
		FILE *banco_dados;
		
		banco_dados=fopen("Banco_de_dados.txt","w");
	
		fprintf(banco_dados,"%s ", jogo.titulo);
		fprintf(banco_dados,"%i ", jogo.codigo);
		fprintf(banco_dados,"%s ", jogo.genero);
		fprintf(banco_dados,"%s ", jogo.plataforma);	
		fprintf(banco_dados,"%i ", jogo.ano_lancamento);
		fprintf(banco_dados,"%f \n", jogo.preco);
		fclose(banco_dados);
	}
	
	//Para evitar repetições de código, foi criada a função cadastro
	void form_cadastro(){
		static int i=0;
		char nomejogo[100];
		struct Jogos jogo[i];
		jogo[i].codigo=i;
		strcpy(jogo[i].titulo, nomejogo);
		
		genero: //LABEL DE RETORNO 01
		printf("   Genero: ");
		gets(jogo[i].genero);
		if(strcmp(jogo[i].genero,"")==0 ||  strcmp(jogo[i].genero," ")==0){
			printf("\n*Insira um genero valido!\n");
			goto genero; //RETORNA A LABEL GÊNERO (01)
		}
		
		plataforma: //LABEL DE RETORNO 02
		printf("   Plataforma: ");
		gets(jogo[i].plataforma);
		if(strcmp(jogo[i].plataforma,"")==0 ||  strcmp(jogo[i].plataforma," ")==0){
			printf("\n*Erro. Insira uma plataforma valida!\n");
			goto plataforma;  //RETORNA A LABEL PLATAFORMA (02)
		}
		
		anolancamento: //LABEL DE RETORNO 03
		printf("   Ano de lancamento: ");
		fflush(stdin); 
		scanf("%i", &jogo[i].ano_lancamento);
		if(jogo[i].ano_lancamento<=1972){
			printf("\n*Erro. O primeiro jogo foi lancado em 1972.\n");
			goto anolancamento;  //RETORNA A LABEL ANOLANCAMENTO (03)
		}
		
		preco: //LABEL DE RETORNO 04
		printf("   Preco em reais: ");
		fflush(stdin); 
		scanf("%f", &jogo[i].preco);
		if(jogo[i].preco<=0){
			printf("\n*Erro. Insira um valor maior que zero.\n");
			goto preco;  //RETORNA A LABEL PRECO (04)
		}
			
		Salvar_banco_de_dados(jogo[i]);
		i++;
		printf("\n*Cadastro Realizado com Sucesso!");
		fflush(stdin); 
	}

	void cadastrar(){
		char nomejogo[100],op;
		int i=0,c=0,igual=1;
		struct Jogos jogo[c];
	    do{
	    	iniciocadastrar: //LABEL DE RETORNO 05
			igual=1;
	    	printf("\n\t[ Cadastrar um novo Jogo ]\n\n");
	    	
	    	titulo:
	    	printf("   Nome do jogo: ");
			fflush(stdin);
			gets(nomejogo);
			if(strcmp(nomejogo,"")==0 ||  strcmp(nomejogo,"")==0){
				printf("\n*Insira um titulo valido!\n");
				goto titulo;
			}
			
			if(i == 0){
	   			form_cadastro(); //CHAMA A FUNÇÃO FORM_CADASTRO PARA EVITAR REPETIÇÃO DE CÓDIGO
	   		} else {
	   			for(c=0; c<i; c++){
					if(strcmp(jogo[c].titulo, nomejogo) == 0){
						printf("\n*Erro. Ja Existe um Jogo com este nome!\n\n");
						igual=0;
						goto iniciocadastrar; //RETORNA A LABEL INICIOCADASTRAR (05)
					}
				}
				
				if(igual==1){
					form_cadastro();  //CHAMA A FUNÇÃO FORM_CADASTRO PARA EVITAR REPETIÇÃO DE CÓDIGO
				}
			} 
			
			erro_cadastro: //LABEL DE RETORNO 06
		   	printf("\n*Deseja realizar mais cadastros? <S>Sim ou <N>Nao\n>");
    		fflush(stdin); 
			scanf("%c", &op);
	   		fflush(stdin); 
	   			if(op!='n' && op!='N'  && op!='s'&& op!='S'){
	   				printf("\n*Erro. Opcao invalida.\n");
	   					goto erro_cadastro; //RETORNA A LABEL ERRO_CADASTRO (06)
	   			}
      	}while((op!='n' && op!='N')  && (op=='s'||op=='S'));
      	
    	Salvar_banco_de_dados(jogo[c]);
	}
      
	void editar(){
		int novoano,i=0,c=0,opcao;
		char novotitulo[100],novogenero[100],novaplataforma[100],nomejogo[100],op;
		struct Jogos jogo[c];
		if(i!=0){
			printf("\n\n 	   [ Editar um cadastro ]");
			printf("\n   Insira o nome exato do jogo: ");
			fflush(stdin); 
			gets(nomejogo);	
	   		for(c=0;c<i;c++){
				if(strcmp(jogo[c].titulo, nomejogo)==0){
					printf("\nJogo encontrado:\n ");
					printf("\n   Titulo: %s", jogo[c].titulo);
					printf("\n   Codigo: %i", jogo[c].codigo);
					printf("\n   Genero: %s", jogo[c].genero);
					printf("\n   Plataforma: %s", jogo[c].plataforma);	
					printf("\n   Ano de lancamento: %i", jogo[c].ano_lancamento);
					printf("\n	 Preco: R$ %.2f\n", jogo[c].preco);
		 	      	do{
						printf("\nEscolha qual das opcoes editar:\n 1. Titulo\n 2. Genero\n 3. Plataforma\n 4. Ano de lancamento\n>");
						scanf("%i",&opcao);
				   			switch(opcao){
								case 1:
									printf("\nInsira o novo titulo: ");
									fflush(stdin); //LIMPA A SUJEIRA NA ENTRADA DE DADOS
									gets(novotitulo);
									if(strcmp(novotitulo, nomejogo)==0){
										printf("\n*Erro. O novo titulo nao pode ser igual ao antigo.");
									}else {
										strcpy(jogo[c].titulo,novotitulo);
										printf("\nNovo titulo: %s\n\n*Editado com sucesso!", jogo[c].titulo);
									}
								break;
								
								case 2:
									printf("\nInsira o novo genero: ");
									fflush(stdin); 
									gets(novogenero);
									if(strcmp(jogo[c].genero, novogenero)==0){
										printf("\n*Erro. O novo genero nao pode ser igual ao antigo");
									}else{
										strcpy(jogo[c].genero,novogenero);
										printf("\nNovo genero: %s\n\n*Editado com sucesso!", jogo[c].genero);
									}
								break;
								
								case 3:
									printf("\nInsira a nova plataforma: ");
									fflush(stdin); 
									gets(novaplataforma);
										if(strcmp(jogo[c].plataforma, novaplataforma)==0 ){
											printf("\n*Erro. A nova plataforma nao pode ser igual a antiga");
									   	}else{
											strcpy(jogo[c].plataforma,novaplataforma);
											printf("Nova plataforma: %s\n\n*Editado com sucesso!", jogo[c].plataforma);
										}
								break;
								
								case 4:
									printf("\nInsira o novo ano de lancamento: ");
									fflush(stdin); 
									scanf("%i",&novoano);
									if (jogo[c].ano_lancamento == novoano){
										printf("\n*Erro. O novo ano de lancamento nao pode ser igual ao antigo");	
									}else{
										jogo[c].ano_lancamento=novoano;
										printf("Novo ano de lancamento: %i\n\n*Editado com sucesso!", jogo[c].ano_lancamento);
									}
								break;
								
								default:
									printf("\n*Erro. Opcao invalida. Insira uma opcao de 1 a 4\n");
								break;
							 }
							 
							printf("\n\n*Continuar editando? <S>Sim ou <N>Nao\n>");
							fflush(stdin);
							scanf("%c",&op);
			    		}while(op!='n' && op!='N');
					break;
		   		} else printf("\n*Erro. Jogo nao encontrado\n");
			}
		}else{
			printf("\n*Opcao indisponivel, nao ha nenhum jogo cadastrado!\n Para utilizar essa funcao, deve haver pelomenos um jogo cadastrado.\n");
		}
		Salvar_banco_de_dados(jogo[c]);
	}
	
	//PARA EVITAR REPETIÇÕES DE CÓDIGO FOI CRIADA A FUNÇÃO EXIBIRJOGOS
	void exibirjogos(int c){
		struct Jogos jogo[c];
		
		printf("\n|Titulo: %s", jogo[c].titulo);
		printf("\n|Codigo: %i", jogo[c].codigo);
		printf("\n|Genero: %s", jogo[c].genero);
		printf("\n|Plataforma: %s", jogo[c].plataforma);	
		printf("\n|Lancamento: %i", jogo[c].ano_lancamento);
		printf("\n|Preco: R$  %.2f", jogo[c].preco);
		printf("\n\n-----------------------------------------------------------------------------\n");
	}
	
	void pesquisar(){
		char nomejogo[100],op;
		int igual=1,i=0,c=0,cod,ano;
		float busca_preco;
		struct Jogos jogo[c];
		if(i!=0){
			printf("\n\n\t[ Pesquisar um Jogo ]");
			do{
		 		fflush(stdin); 
				printf("\nBuscar por:\n 1. Titulo\n 2. Codigo\n 3. Genero\n 4. Plataforma\n 5. Ano de lancamento\n 6. Preco\n>>");
				scanf("%i",&op);
				   	switch(op){
						case 1:
							printf("\nInsira o titulo do jogo a ser encontrado: ");
							fflush(stdin); 
							gets(nomejogo);
							for(c=0;c<i;c++){
								if(strcmp(jogo[c].titulo, nomejogo)==0){
									printf("-----------------------------------------------------------------------------\n");		
									exibirjogos(c); 
									igual=0;
		  						}		 
							}
							
							if(igual==1){
								printf("\n*Erro 404. O jogo Jogo %s nao foi encontrado\n", nomejogo);								
							}	
						break;
						
						case 2:							
							printf("\nInsira o codigo do jogo a ser encontrado: ");
							fflush(stdin); 
							scanf("%i",&cod);
							for(c=0;c<i;c++){
								if(jogo[c].codigo==cod){
									printf("-----------------------------------------------------------------------------\n");
									exibirjogos(c); 
									igual=0;
		  						}		
							}
							
							if(igual==1){
		  						printf("\n*Erro. O codigo '%i' nao faz referencia a nenhum jogo.\n", cod);
		  					}
						break;
									
						case 3:
							printf("\nInsira o genero para listar os jogos disponiveis: ");
							fflush(stdin); 
							gets(nomejogo);
								for(c=0;c<i;c++){
									if(strcmp(jogo[c].genero, nomejogo)==0){
										printf("-----------------------------------------------------------------------------\n");
										exibirjogos(c);
										igual=0;
		  							}		 
								}
								
								if(igual==1){		
		  							printf("\n*Erro. Não foram encontrados jogos com o genero '%s' .\n", nomejogo);
		  						}
						break;
						
						case 4:
							printf("\nInsira a plataforma para listar os jogos disponiveis: ");
							fflush(stdin); 
							gets(nomejogo);
							for(c=0;c<i;c++){
								if(strcmp(jogo[c].plataforma, nomejogo)==0){
									printf("-----------------------------------------------------------------------------\n");
									exibirjogos(c); 
									igual=0;
		  						}		 
							}
							
							if(igual==1){
								printf("\n*Erro. Nao foram encontrados jogos para a plataforma '%s'.\n", nomejogo);								
							}	
						break;
									
						case 5:
							printf("\nInsira o ano de lancamento para listar os jogos disponiveis: ");
							fflush(stdin); 
							scanf("%i",&ano);
								for(c=0;c<i;c++){
									if(jogo[c].ano_lancamento==ano){
										printf("-----------------------------------------------------------------------------\n");
										exibirjogos(c); //CHAMA A FUNÇÃO EXIBIRJOGOS PARA EVITAR REPETIÇÃO DE CÓDIGO
										igual=0;
				  					}		 
								}
								
								if(igual==1){
									printf("\n*Erro. Nao foram encontrados jogos com o ano de lancamento '%i'.\n", ano);								
								}	
						break;
						
						case 6:
							printf("\nDeseja listar os jogos ate que limite de preco?\n ");
							fflush(stdin); 
							scanf("%f",&busca_preco);
							for(c=0;c<i;c++){
								if(jogo[c].preco<=busca_preco){
									printf("-----------------------------------------------------------------------------\n");
									exibirjogos(c); //CHAMA A FUNÇÃO EXIBIRJOGOS PARA EVITAR REPETIÇÃO DE CÓDIGO
									igual=0;
		  						}		 
							}
							
							if(igual==1){
								printf("\n*Erro. nao foram encontrados ogos com precos menores ou iguais a '%f' .\n", busca_preco);								
							}	
						break;
									
						default:
							printf("\nErro. Opcao invalida. Insira uma opcao de 1 a 5");
							break;
					}
					
				printf("\n\n*Continuar pesquisando? <S>Sim ou <N>Nao\n>");
				fflush(stdin); 
			}while(op!='n' && op!='N');
		} else {
			printf("\n*Opcao indisponivel, pois nao ha nenhum jogo cadastrado!\n Para utilizar essa funcao, deve haver pelo menos um jogo cadastrado.\n");
     	}
	}

	void deletar(){
		int a=0,c=0,i=0,igual=1;
		char del_busca[100],op;
		struct Jogos jogo[a];
		
		if(i!=0){
			printf("Insira o nome do jogo a ser excluido: ");
			fflush(stdin);
			printf ("Deseja realmente excluir o jogo '%s' ? <S>Sim ou <N>Nao\n",del_busca);
			gets(&op);
			while (op!= 'n' && op!='N'); 
			for(a=0;a<i;a++){
				if(strcmp(del_busca,jogo[a].titulo)==0){
					printf("\n*Encontrado e excluido do sistema.\n");
					for(c=a; c<i; c++){
						strcpy(jogo[c].titulo, jogo[c+1].titulo);
						jogo[c].codigo= jogo[c+1].codigo;
						strcpy(jogo[c].genero, jogo[c+1].genero);
						strcpy(jogo[c].plataforma, jogo[c+1].plataforma);
						jogo[c].ano_lancamento= jogo[c+1].ano_lancamento;
						jogo[c].preco= jogo[c+1].preco;
						igual=0;
					}
					i--;
					break; 
				} 	
			}
			if(igual==1){
				printf("\n*Erro. Jogo '%s' nao encontrado .\n", del_busca);								
			}	
		} else {
			printf("\n*Opcao indisponivel, nao ha nenhum jogo cadastrado!\n Para utilizar essa funcao, deve haver pelomenos um jogo cadastrado.\n");
		}
	}

	main(){
		int opcao;
		Abrir_banco_de_dados();
		Ler_banco_de_dados();
	 
		 do{
 			menuprincipal:
 			printf("\nMenu Principal >");
 			printf("\n\n 	   [ Menu Principal ]\n");
 	 		printf("\n\t1. Cadastrar \n\t2. Editar \n\t3. Excluir \n\t4. Pesquisar\n\t5. Sair\n\nDigite a opcao desejada: ");
		 	fflush(stdin); //LIMPA A SUJEIRA NA ENTRADA DE DADOS
			scanf("%i",&opcao);
			switch(opcao){
				case 1:
					printf("--------------------------------------------------\n");
					printf("Menu Principal > Cadastrar >\n");
					cadastrar();
				break;
			
				case 2: 
				 	printf("--------------------------------------------------\n");
					printf("Menu Principal > Editar >\n");
					editar();
				break;
			
				case 3:
					printf("--------------------------------------------------\n");
					printf("Menu Principal > Excluir >\n");
					deletar();
				break;
			
				case 4:
					printf("--------------------------------------------------\n");
					printf("Menu Principal > Pesquisar >\n");
					pesquisar();
					break;
				case 5:
					system("cls");
					return 0;
				break;
			}
			
			if(opcao<1 || opcao>5) {
				printf("\n-----------------------------------------------"); 
				printf("\n*Erro. Opcao invalida. Insira uma opcao de 1 a 5");
				printf("\n-----------------------------------------------");
			}
		}while(opcao!=5);
		
		system("PAUSE");
		
	}		
