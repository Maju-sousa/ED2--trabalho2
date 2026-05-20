#ifndef VERMELHO_PRETA_H
#define VERMELHO_PRETA_H

#define RED 1
#define BLACK 0

#define SUCESSO        1
#define ERRO_CURSO     0
#define ERRO_BLOCO     2
#define ERRO_CARGA     3
#define ERRO_SEMESTRE  4
#define ERRO_REPETIDO  5
#define ERRO_DISCIPLINA 6

typedef struct Curso      Curso;
typedef struct Disciplina Disciplina;

typedef struct Nobase {
    struct Nobase *esq;
    struct Nobase *dir;
    int cor;
} Nobase;

typedef struct Aluno {
    Nobase  base;
    int     matricula;
    char    nome[50];
    int     anoingresso;
    int     semestre;
    Curso  *curso;
} Aluno;

typedef struct Curso {
    Nobase      base;
    int         codigo;
    char        nome[50];
    int         qtdBlocos;
    int         semanas;
    Disciplina *raizdisciplinas;
} Curso;

typedef struct Disciplina {
    Nobase base;
    int    codigo;
    char   nome[50];
    int    bloco;
    int    cargahr;
} Disciplina;

int     cor(Nobase *raiz);
void    trocaCor(Nobase *raiz);
Nobase *rotacionaEsquerda(Nobase *raiz);
Nobase *rotacionaDireita(Nobase *raiz);

Curso *criarCurso(int cod, char nome[], int blocos, int semanas);
Curso *inserirCurso(Curso *r, int cod, char nome[], int blocos,
                    int semanas, int *resp);
int    add_ArvCurso(Curso **r, int cod, char nome[], int blocos,
                    int semanas);
Curso *buscarCurso(Curso *raiz, int cod);

Disciplina *criarDisciplina(int cod, char nome[], int bloco, int cargahr);
Disciplina *inserirDisciplina(Disciplina *r, int cod, char nome[],
                               int bloco, int cargahr, int *resp);
int         add_ArvDisciplina(Disciplina **r, int cod, char nome[],
                               int bloco, int cargahr, Curso *curso);
Disciplina *buscarDisciplina(Disciplina *r, int cod);

Aluno *criarAluno(int mat, char nome[], int ano, int semestre, Curso *curso);
Aluno *inserirAluno(Aluno *r, int mat, char nome[], int ano,
                    int semestre, Curso *curso, int *resp);
int    add_ArvAluno(Aluno **r, int mat, char nome[], int ano,
                    int semestre, Curso *curso);

void mostrar_alunos_por_curso(Aluno *r, int codCurso);
void mostrar_alunos_por_ano(Aluno *a, int codCurso, int ano);

void contar_alunos_por_curso(Aluno *r, int codCurso, int *contador);

void imprimir_cursos_em_ordem(Curso *r);

void mostrar_curso(Curso *r, int codCurso);
void mostrar_cursos_por_blocos(Curso *c, int qtdBlocos);
void imprimir_disciplinas(Disciplina *r);

void imprimir_dados_disciplina(Curso *raizCursos,
                                int codCurso,
                                int codDisciplina,
                                int *flag);
void listar_disciplinas_por_bloco(Curso *raizCursos, int codCurso, int bloco,    int *flag);
void listar_disciplinas_por_carga(Curso *raizCursos, int codCurso, int cargahr,  int *flag);

Nobase *moverDireitaRED(Nobase *r);
Nobase *moverEsquerdaRED(Nobase *r);
Nobase *balancear(Nobase *r);
Nobase *procurarMenor(Nobase *r);
Nobase *removerMenor(Nobase *r);

Curso *removerCurso(Curso *r, int cod);
int    remove_curso_arv(Curso **raizCursos, int codCurso);

Disciplina *removerDisciplina(Disciplina *r, int cod);
int         remove_disciplina_arv(Curso *raizCursos, int codCurso, int codDisc);

#endif 
