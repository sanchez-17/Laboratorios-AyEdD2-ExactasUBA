Simbolos: → ∊ ∧L ∀ ≡ ∪ =>

TAD Turno es { Mañana | Tarde | Noche }
TAD Curso es Tupla(string, string) // Nombre, turno
TAD Aula es Nat // Capacidad
TAD Persona es string
TAD CausaDeBaja es { Cupos | Voluntaria | Ausencias }

Observadores:

Cursos: ECIA → Conj(Curso)
CapacidadAula: ECIA e × Curso c → Nat                   { c ∊ cursos(e) }
InscriptosIniciales: ECIA e × Curso c → Conj(Persona)   { c ∊ Cursos(e) }
InscriptosActivos: ECIA e × Curso c → Conj(Persona) 	{ c ∊ Cursos(e) }
CausaDeBaja: ECIA e × Curso c × Persona p → CausaDeBaja {c ∊ Cursos(e) ∧L p ∊ PersonasDadasDeBaja(e, c) }
Asistencias: ECIA e × Curso c × Persona p → Nat         {c ∊ Cursos(e) ∧L p ∊ InscriptosActivos(e, c) }
Faltas: ECIA e × Curso c × Persona P → Nat              {c ∊ Cursos(e) ∧L p ∊ InscriptosActivos(e, c) }

--------------------------------------------------------
Generadores:

-CrearECI: Conj(Curso): cs × Dicc(Curso, Aula): asignaciones × Dicc(Curso, Conj(Persona)) inscriptos
														{ cs = claves(asignaciones) = claves(inscriptos) }

-DarDeBaja: ECIA × Curso c × Persona p                   {c ∊ Cursos(e) ∧L p ∊ InscriptosActivos(e, c) }

-PasarLista: ECIA e × Curso c × Conj(Persona) presentes × Conj(Persona) ausentes → ECIA
														{ c ∊ Cursos(e) ∧L Vacio?(presentes ∩ ausentes) ∧ 
									∀p P: persona: p ∊ presentes ∪ ausentes => p ∊ InscriptosActivos(e, c) }

-JustificarAusencias: ECIA × Curso c × Persona p  		{ c ∊ Cursos(e) ∧L p ∊ PersonasDadasDeBaja(e, c) ∧L
														 CausaDeBaja(e, c, p = Ausencias) }

--------------------------------------------------------
Otras Operaciones:

-ObtenerNReasignados: ECIA e → Conj(Persona) // A definir a futuro
-DeBajaPorAusencias: ECIA e × Curso c → Conj(Persona)       	 { c ∊ Cursos(e) }
-DeBajaPorCupos: ECIA e × Curso c → Conj(Persona) 				 { c ∊ Cursos(e) }
-DeBajaVoluntaria: ECIA e × Curso c → Conj(Persona) 			 { c ∊ Cursos(e) }
-PersonasDadasDeBaja: ECIA e × Curso c → Conj(Persona)			 { c ∊ Cursos(e) }
-LlegaronADosFaltas: ECIA e × Curso c × Conj(Persona) ausentes → Conj(Persona) 
							{ c ∊ Cursos(e) ∧L ∀p P: persona: p ∊ ausentes => p ∊ InscriptosActivos(e, c) }
-FiltrarBajasPor: ECIA e × Curso c × Conj(Persona) deBaja × CausaDeBaja → Conj(Persona)
							{ c ∊ Cursos(e) ∧L ∀p P: persona: p ∊ deBaja => p ∊ PersonasDadasDeBaja(e, c) }

---------------------------------------------------------
Axiomatizacion:
Cursos(CrearECI(cs,asignaciones,inscriptos)) ≡ cs
Cursos(DarDeBaja(e,c,p)) ≡ cursos(e)
Cursos(PasarLista(e,c,presentes,ausentes)) ≡ Cursos(e)
Cursos(JustificarAusencias(e,c,p))≡ Cursos(e)
----
CapacidadAula(CrearECI(cs,asignaciones,inscriptos),c) ≡ obtener(c,asignaciones)
CapacidadAula(DarDeBaja(e,c,p),c) ≡ CapacidadAula(e,c)
CapacidadAula(PasarLista(e,c,presentes,ausentes),c) ≡ CapacidadAula(e,c)
CapacidadAula(JustificarAusencias(e,c,p),c) ≡ CapacidadAula(e,c)
----
InscriptosIniciales(CrearECI(cs,asignaciones,inscriptos),c) ≡ obtener(c,inscriptos)
InscriptosIniciales(DarDeBaja(e,c_0,p),c_1) ≡ InscriptosIniciales(e,c_1)
InscriptosIniciales(PasarLista(e,c_0,presentes,ausentes),c_1) ≡ InscriptosIniciales(e,c_1)
InscriptosIniciales(JustificarAusencias(e,c_0,p),c_1) ≡ InscriptosIniciales(e,c_1)
----
InscriptosActivos(CrearECI(cs,asignaciones,inscriptos),c) ≡ 
//Chequeo si la capacidad del aula es menor a la cantidad de inscriptos, si excede tomo 
//#incrip-# personas:
//Si el aula es mayor que la cantidad de inscriptos, 
if obtener(c,asignaciones) = #obtener(c,inscriptos) 
	then obtener(c,inscriptos) 
	else if obtener(c,asignaciones) < #obtener(c,inscriptos)
			then dameN(inscriptos,obtener(c,asignaciones)) //Obtengo tantas personas como cap del aula
		    else obtener(c,inscriptos) U Nreasignados(e,obtener(c,inscriptos) - #obtener(c,inscriptos))
		 fi
fi

InscriptosActivos(DarDeBaja(e,c_0,p),c_1) ≡ 
if c_0 = c_1 
	then InscriptosActivos(e,c_1) - {p}
	else InscriptosActivos(e,c_1)
fi

InscriptosActivos(PasarLista(e,c_0,presentes,ausentes),c_1) ≡ 
if c_0 = c_1 
	then presentes U conCeroFaltas(e,ausentes,c_0)
	else InscriptosActivos(e,c_1)
fi

conCeroFaltas(e,ausentes,c)≡ 
if vacia?(ausentes)
	then ∅
	else if faltas(e,c,dameUno(ausentes)) = 0
			then Ag(dameUno(ausentes),conCeroFaltas(e,sinUno(ausentes),c) )
			else conCeroFaltas(e,sinUno(ausentes),c)
		fi
fi

InscriptosActivos(JustificarAusencias(e,c_0,p),c_1) ≡ 
if c_0 = c_1 
	then Ag(p,InscriptosActivos(e,c_1))
	else InscriptosActivos(e,c_1)
fi
----
CausaDeBaja(CrearECI(cs,asignaciones,inscriptos),c,p) ≡ Cupos
CausaDeBaja(DarDeBaja(e,c_0,p_0),c_1,p_1) ≡ 
if c_0 = c_1 ∧ p_0 = p_1 
	then Voluntaria
	else CausaDeBaja(e,c_1,p_1)
fi

CausaDeBaja(PasarLista(e, c_0, presentes, ausentes), c_1, p) ≡
if c_0 = c_1 ∧ p ∊ ausentes ∧ faltas(e,c_0,p) = 1
	then Ausencias
	else CausaDeBaja(e,c_1,p)
fi

CausaDeBaja(JustificarAusencias(e, c_0, p_0),c_1,p_1) ≡ 
if c_0 = c_1 ∧ p_0 = p_1
	then Ausencias
	else CausaDeBaja(e,c_1,p_1) 
fi

Asistencias(CrearECI(cs, asignaciones, inscriptos), c, p) ≡ 0
Asistencias(DarDeBaja(e,c_0,p_0), c_1, p_1) ≡ Asistencias(e,c_1,p_1)
Asistencias(PasarLista(e, c_0, presentes, ausentes), c_1, p_1) ≡ 
if c_0 = c_1 ∧ p_1 ∊ presentes
	then Asistencias(e,c_1,p_1) + 1
	else Asistencias(e,c_1,p_1)
fi
Asistencias(JustificarAusencias(e, c_0, p_0), c_1, p_1) ≡ Asistencias(e,c_1,p_1)
----
Faltas(CrearECI(cs, asignaciones, inscriptos),c,p) ≡ 0
Faltas(DarDeBaja(e,c_0,p_0),c_1,p_1) ≡ Faltas(e,c_1,p_1)
Faltas(PasarLista(e, c_0, presentes, ausentes),c_1,p_1) ≡ 
if c_0 = c_1 ∧ p_1 ∊ ausentes
	then Faltas(e,c_1,p_1) + 1
	else Faltas(e,c_1,p_1)
fi
Faltas(JustificarAusencias(e, c_0, p_0),c_1,p_1) ≡ 
if c_0 = c_1 ∧ p_0 = p_1
	then 0
	else Faltas(e,c_1,p_1)
----
PersonasDadasDeBaja(e,c) ≡ InscriptosIniciales(e,c) - InscriptosActivos(e,c)
DeBajaPorAusencias(e,c) ≡ FiltrarBajasPor(e,c,PersonasDadasDeBaja(e,c),Ausencias)
DeBajaVoluntaria(e,c) ≡ FiltrarBajasPor(e,c,PersonasDadasDeBaja(e,c),Voluntaria)
DeBajaPorCupos(e,c) ≡ FiltrarBajasPor(e,c,PersonasDadasDeBaja(e,c),Cupos)
FiltrarBajasPor(e,c,deBaja,CausaDeBaja) ≡ 
if vacia?(deBaja)
	then ∅
	else if CausaDeBaja(e,c,dameUno(deBaja)) = CausaDeBaja
			then Ag(dameUno(deBaja),FiltrarBajasPor(e,c,sinUno(deBaja),CausaDeBaja))
			else FiltrarBajasPor(e,c,sinUno(deBaja),CausaDeBaja)
		 fi
fi

