# Práctica 3 · Potencia como función primitiva recursiva

Implementación en **C++17**, con diseño orientado a objetos, de la función

## 1. Configurar (crea carpeta build/)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

## 2. Compilar
cmake --build build -j

## 3. Ejecutar el programa principal
./build/potencia_pr -x 2 -y 10

## 4. Ejecutar las pruebas automáticas
ctest --test-dir build --output-on-failure

## 5. Uso general

./build/potencia_pr -x <base> -y <exponente>

## Ejemplos

./build/potencia_pr -x 2 -y 10

potencia(2, 10) = 1024
Numero de llamadas a funciones: 6292

## Ver la ayuda

./build/potencia_pr -h
./build/potencia_pr --help

## Manejo de errores

### Falta un parámetro
./build/potencia_pr -x 2
# Error: es obligatorio indicar la base (-x) y el exponente (-y).

### Valor no numérico
./build/potencia_pr -x abc -y 2
### Error: El valor 'abc' de la opcion -x no es un numero natural

### Desbordamiento (64 bits)
./build/potencia_pr -x 2 -y 64
### Error: 2^64 no es representable con enteros de 64 bits (unsigned long long).

### Coste muy elevado -> muestra un aviso por stderr
./build/potencia_pr -x 2 -y 40
### Aviso: el numero de llamadas estimado es muy elevado...