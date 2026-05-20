#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vermelho_preta.h"

void limpar_buffer(void) {

    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}


void exibir_menu(void) {


    printf(" 1  - Cadastrar curso\n");
    printf(" 2  - Cadastrar disciplina\n");
    printf(" 3  - Cadastrar aluno\n");

    printf(" 4  - Mostrar alunos de um curso\n");
    printf(" 5  - Mostrar alunos de um curso por ano\n");
    printf(" 6  - Mostrar quantidade de alunos de um curso\n");

    printf(" 7  - Imprimir cursos em ordem\n");
    printf(" 8  - Mostrar dados de um curso\n");
    printf(" 9  - Mostrar cursos com mesma qtd de blocos\n");

    printf("10  - Imprimir disciplinas de um curso\n");
    printf("11  - Buscar disciplina\n");
    printf("12  - Mostrar disciplinas por bloco\n");
    printf("13  - Mostrar disciplinas por carga horaria\n");

    printf("14  - Remover disciplina\n");
    printf("15  - Remover curso\n");

    printf(" 0  - Sair\n");

    printf("========================================\n");
    printf("Opcao: ");

    
}



void menu_cadastrar_curso(Curso **raizCursos) {

    int cod;
    int blocos;
    int semanas;
    int resp;

    char nome[50];

    printf("\n CADASTRAR CURSO \n");



    do {

        printf("Codigo do curso: ");
        scanf("%d", &cod);

        if (buscarCurso(*raizCursos, cod) != NULL) {

            printf(" Codigo ja cadastrado.\n");
        }

    } while (buscarCurso(*raizCursos, cod) != NULL);

    limpar_buffer();



    printf("Nome do curso: ");
    fgets(nome, sizeof(nome), stdin);

    nome[strcspn(nome, "\n")] = '\0';



    do {

        printf("Quantidade de blocos: ");
        scanf("%d", &blocos);

        if (blocos <= 0) {

            printf(" Quantidade invalida.\n");
        }

    } while (blocos <= 0);



    do {

        printf("Quantidade de semanas: ");
        scanf("%d", &semanas);

        if (semanas <= 0) {

            printf(" Quantidade invalida.\n");
        }

    } while (semanas <= 0);

    limpar_buffer();



    resp = add_ArvCurso(raizCursos, cod, nome, blocos, semanas );



    if (resp == SUCESSO) {

        printf(" Curso cadastrado com sucesso.\n");

    } else {

        printf(" Falha no cadastro.\n");
    }
}



void menu_cadastrar_disciplina(Curso *raizCursos) {

    int codCurso;
    int codDisc;
    int bloco;
    int cargahr;
    int resp;

    char nome[50];

    Curso *curso = NULL;



    printf("\n CADASTRAR DISCIPLINA \n");


    do {

        printf("Codigo do curso: ");
        scanf("%d", &codCurso);

        curso = buscarCurso(raizCursos, codCurso);

        if (curso == NULL) {

            printf("[ERRO] Curso nao encontrado.\n");
        }

    } while (curso == NULL);

    limpar_buffer();



    do {

        printf("Codigo da disciplina: ");
        scanf("%d", &codDisc);

        if (buscarDisciplina(
                curso->raizdisciplinas,
                codDisc
            ) != NULL) {

            printf("O Codigo desta disciplina ja cadastrado.\n");
        }

    } while (
        buscarDisciplina(
            curso->raizdisciplinas,
            codDisc
        ) != NULL
    );

    limpar_buffer();



    printf("Nome da disciplina: ");

    fgets(nome, sizeof(nome), stdin);

    nome[strcspn(nome, "\n")] = '\0';



    do {

        printf(
            "Bloco (0 ate %d): ",
            curso->qtdBlocos - 1
        );

        scanf("%d", &bloco);

        if (
            bloco < 0 ||
            bloco >= curso->qtdBlocos
        ) {

            printf("quantidade de blocos invalido.\n");
        }

    } while (
        bloco < 0 ||
        bloco >= curso->qtdBlocos
    );



    do {

        printf(
            "Carga horaria (multiplo de %d): ",
            curso->semanas
        );

        scanf("%d", &cargahr);

        if (
            cargahr <= 0 ||
            cargahr % curso->semanas != 0
        ) {

            printf(" Carga horaria invalida.\n");
        }

    } while (
        cargahr <= 0 ||
        cargahr % curso->semanas != 0
    );

    limpar_buffer();



    resp = add_ArvDisciplina(&curso->raizdisciplinas, codDisc,nome,bloco,cargahr,curso
    );

    if (resp == SUCESSO) {

        printf(" Disciplina cadastrada.\n");

    } else {

        printf(" Falha no cadastro.\n");
    }
}



void menu_cadastrar_aluno(
    Aluno **raizAlunos,
    Curso *raizCursos
) {

    int mat;
    int ano;
    int semestre;
    int codCurso;
    int resp;

    char nome[50];

    Curso *curso = NULL;



    printf("\n CADASTRAR ALUNO \n");

    do {

        printf("Matricula: ");
        scanf("%d", &mat);

        if (buscarAluno(*raizAlunos, mat) != NULL) {

            printf(" Matricula ja cadastrada.\n");
        }

    } while (
        buscarAluno(*raizAlunos, mat) != NULL
    );

    limpar_buffer();



    printf("Nome do aluno: ");

    fgets(nome, sizeof(nome), stdin);

    nome[strcspn(nome, "\n")] = '\0';



    do {

        printf("Codigo do curso: ");
        scanf("%d", &codCurso);

        curso = buscarCurso(raizCursos, codCurso);

        if (curso == NULL) {

            printf("[ERRO] Curso nao encontrado.\n");
        }

    } while (curso == NULL);


    do {

        printf("Ano de ingresso: ");
        scanf("%d", &ano);

        if (ano <= 0) {

            printf(" Ano invalido.\n");
        }

    } while (ano <= 0);



    do {

        printf("Semestre (1 ou 2): ");
        scanf("%d", &semestre);

        if (
            semestre != 1 &&
            semestre != 2
        ) {

            printf("Semestre invalido.\n");
        }

    } while (
        semestre != 1 &&
        semestre != 2
    );

    limpar_buffer();



    resp = add_ArvAluno(
        raizAlunos,
        mat,
        nome,
        ano,
        semestre,
        curso
    );



    if (resp == SUCESSO) {

        printf(" Aluno cadastrado.\n");

    } else {

        printf("Falha no cadastro.\n");
    }
}



void menu_mostrar_alunos_por_curso(
    Aluno *raizAlunos,
    Curso *raizCursos
) {

    int codCurso;

    Curso *curso = NULL;



    printf("\n--- ALUNOS DE UM CURSO ---\n");



    do {

        printf("Codigo do curso: ");
        scanf("%d", &codCurso);

        curso = buscarCurso(raizCursos, codCurso);

        if (curso == NULL) {

            printf(" Curso nao encontrado.\n");
        }

    } while (curso == NULL);

    limpar_buffer();



    printf("\nCurso: %s\n", curso->nome);

    mostrar_alunos_por_curso(
        raizAlunos,
        codCurso
    );
}



void menu_mostrar_alunos_por_ano(
    Aluno *raizAlunos,
    Curso *raizCursos
) {

    int codCurso;
    int ano;

    Curso *curso = NULL;



    printf("\n ALUNOS POR ANO \n");



    do {

        printf("Codigo do curso: ");
        scanf("%d", &codCurso);

        curso = buscarCurso(raizCursos, codCurso);

        if (curso == NULL) {

            printf("Curso nao encontrado.\n");
        }

    } while (curso == NULL);



    printf("Ano: ");
    scanf("%d", &ano);

    limpar_buffer();



    mostrar_alunos_por_ano(raizAlunos, codCurso, ano
    );
}



void menu_contar_alunos(
    Aluno *raizAlunos,
    Curso *raizCursos
) {

    int codCurso;
    int contador = 0;

    Curso *curso = NULL;



    printf("\n QUANTIDADE DE ALUNOS \n");



    do {

        printf("Codigo do curso: ");
        scanf("%d", &codCurso);

        curso = buscarCurso(raizCursos, codCurso);

        if (curso == NULL) {

            printf("[ERRO] Curso nao encontrado.\n");
        }

    } while (curso == NULL);

    limpar_buffer();



    contar_alunos_por_curso(
        raizAlunos,
        codCurso,
        &contador
    );



    printf(
        "\nQuantidade de alunos: %d\n",
        contador
    );
}

void menu_mostrar_curso(Curso *raizCursos) {

    int codCurso;

    printf("\n MOSTRAR CURSO \n");

    printf("Codigo do curso: ");
    scanf("%d", &codCurso);

    limpar_buffer();

    mostrar_curso(
        raizCursos,
        codCurso
    );
}

void menu_mostrar_cursos_blocos(Curso *raizCursos) {

    int qtdBlocos;

    printf("\n CURSOS POR BLOCOS \n");

    printf("Quantidade de blocos: ");
    scanf("%d", &qtdBlocos);

    limpar_buffer();

    mostrar_cursos_por_blocos(
        raizCursos,
        qtdBlocos
    );
}
void menu_imprimir_disciplinas(Curso *raizCursos
) {

    int codCurso;

    Curso *curso = NULL;

    printf("\n DISCIPLINAS DO CURSO \n");

    do {

        printf("Codigo do curso: ");
        scanf("%d", &codCurso);

        curso = buscarCurso(
            raizCursos,
            codCurso
        );

        if (curso == NULL) {

            printf("Curso nao encontrado.\n");
        }

    } while (curso == NULL);

    limpar_buffer();

    imprimir_disciplinas(
        curso->raizdisciplinas
    );
}
void menu_buscar_disciplina(
    Curso *raizCursos
) {

    int codCurso;
    int codDisc;
    int flag = SUCESSO;

    printf("\n BUSCAR DISCIPLINA \n");

    printf("Codigo do curso: ");
    scanf("%d", &codCurso);

    printf("Codigo da disciplina: ");
    scanf("%d", &codDisc);

    limpar_buffer();

    imprimir_dados_disciplina(
        raizCursos,
        codCurso,
        codDisc,
        &flag
    );

    if (flag == ERRO_CURSO) {

        printf("Curso nao encontrado.\n");

    } else if (flag == ERRO_DISCIPLINA) {

        printf("Disciplina nao encontrada.\n");
    }
}

void menu_disciplinas_por_bloco(
    Curso *raizCursos
) {

    int codCurso;
    int bloco;
    int flag = SUCESSO;

    printf("\n DISCIPLINAS POR BLOCO \n");

    printf("Codigo do curso: ");
    scanf("%d", &codCurso);

    printf("Bloco: ");
    scanf("%d", &bloco);

    limpar_buffer();

    listar_disciplinas_por_bloco(
        raizCursos,
        codCurso,
        bloco,
        &flag
    );

    if (flag == ERRO_CURSO) {

        printf("Curso nao encontrado.\n");

    } else if (flag == ERRO_DISCIPLINA) {

        printf("Nenhuma disciplina encontrada.\n");
    }
}


void menu_disciplinas_por_carga(
    Curso *raizCursos
) {

    int codCurso;
    int carga;
    int flag = SUCESSO;

    printf("\n DISCIPLINAS POR CARGA HORARIA \n");

    printf("Codigo do curso: ");
    scanf("%d", &codCurso);

    printf("Carga horaria: ");
    scanf("%d", &carga);

    limpar_buffer();

    listar_disciplinas_por_carga(
        raizCursos,
        codCurso,
        carga,
        &flag
    );

    if (flag == ERRO_CURSO) {

        printf("Curso nao encontrado.\n");

    } else if (flag == ERRO_DISCIPLINA) {

        printf("Nenhuma disciplina encontrada.\n");
    }
}
void menu_remover_disciplina(
    Curso *raizCursos
) {

    int codCurso;
    int codDisc;
    int status;

    printf("\n REMOVER DISCIPLINA \n");

    printf("Codigo do curso: ");
    scanf("%d", &codCurso);

    printf("Codigo da disciplina: ");
    scanf("%d", &codDisc);

    limpar_buffer();

    status = remove_disciplina_arv(
        raizCursos,
        codCurso,
        codDisc
    );

    if (status == SUCESSO) {

        printf("Disciplina removida.\n");

    } else if (status == ERRO_CURSO) {

        printf("Curso nao encontrado.\n");

    } else {

        printf("Disciplina nao encontrada.\n");
    }
}

void menu_remover_curso(
    Curso **raizCursos
) {

    int codCurso;
    int status;

    printf("\n REMOVER CURSO \n");

    printf("Codigo do curso: ");
    scanf("%d", &codCurso);

    limpar_buffer();

    status = remove_curso_arv(
        raizCursos,
        codCurso
    );

    if (status == SUCESSO) {

        printf("Curso removido.\n");

    } else if (status == ERRO_CURSO) {

        printf("Curso nao encontrado.\n");

    } else {

        printf(
            "Curso possui disciplinas cadastradas.\n"
        );
    }
}
int main(void){

    Curso *raizCursos = NULL;
    Aluno *raizAlunos = NULL;

    int opcao;

    do {

        exibir_menu();

        scanf("%d", &opcao);

        limpar_buffer();

        switch (opcao) {

        case 1:

            menu_cadastrar_curso(
                &raizCursos
            );

            break;

        case 2:

            menu_cadastrar_disciplina(
                raizCursos
            );

            break;

        case 3:

            menu_cadastrar_aluno(
                &raizAlunos,
                raizCursos
            );

            break;

        case 4:

            menu_mostrar_alunos_por_curso(
                raizAlunos,
                raizCursos
            );

            break;

        case 5:

            menu_mostrar_alunos_por_ano(
                raizAlunos,
                raizCursos
            );

            break;

        case 6:

            menu_contar_alunos(
                raizAlunos,
                raizCursos
            );

            break;

        case 7:

            if (raizCursos == NULL) {

                printf(
                    "Nenhum curso cadastrado.\n"
                );

            } else {

                imprimir_cursos_em_ordem(
                    raizCursos
                );
            }

            break;

        case 8:

            menu_mostrar_curso(
                raizCursos
            );

            break;

        case 9:

            menu_mostrar_cursos_blocos(
                raizCursos
            );

            break;

        case 10:

            menu_imprimir_disciplinas(
                raizCursos
            );

            break;

        case 11:

            menu_buscar_disciplina(
                raizCursos
            );

            break;

        case 12:

            menu_disciplinas_por_bloco(
                raizCursos
            );

            break;

        case 13:

            menu_disciplinas_por_carga(
                raizCursos
            );

            break;

        case 14:

            menu_remover_disciplina(
                raizCursos
            );

            break;

        case 15:

            menu_remover_curso(
                &raizCursos
            );

            break;

        case 0:

            printf(
                "\nEncerrando sistema...\n"
            );

            break;

        default:

            printf(
                "Opcao invalida.\n"
            );
        }

    } while (opcao != 0);

    return 0;
}
