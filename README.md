# Trabajo Práctico Especial

Este repositorio contiene el código fuente del desarrollo de **Arr**, un lenguaje de programación enfocado en el manejo de arreglos y operaciones entre los mismos.

**Grupo: Hirsch-Henestrosa-Choi-Ribas**
 
## Compilación del Compilador

Para compilar el proyecto, solo hay que ejecutar la siguiente línea estando en la raíz del repositorio:
```
$ make clean all
```

Esto compilará el código del compilador, dejándolo listo para ser usado.

## Ejecución del Compilador

Dentro de la carpeta */real_tests* se encuentran varios archivos .arr, estos son los archivos de prueba que se requerían según la consigna. Se proporcionan dos scripts para compilación y ejecución de los mismos.

Una vez compilado el código en **Arr**, dentro de la carpeta */real_tests* se encuentran los archivos generados en código en C, en caso de que se quieran inspeccionar.

### Compilación General
Para compilar todos los archivos de prueba para luego poder ejecutarlos por separado, estando en la raíz del proyecto se corre el script de la siguiente manera:

```
$ ./test_real.sh
```

Luego, una vez teniendo el código escrito en **Arr** compilado, para ejecutarlo se para sobre la raíz del proyecto y se ejecuta:

```
$ ./real_tests/results/<nombre_del_archivo>
```

### Compilación Específica
Para compilar y ejecutar un archivo de test particular, estando en la raíz del proyecto se puede correr el script de la siguiente manera:

```
$ ./test_real_specific.sh real_tests/<nombre_del_archivo.arr>
```

## Contenidos del Repositorio

### Documentación
Dentro de la carpeta */Documentación* se encuentra el informe del trabajo práctico, con el nombre *"Informe-Hirsch-Henestrosa-Choi-Ribas.pdf"*

### Código Fuente
El código fuente se encuentra en:
- La carpeta */translation* -> código fuente para realizar traducciones
- Los archivos *node.c* y *node.h* -> archivos para la generación del AST
- El archivo *grammar.l* -> archivo de Lex con todos los lexemas correspondientes
- El archivo *yacc.y* -> archivo de Yacc con las producciones y el código de Yacc para el compilador

### Scripts
Se encuentran también una serie de scripts para poder realizar la compilación y ejecución de los archivos de prueba:
- El script *test_real.sh* -> Compila todos los archivos .arr dentro de la carpeta */real_tests* dejando los binarios para ejecutar dentro de la carpeta */real_tests/results*.
- El script *test_real_specific.sh* -> Recibe por entrada estándar el path al archivo .arr para ser compilado y ejecutado.

## Autores

Gonzalo Hirsch - 59089 (ghirsch@itba.edu.ar)

Ignacio Ribas - 59442 (iribas@itba.edu.ar)

Augusto Henestrosa - 59189 (ahenestrosa@itba.edu.ar)

Francisco Choi - 59285 (fchoi@itba.edu.ar)

Autómatas, Teoría de Lenguajes y Compiladores
2020 - 1er Cuatrimestre