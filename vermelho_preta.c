#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define RED 1
#define BLACK 0

#define SUCESSO 1
#define ERRO_CURSO 0
#define ERRO_BLOCO 2
#define ERRO_CARGA 3
#define ERRO_SEMESTRE 4
#define ERRO_REPETIDO 5
#define ERRO_DISCIPLINA 6

#include "vermelho_preta.h"

int cor(Nobase *raiz) {
    if (raiz == NULL) 
       return BLACK;
 return raiz->cor;
}
void trocaCor(Nobase *raiz) {
    raiz->cor = !raiz->cor;
    if (raiz->esq != NULL)
        raiz->esq->cor = !raiz->esq->cor;
    if (raiz->dir != NULL)
        raiz->dir->cor = !raiz->dir->cor;
}

Nobase* rotacionaEsquerda(Nobase *raiz) {
    Nobase *aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    aux->cor = raiz->cor;
    raiz->cor = RED;
    return aux;
}

Nobase* rotacionaDireita(Nobase *raiz) {
    Nobase *aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->cor = raiz->cor;
    raiz->cor = RED;
    return aux;
}

Curso* criarCurso(int cod, char nome[], int blocos, int semanas){
    Curso *novo = (Curso*) malloc(sizeof(Curso));
    if (novo != NULL) {
        
        novo->codigo= cod;
        strcpy(novo->nome, nome);
        novo->qtdBlocos= blocos;
        novo->semanas= semanas;
        novo->raizdisciplinas= NULL;
        novo->base.cor= RED;
        novo->base.esq= NULL;
        novo->base.dir= NULL;
    }
    return novo;
}

Curso* inserirCurso(Curso *r, int cod, char nome[], int blocos, int semanas, int *resp) {
    if (r == NULL) {

        if (blocos <= 0 || semanas <= 0) {
            *resp = ERRO_CURSO;
        } else {
            r = criarCurso(cod, nome, blocos, semanas);
            *resp = SUCESSO;
        }

    } else {

        if (cod < r->codigo) {

            r->base.esq = (Nobase*)inserirCurso(
                (Curso*)r->base.esq,
                cod, nome, blocos, semanas,
                resp
            );

        } 
        else if (cod > r->codigo) {

            r->base.dir = (Nobase*)inserirCurso(
                (Curso*)r->base.dir,
                cod, nome, blocos, semanas,
                resp
            );

        } 
        else {
            *resp = ERRO_REPETIDO;
        }

        
        if (*resp == SUCESSO) {

            if (cor(r->base.dir) == RED && cor(r->base.esq) == BLACK)
                r = (Curso*)rotacionaEsquerda((Nobase*)r);

            if (cor(r->base.esq) == RED && cor(r->base.esq->esq) == RED)
                r = (Curso*)rotacionaDireita((Nobase*)r);

            if (cor(r->base.esq) == RED && cor(r->base.dir) == RED)
                trocaCor((Nobase*)r);
        }
    }

    return r;
}

int add_ArvCurso(Curso **r, int cod, char nome[], int blocos, int semanas) {
    int resp = 1;
    *r = inserirCurso(*r, cod, nome, blocos, semanas, &resp);
    if (*r != NULL) (*r)->base.cor=BLACK;
    return resp;
}
Curso* buscarCurso(Curso *raiz, int cod){
    Curso *result = NULL;

    if (raiz != NULL) {
        if (cod == raiz->codigo) {
            result = raiz;
        } else {
            if (cod < raiz->codigo) {
                result = buscarCurso((Curso*) raiz->base.esq, cod);
            } else {
                result = buscarCurso((Curso*) raiz->base.dir, cod);
            }
        }
    }
    return result;
}
Disciplina* criarDisciplina(int cod, char nome[], int bloco, int cargahr) {
    Disciplina *novo = (Disciplina*) malloc(sizeof(Disciplina));
    if (novo != NULL) {
       
        novo->codigo = cod;
        strcpy(novo->nome, nome);
        novo->bloco = bloco;
        novo->cargahr = cargahr;
        novo->base.cor = RED;
        novo->base.esq = NULL;
        novo->base.dir = NULL;

    }
    return novo;
}

Disciplina* inserirDisciplina(Disciplina *r, int cod, char nome[], int bloco, int cargahr, int *resp) {

    if (r == NULL) {
        r = criarDisciplina(cod, nome, bloco, cargahr);
        *resp = SUCESSO;
    } 
    else {

        if (cod < r->codigo) {

            r->base.esq = (Nobase*)inserirDisciplina(
                (Disciplina*)r->base.esq,
                cod, nome, bloco, cargahr,
                resp
            );

        } 
        else if (cod > r->codigo) {

            r->base.dir = (Nobase*)inserirDisciplina(
                (Disciplina*)r->base.dir,
                cod, nome, bloco, cargahr,
                resp
            );

        } 
        else {
            *resp = ERRO_REPETIDO;
        }

        if (*resp == SUCESSO) {

            if (cor(r->base.dir) == RED && cor(r->base.esq) == BLACK)
                r = (Disciplina*)rotacionaEsquerda((Nobase*)r);

            if (cor(r->base.esq) == RED && cor(r->base.esq->esq) == RED)
                r = (Disciplina*)rotacionaDireita((Nobase*)r);

            if (cor(r->base.esq) == RED && cor(r->base.dir) == RED)
                trocaCor((Nobase*)r);
        }
    }

    return r;
}
int add_ArvDisciplina(Disciplina **r, int cod, char nome[], int bloco, int cargahr, Curso *curso) {
    int resp = 1;
    int status = SUCESSO;

    if (curso == NULL) {
        status = ERRO_CURSO;
    }
    else if (bloco >= curso->qtdBlocos) {
        status = ERRO_BLOCO;
    }
    else if (cargahr % curso->semanas != 0) {
        status = ERRO_CARGA;
    }
    else {
        *r = inserirDisciplina(*r, cod, nome, bloco, cargahr, &resp);

        if (*r != NULL)
            (*r)->base.cor = BLACK;

        if (resp ==  ERRO_REPETIDO)
            status = ERRO_REPETIDO;
    }

    return status;
}
Disciplina* buscarDisciplina(Disciplina *r, int cod) {

    Disciplina *result = NULL;

    if (r != NULL) {

        if (cod == r->codigo) {
            result = r;
        } else {
            if (cod < r->codigo) {
                result = buscarDisciplina(
                    (Disciplina*) r->base.esq,
                    cod
                );
            } else {
                result = buscarDisciplina( (Disciplina*) r->base.dir,  cod
                );
            }
        }
    }
    return result;
}

Aluno* criarAluno(int mat, char nome[], int ano, int semestre, Curso *curso) {
    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));
    if (novo!= NULL) {
       
        novo->matricula = mat;
        strcpy(novo->nome, nome);
        novo->anoingresso = ano;
        novo->semestre = semestre;
        novo->curso = curso;
        novo->base.cor = RED;
        novo->base.esq = NULL;
        novo->base.dir = NULL;
    }
    return novo;
}

Aluno* inserirAluno(Aluno *r, int mat, char nome[], int ano, int semestre, Curso *curso, int *resp) {

    if (r == NULL) {
        r = criarAluno(mat, nome, ano, semestre, curso);
        *resp = SUCESSO;
    } 
    else {

        if (mat < r->matricula) {

            r->base.esq = (Nobase*)inserirAluno( (Aluno*)r->base.esq,mat, nome, ano, semestre, curso, resp
            );

        } 
        else if (mat > r->matricula) {

            r->base.dir = (Nobase*)inserirAluno(
                (Aluno*)r->base.dir,
                mat, nome, ano, semestre, curso, resp
            );

        } 
        else {
            *resp = ERRO_REPETIDO;
        }

        if (*resp == SUCESSO) {

            if (cor(r->base.dir) == RED && cor(r->base.esq) == BLACK)
                r = (Aluno*)rotacionaEsquerda((Nobase*)r);

            if (cor(r->base.esq) == RED && cor(r->base.esq->esq) == RED)
                r = (Aluno*)rotacionaDireita((Nobase*)r);

            if (cor(r->base.esq) == RED && cor(r->base.dir) == RED)
                trocaCor((Nobase*)r);
        }
    }

    return r;
}

int add_ArvAluno(Aluno **r, int mat, char nome[], int ano, int semestre, Curso *curso) {
    int status = SUCESSO;


    if (curso == NULL) {
        status = ERRO_CURSO;
    } 
   
    else if (semestre != 1 && semestre != 2) {
        status = ERRO_SEMESTRE;
    } 
    else {
        int result = SUCESSO;
        *r = inserirAluno(*r, mat, nome, ano, semestre, curso, &result);

        if (result == ERRO_REPETIDO) {
            status = ERRO_REPETIDO;
        }

        if (*r != NULL)
            (*r)->base.cor = BLACK;
    }

    return status; 
}
//1
void mostrar_alunos_por_curso(Aluno *r, int codCurso) {
    if (r != NULL) {
       
        mostrar_alunos_por_curso((Aluno*)r->base.esq, codCurso);
        if (r->curso != NULL && r->curso->codigo == codCurso) {
            printf("matricula:%d \n Nome:%s\n", r->matricula, r->nome);
        }
        mostrar_alunos_por_curso((Aluno*)r->base.dir, codCurso);
    }
}
///2
void mostrar_alunos_por_ano(Aluno *a, int codCurso, int ano){
    if(a!=NULL){
        mostrar_alunos_por_ano((Aluno*)a->base.esq,codCurso, ano);
         if (a->curso != NULL &&a->curso->codigo == codCurso &&a->anoingresso == ano){
             printf("Matricula: %d | Nome: %s\n", a->matricula, a->nome);
        }
         mostrar_alunos_por_ano((Aluno*)a->base.dir,codCurso, ano);
    }

}
//3 e 4 com lucrecia 

//5
void mostrar_curso(Curso *r, int codCurso){
   
    Curso *c = buscarCurso(r, codCurso);
    if (c != NULL) {
        printf("Codigo: %d\n", c->codigo);
        printf("Nome: %s\n", c->nome);
        printf("Quantidade de blocos: %d\n", c->qtdBlocos);
        printf("Semanas por disciplina: %d\n", c->semanas);
    } else {
        printf("Curso nao encontrado.\n");
    }
}

//6
void mostrar_cursos_por_blocos(Curso *c, int qtdBlocos) {
    if (c != NULL) {
        mostrar_cursos_por_blocos((Curso*)c->base.esq, qtdBlocos);

        if (c->qtdBlocos == qtdBlocos) {
            printf("Codigo: %d | Nome: %s\n", c->codigo, c->nome);
        }

        mostrar_cursos_por_blocos((Curso*)c->base.dir, qtdBlocos);
    }
}
//7 sera preciso duas funções mas a in-ordem ja garante que esta na ordem crescente 
void imprimir_disciplinas(Disciplina *r) {
    if (r != NULL) {
        
        imprimir_disciplinas((Disciplina*)r->base.esq);
        printf("codigo: %d\n Nome: %-25s\n Bloco: %d\n Carga Horaria: %d\n", 
                r->codigo, r->nome, r->bloco, r->cargahr);
        imprimir_disciplinas((Disciplina*)r->base.dir);
    }
}

void buscar_disciplinas_curso(Curso *c, int cod){
   
    Curso *curso = buscarCurso(c, cod);
    if (curso == NULL) {
        printf("Curso nao encontrado!\n");
    } else {
        if (curso->raizdisciplinas == NULL) {
            printf("Esse curso não possui disciplinas cadastradas!\n");
        } else {
            printf("Disciplinas do curso %s:\n\n", curso->nome);
            imprimir_disciplinas(curso->raizdisciplinas);
        }
    }
}
//Lucrecia essas funções são auxuliares das funções de remoção use então não precisa fazer elas novamente so fazer 
// a função 12 normal tenta seguir a mesma estrutura de remoção da 11 que fez aqui a baixo

Nobase* moverDireitaRED(Nobase *r) {

    trocaCor(r);

    if (r->esq != NULL && r->esq->esq != NULL && cor(r->esq->esq) == RED) {

        r = rotacionaDireita(r);

        trocaCor(r);
    }

    return r;
}
Nobase* moverEsquerdaRED(Nobase *r) {

    trocaCor(r);

    if (r->dir != NULL && r->dir->esq != NULL && cor(r->dir->esq) == RED) {

        r->dir = rotacionaDireita(r->dir);

        r = rotacionaEsquerda(r);

        trocaCor(r);
    }

    return r;
}
Nobase* balancear(Nobase *r) {

    if (cor(r->dir) == RED)
        r = rotacionaEsquerda(r);

    if (cor(r->esq) == RED &&
        cor(r->esq->esq) == RED)
        r = rotacionaDireita(r);

    if (cor(r->esq) == RED &&
        cor(r->dir) == RED)
        trocaCor(r);

    return r;
}
Nobase* procurarMenor(Nobase *r) {

    Nobase *atual = r;

    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}
Nobase* removerMenor(Nobase *r) {

    if (r->esq == NULL) {
        free(r);
        return NULL;
    }

    if (cor(r->esq) == BLACK &&
        cor(r->esq->esq) == BLACK)
        r = moverEsquerdaRED(r);

    r->esq = removerMenor(r->esq);

    return balancear(r);
}
//função 11:

Disciplina* removerDisciplina(Disciplina *r, int cod) {

    if (cod < r->codigo) {

        if (cor(r->base.esq) == BLACK &&
            cor(r->base.esq->esq) == BLACK) {

            r = (Disciplina*) moverEsquerdaRED((Nobase*) r);
        }

        r->base.esq =
            (Nobase*) removerDisciplina(
                (Disciplina*) r->base.esq,
                cod
            );

    } else {

        if (cor(r->base.esq) == RED)
            r = (Disciplina*) rotacionaDireita((Nobase*) r);

        if (cod == r->codigo &&
            r->base.dir == NULL) {

            free(r);
            r = NULL;
        }

        else {

            if (cor(r->base.dir) == BLACK &&
                cor(r->base.dir->esq) == BLACK) {

                r = (Disciplina*) moverDireitaRED((Nobase*) r);
            }

            if (cod == r->codigo) {
                Disciplina *aux;

                aux = (Disciplina*)
                 procurarMenor(r->base.dir);

                r->codigo = aux->codigo;
                strcpy(r->nome, aux->nome);
                r->bloco = aux->bloco;
                r->cargahr = aux->cargahr;

                r->base.dir = removerMenor(r->base.dir);

            } else {

                r->base.dir =
                    (Nobase*) removerDisciplina(
                        (Disciplina*) r->base.dir,
                        cod
                    );
            }
        }
    }

    if (r != NULL)
        r = (Disciplina*) balancear((Nobase*) r);

    return r;
}

int remove_disciplina_arv(Curso *raizCursos, int codCurso, int codDisc) {
    int status = SUCESSO;
    Curso *curso;
    Disciplina *disciplina;

    curso = buscarCurso(raizCursos, codCurso);

    if (curso == NULL) {

        status = ERRO_CURSO;

    } else {

        disciplina = buscarDisciplina(curso->raizdisciplinas, codDisc
        );
        
        if (disciplina == NULL) {
            status = ERRO_DISCIPLINA;
        } else {

            curso->raizdisciplinas =
                removerDisciplina(
                    curso->raizdisciplinas,
                    codDisc
                );

            if (curso->raizdisciplinas != NULL)
                curso->raizdisciplinas->base.cor = BLACK;
        }
    }

    return status;
}
