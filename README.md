# Práctica No. 1 - Progración Altas Prestaciones #

Se dispone de un archivo de entrada con el siguiente formtato:
dd-mm-yyyy hh:mm:ss.ssssss "VVVVVV" precio

Se desea generar un archivo por cada valor con el siguiente formato:
dd-mm-yyyy hh:mm precio

El nombre de cada uno de estos archivos debe ser el valor con extensión .txt y contendrá en cada línea como precio el valor promdio durante cada minuto. Si para un minuto determinado no hay cotizaciones, entocnes no se generará la línea. Los datos en este archivo estarán ordenados por el siguiente criterio: año, mes, día, hora, minuto.

## Compilación y ejecución

Para compilar y ejecutar el programa se deben utilizar las siguientes instrucciones

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


### Consideraciones ###

* Se suprime la alerta para C++ 17 en la biblioteca *fmt* debido a incompatibilidad con el compilador usado `(apple clang)`.
* Se utiliza la biblioteca *fmt* deido a que se detectó que el proceso más lento se encontraba en la creación del string final en la salida/escritura de archivos.
* Los datos de fecha y tiempo fueron representados con valores `int` para poder aprovechar los operadores de ordenamiento, los segundos y el precios fueron representados por `double`.
* Las comparaciones de rendimiento se realizaron de forma manual, probando diferentes parámetros de compilación y diferentes métodos dentro del código seleccionando la que prsentó menor tiempo.

### Contacto ###

* Paulo Isaac Chang Ruiz - ID: 2174 11495
* Eddy Omar Castro Jáuregui - ID: 2171 10649