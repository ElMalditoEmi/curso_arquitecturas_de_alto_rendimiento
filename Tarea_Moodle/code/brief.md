#### Nota: Los scripts .sh los hice para trabajar mas agilmente en el ejercicio 2, solamente compilan y ejecutan

# 1. Comparando las versiones
### Compilando y ejecutando la versión de C
Se compilo el archivo ex1.c de la siguiente manera:

![alt text](imagenes/image.png)

Notemos que no se definen `ADDS_VERSION`, `ADDVI_VERSION` en las flags de compilación.
Por lo que la version compilada es la que esta escrita en C.

Esto produce `ex1-scalar.elf`, el cual se ejecuta a través de QEMU de la siguiente manera:
`qemu-mips64 -cpu I6400 ex1-scalar.elf > ex1-scalar.out`

El output producido se guarda en ex1-scalar.out

Para comprobar que no esta vacio hacemos `head ex1-scalar.out` y obtenemos:
![alt text](imagenes/image-1.png)

### Compilando y ejecutando la versión de ADDVI
Se compilo el archivo ex1.c de la siguiente manera para que se compile la versión ADDVI:
![alt text](imagenes/image-2.png)

#### Comparemos los resultados de cada uno
Utilizamos `diff` para comparar los archivos `ex1-scalar.out` y `ex1-vector.out` y obtenemos:
![alt text](imagenes/image-3.png)
Como no se produjo ningún output, podemos concluir que los resultados son iguales.

### Compilando y ejecutando la versión de ADDS
Se compilo el archivo ex1.c de la siguiente manera para que se compile la versión ADDS:
![alt text](imagenes/image-4.png)

#### Comparemos los resultados con los anteriores
Utilizamos `diff` para comparar los archivos `ex1-adds.out` y `ex1-scalar.out` y obtenemos:
![alt text](imagenes/image-5.png)
Como no se produjo ningún output, podemos concluir que los resultados son iguales.

### Conclusiones
Podemos concluir que los resultados de las versiones ADDVI, ADDS y la versión en C son iguales.

# 2. Ejercicio 2, reescribir el código en ensamblador con la librería multimedia
Compilamos el archivo ex2.c de la siguiente manera:
![alt text](imagenes/image-6.png)
Para volver a ejecutar guardando el output en ex2.out hacemos:
![alt text](imagenes/image-7.png)

### Desarrollo del código en ensamblador
Primero me asegure de reservar algunos registros para guardar los valores de los vectores y el resultado.
![alt text](imagenes/image-8.png)

Luego plantee la primera operación de suma de los vectores. Lo hice
sin plantear el loop para poder ver si la suma se realizaba correctamente.
![alt text](imagenes/image-9.png)
Lo que produce el siguiente output:
![alt text](imagenes/image-10.png)
Claramente los dos primeros elementos fueron afectados correctamente.
Sumando B + C y guardando el resultado en A.

Habiendo ganado confianza en la operación de suma, plantee el loop para que se realice la suma de los vectores completos.

![alt text](imagenes/image-11.png)
Obteniendo:
![alt text](imagenes/image-12.png)

Para comprobar que vamos por el buen camino, la columna de los valores
de `a` ya deberia tener los valores correctos.
Esto se chequea sencillamente de la siguiente manera:

Extraemos la columna de los valores de `a` del resultado del programa compilado desde el código C y los guardamos en el archivo `col1_original.out`.
![alt text](imagenes/image-13.png)

Y ahora extraemos la columna de los valores de `a` del resultado del programa compilado desde el código en ensamblador y los guardamos en el archivo `col1_asm.out`.

Finalmente comparamos ambos archivos con `diff` y obtenemos:
![alt text](imagenes/image-14.png)

Como no se produjo ningún output, podemos concluir que los resultados son iguales.

Aregando el resto del código en ensamblador...
![alt text](imagenes/image-15.png)

Veamos y comparemos la salida completa de ambos programas:
![alt text](imagenes/image-16.png)

### Conclusiones
Como no se produjo ningún output, podemos concluir que los resultados son iguales.

