## Requerimientos
- Se tiene que realizar consultas a las tablas de la BD
- Insertar información almacenada en paginas y partir de las paginas se dividen los sectores


## Importante

- Para la creacion de carpetas y archivos: incluir la biblioteca <windows.h> para utilizar la función CreateDirectory() en Windows. Además, ten en cuenta que este código solo funcionará en sistemas Windows. Si estás trabajando en un entorno POSIX como Linux o macOS, deberás utilizar la función mkdir() como se mostró originalmente.


## Pasos a seguir

1. Crear generador de carpetas , subcarpetas y archivos .txt (Disco, Platos, Bloques), ver como se4rán los sectores
2. Crear metadata: capacidad del disco, nro de bloques, capacidad del bloque, nro de sectores, capacidad el sector
    - Capacidad libre, ocupada, de bloques y sectores
3. Crear una forma de almacenar tablas en cada bloque, ose poner columnas con sus registros:
    - Hacer metadata osea el esquema de las tabalas a parte y los registros a parte
        
    - Por el momento longitud fija
4. Hacer que lea archivos .csv y que los almacene en el "disco" , osea que se reparta en los bloques
5. Añadir opcion de registros manuales (En donde se guarda, mostrar tiempo de ejecucion)
6. Añadir N registros de un .csv
  ELiminar registros (mostrar de donde se eliminó , tiempo de ejecucion)
7. Establecer consultas de un registro y que diga en donde están ubicados, que se realice una busqueda en los bloques 
8. Filtrar numeros enteros de registro
9. Mostrar todos los registros
10. Tiempo de ejecucion par todo eso
11. 


- Estructura variable
- En la estructura capacidad total y capacidad usada solo se usa en los tipo bloque en los demas está de adorno corregir eso