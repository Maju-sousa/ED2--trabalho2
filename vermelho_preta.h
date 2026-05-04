#ifndef VERMELHO_PRETA_H
#define VERMELHO_PRETA_H
#define RED 1
#define BLACK 0

typedef struct Curso Curso;
typedef struct Disciplina Disciplina;

typedef struct Nobase {
    struct Nobase *esq;
    struct Nobase *dir;
    int cor;
} Nobase;

typedef struct Aluno {
    Nobase base; 
    int matricula;
    char nome[50];
    int anoingresso;
    int semestre;
    Curso *curso;
} Aluno;

typedef struct Curso {
    Nobase base;
    int codigo;
    char nome[50];
    int qtdBlocos;
    int semanas;
    Disciplina *raizdisciplinas;
} Curso;

typedef struct Disciplina {
    Nobase base;
    int codigo;
    char nome[50];
    int bloco;
    int cargahr;
} Disciplina;
#endif
