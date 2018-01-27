# Práctica No. 1 - Programación de Altas Prestaciones

Se dispone de un archivo de entrada con el siguiente formato:
dd-mm-yyyy hh:mm:ss.ssssss "VVVVVV" precio

Se desea generar un archivo por cada valor con el siguiente formato:
dd-mm-yyyy hh:mm precio

El nombre de cada uno de estos archivos debe ser el valor con extensión .txt y contendrá en cada línea como precio el valor promedio durante cada minuto. Si para un minuto determinado no hay cotizaciones, entocnes no se generará la línea. Los datos en este archivo estarán ordenados por el siguiente criterio: año, mes, día, hora, minuto.

## Compilación y ejecución

Para compilar y ejecutar el programa se deben utilizar las siguientes instrucciones (estando ubicados dentro de */TickerValuator*)

```
cmake .
make
./TickerValuator
```

El programa acepta los argumentos `-i` y `-o` para especificar un archivo de entrada y una ruta de salida para los archivos de resultado, las opciones disponibles son:

* `./TickerValuator` Lee los datos de la entrada estándar y genera los archivos en el directorio actual.
* `./TickerValuator -i <filename>` Lee los datos de *<filename>* y genera los archivos en el directorio actual.
* `./TickerValuator -o <path>` Lee los datos de la entrada estándar y genera los archivos en *<path>*.
* `./TickerValuator -i <filename> -o <path>` Lee los datos de *<filename>* y genera los archivos en *<path>*.

### Objetos utilizados

*<pendiente>*

### Fases del programa

El programa consta de 4 fases principales, las cuales se describen a continuación:

* Lectura: En esta fase se toma la lectura de la entrada estándar o de un archivo de texto especificado dependiendo de los argumentos utilizados para la ejecución del programa. Incluye validaciones tanto de formato de datos como de contenido, indicando alertas en consola en caso encuentre algún dato inválido. 
* Ordenamiento: Esta fase se encarga de ordenar cada uno de los *tickers* ingresados dependiendo de los datos de tiempo que incluyen, en la última fase se necesitará que los datos estén ordenados para poder operarlos.
* Clasificación: La clasificación separa los datos generando un mapa de clasificación que contiene los *ticker* agrupados dependiendo de su *symbol*, manteniendo el orden por tiempo que se obtuvo en la fase anterior.
* Segmentación e impresión: En esta fase se calcula cada uno de los valores de precio por minuto, mientras se va realizando este cálculo se van agregando objetos *ticker simplificado* a un vector. Este vector ordenado se recorre y se calculan los valores por minuto recorriendo y segmentando los *ticker* de acuerdo al minuto donde se encuentran. Cada vez que se completa un segmento de tiempo, éste se añade a la colección. Cuando se cuenta con la colección completa, se envía a impresión. Por cada uno de los datos de precio se genera el formato dd-mm-yyyy hh:mm precio y se genera un archivo con el nombre de *symbol+.txt* en la ruta indicada al momento de la ejecucuón del programa o la ubicación por defecto si no se especifica.


### Paralelización

La sección de cálculos de precio promedio fue paralelizada mediante el uso de la biblioteca *Intel Threading Building Blocks* utilizando los siguientes componentes

* `concurrent_vector`
* `parallel_for`
* `auto_partitioner`
* `parallel_sort`
* `concurrent_unordered_map`

### Otras bibliotecas externas

Para darle formato al texto siguiendo el formato de salida fue utilizada la biblioteca *fmt*, que que dentro de las pruebas realizadas fue la que obtuvo mejor rendimiento realizando esta tarea. Esta biblioteca ofrece una alternativa a la función `printf()` de C++ con la diferencia que permite generar una cadena de caracteres que puede ser utilizada para enviarla a un archivo de texto.

La bilioteca está disponible en [github fmt](<https://github.com/fmtlib/fmt>)

### Pruebas

###### Resultados antes de paralelización

|             |100 resgistros|1000 registros|1000 registros|
|-------------|--------------|--------------|--------------|
|Lectura      |              |              |              |
|Ordenamiento |              |              |              |
|Clasificación|              |              |              |
|Escritura    |              |              |              |

###### Resultados después de paralelización

|             |100 resgistros|1000 registros|1000 registros|
|-------------|--------------|--------------|--------------|
|Lectura      |              |              |              |
|Ordenamiento |              |              |              |
|Clasificación|              |              |              |
|Escritura    |              |              |              |

### Consideraciones

* Se suprime la alerta para C++ 17 en la biblioteca *fmt* debido a incompatibilidad con el compilador usado `(apple clang)`.
* Se utiliza la biblioteca *fmt* deido a que se detectó que el proceso más lento se encontraba en la creación del string final en la salida/escritura de archivos.
* Los datos de fecha y tiempo fueron representados con valores `int` para poder aprovechar los operadores de ordenamiento, los segundos y el precios fueron representados por `double`.
* Las comparaciones de rendimiento se realizaron de forma manual, probando diferentes parámetros de compilación y diferentes métodos dentro del código seleccionando la que prsentó menor tiempo.

### Contribuyentes

* Paulo Isaac Chang Ruiz - [pauloisaac.chang@alumnos.uc3m.es](mailto:pauloisaac.chang@alumnos.uc3m.es)
* Eddy Omar Castro Jáuregui - [eddyomar.castro@alumnos.uc3m.es](mailto:eddyomar.castro@alumnos.uc3m.es)