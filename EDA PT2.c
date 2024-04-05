#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct no
{
    int chave, bal;
    struct no *dir;
    struct no *esq;
}No;

void Caso1 (No (*(*pt)), bool (*(*h)));
void Caso2 (No (*(*pt)), bool (*(*h)));
void InicarNo(No (*(*pt)), int x);
void InserirAVL(int x, No (*(*pt)), bool (*(*h)));
void PreOrdem (No (*pt));
void Caso1R (No (*(*pt)), bool (*(*h)));
void Caso2R (No (*(*pt)), bool (*(*h)));
void balancear(No (*(*pt)), char R, bool (*(*h)));
void trocar(No (*(*pt)), No (*(*s)));
void RemoverAVL(int x, No (*(*pt)), bool (*(*h)));
int ContNo (No (*ptraiz));
int Altura (No (*ptraiz));
int Bal (No (*ptraiz));
bool E_AVL (No (*ptraiz));
void zeraAVL(No (*ptraiz));

int main()
{
    srand(time(0));
    bool *h, check;
    int qtdNo;
    No *ptraiz;
    No **pt = &ptraiz;
    int *vet;
    vet = malloc(1000 * (sizeof(int)));

    //teste realizados
    for(int i = 1; i <= 100; i++)
    {
        ptraiz = NULL;
        int j = 0;
        for(int i = 0; i < 1000; i++)
        {
            vet[i] = -1;
        }

        while(j < 1000)
        {
            int x = rand() % 100000;
            int z = 0;
            int n = 0;
            while(z == 0 && n < 1000)
            {
                if (vet[n] == x)
                {
                    z = 1;
                }
                n++;
            }

            if (z == 0)
            {
                vet[j] = x;
            }
            else
            {
                j--;
            }
            j++;
        }
        
        for(int k = 0; k < 1000; k++)
        {
            pt = &ptraiz;
            InserirAVL(vet[k], pt, &h);
        }

        qtdNo = ContNo(ptraiz);
        printf("\nAVL %d INSERIR\nquantidade de Nos = %d\n", i, qtdNo);

        check = E_AVL(ptraiz);
        if (check)
        {
            printf("E AVL\n");
        }
        else
        {
            printf("NAO E AVL\n");
        }
        
        for(int k = 0; k < 100; k++)
        {
            pt = &ptraiz;
            RemoverAVL(vet[k], pt, &h);
        }

        qtdNo = ContNo(ptraiz);
        printf("AVL %d REMOVER\nquantidade de Nos = %d\n", i, qtdNo);

        check = E_AVL(ptraiz);
        if (check)
        {
            printf("E AVL\n");
        }
        else
        {
            printf("NAO E AVL\n");
        }

        zeraAVL(ptraiz);

    }
    return 0;
}

void Caso1 (No (*(*pt)), bool (*(*h)))
{
	No *ptu = (*pt)->esq;
	if (ptu->bal == -1) //RD
	{
		(*pt)->esq = ptu->dir;
		ptu->dir = (*pt);
		(*pt) = ptu;
		(*pt)->dir->bal = 0;
	}
	else //RDD
	{
		No *ptv = ptu->dir;
		ptu->dir = ptv->esq;
		(*pt)->esq = ptv->dir;		
        ptv->esq = ptu;
		ptv->dir = (*pt);
		switch (ptv->bal)
		{
			case 1: 
				(*pt)->bal = 0;
				ptu->bal = -1;
                break;
			case 0:
				(*pt)->bal = 0;
				ptu->bal = 0;
                break;
			case -1:
				(*pt)->bal = 1;
				ptu->bal = 0;
                break;
		}
		(*pt) = ptv;
	}
	(*pt)->bal = 0;
	(*h) = false;
}

void Caso2 (No (*(*pt)), bool (*(*h)))
{
	No *ptz = (*pt)->dir;
	if (ptz->bal == 1) //RE
	{
		(*pt)->dir = ptz->esq;
		ptz->esq = (*pt);
		(*pt) = ptz;
		(*pt)->esq->bal = 0;
	}
	else //RDE
	{
		No *pty = ptz->esq;
		ptz->esq = pty->dir;
		(*pt)->dir = pty->esq;
        pty->esq = (*pt);
		pty->dir = ptz;
		switch (pty->bal)
		{
			case 1: 
				(*pt)->bal = -1;
				ptz->bal = 0;
                break;
			case 0:
				(*pt)->bal = 0;
				ptz->bal = 0;
                break;
			case -1:
				(*pt)->bal = 0;
				ptz->bal = 1;
                break;
		}
		(*pt) = pty;
	}
	(*pt)->bal = 0;
	(*h) = false;
}

void InicarNo(No (*(*pt)), int x)
{
    No *novo = malloc(sizeof(No));
    novo->chave = x;
    novo->bal = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    (*pt) = novo;
}

void InserirAVL(int x, No (*(*pt)), bool (*(*h)))
{
    if ((*pt) == NULL)
    {
        InicarNo(&(*pt), x);
        (*h) = true;
    }
    else //caso onde ja tem No na funcao
    {
        if (x == (*pt)->chave)
        {
            //("elemento ja existe");
        }
        else if (x < (*pt)->chave)
        {
            InserirAVL(x, &((*pt)->esq), h);
            if ((*h) == true) //caso a altura seja modificada deve se verificar o bal
            {
                switch ((*pt)->bal)
                {
                case 1:
                    (*pt)->bal = 0;
                    (*h) = false;
                    break;
                case 0:
                    (*pt)->bal = -1;
                    break;
                case -1:
                    Caso1(&(*pt), &(*h));
                    break;
                }
            }
        }
        else
        {
            InserirAVL(x, &((*pt)->dir), &(*h));
            if ((*h) == true) //caso a altura seja alterada
            {
                switch ((*pt)->bal)
                {
                case -1:
                    (*pt)->bal = 0;
                    (*h) = false;
                    break;
                case 0:
                    (*pt)->bal = 1;
                    break;
                case 1:
                    Caso2(&(*pt), &(*h));
                }
            }
        }
    }
}

void PreOrdem (No (*pt))
{
    printf(" %d ", pt->chave);
    if (pt->esq != NULL)
    {
        PreOrdem(pt->esq);
    }
    if (pt->dir != NULL)
    {
        PreOrdem(pt->dir);
    }
}

void Caso1R (No (*(*pt)), bool (*(*h)))
{
    No *ptu = (*pt)->esq;
    if (ptu->bal <= 0) //RD
    {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt) = ptu;
        if (ptu->bal == -1)
        {
            ptu->bal = (*pt)->dir->bal = 0;
            (*h) = true;
        }
        else
        {
            ptu->bal = 1;
            (*pt)->dir->bal = -1;
            (*h) = false;
        }
    }
    else //RDD
    {
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        (*pt)->esq = ptv->dir;
        ptv->esq = ptu;
        ptv->dir = (*pt);
        (*pt) = ptv;
        switch (ptv->bal)
        {
        case -1:
            ptu->bal = 0;
            (*pt)->dir->bal = 1;
            break;
        
        case 0:
            ptu->bal = 0;
            (*pt)->dir->bal = 0;
            break;

        case 1:
            ptu->bal = -1;
            (*pt)->dir->bal = 0;
            break;
        }
        (*pt)->bal = 0;
        (*h) = true;
    }
}

void Caso2R (No (*(*pt)), bool (*(*h)))
{
    No *ptz = (*pt)->dir;
    if (ptz->bal >= 0) //RE
    {
        (*pt)->dir = ptz->esq;
        ptz->esq = (*pt);
        (*pt) = ptz;
        if (ptz->bal == 1)//
        {
            ptz->bal = (*pt)->esq->bal = 0;
            (*h) = true;
        }
        else
        {
            ptz->bal = -1;
            (*pt)->esq->bal = 1;
            (*h) = false;
        }
    }
    else //RDE
    {
        No *pty = ptz->esq;
        ptz->esq = pty->dir;
        (*pt)->dir = pty->esq;
        pty->dir = ptz;
        pty->esq = (*pt);
        (*pt) = pty;
        switch (pty->bal)
        {
        case -1:
            ptz->bal = 1;
            (*pt)->esq->bal = 0;
            break;
        
        case 0:
            ptz->bal = 0;
            (*pt)->esq->bal = 0;
            break;

        case 1:
            ptz->bal = 0;
            (*pt)->esq->bal = -1;
            break;
        }
        (*pt)->bal = 0;
        (*h) = true;
    }
}

void balancear(No (*(*pt)), char R, bool (*(*h)))
{
    if ((*h) == true)
    {
        if(R == 'D')
        {
            switch ((*pt)->bal)
            {
            case 1:
                (*pt)->bal = 0;
                break;
            
            case 0:
                (*pt)->bal = -1;
                (*h) = false;
                break;

            case -1:
                Caso1R(&(*pt), h);
                break;
            }
        }
        else
        {
            switch ((*pt)->bal)
            {
            case -1:
                (*pt)->bal = 0;
                break;
            
            case 0:
                (*pt)->bal = 1;
                (*h) = false;
                break;

            case 1:
                Caso2R(&(*pt), h);
                break;
            }
        }
    }
}

void trocar(No (*(*pt)), No (*(*s)))
{
    No *aux;
    int x;

    aux = (*s);
    (*s) = (*pt);
    (*pt) = aux;

    aux = (*s)->esq;
    (*s)->esq = (*pt)->esq;
    (*pt)->esq = aux;

    aux = (*s)->dir;
    (*s)->dir = (*pt)->dir;
    (*pt)->dir = aux;

    x = (*s)->bal;
    (*s)->bal = (*pt)->bal;
    (*pt)->bal = x;
    
}

void RemoverAVL(int x, No (*(*pt)), bool (*(*h)))
{
    if ((*pt) == NULL)
    {
        //("elemento nao existe");
        (*h) = false;
    }
    else
    {
        if (x < (*pt)->chave)
        {
            RemoverAVL(x, &((*pt)->esq), h);
            balancear(&(*pt), 'E', h);
        }
        else if (x > (*pt)->chave)
        {
            RemoverAVL(x, &((*pt)->dir), h);
            balancear(&(*pt), 'D', h);
        }
        else
        {
            No *aux = (*pt);
            if ((*pt)->esq == NULL)
            {
                (*pt) = (*pt)->dir;
                (*h) = true;
                free(aux);

            }
            else if ((*pt)->dir == NULL)
            {
                (*pt) = (*pt)->esq;
                (*h) = true;
                free(aux);
            }
            else
            {
                No *s = (*pt)->dir; //menor elemento a direita do pt
                No *PaiS; //pai do menor elemento a direita do pt
                if (s->esq == NULL)
                {
                    s->esq = (*pt)->esq;
                    s->bal = (*pt)->bal;
                    (*pt) = s;
                    (*h) = true;
                    free(aux);
                }
                else
                {
                    while (s->esq != NULL)
                    {
                        PaiS = s;
                        s = s->esq;
                    }
                    trocar(pt, &(PaiS->esq));
                    RemoverAVL(x, &((*pt)->dir), h);
                }
                balancear(&(*pt), 'D', h);
            }
        }
    }
}

int ContNo (No (*ptraiz))
{
    if (ptraiz == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + ContNo(ptraiz->esq) + ContNo(ptraiz->dir);
    }
    
}

int Altura (No (*ptraiz))
{
    int esq, dir;
    if(ptraiz == NULL)
    {
        return -1;
    }
    else
    {
        esq = Altura(ptraiz->esq);
        dir = Altura(ptraiz->dir);
        if (esq > dir)
        {
            return esq + 1;
        }
        else
        {
            return dir + 1;
        }
    }

}

int Bal (No (*ptraiz))
{
    int alt_esq = Altura (ptraiz->esq);
    int alt_dir = Altura (ptraiz->dir);
    return alt_dir - alt_esq;
}

bool E_AVL (No (*ptraiz))
{
    int bal = Bal(ptraiz);
    if (ptraiz->bal != bal)
    {
        return false;
    }
    else
    {
        bool dir, esq;

        if (ptraiz->esq != NULL)
        {
            esq = E_AVL(ptraiz->esq);
        }
        else
        {
            return true;
        }

        if (ptraiz->dir != NULL)
        {
            dir = E_AVL(ptraiz->dir);
        }
        else
        {
            return true;
        }
        
        return (esq && dir);
    }
}

void zeraAVL(No (*ptraiz))
{

    if (ptraiz->esq != NULL)
    {
        zeraAVL(ptraiz->esq);
    }
    if (ptraiz->dir != NULL)
    {
        zeraAVL(ptraiz->dir);
    }
    free(ptraiz);
}
