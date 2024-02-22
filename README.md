# L5S-AEP

O L5S-AEP, é um Ambiente de Ensino de Programação. Seu foco principal é o ensino do pensamento computacional para crianças, tendo como inspiração os estudos de Seymour Papert e a Filosofia LOGO. O projeto foi idealizado e realizado durante o Trabalho de Conclusão de Curso de [Lucas S. Souza](https://github.com/lucassoaresouza) tendo a orientação dos professores doutores Milene e Maurício Serrano da Universidade de Brasília.

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
![menu-principal](https://github.com/lucassoaresouza/L5S-AEP/assets/21176137/3da2a624-f084-406c-9fc7-bfc8cf138ab8)


