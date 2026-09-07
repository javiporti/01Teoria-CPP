# Clase 1: Guía práctica de C++ para estudiantes

## Cómo usar esta guía

Cada bloque de esta guía introduce una idea y termina en un pequeño ejercicio. Para ver el resultado compila y ejecuta en VS Code o en un entorno online. Lee primero el planteamiento, intenta imaginar qué hace el programa (o escríbelo tú mismo en un papel o editor aparte) y solo después despliega el código para comparar tu razonamiento. Por último, comprueba el resultado.

---

## 1. Tu primer programa

Todo programa en C++ necesita una función `main`, que es el punto de entrada: el sistema operativo empieza a ejecutar el programa justo ahí.

Puntos que conviene fijar desde el principio:

- Las líneas que empiezan por `#include` no son C++ propiamente dicho, sino instrucciones para el *preprocesador*: le piden que pegue ahí el contenido de otro fichero (normalmente uno de la biblioteca estándar).
- `std::cout` y `std::cin` son objetos de la biblioteca estándar que representan, respectivamente, la salida (C-out) y la entrada (C-in) estándar. El prefijo `std::` indica que pertenecen al *espacio de nombres* llamado `std`.
- `<<` envía datos hacia la salida; `>>` los extrae desde la entrada. Fíjate en la dirección de las "flechas": apuntan hacia donde va el dato.
- `main` devuelve un entero. Por convención, `0` significa "todo salió bien".

### Ejercicio 1 — Suma, producto y promedio

Vas a ver un programa que pide dos números enteros al usuario y calcula tres cosas a partir de ellos: su suma, su producto y su promedio.

**Antes de mirar el código:** ¿qué tipo debería tener la variable que guarda el promedio, si los números de entrada son enteros? ¿Por qué crees que hace falta tener cuidado ahí?

Supón que el usuario introduce `12` y `7`.

<details>
<summary>Mostrar código</summary>

```cpp
// 01_primer_programa.cpp
// Objetivo: mostrar la estructura mínima de un programa en C++:
// directivas #include, la función main, entrada/salida y el valor de retorno.

#include <cstdlib>   // EXIT_SUCCESS
#include <iostream>  // std::cin, std::cout

int main() {
    int x, y;

    std::cout << "Introduce dos numeros enteros separados por espacio: ";
    std::cin >> x >> y;

    int suma = x + y;
    double promedio = (x + y) / 2.0;   // se usa 2.0 para forzar division real
    int producto = x * y;

    std::cout << "Suma: "      << suma      << '\n';
    std::cout << "Producto: "  << producto  << '\n';
    std::cout << "Promedio: "  << promedio  << '\n';

    return EXIT_SUCCESS;   // por convencion, 0 indica que todo fue bien
}
```

</details>

---

## 2. Tipos fundamentales

C++ es un lenguaje de **tipado estático**: cada variable tiene un tipo fijo, decidido en tiempo de compilación, que determina cuánta memoria ocupa y qué operaciones admite.

| Tipo                         | Uso típico                                                     |
| ---------------------------- | --------------------------------------------------------------- |
| `bool`                     | verdadero/falso                                                 |
| `char`                     | un carácter (habitualmente 1 byte)                             |
| `short`, `int`, `long` | números enteros de distinto rango                              |
| `float`                    | coma flotante, precisión simple                                |
| `double`                   | coma flotante, precisión doble (la opción por defecto)        |
| `enum`                     | un conjunto cerrado de valores con nombre                       |
| `void`                     | "ausencia de tipo"; se usa para funciones que no devuelven nada |

Algunas ideas importantes:

- El tamaño exacto en bits de `short`, `int` y `long` no está fijado por el estándar; depende del compilador y la plataforma. El operador `sizeof(T)` te dice cuántos bytes ocupa el tipo `T` en tu sistema.
- El estándar de C++ **no define un tamaño exacto en bytes** para la mayoría de los tipos (como `int`, `long` o `long long`). En su lugar, el estándar solo garantiza un **tamaño mínimo** y una **relación de orden** entre ellos:

$$
\text{sizeof(char)} \le \text{sizeof(short)} \le \text{sizeof(int)} \le \text{sizeof(long)} \le \text{sizeof(long long)}
$$

---

## Tamaños mínimos garantizados por el estándar

| Tipo básico  | Tamaño mínimo garantizado         | Tamaño común en la actualidad                       |
| :------------ | :---------------------------------- | :---------------------------------------------------- |
| `char`      | **1 byte** (mínimo 8 bits)   | 1 byte                                                |
| `short`     | **2 bytes** (mínimo 16 bits) | 2 bytes                                               |
| `int`       | **2 bytes** (mínimo 16 bits) | **4 bytes** (en casi todo PC/móvil moderno)    |
| `long`      | **4 bytes** (mínimo 32 bits) | **4 u 8 bytes** (depende del Sistema Operativo) |
| `long long` | **8 bytes** (mínimo 64 bits) | 8 bytes                                               |

- Una variable no inicializada tiene un valor indeterminado (basura). Acostumbra a inicializar siempre tus variables.
- Los literales de coma flotante son `double` por defecto; si necesitas un `float`, añade el sufijo `f` (`3.14f`).
- Las enumeraciones (`enum`) son muy útiles para dar nombre a un conjunto de opciones relacionadas, en lugar de usar constantes sueltas por el código.

### Ejercicio 2 — Tamaños de tipo y una enumeración cíclica

El programa declara variables de varios tipos fundamentales e imprime cuánto ocupa cada una con `sizeof`. Después define una enumeración `Cardinal` (los cuatro puntos cardinales) y una función que, dado un punto cardinal, devuelve el siguiente girando en sentido horario.

<details>
<summary>Mostrar código</summary>

```cpp
// 02_tipos_fundamentales.cpp
// Objetivo: repasar los tipos basicos de C++, sizeof, y una enumeracion.

#include <iostream>

// Una enumeracion da nombre a un conjunto cerrado de valores relacionados.
// Es preferible a usar numeros "magicos" sueltos por el codigo.
enum Cardinal { NORTE, ESTE, SUR, OESTE };

// Dado un punto cardinal, devuelve el siguiente girando en sentido horario.
Cardinal siguienteEnSentidoHorario(Cardinal actual) {
    switch (actual) {
        case NORTE: return ESTE;
        case ESTE:  return SUR;
        case SUR:   return OESTE;
        case OESTE: return NORTE;
    }
    return NORTE; // nunca deberia llegar aqui
}

const char* nombreDe(Cardinal c) {
    switch (c) {
        case NORTE: return "Norte";
        case ESTE:  return "Este";
        case SUR:   return "Sur";
        case OESTE: return "Oeste";
    }
    return "?";
}

int main() {
    bool activo = true;
    char inicial = 'A';
    short pequenio = 100;
    int entero = 123456;
    long grande = 3141592653L;
    float simple = 3.14f;
    double doble = 3.14159265358979;

    std::cout << "bool activo    = " << activo   << " (ocupa " << sizeof(bool)   << " bytes)\n";
    std::cout << "char inicial   = " << inicial  << " (ocupa " << sizeof(char)   << " bytes)\n";
    std::cout << "short pequenio = " << pequenio << " (ocupa " << sizeof(short)  << " bytes)\n";
    std::cout << "int entero     = " << entero   << " (ocupa " << sizeof(int)    << " bytes)\n";
    std::cout << "long grande    = " << grande   << " (ocupa " << sizeof(long)   << " bytes)\n";
    std::cout << "float simple   = " << simple   << " (ocupa " << sizeof(float)  << " bytes)\n";
    std::cout << "double doble   = " << doble    << " (ocupa " << sizeof(double) << " bytes)\n";

    std::cout << "\n--- Enumeracion Cardinal ---\n";
    Cardinal direccion = NORTE;
    for (int i = 0; i < 5; i++) {
        std::cout << "Direccion actual: " << nombreDe(direccion) << '\n';
        direccion = siguienteEnSentidoHorario(direccion);
    }

    return 0;
}
```

</details>

**Preguntas:**

- ¿Cuánto ocupa una variable enumerada? ¿Y una cadena?
- En C++ el tamaño de los tipos básicos puede variar según la arquitectura de la máquina, el sistema operativo y el compilador. Busca un caso en el que se pueda observar.

**Para practicar:** declara tu propio `enum` (de los días de la semana en español) y escribe una función que calcule "en qué día cae una fecha determinada". Echa un vistazo a la librería chrono (C++20).

---

## 3. Punteros, arrays y estructuras

Esta es, probablemente, la parte que más cuesta al principio y también la más importante para entender cómo funciona realmente un programa.

**Punteros.** Toda variable vive en una dirección de memoria. Un **puntero** es una variable cuyo contenido es, precisamente, una dirección de memoria de otra variable.

- `&x` obtiene la dirección de `x` (operador "dirección de").
- Si `p` es un puntero, `*p` accede al valor almacenado en la dirección que `p` guarda (operador de *desreferencia*).
- Un puntero que no apunta a ningún objeto válido se marca convencionalmente como `nullptr` (en C++ moderno; en código más antiguo verás `NULL` o `0`). Desreferenciar un puntero así es un error grave en tiempo de ejecución.
- Ojo `Tipo& variable` no es el operador dirección de la variable, forma parte del Tipo y significa `referencia a Tipo`, es decir un alias a la variable. Es como un puntero que maneja el compilador y permite copiar por referencia.

**Arrays.** Una colección de elementos del mismo tipo, de tamaño fijo, en memoria contigua. C++ no comprueba en tiempo de ejecución que el índice esté dentro de los límites del array: escribir fuera de rango es un error silencioso que puede corromper memoria sin avisarte. Ese es uno de los motivos por los que, en programas "reales", se prefiere `std::vector` (de la biblioteca estándar) frente a los arrays estilo C: `vector` sí puede comprobar límites (con el método `.at()`) y puede cambiar de tamaño dinámicamente.

Un dato curioso (y fuente de muchas confusiones): el nombre de un array, usado en una expresión, se comporta como un puntero a su primer elemento. Por eso `arr[i]` y `*(arr + i)` significan lo mismo.

**Estructuras.** Una `struct` agrupa varios datos bajo un mismo nombre. Si tienes un puntero a una estructura, usa `->` en lugar de `(*p).miembro`.

**Memoria dinámica.** A veces no sabemos de antemano cuántos objetos vamos a necesitar, o queremos que un objeto sobreviva más allá del bloque en el que fue creado. Para eso existe la memoria dinámica (el "*free store*" o "*heap*").`new` reserva memoria; `delete` (o `delete[]` para arrays) la libera. Todo lo reservado con `new` debe liberarse exactamente una vez, o se produce una fuga de memoria (*memory leak*): memoria que queda reservada pero inaccesible durante el resto de la ejecución del programa.

**Referencias.** Una referencia es un alias de otra variable: otro nombre para la misma zona de memoria. A diferencia de un puntero, una referencia debe inicializarse en el momento de su declaración y no puede "reapuntar" después a otra variable.

```cpp
int original = 5;
int& alias = original;
alias = 10;              // esto también cambia "original"
```

Las referencias son especialmente útiles al pasar argumentos a funciones.

### Ejercicio 3 — Encontrar el mayor elemento con punteros

El programa combina las cuatro ideas anteriores: modifica una variable a través de un puntero, recorre un array buscando su elemento mayor (devolviendo un puntero a él), trabaja con una `struct Punto` y reserva/libera memoria dinámica, incluyendo un array dinámico.

**Antes de mirar el código:** dado el array `{7, 9, 5, 10, 8}`, ¿qué valor debería devolver una función que busca el mayor elemento? Si esa función devuelve un puntero en lugar del valor directamente, ¿qué ventaja tiene frente a devolver solo el valor?

<details>
<summary>Mostrar código</summary>

```cpp
// 03_punteros_arrays_estructuras.cpp
// Objetivo: practicar punteros, arrays, structs y memoria dinamica.

#include <iostream>

struct Punto {
    double x;
    double y;
};

void imprimirPunto(const Punto& p) {   // referencia constante: no copia, no modifica
    std::cout << "(" << p.x << ", " << p.y << ")";
}

// Recibe un array y su tamanio; devuelve un puntero al mayor elemento.
int* direccionDelMayor(int datos[], int n) {
    int* mejor = &datos[0];
    for (int i = 1; i < n; i++) {
        if (datos[i] > *mejor) {
            mejor = &datos[i];
        }
    }
    return mejor;
}

int main() {
    // --- Punteros basicos ---
    int x = 10;
    int* p = &x;
    std::cout << "x = " << x << ", *p = " << *p << '\n';
    *p = 20;
    std::cout << "Tras *p = 20, x vale " << x << '\n';

    // --- Arrays ---
    int notas[5] = {7, 9, 5, 10, 8};
    std::cout << "\nNotas: ";
    for (int i = 0; i < 5; i++) {
        std::cout << notas[i] << ' ';
    }
    std::cout << '\n';

    int* mejor = direccionDelMayor(notas, 5);
    std::cout << "La mejor nota es " << *mejor << '\n';

    // --- Estructuras ---
    Punto origen = {0.0, 0.0};
    Punto destino = {3.0, 4.0};
    std::cout << "\nOrigen: ";
    imprimirPunto(origen);
    std::cout << "  Destino: ";
    imprimirPunto(destino);
    std::cout << '\n';

    Punto* pd = &destino;
    pd->x += 1.0;   // equivalente a (*pd).x += 1.0;
    std::cout << "Destino tras mover: ";
    imprimirPunto(destino);
    std::cout << '\n';

    // --- Memoria dinamica ---
    int* dinamico = new int;
    *dinamico = 99;
    std::cout << "\nValor dinamico: " << *dinamico << '\n';
    delete dinamico;   // liberar cuando ya no se necesita

    int n = 5;
    int* arrayDinamico = new int[n];
    for (int i = 0; i < n; i++) {
        arrayDinamico[i] = i * i;
    }
    std::cout << "Array dinamico: ";
    for (int i = 0; i < n; i++) {
        std::cout << arrayDinamico[i] << ' ';
    }
    std::cout << '\n';
    delete [] arrayDinamico;   // los arrays se liberan con delete[]

    return 0;
}
```

</details>

**Para practicar:** modificar el código para que si la mejor nota es mayor a 9.5, subirla a 10.

---

## 4. Expresiones, operadores y conversión de tipos

C++ hereda de C una extensa colección de operadores. Algunos grupos a recordar:

- **Aritméticos**: `+ - * / %`. La división entre enteros trunca (descarta la parte decimal); si quieres una división real, al menos uno de los operandos debe ser de coma flotante.
- **Incremento/decremento**: `i++` (postfijo, devuelve el valor y *después* incrementa) frente a `++i` (prefijo, incrementa y *después* devuelve). La diferencia importa cuando el resultado se usa en la misma expresión.
- **Relacionales y lógicos**: `< <= > >= == !=`, y `&& || !`. Los operadores `&&` y `||` son de "cortocircuito": si el resultado ya puede determinarse con el operando izquierdo, el derecho ni siquiera se evalúa. Esto se aprovecha a menudo para evitar errores, por ejemplo comprobando que un puntero no sea nulo antes de desreferenciarlo:

```cpp
if (p != nullptr && p->activo) { /* ... */ }
```

- **Operador condicional (ternario)**: `condicion ? valor_si_verdadero : valor_si_falso`.
- **Operadores de asignación compuesta**: `+= -= *= /= %=` y sus equivalentes con operadores de bits `&= |= ^= <<= >>=`(and, or, xor, desplazamiento izq, despl. derecha y asignación en todos los casos).

**Casting** Cuando necesitas forzar el tipo de una expresión, C++ moderno recomienda `static_cast`, que documenta explícitamente tu intención:

```cpp
double resultado = static_cast<double>(a) / b;
```

### Ejercicio 4 — División entera vs. división real

**Antes de mirar el código:** si `a = 7` y `b = 2`, ¿qué da `a / b` si ambos son `int`? ¿Y si casteas `a` a `double` antes de dividir? ¿Cambia algo si en vez de eso casteas el *resultado* de `a / b` (ya calculado como entero) a `double`?

<details>
<summary>Mostrar código</summary>

```cpp
// 04_expresiones_y_casting.cpp
// Objetivo: practicar operadores y conversion de tipos (casting).

#include <iostream>

int main() {
    // --- Aritmetica entera vs. real ---
    int a = 7, b = 2;
    std::cout << "7 / 2 (entero)          = " << (a / b) << '\n';
    std::cout << "7 % 2 (resto)           = " << (a % b) << '\n';
    std::cout << "static_cast<double>(7)/2 = "
              << (static_cast<double>(a) / b) << '\n';

    // --- Incremento pre y post ---
    int i = 5;
    int j = i++;   // j toma 5, luego i pasa a 6
    int k = ++i;   // i pasa a 7, k toma 7
    std::cout << "\ni=" << i << " j=" << j << " k=" << k << '\n';

    // --- Cortocircuito logico ---
    int* puntero = nullptr;
    if (puntero != nullptr && *puntero > 0) {
        std::cout << "esto nunca se imprime\n";
    } else {
        std::cout << "\nEl cortocircuito evito desreferenciar un puntero nulo\n";
    }

    // --- Operador condicional (ternario) ---
    int x = 15, y = 42;
    int menor = (x < y) ? x : y;
    std::cout << "\nEl menor entre " << x << " y " << y << " es " << menor << '\n';

    // --- Asignacion compuesta ---
    double saldo = 100.0;
    saldo += 25.5;
    saldo -= 10.0;
    saldo *= 2;
    std::cout << "\nSaldo final: " << saldo << '\n';

    return 0;
}
```

</details>

**Para practicar:** cambia el puntero nulo del ejemplo por uno que sí apunte a un entero válido y observa cómo cambia el resultado de la comprobación de cortocircuito.

---

## 5. Control de flujo

C++ ofrece las estructuras habituales: `if / else if / else`, `switch`, y tres tipos de bucles: `while`, `do-while` (el cuerpo se ejecuta siempre al menos una vez) y `for`. `break` interrumpe inmediatamente el bucle o `switch` más interno; `continue` salta directamente a la siguiente iteración.

### Ejercicio 5 — Combinar todas las estructuras de control

**Antes de mirar el código:** el programa recorre los números del 1 al 10, salta los pares con `continue` y se detiene con `break` al llegar al 9. ¿Qué números crees que se imprimirán al final?

<details>
<summary>Mostrar código</summary>

```cpp
// 05_control_flujo.cpp
// Objetivo: practicar if/else, switch, while, do-while, for, break y continue.

#include <iostream>

int main() {
    // --- if / else if / else ---
    int temperatura = 38;
    if (temperatura < 10) {
        std::cout << "Hace frio\n";
    } else if (temperatura < 25) {
        std::cout << "Temperatura agradable\n";
    } else {
        std::cout << "Hace calor\n";
    }

    // --- switch ---
    char opcion = 'B';
    switch (opcion) {
        case 'A':
            std::cout << "Elegiste A\n";
            break;
        case 'B':
            std::cout << "Elegiste B\n";
            break;
        default:
            std::cout << "Opcion desconocida\n";
            break;
    }

    // --- while: suma hasta encontrar un numero negativo ---
    int datos[] = {4, 8, 15, 16, -1, 23, 42};
    int idx = 0, suma = 0;
    while (idx < 7 && datos[idx] >= 0) {
        suma += datos[idx];
        idx++;
    }
    std::cout << "\nSuma antes del primer negativo: " << suma << '\n';

    // --- do-while: se ejecuta al menos una vez ---
    int contador = 0;
    do {
        std::cout << "do-while contador = " << contador << '\n';
        contador++;
    } while (contador < 3);

    // --- for: recorrido con indice ---
    std::cout << "\nCuadrados del 1 al 5:\n";
    for (int n = 1; n <= 5; n++) {
        std::cout << n << "^2 = " << n * n << '\n';
    }

    // --- break y continue ---
    std::cout << "\nNumeros del 1 al 10, saltando los pares, "
                 "y parando al llegar a 9:\n";
    for (int n = 1; n <= 10; n++) {
        if (n % 2 == 0) continue;  // salta los pares
        if (n == 9) break;         // corta el bucle al llegar a 9
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

</details>

---

## 6. Funciones

Una función se caracteriza por su **firma**: tipo de retorno, nombre y lista de parámetros. Es buena práctica separar **declaración** (lo que necesita saber quien la usa) de **definición** (el cuerpo con la implementación real), especialmente en programas repartidos en varios ficheros.

**Paso de parámetros: por valor vs por referencia**
Por defecto, los argumentos se pasan **por valor** (la función recibe una copia). Si declaras el parámetro como referencia (`int&`), la función puede modificar la variable original. Para estructuras o clases grandes, se prefiere pasar por **referencia constante** (`const std::string&`): evita la copia y, además, el compilador impide que la función la modifique por error.

```cpp
void imprimir(const Punto& p) { /* ... */ }
```

Los arrays, por cierto, nunca se pasan por valor: al pasarlos a una función, se convierten automáticamente en un puntero a su primer elemento.

**Sobrecarga de funciones** Puedes definir varias funciones con el mismo nombre pero distinta lista de parámetros: eso se llama **sobrecarga**, y el compilador elige la versión adecuada según los tipos de los argumentos reales.

```cpp
void mostrar(int x);
void mostrar(double x);
void mostrar(const std::string& s);
```

### Ejercicio 6 — Por valor, por referencia y sobrecarga

**Antes de mirar el código:** si una función recibe un `int` por valor y lo incrementa dentro de su cuerpo, ¿cambia la variable original del programa que la llamó? ¿Y si el parámetro es `int&` en lugar de `int`?

<details>
<summary>Mostrar código</summary>

```cpp
// 06_funciones.cpp
// Objetivo: practicar paso por valor, por referencia, referencia constante
// y sobrecarga de funciones.

#include <iostream>
#include <string>

// Paso por valor: la copia local no afecta al argumento original.
void incrementarPorValor(int x) {
    x++;
}

// Paso por referencia: modifica directamente la variable del llamador.
void incrementarPorReferencia(int& x) {
    x++;
}

// Intercambia dos enteros por referencia (sobrecarga 1).
void intercambiar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
// Función que recibe dos punteros a enteros
void intercambiar(int* a, int* b) {
    int temp = *a; // Guarda el valor al que apunta 'a'
    *a = *b;       // Asigna el valor de 'b' a 'a'
    *b = temp;     // Asigna el valor guardado a 'b'
}


// Intercambia dos numeros reales (sobrecarga 2, mismo nombre distinta firma).
void intercambiar(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

// Referencia constante: eficiente (no copia la cadena) y segura
// (el compilador impide que la modifiquemos por error).
void saludar(const std::string& nombre) {
    std::cout << "Hola, " << nombre << "!\n";
}

int main() {
    int n = 10;
    incrementarPorValor(n);
    std::cout << "Tras incrementarPorValor: n = " << n << " (no cambio)\n";

    incrementarPorReferencia(n);
    std::cout << "Tras incrementarPorReferencia: n = " << n << " (si cambio)\n";

    int p = 1, q = 2;
    std::cout << "\nAntes de intercambiar: p=" << p << " q=" << q << '\n';
    intercambiar(p, q);
    std::cout << "Despues de intercambiar: p=" << p << " q=" << q << '\n';
	intercambiar(&p,&q);
  	std::cout << "Despues de intercambiar: p=" << p << " q=" << q << '\n';
    double r = 1.5, s = 2.5;
    intercambiar(r, s);   // el compilador elige automaticamente la version double
    std::cout << "Despues de intercambiar (double): r=" << r << " s=" << s << '\n';

    saludar("Estudiante de C++");

    return 0;
}
```

</details>

**Para practicar:** añade una tercera sobrecarga de `intercambiar` que funcione con `std::string`.

---

## 7. Clases: la base de la programación orientada a objetos

Una `class` agrupa datos o atributos y funciones que operan sobre ellos (**funciones miembro**) en una única unidad. En una `class`, los miembros son `private` por defecto (en una `struct`, `public`). La idea de fondo es la **encapsulación**: separar el *qué hace* una clase de *cómo lo hace*.

**Control de acceso**

- `public`: accesible desde cualquier parte del programa.
- `private`: solo accesible desde dentro de las propias funciones miembro de la clase.
- `protected`: como `private`, pero también accesible desde clases derivadas

### Constructores

Un constructor es una función miembro especial, con el mismo nombre que la clase y sin tipo de retorno, que se ejecuta automáticamente al crear un objeto. Su trabajo es dejar el objeto en un estado válido desde el primer instante.

Puedes definir varios constructores (sobrecarga), incluyendo:

- **Constructor por defecto**: no recibe argumentos (o todos tienen valor por defecto).
- **Constructor de copia**: recibe una referencia constante a otro objeto de la misma clase y copia su contenido. Su firma típica es `NombreClase(const NombreClase& otro)`.

### Destructores

Un destructor (`~NombreClase()`) se ejecuta automáticamente cuando el objeto deja de existir. Si la clase reservó memoria dinámica con `new` en algún momento de su vida, es responsabilidad del destructor liberarla con `delete`.

### Ejercicio 7 — Una clase sencilla con encapsulación

**Antes de mirar el código:** la clase tiene un miembro privado `cuenta` y métodos públicos `incrementar`, `reiniciar` y `valor`. ¿Por qué crees que conviene que `cuenta` no sea accesible directamente desde fuera de la clase?

<details>
<summary>Mostrar código</summary>

```cpp
// 07_clase_contador.cpp
// Objetivo: presentar una clase sencilla, con encapsulacion basica
// (miembros privados accesibles solo mediante funciones publicas).

#include <iostream>

class Contador {
public:
    Contador();                       // constructor por defecto
    explicit Contador(int inicial);   // constructor con valor inicial
    void incrementar(int paso = 1);   // metodo publico, con argumento por defecto
    void reiniciar();
    int valor() const;                // "getter": solo lectura, marcado const

private:
    int cuenta;                       // miembro de dato privado
};

Contador::Contador() {
    cuenta = 0;
}

Contador::Contador(int inicial) {
    cuenta = inicial;
}

void Contador::incrementar(int paso) {
    cuenta += paso;
}

void Contador::reiniciar() {
    cuenta = 0;
}

int Contador::valor() const {
    return cuenta;
}

int main() {
    Contador visitas;              // usa el constructor por defecto -> 0
    std::cout << "Visitas iniciales: " << visitas.valor() << '\n';

    visitas.incrementar();         // usa el paso por defecto (1)
    visitas.incrementar(5);
    std::cout << "Visitas tras incrementos: " << visitas.valor() << '\n';

    Contador puntuacion(100);      // usa el segundo constructor
    puntuacion.incrementar(-30);
    std::cout << "Puntuacion: " << puntuacion.valor() << '\n';

    puntuacion.reiniciar();
    std::cout << "Puntuacion tras reiniciar: " << puntuacion.valor() << '\n';

    // visitas.cuenta = 1000;   // ERROR de compilacion: 'cuenta' es privado

    return 0;
}
```

</details>

---

### La regla de los tres

Si una clase gestiona memoria dinámica (por ejemplo, un puntero reservado con `new[]`), debe proporcionar tres elementos, o el compilador generará versiones "por defecto" que solo copian punteros (una copia superficial), provocando que dos objetos acaben compartiendo la misma memoria:

1. **Destructor** — libera lo reservado.
2. **Constructor de copia** — reserva memoria *nueva* y copia el contenido.
3. **Operador de asignación (`operator=`)** — libera lo que ya tenía, reserva memoria nueva y copia el contenido (comprobando la auto-asignación).

### Ejercicio 8 — Poniendo a prueba la regla de los tres

**Antes de mirar el código:** se crea una lista `original`, se copia en `copia` mediante el constructor de copia, y luego se modifica un elemento de `copia`. ¿Debería cambiar también `original`? ¿Qué pasaría si la clase *no* tuviera un constructor de copia propio?

<details>
<summary>Mostrar código</summary>

```cpp
// 08_clase_con_memoria_dinamica.cpp
// Objetivo: ilustrar la "regla de los tres": cuando una clase reserva
// memoria dinamica, necesita destructor, constructor de copia
// y operador de asignacion propios, o se arriesga a copias superficiales,
// fugas de memoria y punteros colgantes.

#include <iostream>

class ListaEnteros {
public:
    explicit ListaEnteros(int capacidad);
    ListaEnteros(const ListaEnteros& otra);            // constructor de copia
    ListaEnteros& operator=(const ListaEnteros& otra);  // operador de asignacion
    ~ListaEnteros();                                    // destructor

    void establecer(int indice, int valor);
    int obtener(int indice) const;
    int tamanio() const;
    void imprimir() const;

private:
    int* datos;
    int capacidad;
};

ListaEnteros::ListaEnteros(int cap) {
    capacidad = cap;
    datos = new int[capacidad];
    for (int i = 0; i < capacidad; i++) {
        datos[i] = 0;
    }
}

// Constructor de copia: reserva memoria NUEVA y copia el contenido,
// en vez de copiar solo el puntero (lo que haria el compilador por defecto).
ListaEnteros::ListaEnteros(const ListaEnteros& otra) {
    capacidad = otra.capacidad;
    datos = new int[capacidad];
    for (int i = 0; i < capacidad; i++) {
        datos[i] = otra.datos[i];
    }
}

// Operador de asignacion: libera lo que ya tenia, reserva memoria nueva
// y copia el contenido. Comprueba la auto-asignacion (a = a).
ListaEnteros& ListaEnteros::operator=(const ListaEnteros& otra) {
    if (this != &otra) {
        delete [] datos;
        capacidad = otra.capacidad;
        datos = new int[capacidad];
        for (int i = 0; i < capacidad; i++) {
            datos[i] = otra.datos[i];
        }
    }
    return *this;
}

ListaEnteros::~ListaEnteros() {
    delete [] datos;
}

void ListaEnteros::establecer(int indice, int valor) {
    if (indice >= 0 && indice < capacidad) {
        datos[indice] = valor;
    }
}

int ListaEnteros::obtener(int indice) const {
    return datos[indice];
}

int ListaEnteros::tamanio() const {
    return capacidad;
}

void ListaEnteros::imprimir() const {
    std::cout << "[ ";
    for (int i = 0; i < capacidad; i++) {
        std::cout << datos[i] << ' ';
    }
    std::cout << "]\n";
}

int main() {
    ListaEnteros original(5);
    for (int i = 0; i < original.tamanio(); i++) {
        original.establecer(i, i * 10);
    }

    std::cout << "Original: ";
    original.imprimir();

    // Constructor de copia en accion:
    ListaEnteros copia(original);
    copia.establecer(0, 999);   // modificar la copia...

    std::cout << "Original tras modificar la copia: ";
    original.imprimir();        // ...no debe afectar al original
    std::cout << "Copia: ";
    copia.imprimir();

    // Operador de asignacion en accion:
    ListaEnteros tercera(2);
    tercera = original;
    tercera.establecer(1, -1);

    std::cout << "\nOriginal tras modificar 'tercera': ";
    original.imprimir();
    std::cout << "Tercera: ";
    tercera.imprimir();

    return 0;
    // Al salir de main, se llaman automaticamente los destructores
    // de 'original', 'copia' y 'tercera', liberando cada uno su propia memoria.
}
```

</details>

---

### Miembros `friend` (No necesario)

Excepcionalmente, puedes declarar que una función (o incluso otra clase entera) es `friend` de tu clase, lo que le concede acceso a sus miembros privados. Se usa con moderación: es habitual para operadores de entrada/salida o cuando dos clases están muy estrechamente relacionadas.

### Ejercicio 9 — Amistad entre clases

**Antes de mirar el código:** `Matriz2x2` necesita multiplicar sus valores por las coordenadas privadas de un `Vector2D`. Sin declarar amistad, ¿podría `Matriz2x2` acceder a esas coordenadas privadas? ¿Qué alternativa de diseño (sin usar `friend`) se te ocurre?

<details>
<summary>Mostrar código</summary>

```cpp
// 09_amistad_entre_clases.cpp
// Objetivo: ilustrar el uso de "friend" para permitir que una funcion
// (o clase) externa acceda a los miembros privados de una clase.
// Se usa con moderacion: normalmente para operadores de E/S o
// para un par de clases muy estrechamente relacionadas.

#include <iostream>

class Vector2D {
public:
    Vector2D(double x, double y) : x_(x), y_(y) {}

    // Declaramos el operador << como friend: necesita acceder a x_ e y_,
    // pero no puede definirse como metodo miembro porque el operando
    // izquierdo (ostream) no es un Vector2D.
    friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);

    // Tambien concedemos amistad a una clase entera relacionada: Matriz2x2.
    friend class Matriz2x2;

private:
    double x_, y_;
};

std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
    out << "(" << v.x_ << ", " << v.y_ << ")";
    return out;
}

class Matriz2x2 {
public:
    Matriz2x2(double a, double b, double c, double d)
        : a_(a), b_(b), c_(c), d_(d) {}

    // Gracias a la amistad declarada en Vector2D, podemos acceder
    // directamente a v.x_ y v.y_ desde aqui.
    Vector2D multiplicar(const Vector2D& v) const {
        double nuevoX = a_ * v.x_ + b_ * v.y_;
        double nuevoY = c_ * v.x_ + d_ * v.y_;
        return Vector2D(nuevoX, nuevoY);
    }

private:
    double a_, b_, c_, d_;
};

int main() {
    Vector2D v(3.0, 4.0);
    std::cout << "Vector original: " << v << '\n';

    Matriz2x2 identidadEscalada(2, 0, 0, 2);   // escala por 2
    Vector2D resultado = identidadEscalada.multiplicar(v);
    std::cout << "Vector escalado: " << resultado << '\n';

    return 0;
}
```

</details>

---

## 8. La Biblioteca Estándar de Plantillas (STL)

La STL proporciona contenedores genéricos ya probados y eficientes, para que no tengas que reinventar estructuras de datos básicas. Algunos de los más usados:

| Contenedor                      | Idea                                                |
| ------------------------------- | --------------------------------------------------- |
| `std::vector`                 | array dinámico, de tamaño variable                |
| `std::string`                 | cadena de texto con montones de operaciones útiles |
| `std::list`                   | lista doblemente enlazada                           |
| `std::map`                    | diccionario ordenado (clave → valor)               |
| `std::set`                    | conjunto ordenado sin duplicados                    |
| `std::stack` / `std::queue` | pila y cola                                         |

`std::vector` es, en la práctica, el sustituto natural del array estilo C: crece dinámicamente y permite comprobación de límites con `.at()`. `std::string` sustituye a las cadenas estilo C, con montones de operaciones útiles (concatenación, búsqueda, subcadenas...).

```cpp
#include <vector>
std::vector<int> numeros(10);      // 10 enteros, inicializados a 0
numeros.push_back(42);             // añade un elemento al final
numeros.at(3) = 7;                 // acceso con comprobación de límites
std::cout << numeros.size();       // número de elementos actuales
```

Fíjate en que `vector` es una plantilla (*template*): `vector<int>` y `vector<std::string>` son, en la práctica, dos clases distintas generadas a partir de la misma plantilla, una por cada tipo con el que la usas. Los templates son el mecanismo de C++ para escribir código genérico, independiente del tipo concreto.

### Ejercicio 10 — Vectores, cadenas y ordenación

**Antes de mirar el código:** el programa mete cuatro nombres en un `vector<string>` y los ordena con `std::sort`. ¿En qué orden crees que quedarán `{"Turing", "Lovelace", "Hopper", "Knuth"}`?

<details>
<summary>Mostrar código</summary>

```cpp
// 10_stl_vector_string.cpp
// Objetivo: practicar std::vector y std::string, dos piezas centrales
// de la Biblioteca Estandar de Plantillas (STL).

#include <algorithm>   // std::sort
#include <iostream>
#include <string>
#include <vector>

int main() {
    // --- std::vector ---
    std::vector<int> numeros;              // vector vacio
    for (int i = 1; i <= 5; i++) {
        numeros.push_back(i * i);          // añade al final
    }

    std::cout << "Cuadrados: ";
    for (int n : numeros) {                // bucle basado en rango
        std::cout << n << ' ';
    }
    std::cout << "\nTamanio: " << numeros.size() << '\n';

    numeros.at(0) = 1000;                  // acceso con comprobacion de limites
    std::cout << "Tras modificar numeros.at(0): " << numeros[0] << '\n';

    // --- std::string ---
    std::string nombre = "Ada";
    std::string saludo = "Hola, " + nombre + "!";
    std::cout << "\n" << saludo << '\n';
    std::cout << "Longitud: " << saludo.size() << '\n';
    std::cout << "Posicion de 'Ada': " << saludo.find("Ada") << '\n';

    // --- Vector de strings + ordenacion ---
    std::vector<std::string> nombres = {"Turing", "Lovelace", "Hopper", "Knuth"};

    std::cout << "\nAntes de ordenar:\n";
    for (const std::string& n : nombres) {
        std::cout << "  " << n << '\n';
    }

    std::sort(nombres.begin(), nombres.end());

    std::cout << "Despues de ordenar alfabeticamente:\n";
    for (const std::string& n : nombres) {
        std::cout << "  " << n << '\n';
    }

    return 0;
}
```

</details>

**Para practicar:** ordena el vector de nombres por longitud en lugar de alfabéticamente (pista: `std::sort` admite un tercer argumento con el criterio de comparación).

---

## 9. Organizar un programa en varios ficheros

Los programas reales rara vez caben en un único fichero. La convención habitual en C++ es:

- **Ficheros de cabecera (`.h`)**: contienen declaraciones — de clases, funciones, constantes — pero normalmente no la implementación completa de funciones "grandes". Se incluyen con `#include "miClase.h"`.
- **Ficheros fuente (`.cpp`)**: contienen las implementaciones (los cuerpos de las funciones).

Para evitar que una cabecera se procese dos veces (lo cual provocaría errores de redefinición si dos ficheros distintos la incluyen, directa o indirectamente), se usa un "guardián de inclusión":

```cpp
#ifndef MI_CLASE_H
#define MI_CLASE_H

// contenido de la cabecera...

#endif
```

### Ejercicio 11 — Una clase dividida en cabecera, fuente y programa principal

**Antes de mirar el código:** `CuentaBancaria` permite ingresar y retirar dinero, pero un retiro debe rechazarse si supera el saldo disponible. Si el saldo inicial es 500, se ingresan 150, se intenta retirar 1000 (debería fallar) y luego se retiran 200, ¿cuál debería ser el saldo final?

<details>
<summary>Mostrar código (3 ficheros)</summary>

**`CuentaBancaria.h`**

```cpp
// CuentaBancaria.h
// Fichero de cabecera: declara la clase, sin implementar los metodos "grandes".
// El guardian de inclusion (#ifndef / #define / #endif) evita que este
// fichero se procese dos veces si varios .cpp lo incluyen (directa o
// indirectamente).

#ifndef CUENTA_BANCARIA_H
#define CUENTA_BANCARIA_H

#include <string>

class CuentaBancaria {
public:
    CuentaBancaria(const std::string& titular, double saldoInicial = 0.0);

    std::string titular() const { return titular_; }   // trivial: en linea
    double saldo() const { return saldo_; }             // trivial: en linea

    bool ingresar(double cantidad);          // implementadas en el .cpp
    bool retirar(double cantidad);

private:
    std::string titular_;
    double saldo_;
};

// Operador de salida declarado fuera de la clase, implementado en el .cpp
std::ostream& operator<<(std::ostream& out, const CuentaBancaria& cuenta);

#endif // CUENTA_BANCARIA_H
```

**`CuentaBancaria.cpp`**

```cpp
// CuentaBancaria.cpp
// Fichero fuente: contiene la implementacion (el cuerpo) de las funciones
// declaradas en CuentaBancaria.h

#include "CuentaBancaria.h"
#include <iostream>

CuentaBancaria::CuentaBancaria(const std::string& titular, double saldoInicial) {
    titular_ = titular;
    saldo_ = saldoInicial;
}

bool CuentaBancaria::ingresar(double cantidad) {
    if (cantidad <= 0) {
        return false;   // operacion invalida
    }
    saldo_ += cantidad;
    return true;
}

bool CuentaBancaria::retirar(double cantidad) {
    if (cantidad <= 0 || cantidad > saldo_) {
        return false;   // fondos insuficientes o cantidad invalida
    }
    saldo_ -= cantidad;
    return true;
}

std::ostream& operator<<(std::ostream& out, const CuentaBancaria& cuenta) {
    out << "Cuenta de " << cuenta.titular()
        << " | saldo: " << cuenta.saldo();
    return out;
}
```

**`main.cpp`**

```cpp
// main.cpp
// Programa principal de prueba: usa la clase CuentaBancaria definida
// en CuentaBancaria.h / CuentaBancaria.cpp
//
// Para compilar (desde esta carpeta):
//   g++ -std=c++17 -Wall -o prueba_cuenta main.cpp CuentaBancaria.cpp
//   ./prueba_cuenta

#include "CuentaBancaria.h"
#include <iostream>

int main() {
    CuentaBancaria cuenta("Grace Hopper", 500.0);
    std::cout << cuenta << '\n';

    cuenta.ingresar(150.0);
    std::cout << "Tras ingresar 150: " << cuenta << '\n';

    bool exito = cuenta.retirar(1000.0);   // deberia fallar: fondos insuficientes
    std::cout << "Intento de retirar 1000 -> "
              << (exito ? "conseguido" : "rechazado") << '\n';

    cuenta.retirar(200.0);
    std::cout << "Tras retirar 200: " << cuenta << '\n';

    return 0;
}
```

</details>

<details>
<summary>Mostrar resultado</summary>

```
Cuenta de Grace Hopper | saldo: 500
Tras ingresar 150: Cuenta de Grace Hopper | saldo: 650
Intento de retirar 1000 -> rechazado
Tras retirar 200: Cuenta de Grace Hopper | saldo: 450
```

</details>

**Para practicar:** añade un método `transferir(CuentaBancaria& destino, double cantidad)` que retire de una cuenta e ingrese en otra, solo si hay saldo suficiente.

---

## El proceso de escribir un programa

Antes de teclear la primera línea de código, conviene pasar por tres fases:

1. **Diseño.** Decide qué "actores" (clases) va a tener tu programa, qué responsabilidad tiene cada uno, y cómo se comunican entre sí.
2. **Pseudocódigo.** Describe el algoritmo con una mezcla de lenguaje natural y estructuras de control, sin preocuparte todavía por la sintaxis exacta.
3. **Codificación, prueba y depuración.** Escribe el código, compílalo, pruébalo con casos variados (incluyendo casos límite) y localiza errores paso a paso.

Un consejo práctico: compila con frecuencia, en pasos pequeños. Es mucho más fácil encontrar el error si acabas de añadir cinco líneas que si acabas de escribir doscientas.

---

## Resumen visual de conceptos clave

- **Tipo**: determina qué valores puede tomar una variable y qué operaciones admite.
- **Puntero**: variable que guarda una dirección de memoria.
- **Referencia**: alias de otra variable, fijado en su creación.
- **Array**: colección de tamaño fijo, sin comprobación de límites.
- **Estructura/Clase**: agrupación de datos y (en el caso de las clases) funciones que operan sobre ellos.
- **Constructor/Destructor**: inicializan y liberan, respectivamente, los recursos de un objeto.
- **Regla de los tres**: destructor + constructor de copia + operador de asignación, cuando hay memoria dinámica de por medio.
- **STL**: contenedores y algoritmos genéricos ya probados, que evitan reinventar la rueda.
