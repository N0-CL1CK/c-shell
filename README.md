## Construção de um SHELL em C lang
### Instruções:

> Parar compilar o código (gerar o executável) necessita ter o GCC instalado e rodar o seguinte comando:
>> `$ gcc main.c -o main`
>
> Em seguida, para poder executar o programa, basta rodar:
>> `$ ./main`
>
> Obs.: Estes comandos rodarão apenas em ambientes UNIX.

<br>

### Configurações:

O '`#define MAX_LENGTH`' definirá o tamanho máximo dos comandos a serem executados. Ele levará em consideração o tamanho da string inteira, por exemplo:

> `osh > ls -la`

será contabilizado como o seguinte array de chars:

> `['l', 's', ' ', '-', 'l', 'a']`

portanto, o tamanho será de <em><b>6 caracteres</b></em>