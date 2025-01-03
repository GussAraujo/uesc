// Gustavo Araujo - 202210689
// João Dutterle - 202211138
// Pedro Elias - 202210359

#include <iostream>
#include <math.h>
#define TAMANHOPILHA 1000

using namespace std;

typedef struct pilha {
    char itens[TAMANHOPILHA];
    int tamanho;
} pilha;

bool empilhar(pilha *p, int obj) {
    bool ret = false;
    if(p->tamanho  < TAMANHOPILHA) {
        p->itens[p->tamanho++] = obj;
        ret = true;
    }
    return ret;
}

bool desempilhar(pilha *p) {
    bool result = false;
    if(p->tamanho > 0) {
        p->tamanho--;
        result = true;
    }
    return result;
}

int topo(pilha p) {
    int val = 0;
    if (p.tamanho > 0) val = p.itens[p.tamanho-1];
    
    return val;
}

bool ehOperador (char op){
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')
        return true;
    else return false;
}

int calcular(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            break;
    }

    return 0;
}

bool ehvazia(pilha p) {
    return p.tamanho ? false : true;
}

int main() {
    bool valid = true;
    pilha p;
    p.tamanho = 0;

    char simb;
    string express = "-+254";
    int n = 0;

    while (express.length() != 0) {
        // procura por um número
        do {
            simb = express[n];
            n++;
        } while (ehOperador(simb));

        // transforma o simb (que é char) em int
        int a = simb - '0';
        // pega o operador anterior a ele
        char op = express[n-2];
        // pega o número após ele e tbm transforma em int
        int b = express[n] - '0';

        // 2
        // 0 1 2 3 4 5
        express.erase(n-2, n);
        int r =  calcular(a, b, op);
        empilhar(&p, r);
        n = 0;

        if(express.length() == 1) {
            if(ehOperador(express[0])){
                int a = topo(p);
                desempilhar(&p);
                int b = topo(p);
                desempilhar(&p);

                int result = calcular(a, b, express[0]);
                empilhar(&p, result);
            }
            break;
        }
    }

    cout << topo(p) << endl;

    return 0;
}