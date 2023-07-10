Parcial 11/12/2021
Id del curso            : Nat,se puede usar una funcion llamada NuevoID()
Nombre                  : String(con maxima longitud acotada)
Area tematica principal : String (acotada) de un listado predefinido de areas
Cupo                    :
Precio                  :
Docente a cargo         :(Usuario de la plataforma)

-Manejar inscripciones de la plataforma
-Realizar busquedas de cursos
-Identificar cursos con cupo disponible

Courseasy se representa con estr
	donde estr es tupla(cursos: diccLog(idCurso:Nat,tupla<Nombre:Nombre,
														   Cupo:Nat,
														   Precio:Nat,
														   inscriptos:conjLog(usuario),
														   docente:<nombre:usuario,itACursosDelDocente:itConj>,
														   itAInscriptos:lista(<nombre:usuario,itACursoDelUsuario:itConj),
														   abiertaLaInscripcion:bool>)
						usuarios: diccLog(Usuario:Nat,tupla<cursosQueToma   :conjLog(curso),
															cursosQueEnseña :conjLog(curso>))
						cursosPorArea     :diccTrie(area:area,conjLog(curso))
						historicoDeCursos :conjLog(curso)
					   )

Donde curso es Nat
	  usuario es Nat
	  area es String


Algoritmos:

"Donde 
 n es la cantidad de cursos actuales (sin contar eliminados),
 u es la cantidad de usuarios,
 i es la cantidad de inscriptos a un curso determinado"

iPublicarCurso(inout s:courseasy,in nombre:string,in areaTematica:string,in docenteACargo: usuario,in precio:nat,in cupo:nat)->idCurso:nat
	//Definimos en el conj de cursos del usuario que es docenteACargo
	idCurso <- NuevoID()
	itACursoDocente <- agregar(significado(s.usuarios,docenteACargo).cursosQueEnseña,idCurso)       //O(log(u)+log(n))
	//Guardamos la info en s.cursos
	infoDocente <- <docenteACargo,itACursoDocente>													//O(1)
	infoCurso   <- <nombre,cupo,precio,vacio(),infoDocente,vacia(),true>							//O(1)
	definir(s.cursos,idCurso,infoCurso)																//O(log(n))
	//Guardamos el curso en el historico y por area
	agregar(s.historicoDeCursos,idCurso)															//O(log(n))
	agregar(significado(s.cursosPorArea,areaTematica),idCurso)										//O(log(n))

Complejidad Mejor Caso: 
Cuando el curso no esta definido en los conjuntos del docente, historico ni porArea. Esto la pre no lo asegura
Se puede utilizar el agregado rapido para conjuntos
	O(log(u))
Complejidad Peor Caso:
El curso ya esta definido en los conjuntos mencionados anteriormente
   O(log(u)+log(n))

iInscribirACurso(inout s:courseasy,in idCurso:nat,in estudiante: usuario)
	//Definimos en el conj de cursos tomados del usuario
	itACursoDelUsuario <- agregar(significado(s.usuarios,docenteACargo).cursosQueToma,idCurso)       //O(log(u)+log(n))
	//Accedemos a la info del curso por referencia
	infoCurso <- significado(s.cursos,idCurso)														 //O(log(n))
	//Inscribimos al estudiante y guardamos su info
	agregarRapido(infoCurso.inscriptos,estudiante)													 //O(1)
	infoEstudiante <- <estudiante,itACursoDelUsuario>												 //O(1)
	agregarAtras(infoCurso.itAInscriptos,infoEstudiante)											 //O(1)

La complejidad tanto en mejor como en peor caso es la misma. Ya que tengo que acceder a la informacion buscando por usuario y luego por 
curso. Queda (O(log(n)+log(u)))

Ejercicio F. Se agrega a estr el atributo cursosDisponibles: lista(tupla(cupo:nat,itACurso:itDiccLog))
Donde itACurso apunta al significado de la clave del curso en s.cursos. 
iPublicarCurso:
Cada vez que se agrega un curso a s.cursos guardamos el it y lo agregamos a cursosDisponibles junto con su cupo correpondiente
Esto nos suma el costo de reordenar la lista descendientemente con respecto al primer elemento de la tupla añadida(cupo)
con mergeSort: O(n.log(n))
iEliminarCurso:
Al publicar el curso a la lista de cursosDisponibles guardamos el it tambien, asi al acceder a la info del curso en s.cursos, 
lo usamos para eliminar la tupla en la lista en O(1). La lista mantiene su orden.     

iCursosDisponibles(in s:courseasy)->itACursos
	itACursos <- & s.cursosDisponibles