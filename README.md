# Descripcion General de memfilled.bin

**_With 💜, by KnowYourselves_**

## Introduccion

La memoria esta llena de muchos procesos, cada uno con varios archivos. En este archivo describiremos los contenidos de 3 de las 16 entradas de la PCB.

## Entrada 0

Esta entrada (la primera) esta vacía. Por lo cual al leerla su byte de estado sería 0.

## Entrada 3

Esta entrada tiene un proceso sin ningún archivo. El proceso tiene id 32 y nombre "empty".

Además, al leer las diez subentradas de archivos de este proceso, todos sus bytes de validez serán 0, al igual que el bit de validez de sus 32 páginas.

## Entrada 14

Esta entrada tiene un proceso con 4 archivos utilizando sus dos primeras páginas. Su id es 0 y su nombre es "main".

### Tabla de Paginas

La primera pagina tendrá su bit de validez igual 1 y los otros 7 bits darán como resultado el frame 127.

La segunda pagina tendrá su bit de validez igual 1 y los otros 7 bits darán como resultado el frame 5.

El resto de las paginas tendrán su bit de validez igual a 0.

### Archivos

Hay que recordar que las subentradas no necesariamente estarán "en orden", por ejemplo, en este proceso la primera entrada es inválida, mientras que el primer archivo de la memoria virtual está en la entrada 4. Pueden inferir el orden de los archivos viendo sus direcciones virtuales.

#### Subentrada 1

Esta subentrada contiene un archivo con nombre "secret.txt", su tamaño es 49474 bytes y su direccion virtual es 89216.

#### Subentrada 3

Esta subentrada contiene un archivo con nombre "message.txt", su tamaño es 16 bytes y su direccion virtual es 9527685.

#### Subentrada 4

Esta subentrada contiene un archivo con nombre "test.jpg", su tamaño es 89216 bytes y su direccion virtual es 0.

#### Subentrada 9

Esta subentrada contiene un archivo con nombre "im_a_mp3.bin", su tamaño es 9513795 bytes y su direccion virtual es 138690. Cabe notar que este archivo utiliza dos frames.

## Palabras Finales

Espero que esta memoria junto a este archivo les sea útil. Les recomiendo enfocarse en los 3 procesos mencionados en este archivo (cubren prácticamente todos los casos), pero de todas formas los invitamos a descubrir el resto de los archivos ocultos en esta memoria.

Éxito!
