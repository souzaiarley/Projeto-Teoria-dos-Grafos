## Problemas de Grafos

### Alunos
- Antônio Joabe Alves Morais
- Iarley Natã Lopes Souza

### Execução
Para compilar o programa, basta executar o comando `make` na pasta raiz do projeto.

Só chamar `make`, irá compilar as 3 soluções e gerar os executáveis `run01`, `run02` e `run03` no caminho "`./bin/`".

Para compilar uma solução específica, basta executar o comando `make 01`, `make 02` ou `make 03` na pasta raiz do projeto, gerando e rodando individualmente os executáveis.
A execução do comando `./run*`. não é necessária, pois os programas são executados automaticamente após a compilação.

Para limpar os arquivos gerados pela compilação, basta executar o comando `make clean` na pasta raiz do projeto.

Os arquivos estão organizados da seguinte forma:
- `src/`: Contém os arquivos fonte do programa.
- `bin/`: Contém os arquivos executáveis gerados pela compilação.

### Mudanças de Arquivos
Em cada solução, existem variáveis do tipo `string` que podem ser mudadas para alterar o arquivo de entrada para a leitura dos grafos.
Por exemplo, na solução 01:
```c++
    /* Nome do arquivo que contém os grafos */
    string graphFilename = "snarks_24_vertices.txt";
    /* Nome da pasta que contém os grafos: (SIM / NAO)*/
    string YorN = "NAO";
    /* Caminho completo do arquivo */
    string filePath = "./tests/q1/" + YorN + "/" + graphFilename;
```
Para mudar o arquivo de entrada, basta alterar o nome do arquivo na variável `graphFilename` e o nome da pasta na variável `YorN` (SIM / NAO).
(A variável `YorN` só está presente na solução 01, pois é a única que possui arquivos de entrada em pastas diferentes).
