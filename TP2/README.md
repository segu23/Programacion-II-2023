# Trabajo Práctico Nro. 2: Listas

## Participantes:
 - Maria Nazarena Gonzalez (Leg.190217)
 - Valentín Joel Romero Monteagudo (Leg. 190306)
 - Segundo Nazareno Schmidt (Leg. 193970)
 - Santiago Alejo Conti (Leg. 168849)
 - Agustín Ignacio Gonzalez (Leg. 175631)
 - Ausqui Mateo Javier (Leg. 190236)
 
## Profesor a Cargo de la Asignatura:
 - Mario Perello
 
## Trabajos Prácticos a Cargo de:
 - Claudia Reinaudi
 - José Racker
 - Pablo Chale
 - Mariano Goldman

## Complejidad Punto 4:
 - La cota de complejidad algorìtmica temporal de la solución es: O(n).
   Siendo n la lista de menor longitud.
 - La cota de complejidad algorítmica espacial de la solución es: O(m).
   Siendo m la cantidad de elementos de la lista de mayor longitud.
 - Ver en justificaciòn en comentarios de archivo TP2_pto_4.c.
 
 ## Complejidad Punto 6:
 - La complejidad algoritmica de la funcion sublista es de algo de O(n^2) orden cuadratico, ya que para saber si alguna de las listas es sublista de otra, recorro la
   lista mas corta y por cada elemento de esta uso l_buscar en la otra lista que tambien la recorre, entonces tenemos N*N*O(1) = O(n^2).
