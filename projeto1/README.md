# IF767 - Processamento de Cadeias de Caracteres - PMT

Esse repositorio consiste no primeiro da disciplina [Processamento de Cadeias de Caracteres (IF767)](http://www.cin.ufpe.br/~if767), que tem como objetivo a implementação de uma ferramenta para busca exata e aproximada de padrões em arquivos.
Esse projeto foi desenvolvido por:

[Lucas Cavalcanti](https://github.com/lhcavalcanti)

[Roberto Fernandes](https://github.com/bebetocf)

## Para compilar

Simplesmente o comando `make`

## Para rodar

Simplesmente o comando `./bin/pmt`

Ao rodar `./bin/pmt --help` mostrasse as opções para rodar o programa, como demostrado abaixo.

```
pmt [-a {aho-corasick, shift-or, wu-manber, sellers}] [-c] [-e NUM] [-p FILE]|PATTERN FILE [FILE2...]
Pattern search in files.
Algorithms:
ShiftOr, WuManber, Sellers, Aho-Corasick
        --algorithm -a ALGORITHMS    Chose algorithm
        --count     -c               Print only occurrences count
        --edit      -e NUM           NUM chooses algorithm edit distance
                                        Used only if algorithm supports
                                        If no algoritmh chosen, pmt uses wu-manbem
        --pattern   -p ARQUIVO       Search each pattern on file, one per line
                                        More than 1 pattern, works only for aho-corasick
        --help      -h               Show help
Made by: Lucas Cavalcanti and Roberto Fernandes  - {lhcs, rcf6}@cin.ufpe.br
```
