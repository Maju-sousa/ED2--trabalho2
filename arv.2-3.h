
#ifndef ARVORE23_H
#define ARVORE23_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Curso Curso;
typedef struct Disciplina Disciplina;
typedef struct Aluno Aluno;

typedef struct Nobase23 {

    struct Nobase23 *esq;
    struct Nobase23 *centro;
    struct Nobase23 *dir;

    int qtdInfos;

} Nobase23;

typedef struct Arv23Disciplina Arv23Disciplina;

struct Arv23Disciplina {

    Nobase23 base;

    Disciplina *info1;
    Disciplina *info2;
};

typedef struct Arv23Aluno Arv23Aluno;

struct Arv23Aluno {

    Nobase23 base;

    Aluno *info1;
    Aluno *info2;
};
struct Arv23Curso {

    Nobase23 base;

    Curso *info1;
    Curso *info2;
};

typedef struct Curso {
    int codigo;
    char nome[50];
    int qtdBlocos;
    int semanas;

    Arv23Disciplina *raizdisciplinas;

} Curso;
typedef struct Aluno {

    int matricula;
    char nome[50];
    int anoingresso;
    int semestre;

    Curso *curso;

} Aluno;
typedef struct Disciplina {

    int codigo;
    char nome[50];
    int bloco;
    int cargahr;

} Disciplina;

#endif
