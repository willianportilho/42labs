<h1 align="center"> 42RAR </h1>

<p align="center"> A 42 project written in C language</p>

<p align="center">
  <img alt="status completed" src="https://img.shields.io/badge/STATUS-COMPLETED-green">
  <img alt="made with c language" src="https://img.shields.io/badge/MADE%20WITH-C-blue">
</p>

---

- [Introduction](#introduction)
- [Explanation](#explanation)
- [Example 1](#example-1-logic-function)
- [Example 2](#example-2-call-function)
- [Usage](#%EF%B8%8F-usage)

## Introduction

<p> This project had the purpose of create two programms (encoder and decoder), establishing communication via shared memory. in addition, the huffman algorithm for compressing multiple texts was required.</p>

---

### Explanation
We aimed to use shared memory in conjunction with the huffman algorithm. To merge this, we did the compression of multiple texts in the encoder program and, through the shared memory, we sent this compressed file. In the decoder, the file goes through a process to be decompressed and sent back to the encoder. In the end, the encoder creates files with the uncompressed text, a file with all the texts compressed, and a file with all the texts uncompressed, and finally, it displays execution information.
There are two issues to be discussed, let's start with shared memory.

#### Shared memory
There are many ways to communicate between processes and programs. In this project, we were introduced to shared memory operations. With it, we can establish communication between two different programs, whether or not they run at the same time. For this, this type of sharing uses the location of the files as a reference, making both programs find the same block of memory associated with the chosen file. Thus, we managed to establish a connection that is useful and simple to use.

![ilustration image](images/image_1.jpg)
*_Consult the [code](src/01_encoder.c) for more details_

##### ftok
To use shared memory, we use the ftok function, which returns a numerical key associated with the name of the file we chose:
```c
key = ftok("Makefile", proj_id);
```
#### shmget
Uses the generated key to create a shared memory block associated with the key, returning a shared memory block ID:
```c
id = shmget(key, size_block, 0644 | IPC_CREAT);
```
#### shmat
It takes the ID and maps the block to this address space returns a block pointer to use.
```c
void *block = shmat(id_block, NULL, 0);
```
#### shmdt
Issues a warning that the memory has already been used by the current program. This function does not release the block, it only issues the warning:

#### shmclt
Permanently erase memory

### Huffman Algorithm



## 🛠️ Usage
<p> For use this aplication, follow these steps:</p>

- Clone this repository:
```
https://github.com/42sp/42labs-selection-process-v4-willianportilho
```

## 🤖 Makefile Commands
- `make` to create *.o objects and compile the libftprintf.a;
- `make bonus` to include bonus functions (lists) in the libftprintf.a;
- `make clean` to erase *.o objects;
- `make fclean` to erase *.o objects and libftprintf.a;
- `make re` to erase *.o objects and libftprintf.a, and recriate *.o and libftprintf.a;

# Labs 4º Edição

## Desafio

O desafio consiste no desenvolvimento de uma aplicação de análise e compressão de dados. Essa aplicação utilizará o algoritmo de compressão Huffman e poderá receber múltiplos dados onde, uma vez que comprimido deve ser descomprimido e coletar informações pertinentes para a análise do processo e dado.

Para isso, você criará dois programas: `encoder` e `decoder`. O encoder receberá o dado a ser comprimido e exibirá suas informações vindas do decoder. Já, o decoder descomprimirá o dado e irá enviá-lo ao encoder com suas informações, onde será exibido. Os programas devem se comunicar utilizando *shared memory operations*.

A linguagem C será utilizada para o desenvolvimento e não há bibliotecas externas permitidas.

## É necessário

- Que existam dois programas `encoder` e `decoder` que se comuniquem via memória compartilhada.
- Que o `encoder` possa receber, no mínimo, múltiplos textos como dado e comprimi-lo. Caso mais de um texto seja enviado, devem ser comprimidos juntos, resultando em apenas um único dado.
- Que o algoritmo de Huffman seja implementando em sua totalidade e que o processo de compressão e descompressão ocorram utilizando-o.
-  Que o `decoder` possa descomprimir e enviar as seguintes informações ao `encoder`: dado descomprimido, quantidade de bits ou bytes totais, quantidade de bits ou bytes comprimidos e o tempo da operação de descompressão.
- O `encoder` exibir as informações recebidas pelo `decoder`.

### O que será avaliado

- Código bem escrito e limpo.
- A documentação do seu código.
- Ferramentas que foram utilizadas e por quê.
- Sua criatividade e capacidade de lidar com problemas diferentes.
- Alinhamento do seu projeto com a proposta.

### O mínimo necessário

- README.md com a documentação contendo informações do projeto.

### Bônus

Os itens a seguir não são obrigatórios, mas são funcionalidades que darão mais valor ao seu desafio.

- Compressão de múltiplos arquivos binários.
- Criptografia do dado comprimido, utilizando senha fornecida pelo usuário.
- Verificação de integridade do arquivo comprimido.
- Opção para escolher mais outro algoritmo de compressão a ser utilizado.
- Tempo de descompressão (`decoder`) abaixo da média dos candidatos.
- Cuidados especiais com otimização e padrões de código.
- Uso de ferramentas externas para planejamento nas etapas de desenvolvimento.

<sub><sup>[Importante](https://xkcd.com/1381/)</sup></sub>
