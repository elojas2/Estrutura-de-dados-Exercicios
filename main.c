/*
    Escreva as seguintes funções:
        (Q1) cópia de uma árvore: TAB* copia (TAB *a); - Feito
        (Q2) espelho de uma árvore (o que está a esquerda na árvore original, estará a direita no espelho, e
        vice-versa): TAB* espelho (TAB *a); - Feito
        (Q3) maior elemento da árvore: TAB* maior(TAB *a); - Feito
        (Q4) menor elemento da árvore: TAB* menor(TAB *a); - Feito

        (Q5) uma função que, dadas duas árvores deste tipo, testa se estas árvores são iguais. A função
        retorna um se elas são iguais e zero, caso contrário. A função deve obedecer ao seguinte protótipo:
        int igual (TAB* a1, TAB* a2); - Feito

        (Q6) uma função em C que, dada uma árvore binária qualquer, retire todos os elementos pares da
        árvore original. A função deve ter o seguinte protótipo: TAB* retira_pares (TAB* arv);

        (Q9) ache a quantidade de nós folha: int nf(TAB *a); - Feito

        (Q10) Escreva uma função em C para testar se uma árvore é zigue-zague, isto é, se todos
os nós internos possuem exatamente uma sub-árvore vazia: int zz(TAB *a);

 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int info;
    struct node *left, *right;

}Node;

Node* insertNewVersionTwo(Node *root, int value){
    if(root == NULL){
        Node *new = (Node *) malloc(sizeof(Node));
        new->info = value;
        new->left = NULL;
        new->right = NULL;
        return new;
    }else{
        if(value < root->info){
            root->left = insertNewVersionTwo(root->left, value);
        }
        if(value > root->info){
            root->right = insertNewVersionTwo(root->right, value);
        }
        return root;
    }
}

Node* insertNewVersion(Node *root, int value){
    if(root == NULL){
        Node *new = (Node *) malloc(sizeof(Node));
        new->info = value;
        new->left = NULL;
        new->right = NULL;
        return new;
    }else{
        if(value < root->info){
            root->left = insertNewVersion(root->left, value);
        }
        if(value > root->info){
            root->right = insertNewVersion(root->right, value);
        }
        return root;
    }
}


int lenght(Node *root){
    if(root == NULL){
        return 0;
    }else{
        return 1 + lenght(root->left) + lenght(root->right);
    }

}
void write(Node *root){

    if(root != NULL) {
        write(root->left);
        printf("%d ", root->info);
        write(root->right);

    }
}

Node* copy(Node *c){

    if(c == NULL){
        return NULL;
    }
    Node *new = (Node *) malloc(sizeof(Node));
    new->info = c->info;
    new->left = copy(c->left);
    new->right = copy(c->right);
    return new;
}

Node *mirrored(Node *root){

    if(root == NULL){
        return NULL;
    }
    Node *mirror = (Node*) malloc(sizeof (Node));
    mirror->info = root->info;
    mirror->left = mirrored(root->right);
    mirror->right = mirrored(root->left);
    return mirror;

}

//Maior num
Node *higherNum(Node *root){

    //Os maiores valores estão na direita

    if((root != NULL) && (root->right > root->info )) {
        root->info = higherNum(root->right);
    }
    return root->info;
}

//Menor num
Node* smallestNum(Node *root){
    if((root != NULL) && (root->left > root->info)){
        root->info = smallestNum(root->left);
    }
    return root->info;
}

//Search tree
int search(Node *root, int key){

    if(root == NULL){
        return 0;
    }else{
        if(root->info == key){
            return 1;
        }else{

            if(key < root->info){
                return search(root->left, key);
            }else{
                return search(root->right, key);
            }
        }
    }
}
int quantidadeNodes(Node *root){

    int quantidade = 0;
    if(root == NULL){
        printf("oie primeiro uf");
        return 0;
    }
    else if(root->left == NULL && root->right == NULL) {
        return 1;
        //quantidade = quantidade + 1;
        //printf("quant: %d\n\n", quantidade);
    }else{
        return quantidadeNodes(root->left) + quantidadeNodes(root->right);
    }


    return quantidade;
}
//delete
Node *delete(Node*root, int key){

    if(root == NULL){
        return NULL;
    }else{

        if(root->info == key){
            //remove nós folhas
            if(root->left == NULL && root->right == NULL){
                free(root);
                return NULL;
            }else{
                //remove nós que possuem apenas 1 filho
                if(root->left == NULL || root->right == NULL){
                    Node* aux;
                    if(root->left != NULL)
                        aux = root->left;
                    else
                        aux = root->right;
                    free(root);
                    return aux;
                }else{
                    Node *aux = root->left; //Aponta para a subarvore da esquerda

                    //While para pegar o maior resultado a direita da subarvore da esquerda
                    while(aux->right != NULL){
                        aux = aux->right;
                    }
                    root->info = aux->info;
                    aux->info = key;
                    root->left = delete(root->left, key);
                    return root;

                }
            }
        }

        else{

            if(key < root->info){
                root->left = delete(root->left, key);
            }else{
                root->right = delete(root->right,key);
            }

            return root;

        }

    }


}
//Q10) Escreva uma função em C para testar se uma árvore é zigue-zague, isto é, se todos
//       os nós internos possuem exatamente uma sub-árvore vazia: int zz(TAB *a)

int zz(Node *root){

    int zigue = 0;

    if(root == NULL) return 0;


    if(root->left != NULL && root->right != NULL){
        return 0;
    }
    else if(root->right == NULL && root->left != NULL){
        zigue = 1;
        zz(root->left);
    }else if(root->left == NULL  && root->right != NULL){
        zigue = 1;
        zz(root->right);

    }
    return zigue;
}


int iguais(Node *rootA, Node *rootB){

    if((rootA == NULL) && (rootB == NULL)) {
        return 1;
    }

    else if((rootA != NULL) && (rootB == NULL)){
        return 0;
    }else if((rootA == NULL) && (rootB != NULL)){
        return 0;
    }else{


        if(rootA->info == rootB->info && iguais(rootA->left, rootB->left) && iguais(rootA->right, rootB->right)){
            return 1;
        }else{
            return 0;
        }


    }

}
//Escreva uma função em C para verificar se uma árvore é estritamente binária, isto
//é, se os nós dessa árvore possuem ou zero ou dois filhos: int estbin(TAB
//*a);
int ehbin(Node *root){

    int bin = 0;
    if(root == NULL) return 0;


    if(root->left != NULL && root->right != NULL){
        bin = 1;
        ehbin(root->right);
        ehbin(root->left);

    }else if(root->left && root->right){
        bin = 1;
    }else{
        bin = 0;
    }
    return bin;
}

int main() {


    Node *mirror = NULL;
    Node *clone = NULL;
    Node *root = NULL;
    Node *root1 = NULL;

    int op;
    int value;
    int zero = 0;
    int quant = 0;

    do{

        printf("\n---------------MENU---------------\n");
        printf("\n0 - Exit\n1 - Insert\n2 - Show Binary Tree\n3 - Insert a second binary tree \n4 - Mirror Binary Tree\n"
               "5 - Higher number  \n6 - Smallest number\n7 - Delete\n8 - Search\n9 - Compare binary trees\n10 - Copy\n11 - Nodes\n12 - Zigue\n13 - Its binary\n");
        printf("Choice a number: ");
        printf("\n");
        scanf("%d", &op);

        switch(op){

            case 0:
                printf("Leaving....\n Bye!\n");
                break;
            case 1:
                printf("\nWrite a number to insert in binary tree, pls:");
                scanf("%d", &value);
                root = insertNewVersion(root, value);
                break;
            case 2:
                write(root);
                printf("\n");
                printf("Size: %d\n", lenght(root));
                break;
            case 3:
                printf("\nWrite a number to insert in second binary tree, pls:");
                scanf("%d", &value);
                root1 = insertNewVersionTwo(root, value);
                break;

            case 4:
                mirror = mirrored(root);
                printf("Mirror binary tree:\n");
                write(mirror);
                break;
            case 5:

                printf("The largest number in binary tree: %d\n", higherNum(root));
                break;

            case 6:
                printf("The smallest number in binary tree: %d\n", smallestNum(root));
                break;
            case 7:

                printf("Choice a number to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                printf("\nNumber deleted!!!\n");
                break;

            case 8:

                printf("Choice a number to search in binary tree: ");
                scanf("%d", &value);
                int result = search(root, value);
                if(result == 0)
                    printf("\nSorry, not found in binary tree, try other number!:D\n");
                else
                    printf("\nNumber found!!!\n:D\n");
                break;

            case 9:
                zero = iguais(root, root1);

                if(zero == 0){
                    printf("Not yet\n");
                }else{
                    printf("Yes, are the same tree\n");
                }
                break;


            case 10:
                clone = copy(root);
                printf("Clone binary tree:\n");
                write(clone);
                break;
            case 11:

                quant = quantidadeNodes(root);
                printf("Quantidade: %d\n", quant);
                break;
            case 12:
                zero = zz(root);
                if(zero == 1){
                    printf("Eh zigue zague\n");
                }else{
                    printf("Nao eh zigue zague\n");
                }
                break;
            case 13:
                zero = ehbin(root);
                if(zero == 0) printf("Nao eh binaria\n");

                else printf("Eh binaria\n");

                break;
            default:
                printf("Invalid option ;(\n");
        }

    }while(op != 0 );


    return 0;
}








