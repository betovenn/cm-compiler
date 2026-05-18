# Reporte de Correcciones

## Estado actual antes de las correcciones implementadas

El proyecto contenia un compilador C-Minus en desarrollo con las etapas de analisis lexico, analisis sintactico y generacion de arbol sintactico abstracto ya implementadas.

La estructura principal del proyecto estaba organizada de la siguiente forma:

- `src/lexer.l`: especificacion Flex del analizador lexico.
- `src/parser.y`: gramatica Bison del analizador sintactico.
- `src/ast.h` y `src/ast.c`: definicion, creacion e impresion del arbol sintactico abstracto.
- `tests/`: conjunto de archivos de prueba validos e invalidos.
- `output/`: archivos generados por la ejecucion del compilador:
  - `tokens.txt`
  - `LexErr.txt`
  - `SintaxErr.txt`
  - `Arbol.txt`

Antes de las correcciones, el compilador podia reconocer correctamente varios programas validos y generar su AST. Sin embargo, existia un problema importante en la recuperacion de errores sintacticos: cuando un error aparecia dentro de una estructura como `while` o `if`, el parser no se resincronizaba en el punto correcto y terminaba reportando errores adicionales en sentencias internas o llaves de cierre.

Ademas, el binario existente inicialmente estaba desfasado respecto a las fuentes actuales. Al recompilar desde `src/parser.y` y `src/lexer.l`, el comportamiento se alineo con la gramatica fuente.

## Problematica que debia resolverse

La problematica principal era que los errores sintacticos no se informaban de forma precisa cuando ocurrian dentro de condiciones estructurales.

Ejemplo del problema:

```c
void main(void) {
    int i;

    while (i < ) {
        i = i + 1;
    }
}
```

El error real esta en la condicion del `while`, especificamente antes del cierre `)`. El compilador debia reportar el problema en esa condicion.

Antes de la correccion, el parser reportaba el error en la condicion, pero tambien generaba errores derivados sobre la sentencia interna y sobre los cierres estructurales. Esto hacia que el diagnostico fuera confuso, porque parecia que habia multiples errores cuando en realidad el problema principal era uno solo.

## Problemas extras encontrados durante el analisis

Durante la revision se encontraron los siguientes puntos adicionales:

- El proyecto no tenia repositorio Git inicializado, por lo que no habia historial local para comparar cambios.
- `bison`, `flex` y `gcc` no estaban disponibles directamente en el `PATH` de PowerShell, aunque si estaban instalados en MSYS2.
- El archivo `tests/arbolote.txt` contiene un error real en la linea 31: la expresion tiene 13 parentesis de apertura y 12 de cierre.
- Algunos archivos de prueba, como `test.txt` e `input.txt`, usan construcciones no soportadas por la gramatica actual, por ejemplo `int main()` sin `void` en parametros o declaraciones con inicializacion directa como `int i = 0;`.
- El mensaje duplicado `Sentencia invalida` dentro de la regla `statement: error SEMI` generaba ruido adicional despues de que Bison ya habia informado el error sintactico principal.

## Procedimiento para resolver los problemas detectados

Primero se reviso la estructura del proyecto y los archivos principales del compilador:

- `src/parser.y`
- `src/lexer.l`
- `src/ast.h`
- `src/ast.c`
- `Makefile`
- archivos de prueba en `tests/`

Despues se recompilo el compilador desde las fuentes usando las herramientas instaladas en MSYS2:

```powershell
$env:PATH='C:\msys64\mingw64\bin;C:\msys64\usr\bin;' + $env:PATH
bison -d -o parser/parser.tab.c src/parser.y
flex -o lexer/lexer.yy.c src/lexer.l
gcc parser/parser.tab.c lexer/lexer.yy.c src/ast.c -I./src -o bin/compiler.exe
```

Luego se reprodujo el error principal con una condicion invalida dentro de un `while`. Esto confirmo que el parser se recuperaba demasiado tarde y terminaba propagando el error hacia otras partes de la estructura.

Para corregirlo se realizaron estos cambios:

- Se cambio la directiva de errores de Bison a:

```bison
%define parse.error detailed
%define parse.lac full
%locations
```

- Se agrego soporte de ubicaciones desde el lexer mediante `YY_USER_ACTION`, asignando la linea actual a `yylloc`.
- Se agregaron contextos sintacticos para indicar si el error ocurre dentro de la condicion de un `if` o de un `while`.
- Se agregaron reglas de recuperacion especificas para condiciones invalidas:

```bison
IF LPAREN if_condition_context error RPAREN clear_condition_context statement
WHILE LPAREN while_condition_context error RPAREN clear_condition_context statement
```

- Se elimino el reporte manual duplicado de `Sentencia invalida` en la regla general:

```bison
statement : error SEMI
```

Con esto, Bison puede detectar el error en la condicion, sincronizarse en el parentesis de cierre correspondiente y continuar con el bloque sin marcar falsamente las llaves o sentencias internas como errores independientes.

## Resultado final del nuevo compilador y nuevo estado

El compilador fue regenerado y recompilado correctamente. Los archivos generados quedaron actualizados:

- `parser/parser.tab.c`
- `parser/parser.tab.h`
- `lexer/lexer.yy.c`
- `bin/compiler.exe`

El caso problematico principal ahora produce un diagnostico unico y localizado:

```text
Linea 3: syntax error, unexpected RPAREN, expecting LPAREN or ID or NUM en la condicion del while cerca de ')'
```

Tambien se verifico el mismo comportamiento con errores en condiciones de `if`.

Los programas validos revisados continuan funcionando correctamente hasta la etapa solicitada de analisis sintactico y generacion de AST. Se probaron, entre otros:

- `tests/prueba1.txt`
- `tests/prueba2.txt`
- `tests/prueba3.txt`
- `tests/prueba4.txt`
- `tests/prueba5.txt`
- `tests/prueba6.txt`
- `tests/prueba7.txt`
- `tests/prueba8.txt`
- `tests/prueba10.txt`
- `tests/prueba18.txt`

En estos casos no se generaron errores lexicos ni sintacticos, y `output/Arbol.txt` fue producido correctamente.

El nuevo estado del compilador es el siguiente:

- El analisis lexico sigue operando correctamente para los casos probados.
- El analisis sintactico reporta mejor los errores en condiciones de estructuras `if` y `while`.
- La recuperacion de errores ya no propaga diagnosticos falsos hacia cierres estructurales cuando el error real esta dentro de la condicion.
- La generacion del arbol sintactico abstracto sigue funcionando para programas validos.
- El compilador queda funcional hasta la fase de analisis sintactico y generacion de AST, de acuerdo con el alcance solicitado.
