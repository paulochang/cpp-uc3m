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

### Fases del programa

El programa consta de 4 fases principales, las cuales se describen a continuación:

* Lectura: En esta fase se toma la lectura de la entrada estándar o de un archivo de texto especificado dependiendo de los argumentos utilizados para la ejecución del programa. Incluye validaciones tanto de formato de datos como de contenido, indicando alertas en consola en caso encuentre algún dato inválido. 
* Ordenamiento: Esta fase se encarga de ordenar cada uno de los *tickers* ingresados dependiendo de los datos de tiempo que incluyen, en la última fase se necesitará que los datos estén ordenados para poder operarlos.
* Clasificación: La clasificación separa los datos generando un mapa de clasificación que contiene los *ticker* agrupados dependiendo de su *symbol*
* Segmentación e impresión: En esta fase se calcula cada uno de los valores de precio por minuto, mientras se va realizando este cálculo se van agregando objetos *ticker simplificado* a un vector. Este vector ordenado se recorre y se calculan los valores por minuto recorriendo y segmentando los *ticker* de acuerdo al minuto donde se encuentran. Cada vez que se completa un segmento de tiempo, éste se añade a la colección. Cuando se cuenta con la colección completa, se envía a impresión. Por cada uno de los datos de precio se genera el formato dd-mm-yyyy hh:mm precio y se genera un archivo con el nombre de *symbol+.txt* en la ruta indicada al momento de la ejecucuón del programa o la ubicación por defecto si no se especifica.

### Objetos utilizados

#### `ticker` 

El objeto `ticker` es utilizado para representar cada uno de los datos de entrada (*tickers*) con repesentaciones que favorecen la optimización de acuerdo a la forma que son utilizados los valores en sus atributos por los diferentes métodos del programa.

###### Atributos

* `unsigned int date_`: Almacena el valor de la fecha en formato numérico, por ejemplo almacenará el valor 15112018 para la fecha 15 de noviembre de 2018.

* `unsigned short time_`: Almacena el valor del tiempo en formato numérico, por ejemplo almacenará el valor 1234 para la hora 12:34.
* `double seconds_`: Almacena el valor de los segundos.
* `string symbol_`: Almacena el símbolo que identifica al *ticker*.
* `double price_`: Almacena el valor numérico del precio (parte entera y decimal).

###### Métodos

* `ticker() {}`: Constructor por defecto del objeto *ticker*.

* `ticker(unsigned short d, unsigned short m, unsigned short y, unsigned short h, unsigned short min, unsigned short secs, float decimals, std::string symbol, double price)`: Constructor del objeto *ticker*.

	Parámetros 
	* `unsigned short d`: Valor numérico del día (dd).
	* `unsigned short m`: Valor numérico del mes (mm).
	* `unsigned short y`: Valor numérico del año (yyyy).
	* `unsigned short h`: Valor numérico de la hora (hh).
	* `unsigned short min`: Valor numérico de los minutos (mm).
	* `unsigned short secs`: Valor numérico de la parte entera de los segundos (ss).
	* `float decimals`: Valor numérico de los decimales de los segundos (.ssssss).
	* `std::string symbol`: Cadena de caracteres que representa el símbolo del *ticker*.
	* `double price`: Valor numérico del precio (parte entera y decimal).
 

* `ticker(unsigned int date, unsigned short my_time, double seconds, std::string symbol, double price)`: Constructor del objeto *ticker*

	Parámetros
	* `unsigned int date`: Valor de la fecha en formato numérico (15112018 representa la fecha 15 de noviembre de 2018).
	* `unsigned short my_time`: Valor del tiempo en formato numérico (1234 representa la hora 12:34).
	* `double seconds`: Valor de la parte decimal de los segundos.
	* `std::string symbol`: Cadena de caracteres que representa el símbolo del *ticker*.
	* `double price`: Valor numérico del precio (parte entera y decimal).

* `void add_price(double price)`: Método para fijar el valor del precio.
	
	Parámetros
	* `double price`: Valor numérico del precio (parte entera y decimal).

* `double avg_price() const`: Método para obtener el valor promedio del precio.
	
	Retorno
	* `double avg_price` : Valor del precio promedio para el *ticker*.

* `bool operator<(const ticker &a) const`: Método que sustituye al operador `<` para determinar el orden de dos *ticker*.
	
	Parámetros
	* `const ticker &a`: 	Objeto *ticker* con el que se desea hacer la comparación.
	 
	Retorno
	* `bool <`: *true* en caso sea menor el *ticker* comparado con el que es recibió de parámetro.

* `bool operator==(const ticker &a) const`: Método que sustituye al operador `==` para determinar igualdad de dos *ticker*.

	Parámetros
	* `const ticker &a`: 	Objeto *ticker* con el que se desea hacer la comparación.
	 
	Retorno
	* `bool ==`: *true* en caso sea igual el *ticker* comparado con el que es recibió de parámetro.

* `unsigned int date() const`: Método para obtener el valor de la fecha (ddmmyyyy) del *ticker*.

	Retorno
	* `unsigned int date`: Valor de la fecha en formato numérico (15112018 representa la fecha 15 de noviembre de 2018).

* `unsigned short time() const`: Método para obtener el valor del tiempo (hhmm) del *ticker*.

	Retorno
	* `unsigned short time`: Valor del tiempo en formato numérico (1234 representa la hora 12:34).

* `double seconds() const`: Método para obtener el valor de los segundos del *ticker*.

	Retorno
	* `double seconds`: Valor de la parte decimal de los segundos.

* `const double &price() const`: Método para obtener el valor del precio del *ticker*.

	Retorno
	* `const double price`: Valor numérico del precio (parte entera y decimal).

* `const std::string &symbol() const`: Método para obtener el valor del símbolo del *ticker*.

	Retorno
	* `const std::string symbol`: Cadena de caracteres que representa el símbolo del *ticker*.


#### `simplified_ticker`

El objeto `simplified_ticker` es utilizado para representar un objeto `ticker` almacenando únicamente los valores que son utilizados para la impresión.

###### Atributos

* `unsigned int date_`: Almacena el valor de la fecha en formato numérico (15112018 representa la fecha 15 de noviembre de 2018).
    
* `unsigned short time_`: Almacena el valor del tiempo en formato numérico (1234 representa la hora 12:34).
* `double price_`: Almacena el valor numérico del precio (parte entera y decimal).

###### Métodos

* `simplified_ticker(unsigned int date_, unsigned short time_, double price)`: Constructor del objeto *simplified ticker*

	Parámetros
	* `unsigned int date_`: Valor de la fecha en formato numérico (15112018 representa la fecha 15 de noviembre de 2018).
    
	* `unsigned short time_`: Valor del tiempo en formato numérico (1234 representa la hora 12:34).
	* `double price_`: Valor numérico del precio (parte entera y decimal).

* `unsigned int date() const`: Método para obtener el valor de la fecha (ddmmyyyy) del *ticker*.

	Retorno
	* `unsigned int date`: Valor de la fecha en formato numérico (15112018 representa la fecha 15 de noviembre de 2018).

* `unsigned short time() const`: Método para obtener el valor del tiempo (hhmm) del *ticker*.

	Retorno
	* `unsigned short time`: Valor del tiempo en formato numérico (1234 representa la hora 12:34).

* `double price() const`: Método para obtener el valor del precio del *ticker*.

	Retorno
	* `double price`: Valor numérico del precio (parte entera y decimal).

* `void write(fmt::MemoryWriter &out)`: Método utilizado para la impresión de los valores del *ticker* de acuerdo al formato necesario.

	Parámetros
	* `fmt::MemoryWriter &out`: Objeto `MemoryWriter` de la biblioteca *fmt* en donde se agregará el *ticker* actual.


#### `ticker_storage`

###### Atributos

* `tbb::concurrent_vector<ticker> ticker_vector_`:
    
* `tbb::concurrent_unordered_set<std::string> symbol_set_`:
    
* `tbb::concurrent_unordered_map<std::string, std::pair<tbb::concurrent_vector<ticker>::iterator, tbb::concurrent_vector<ticker>::iterator>> classifying_map_`: 
    
* `bool is_sorted{false}`:

###### Métodos

* `void add_ticker(const ticker &myTicker)`:

* `void sort_ticker()`:

* `void symbol_classify()`: 

* `const tbb::concurrent_unordered_map<std::string, std::pair<tbb::concurrent_vector<ticker>::iterator, tbb::concurrent_vector<ticker>::iterator>> & classifying_map() const`: 

    const tbb::concurrent_vector<ticker> &ticker_vector() const;


#### `file_manager`

Este objeto es utilizado para las operaciones que tienen interacción con archivos, lectura y escritura.

###### Métodos

* `ticker_storage file_reader(string input_path)`:

* `void file_writer(string output_path, string file_name, const tbb::concurrent_vector<simplified_ticker> &printing_vector) const`:


### Paralelización

La sección de cálculos de precio promedio fue paralelizada mediante el uso de la biblioteca *Intel Threading Building Blocks* utilizando los siguientes componentes

* `concurrent_vector`
* `parallel_for`
* `auto_partitioner`
* `parallel_sort`
* `concurrent_unordered_map`

Estos componentes fueron utilzados en dos partes principales

##### *ticker_storage*:

En *ticker storage* se cambiaron todas las colecciones a la versión paralela de *Intel tbb*, esto permite que al momento de la impresión sea posible imprimir varios símboles de forma simultánea. Otra sección que se paralelizó fue el ordenamiento, esto se realizó por medio de `parallel_sort`. La única sección que se dejó sin paralelizar, debido al poco aporte que tendría, es la de clasificación (Ley de Amdahl).

##### *print_processed_list*:

En esta sección se realizó el cambio más importante para el programa en general en cuanto a parelelización ya que se pasó de una impresión serializada a una paralelizada. Eto permite que se vaya realizando el cálculo del área (precio promedio) y la impresión en archivo de los símbolos para los cuales ya se tienen los valores calculados de forma paralela.


### Otras bibliotecas externas

Para darle formato al texto siguiendo el formato de salida fue utilizada la biblioteca *fmt*, que que dentro de las pruebas realizadas fue la que obtuvo mejor rendimiento realizando esta tarea. Esta biblioteca ofrece una alternativa a la función `printf()` de C++ con la diferencia que permite generar una cadena de caracteres que puede ser utilizada para enviarla a un archivo de texto.

La bilioteca está disponible en [github fmt](<https://github.com/fmtlib/fmt>)

### Pruebas

###### Resultados antes de paralelización

|             |100 resgistros|1000 registros|10000 registros|
|-------------|--------------|--------------|---------------|
|Lectura      |              |              |               |
|Ordenamiento |              |              |               |
|Clasificación|              |              |               |
|Escritura    |              |              |               |

###### Resultados después de paralelización

|             |100 resgistros|1000 registros|10000 registros|
|-------------|--------------|--------------|---------------|
|Lectura      |              |              |               |
|Ordenamiento |              |              |               |
|Clasificación|              |              |               |
|Escritura    |              |              |               |

### Consideraciones

* Se suprime la alerta para C++ 17 en la biblioteca *fmt* debido a incompatibilidad con el compilador usado `(apple clang)`.
* Se utiliza la biblioteca *fmt* deido a que se detectó que el proceso más lento se encontraba en la creación del string final en la salida/escritura de archivos.
* Los datos de fecha y tiempo fueron representados con valores `int` para poder aprovechar los operadores de ordenamiento, los segundos y el precios fueron representados por `double`.
* Las comparaciones de rendimiento se realizaron de forma manual, probando diferentes parámetros de compilación y diferentes métodos dentro del código seleccionando la que prsentó menor tiempo.

### Contribuyentes

* Paulo Isaac Chang Ruiz - [pauloisaac.chang@alumnos.uc3m.es](mailto:pauloisaac.chang@alumnos.uc3m.es)
* Eddy Omar Castro Jáuregui - [eddyomar.castro@alumnos.uc3m.es](mailto:eddyomar.castro@alumnos.uc3m.es)