## **Diagramas**

- **Buffer Manager**

![Descripción de la imagen](imgs/Diagrama_BufferManager.png)

- **Estructura de Manejo HDD**

![Descripción de la imagen](imgs/Diagrama_Estructura_Espacio_HDD.svg)


## **Teoría a considerar**

### Tipos de Datos y tamanios de ccampo:

1. **Tipos de Datos Numéricos**:
   - **INT**: Generalmente ocupa 4 bytes. - CONSIDERADO
   - **SMALLINT**: Generalmente ocupa 2 bytes.
   - **BIGINT**: Generalmente ocupa 8 bytes.
   - **FLOAT**: Generalmente ocupa 4 bytes.
   - **DOUBLE**: Generalmente ocupa 8 bytes.
   - **DECIMAL**: El tamaño depende de la precisión y escala especificadas.

2. **Tipos de Datos de Cadena**:
   - **CHAR(n)**: Ocupa n bytes, donde n es el número de caracteres especificados. 
   - **VARCHAR(n)**: Ocupa el tamaño real de la cadena más 1 o 2 bytes adicionales para almacenar la longitud de la cadena. - CONSIDERADO
   - **TEXT**: El tamaño puede variar ampliamente y depende de la implementación de la base de datos.

3. **Tipos de Datos de Fecha y Hora**:
   - **DATE**: Generalmente ocupa 3 bytes.
   - **TIME**: Generalmente ocupa 3 bytes.
   - **DATETIME**: Generalmente ocupa 8 bytes.
   - **TIMESTAMP**: Generalmente ocupa 4 bytes.

4. **Tipos de Datos Binarios**:
   - **BLOB**: El tamaño puede variar ampliamente y depende de la implementación de la base de datos.

#### Definición de Campos con Diferentes Tipos de Datos:

```sql
CREATE TABLE ejemplo (
    id INT,                 -- 4 bytes
    nombre VARCHAR(255),    -- Longitud de la cadena + 1 o 2 bytes
    edad SMALLINT,          -- 2 bytes
    salario DECIMAL(10, 2), -- Dependiendo de la implementación
    fecha_nacimiento DATE,  -- 3 bytes
    foto BLOB               -- Tamaño variable
);
```

### Relación entre espacio y caracteres

- **ASCII:** caracter = 1 byte (8 bits) - CONSIDERADO
- **Unicode y UTF-8:** caracter = entre 1 y 4 bytes
- **UTF-16:** caracter = entre 2 y 4 bytes
- **UTF-32:** caracter = 4 bytes

## **Importante**

- Para la creacion de carpetas y archivos: incluir la biblioteca <windows.h> para utilizar la función CreateDirectory() en Windows. Además, tener en cuenta que este código solo funcionará en sistemas Windows. Si estás trabajando en un entorno POSIX como Linux o macOS, deberás utilizar la función mkdir() como se mostró originalmente.





