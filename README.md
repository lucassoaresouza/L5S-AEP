# L5S-AEP

O L5S-AEP, é um Ambiente de Ensino de Programação. Seu foco principal é o ensino do pensamento computacional para crianças, tendo como inspiração os estudos de Seymour Papert e a Filosofia LOGO. O projeto foi idealizado e realizado durante o Trabalho de Conclusão de Curso de [Lucas S. Souza](https://github.com/lucassoaresouza) tendo a orientação dos professores doutores Milene e Maurício Serrano da Universidade de Brasília.

## Recursos Principais:

- Criação de usuário;  
- Seleção de avatar;   
- Seleção de grupo de Levels;  
- Solução de problemas;  

## Código Suportado

- Movimentação de Avatar:
    - **sigaNorte(<QTD_DE_CASAS>);**: Move o avatar em direção ao norte por X casas;
    - **sigaSul(<QTD_DE_CASAS>);**: Move o avatar em direção ao sul por X casas;
    - **sigaLeste(<QTD_DE_CASAS>);**: Move o avatar em direção ao leste por X casas;
    - **sigaOeste(<QTD_DE_CASAS>);**: Move o avatar em direção ao oeste por X casas;
- Declaração de Variáveis
```
nome_variavel = <VALOR_OU_OPERAÇÃO>

Obs.: Variáveis podem ser inteiros e decimais;
```
- Operações
  - Comparações:
      - Maior que: `variavelA > variavelB;`
      - Maior ou igual que: `variavelA >= variavelB;`
      - Menor que: `variavelA < variavelB;`
      - Menor ou igual que: `variavelA <= variavelB;`
      - Igualdade: `variavelA == variavelB;`
  - Matemáticas:
      - Soma: `variavelA + variavelB;`
      - Subtração: `variavelA - variavelB;`
      - Divisão: `variavelA / variavelB;`
      - Multiplicação: `variavelA * variavelB;`
- Estruturas de Decisão
```
Se(<CONDIÇÃO>){
    ...
} 

Ou

se(<CONDIÇÃO>){
    ...
}  senao {
   ...
}
```
- Estrutura de Repetição
```
rerpita(<QTD_DE_VEZES>){
   ...
}
```

## Telas

**Menu Principal**
![menu-principal](https://github.com/lucassoaresouza/L5S-AEP/assets/21176137/bbaf95e8-ee47-4ca6-93ff-e5130c2b1e76)
**Seleção de Avatar e Level**
![escolha-personagem](https://github.com/lucassoaresouza/L5S-AEP/assets/21176137/466f93cf-32cc-45cf-9dbf-5d2b5037f8e4)
**Resolução de Problema**
![exemplo](https://github.com/lucassoaresouza/L5S-AEP/assets/21176137/c98b25c4-c4dc-4af2-a6af-342474be8532)

## Compilação

### Dependências

- [Cmake](https://discourse.cmake.org/)
- [C++ 11](https://isocpp.org/)
- [Yacc](https://pt.wikipedia.org/wiki/Yacc)
- [Bison](https://www.gnu.org/software/bison/)
- [SDL2](https://www.libsdl.org/)
    - libsdl2-dev
    - libsdl2-image-dev
    - libsdl2-ttf-dev
    - libsdl2-mixer-dev

### Como compilar

1. Instale as dependências. Caso prefira, execute o script **install_requirements.sh**;  
```shell
./install_requirements.sh
```
2. Inicialize o CMake;  
```shell
cmake .
```
![cmake-init](https://github.com/lucassoaresouza/L5S-AEP/assets/21176137/bab15314-643c-480d-8351-8d0e47a33795)  
3. Realize a build, e  
```shell
cmake --build .
```
![cmake-build](https://github.com/lucassoaresouza/L5S-AEP/assets/21176137/cb387622-68aa-4cc9-b4a6-ccb34cd45f1b)  
6. Execute o binário.  
```shell
./bin/aep
```


