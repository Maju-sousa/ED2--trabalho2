#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vermelho_preta.h"

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


static void exibir_menu(void) {

    printf("\n========================================\n");
    printf("   SISTEMA DE GESTAO ACADEMICA — UFPI   \n");
    printf("========================================\n");

    printf(" 1  - Cadastrar curso\n");
    printf(" 2  - Cadastrar disciplina\n");
    printf(" 3  - Cadastrar aluno\n");

    printf(" 4  - Mostrar alunos de um curso\n");
    printf(" 5  - Mostrar alunos de um curso por ano de ingresso\n");
    printf(" 6  - Mostrar quantidade de alunos de um curso\n");

    printf(" 7  - Imprimir cursos em ordem crescente\n");
    printf(" 8  - Mostrar dados de um curso\n");
    printf(" 9  - Mostrar cursos com mesma quantidade de blocos\n");

    printf(" 10 - Imprimir disciplinas de um curso em ordem crescente\n");
    printf(" 11 - Buscar disciplina de um curso\n");
    printf(" 12 - Mostrar disciplinas de um bloco de um curso\n");
    printf(" 13 - Mostrar disciplinas de um curso com mesma carga horaria\n");

    printf(" 14 - Remover disciplina de um curso\n");
    printf(" 15 - Remover curso sem disciplinas\n");

    printf(" 0  - Sair\n");

    printf("----------------------------------------\n");
    printf(" Opcao: ");
}


static void menu_cadastrar_curso(Curso **raizCursos) {
    int  cod, blocos, semanas, resp;
    char nome[50];

    printf("\n--- CADASTRAR CURSO ---\n");
    printf("Codigo do curso  : ");
    scanf("%d", &cod);
    limpar_buffer();

    printf("Nome do curso    : ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Qtd. de blocos   : ");
    scanf("%d", &blocos);

    printf("Semanas/discipl. : ");
    scanf("%d", &semanas);
    limpar_buffer();

    resp = add_ArvCurso(raizCursos, cod, nome, blocos, semanas);

    switch (resp) {
        case SUCESSO:
            printf("Curso cadastrado com sucesso.\n");
            break;
        case ERRO_REPETIDO:
            printf(" Codigo de curso ja cadastrado.\n");
            break;
        case ERRO_CURSO:
            printf("Blocos e semanas devem ser maiores que zero.\n");
            break;
        default:
            printf("Falha no cadastro do curso.\n");
    }
}


static void menu_cadastrar_disciplina(Curso *raizCursos) {
    int  codCurso, codDisc, bloco, cargahr, resp;
    char nome[50];
    Curso *curso = NULL;

    printf("\n--- CADASTRAR DISCIPLINA ---\n");
    printf("Codigo do curso      : ");
    scanf("%d", &codCurso);
    limpar_buffer();

    curso = buscarCurso(raizCursos, codCurso);

    if (curso == NULL) {
        printf("Curso nao encontrado.\n");
        return;
    }

    printf("Codigo da disciplina : ");
    scanf("%d", &codDisc);
    limpar_buffer();

    printf("Nome da disciplina   : ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Bloco (0 a %d)      : ", curso->qtdBlocos - 1);
    scanf("%d", &bloco);

    printf("Carga horaria (mult. de %d): ", curso->semanas);
    scanf("%d", &cargahr);
    limpar_buffer();

    resp = add_ArvDisciplina(
        &curso->raizdisciplinas,
        codDisc, nome, bloco, cargahr,
        curso
    );

    switch (resp) {
        case SUCESSO:
            printf("Disciplina cadastrada com sucesso.\n");
            break;
        case ERRO_REPETIDO:
            printf("Codigo de disciplina ja cadastrado neste curso.\n");
            break;
        case ERRO_BLOCO:
            printf("Bloco invalido (deve ser menor que %d).\n",
                   curso->qtdBlocos);
            break;
        case ERRO_CARGA:
            printf("Carga horaria deve ser multiplo de %d.\n",
                   curso->semanas);
            break;
        case ERRO_CURSO:
            printf(" Curso invalido.\n");
            break;
        default:
            printf("Falha no cadastro da disciplina.\n");
    }
}


static void menu_cadastrar_aluno(Aluno **raizAlunos, Curso *raizCursos) {
    int  mat, ano, semestre, codCurso, resp;
    char nome[50];
    Curso *curso = NULL;

    printf("\n--- CADASTRAR ALUNO ---\n");
    printf("Matricula            : ");
    scanf("%d", &mat);
    limpar_buffer();

    printf("Nome do aluno        : ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Codigo do curso      : ");
    scanf("%d", &codCurso);
    limpar_buffer();

    curso = buscarCurso(raizCursos, codCurso);

    if (curso == NULL) {
        printf(" Curso nao encontrado.\n");
        return;
    }

    printf("Ano de ingresso      : ");
    scanf("%d", &ano);

    printf("Semestre (1 ou 2)    : ");
    scanf("%d", &semestre);
    limpar_buffer();

    resp = add_ArvAluno(raizAlunos, mat, nome, ano, semestre, curso);

    switch (resp) {
        case SUCESSO:
            printf("Aluno cadastrado com sucesso.\n");
            break;
        case ERRO_REPETIDO:
            printf(" Matricula ja cadastrada.\n");
            break;
        case ERRO_SEMESTRE:
            printf("Semestre invalido (informe 1 ou 2).\n");
            break;
        case ERRO_CURSO:
            printf("Curso invalido.\n");
            break;
        default:
            printf("Falha no cadastro do aluno.\n");
    }
}


static void menu_contar_alunos(Aluno *raizAlunos, Curso *raizCursos) {
    int   codCurso;
    int   contador = 0;
    Curso *curso   = NULL;

    printf("\n--- QUANTIDADE DE ALUNOS DE UM CURSO ---\n");
    printf("Codigo do curso: ");
    scanf("%d", &codCurso);
    limpar_buffer();

    curso = buscarCurso(raizCursos, codCurso);

    if (curso == NULL) {
        printf("Curso nao encontrado.\n");
        return;
    }

    contar_alunos_por_curso(raizAlunos, codCurso, &contador);

    printf("\nCurso   : %s (cod. %d)\n", curso->nome, curso->codigo);
    printf("Alunos  : %d\n", contador);
}


static void menu_imprimir_cursos(Curso *raizCursos) {

    printf("\n--- CURSOS EM ORDEM CRESCENTE ---\n");

    if (raizCursos == NULL) {
        printf("Nenhum curso cadastrado.\n");
        return;
    }

    imprimir_cursos_em_ordem(raizCursos);
}


static void menu_buscar_disciplina(Curso *raizCursos) {
    int codCurso, codDisc;
    int flag = SUCESSO;

    printf("\n--- BUSCAR DISCIPLINA DE UM CURSO ---\n");
    printf("Codigo do curso      : ");
    scanf("%d", &codCurso);

    printf("Codigo da disciplina : ");
    scanf("%d", &codDisc);
    limpar_buffer();

    imprimir_dados_disciplina(raizCursos, codCurso, codDisc, &flag);

    switch (flag) {
        case SUCESSO:
            break;
        case ERRO_CURSO:
            printf(" Curso nao encontrado.\n");
            break;
        case ERRO_DISCIPLINA:
            printf("Disciplina nao encontrada neste curso.\n");
            break;
        default:
            printf("Falha na busca.\n");
    }
}


static void menu_listar_disciplinas_por_bloco(Curso *raizCursos) {
    int codCurso, bloco;
    int flag = SUCESSO;

    printf("\n--- DISCIPLINAS DE UM BLOCO DE UM CURSO ---\n");
    printf("Codigo do curso: ");
    scanf("%d", &codCurso);

    printf("Bloco          : ");
    scanf("%d", &bloco);
    limpar_buffer();

    listar_disciplinas_por_bloco(raizCursos, codCurso, bloco, &flag);

    switch (flag) {
        case SUCESSO:
            break;
        case ERRO_CURSO:
            printf("Curso nao encontrado.\n");
            break;
        case ERRO_DISCIPLINA:
            printf("Nenhuma disciplina encontrada no bloco %d.\n", bloco);
            break;
        default:
            printf("Falha na busca.\n");
    }
}


static void menu_listar_disciplinas_por_carga(Curso *raizCursos) {
    int codCurso, cargahr;
    int flag = SUCESSO;

    printf("\n--- DISCIPLINAS DE UM CURSO COM MESMA CARGA HORARIA ---\n");
    printf("Codigo do curso  : ");
    scanf("%d", &codCurso);

    printf("Carga horaria (h): ");
    scanf("%d", &cargahr);
    limpar_buffer();

    listar_disciplinas_por_carga(raizCursos, codCurso, cargahr, &flag);

    switch (flag) {
        case SUCESSO:
            break;
        case ERRO_CURSO:
            printf(" Curso nao encontrado.\n");
            break;
        case ERRO_DISCIPLINA:
            printf(" Nenhuma disciplina encontrada com carga de %d h.\n", cargahr);
            break;
        default:
            printf("Falha na busca.\n");
    }
}


static void menu_remover_curso(Curso **raizCursos) {
    int codCurso;
    int status = SUCESSO;

    printf("\n--- REMOVER CURSO ---\n");
    printf("Codigo do curso: ");
    scanf("%d", &codCurso);
    limpar_buffer();

    status = remove_curso_arv(raizCursos, codCurso);

    switch (status) {
        case SUCESSO:
            printf("Curso removido com sucesso.\n");
            break;
        case ERRO_CURSO:
            printf(" Curso nao encontrado.\n");
            break;
        case ERRO_DISCIPLINA:
            printf("O curso possui disciplinas cadastradas e nao pode ser removido.\n");
            break;
        default:
            printf("Falha na remocao do curso.\n");
    }
}


static void menu_mostrar_alunos_por_curso(Aluno *raizAlunos,
                                           Curso *raizCursos) {
    int    codCurso;
    Curso *curso = NULL;

    printf("\n--- MOSTRAR ALUNOS DE UM CURSO ---\n");
    printf("Codigo do curso: ");
    scanf("%d", &codCurso);
    limpar_buffer();

    curso = buscarCurso(raizCursos, codCurso);

    if (curso == NULL) {
        printf(" Curso nao encontrado.\n");
    } else {
        printf("\nAlunos do curso: %s (cod. %d)\n",
               curso->nome, curso->codigo);
        printf("------------------------------\n");
        mostrar_alunos_por_curso(raizAlunos, codCurso);
        printf("------------------------------\n");
    }
}


static void menu_mostrar_alunos_por_ano(Aluno *raizAlunos,
                                         Curso *raizCursos) {
    int    codCurso, ano;
    Curso *curso = NULL;

    printf("\n--- MOSTRAR ALUNOS DE UM CURSO POR ANO DE INGRESSO ---\n");
    printf("Codigo do curso  : ");
    scanf("%d", &codCurso);

    printf("Ano de ingresso  : ");
    scanf("%d", &ano);
    limpar_buffer();

    curso = buscarCurso(raizCursos, codCurso);

    if (curso == NULL) {
        printf("Curso nao encontrado.\n");
    } else {
        printf("\nAlunos do curso: %s (cod. %d) — ano %d\n",
               curso->nome, curso->codigo, ano);
        printf("------------------------------\n");
        mostrar_alunos_por_ano(raizAlunos, codCurso, ano);
        printf("------------------------------\n");
    }
}


static void menu_remover_disciplina(Curso *raizCursos) {
    int codCurso, codDisc;
    int status = SUCESSO;

    printf("\n--- REMOVER DISCIPLINA DE UM CURSO ---\n");
    printf("Codigo do curso      : ");
    scanf("%d", &codCurso);

    printf("Codigo da disciplina : ");
    scanf("%d", &codDisc);
    limpar_buffer();

    status = remove_disciplina_arv(raizCursos, codCurso, codDisc);

    switch (status) {
        case SUCESSO:
            printf("Disciplina removida com sucesso.\n");
            break;
        case ERRO_CURSO:
            printf("Curso nao encontrado.\n");
            break;
        case ERRO_DISCIPLINA:
            printf("Disciplina nao encontrada neste curso.\n");
            break;
        default:
            printf("Falha na remocao da disciplina.\n");
    }
}


static void menu_mostrar_curso(Curso *raizCursos) {
    int codCurso;

    printf("\n--- MOSTRAR DADOS DE UM CURSO ---\n");
    printf("Codigo do curso: ");
    scanf("%d", &codCurso);
    limpar_buffer();

    printf("------------------------------\n");
    mostrar_curso(raizCursos, codCurso);
    printf("------------------------------\n");
}


static void menu_mostrar_cursos_por_blocos(Curso *raizCursos) {
    int qtdBlocos;

    printf("\n--- CURSOS COM MESMA QUANTIDADE DE BLOCOS ---\n");
    printf("Quantidade de blocos: ");
    scanf("%d", &qtdBlocos);
    limpar_buffer();

    printf("------------------------------\n");
    mostrar_cursos_por_blocos(raizCursos, qtdBlocos);
    printf("------------------------------\n");
}


static void menu_imprimir_disciplinas(Curso *raizCursos) {
    int    codCurso;
    Curso *curso = NULL;

    printf("\n--- DISCIPLINAS DE UM CURSO EM ORDEM CRESCENTE ---\n");
    printf("Codigo do curso: ");
    scanf("%d", &codCurso);
    limpar_buffer();

    curso = buscarCurso(raizCursos, codCurso);

    if (curso == NULL) {
        printf("Curso nao encontrado.\n");
    } else {
        printf("\nDisciplinas do curso: %s (cod. %d)\n",
               curso->nome, curso->codigo);
        printf("------------------------------\n");
        imprimir_disciplinas(curso->raizdisciplinas);
        printf("------------------------------\n");
    }
}

int main(void) {

    Curso *raizCursos = NULL;
    Aluno *raizAlunos = NULL;
    int    opcao      = -1;

    do {

        exibir_menu();

        scanf("%d", &opcao);

        limpar_buffer();

        switch (opcao) {

            case 1:
                menu_cadastrar_curso(&raizCursos);
                break;

            case 2:
                menu_cadastrar_disciplina(raizCursos);
                break;

            case 3:
                menu_cadastrar_aluno(&raizAlunos, raizCursos);
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
                menu_imprimir_cursos(
                    raizCursos
                );
                break;

            case 8:
                menu_mostrar_curso(
                    raizCursos
                );
                break;

            case 9:
                menu_mostrar_cursos_por_blocos(
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
                menu_listar_disciplinas_por_bloco(
                    raizCursos
                );
                break;

            case 13:
                menu_listar_disciplinas_por_carga(
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
                    "\nEncerrando o sistema. Ate logo!\n"
                );
                break;

            default:
                printf(
                    "Opcao invalida. Tente novamente.\n"
                );
        }

    } while (opcao != 0);

    return 0;
}