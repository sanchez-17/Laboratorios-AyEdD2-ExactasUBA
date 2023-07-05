Simbolos: → ∊ ∧L ∀ ≡ ∪ => ¬ ∅ ⊆ β =>L

##################################################################################################
# 									 	1P1C2023									  06/05/2023 #
#								   	 ECI ASISTENCIAS		 								     #
##################################################################################################
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

##################################################################################################
# 										1P2C2021 									  11/09/2021 #
#										STOPIFAIL											     #
##################################################################################################
-Oyentes
-Artistas
-Artistas Favoritos
-Canciones de Artistas
-Playlist(oyente)->secu

##################################################################################################
# 										1P1C2022 									  29/04/2022 #
#								   JUEGO DE CALAMARES											 #
##################################################################################################

TAD Calamar ES String

TAD JUEGO DE CALAMARES
genero JDC

Observadores
calamaresEnCompetencia    : JDC → conj(calamares)
seguidoresDe 			  : JDC x calamar → conj(calamar)

Generadores
luchaDePoder      : JDC x calamar: avergonzador x calamar: avergonzado → JDC 
cambiarSeguidor   : JDC x calamar c_1 x calamar c_2 → JDC 

Otras Operaciones
quienesVanGanando : JDC → conj(calamares)

##################################################################################################
# 										1P1C2022 									  06/07/2019 #
#								       GUESTEROS			     								 #
##################################################################################################
TAD Reino ES String
TAD GUESTEROS
-genero g
-igualdad observacional
(∀g_1,g_2:GUESTEROS) ( g_1 = g_2 ⇔ reinos(g_1)=reinos(g_2) ∧ 
					   (∀r:reino)(r ∊ reinos(g_1) =>L poderio(g_1,r)=poderio(g_2,r)  ∧ ) ∧
					   								 aliados(g_1,r)=aliados(g_2,r)  ∧
					   								 espiasEn(g_1,r)=espiasEn(g_2,r)
					   	batallaMasSangrienta(g_1)=batallaMasSangrienta(g_2)
					  )
-Observadores Basicos

reinos               : g → conj(reino)
poderio              : g x r → Nat 					{r ∊ reinos(g)}
aliados              : g x r → conj(reino)					{r ∊ reinos(g)}
espiaA               : g x r → conj(reino)			{r ∊ reinos(g)}
batallaMasSangrienta : g → Nat				

-Generadores Basicos

iniciarCancionDeFuegoYHielo     : conj(reino):rs x dicc(reino,Nat) s → g  	{¬(vacio?(rs)) ∧ rs=claves(s)}
invadirReino 					: g x reino: atacante x reino:defensor → g      
					{ atacante ≠ defensor ∧ {atacante,defensor} ⊆ reinos(g) ¬(defensor ∊ aliados(g,atacante)) }
aliarse 						: g x reino r1 x reino r2 → g 
												{{r1,r2} ⊆ reinos(g) ∧ ¬(r2 ∊ aliados(g,r1))}
espiarEn						: g x reino r1 x reino r2 → g
												{ {r1,r2} ⊆ reinos(g)}

-Otras Operaciones

reinosLosers : g → conj(reino)
poderioAliado : g x reino → Nat  

-Axiomatizacion
reinos(iniciar(rs,cs))    		≡ rs
reinos(invadirReino(g,r1,r2))   ≡ reinos(g)
reinos(aliarse(g,r1,r2))        ≡ reinos(g)
reinos(espiarEn(g,r1,r2))       ≡ reinos(g)
  
poderio(iniciar(rs,cs),r)             ≡ obtener(r,cs)
poderio(invadirReino(g,r1,r2),r)      ≡  //Arreglar poderioAliado, tiene que filtrar el poderio de aliados en comun
if r1=r
	then if (poderio(r) + poderioAliado(r1)) * 2 * β(r2 ∊ espiaA(g,r1))  > (poderio(r2) + poderioAliado(r2)) * 2 * β(r1 ∊ espiaA(g,r2))
			then poderio(r) + β(porc(poderio(r2),70) < porc(poderio(r),10)) * poderio(r2)
			else if porc(poderio(r),70) < porc(poderio(r2),10) 
					then 0
					else porc(poderio(r),70)
				 fi
		 fi
	else poderio(r)
fi
poderio(aliarse(g,r1,r2),r)  ≡ poderio(g,r)
poderio(espiarEn(g,r1,r2),r) ≡ poderio(g,r)

aliados(iniciar(rs,cs),r)      ≡ ∅
aliados(invadirReino(g,r1,r2),r)  ≡
if gana(g,r1,r2)
	then if ocupaReino(g,r1,r2)
			then if r = r1
					then aliados(r) U {r2}
					else if r = r2
							then {r1}
							else aliados(r)
						 fi
				 fi
			else aliados(r)
		 fi
	else if ocupaReino(r2,r1)
			then if r = r2 
					then aliados(r) U {r1}
					else if r = r1
							then {r2}
							else aliados(r)
						 fi
				 fi
			else aliados(r)
		 fi
fi


if r1 = r ∧ gana(g,r,r2)
	then if ocupaReino(g,r,r2)
			then aliados(r) U {r2}
		 fi
	else if r = r2 ∧ gana(g,r,r2)

  

#######En caso de que no uses un dicc en GUESTEROS para registrar el poderio de cada reino ##############
#	TAD Reino 																							#
#	genero reino 																						#
#																										#
#	Observadores 																						#
#	Nombre         : reino → string 	 																#
#	CantDeSoldados : reino → Nat 																		#
#																										#																		
#	Generadores																							#
#	crearReino         : Nat:cantSoldados x String:nombre      	   → reino {cantSoldados>0} 			#
#	actualizarPoderio  : reino x Nat:incrementar x Nat:decrementar → reino 								#
#########################################################################################################

##################################################################################################
# 										1P2C2021 									  04/12/2021 #
#								       MiComprAR			     								 #
##################################################################################################

TAD Producto ES String
TAD Cant,Precio,Item,UnidadesVendidas ES Nat
TAD Comprador, Vendedor es String

TAD MiComprAR
genero MiCAR
igualdad observacional 
(∀m1,m2:MiCAR) ( m1 = m2 ⇔ vendedores(m1)=vendedores(m2) ∧ compradores(m1) = compradores(m2) ∧ 
					   (∀v:Vendedor)(v ∊ vendedores(m1) =>L  stock(m1,v)=stock(m2,v) ∧L 
					   				  (∀i:Item)(i ∊ claves(stock(m2,v)) =>L listaDeEspera(m1,item,v)=listaDeEspera(m1,item,v))
					   				 )
					∧ (∀c:Comprador)(c ∊ compradores(m1) =>L  gastosPorCliente(m1,c)=gastosPorCliente(m2,c))
				)	

-Observadores Basicos

vendedores       : MiCAR → conj(Vendedor)
compradores      : MiCAR → conj(Comprador)
stock            : MiCar:m x Vendedor:v → dicc(Item,<Cant,Precio,UnidadesVendidas>) {v∊ vendedores(m)}
gastosPorCliente : MiCAR:m x Comprador:c → Nat
listasDeEspera   : MiCAR → dicc(Item,secu(<Comprador,Cant>))

-Generadores

iniciar 			: → MiCAR
registrarVendedor   : MiCAR:m x Vendedor:v → MiCAR               		{¬(v ∊ vendedores(m))}
registrarComprador  : MiCar:m x Comprador:c → MiCAR  				    {¬(c ∊ compradores(m))}
publicar            : MiCAR x Vendedor x Item x Cant x Precio → MiCAR
comprar             : MiCAR x Comprador x Item x Cant → MiCAR
actualizarStock     : MiCAR x Vendedor x Item x Cant → MiCAR

-Otras Operaciones
CuantoSeVendioDe    : MiCAR x Item → Nat
#VIP                : MiCAR → Nat 

-Axiomatizacion
vendedores(iniciar()) ≡ ∅
vendedores(registrarVendedor(m,v)) ≡ vendedores(m) U {v}
vendedores(registrarComprador(m,c)) ≡ vendedores(m)
vendedores(publicar(m,v,i,c,p)) ≡ vendedores(m)
vendedores(comprar(m,v,i,c,p)) ≡ vendedores(m)
vendedores(actualizarStock(m,v,i,c)) ≡ vendedores(m) 

stock(iniciar)




##################################################################################################
# 											TAD	PDZ 								  --/--/---- #
#								         Peajes Del Zar 			     				     	 #
##################################################################################################
TAD Cabina ES Nat
TAD Precio ES Nat
TAD Limite ES Nat
TAD TipoAuto ES String
TAD PeajesDelZar
genero PDZ
igualdad observacional 
(∀p1,p2:PDZ)(p1 = p2 ⇔ cabinas(p1) = cabinas(p2) ∧ preciosPorTipo(p1)=preciosPorTipo(p2) ∧limitePorCabina(p1)=limitePorCabina(p2)∧
			( (∀c:Cabina)(c ∊ cabinas(p1) =>L autosEnCabina(p1,c)=autosEnCabina(p2,c) ∧ facturacion(p1,c)=facturacion(p2,c)
			 ∧ (∀t:TipoAuto)(t∊claves(preciosPorTipo(p1))=>L(cantAutosQuePasaronPor(p1,t,c)=cantAutosQuePasaronPor(p2,t,c)

-Observadores Basicos
cabinas                 : PDZ → conj(Cabina)
preciosPorTipo          : PDZ → dicc(TipoAuto,Precio)
limitePorCabina         : PDZ → Limite
autosEnCabina           : PDZ:p x Cabina:c → colaPrior(TipoAuto)     {c ∊ cabinas(p)}
facturacion             : PDZ:p x Cabina:c → Precio                  {c ∊ cabinas(p)}
cantAutosQuePasaronPor  : PDZ:p x TipoAuto:t x Cabina:c → Nat    {t∊claves(preciosPorTipo(p) ∧ c ∊ cabinas(p))}

-Generadores
iniciarPeaje   : conj(Cabina):cs x dicc(TipoAuto,Precio):d x Limite:l → PDZ 			{¬(vacia?(cs)∧ d=vacio) ∧ l>0 }
llegaAuto      : PDZ:p x TipoAuto:a x Cabina:c → PDZ 									{c ∊ cabinas(p)∧ a ∊ claves(preciosPorTipo(p))}
atenderFila    : PDZ:p x Cabina:c → PDZ 												{c ∊ cabinas(p)}

-Otras Operaciones
porCualCabinaPasoMasDe :PDZ:p x TipoAuto:t → conj(Cabina)          					    {t ∊ claves(preciosPorTipo(p))}

-Axiomatizacion
cabinas(iniciarPeaje(cs,d,l)) ≡ cs 
cabinas(llegaAuto(p,a,c))     ≡ cabinas(p)
cabinas(atenderFila(p,c))     ≡ cabinas(p)

preciosPorTipo(iniciarPeaje(cs,d,l)) ≡ d
preciosPorTipo(llegaAuto(p,a,c))     ≡ preciosPorTipo(p)
preciosPorTipo(atenderFila(p,c))     ≡ preciosPorTipo(p)

limitePorCabina(iniciarPeaje(cs,d,l)) ≡ l
limitePorCabina(llegaAuto(p,a,c))     ≡ limitePorCabina(p)
limitePorCabina(atenderFila(p,c))     ≡ limitePorCabina(p)

autosEnCabina(iniciarPeaje(cs,d,l),c) ≡ vacia
autosEnCabina(llegaAuto(p,a,c1),c)    ≡
if c1=c 
	then if long(autosEnCabina(p,c))=limitePorCabina(p)
			then encolar(a,desencolarN(autosEnCabina(p,c),long(autosEnCabina(p,c))/2))
			else encolar(a,autosEnCabina(p,c))
		 fi
	else autosEnCabina(p,c)
fi
autosEnCabina(atenderFila(p,c1),c) ≡
if c1=c
	then desencolar(autosEnCabina(p,c))
	else autosEnCabina(p,c)
fi

facturacion(iniciarPeaje(cs,d,l),c) ≡ 0
facturacion(llegaAuto(p,t,c1),c)    ≡ facturacion(p,c)
facturacion(atenderFila(p,c1),c)    ≡ 
if c1=c
	then facturacion(p,c) + obtener(proximo(autosEnCabina(p,c),preciosPorTipo(p)))
	else facturacion(p,c)
fi

cantAutosQuePasaronPor(iniciarPeaje(cs,d,l),t,c) ≡ 0
cantAutosQuePasaronPor(llegaAuto(p,t1,c1),t,c)   ≡ cantAutosQuePasaronPor(p,t,c)
if c1=c ∧ long(autosEnCabina(p,c))=limitePorCabina(p) 
	then cantAutosQuePasaronPor(p,t,c) + #AutosDelTipoEn(desencolarN(autosEnCabina(p,c),long(autosEnCabina(p,c))/2),t)
	else cantAutosQuePasaronPor(p,t,c)
fi
cantAutosQuePasaronPor(atenderFila(p,c1),t,c) ≡
if c1=c ∧ t=proximo(autosEnCabina(p,c))
	then cantAutosQuePasaronPor(p,t,c) + 1
	else cantAutosQuePasaronPor(p,t,c)
fi

porCualCabinaPasoMasDe(p,t)             ≡ obtenerCabinasConCantDeYTipo(p,cabinas(p),maximaCantDelTipo(p,cabinas(p),t),t)
//Recorro todas las cabinas y veo cual es la maxima cant de vehiculos que pasaron del tipo t
maximaCantDelTipo(p,cs,t) 		≡ aux(p,cs,t,0)
aux(p,cs,t,cont) 				≡
if vacia?(cs)
	then cont
	else if cantAutosQuePasaronPor(p,t,dameUno(cs)) > cont
			then aux(p,sinUno(cs),t,cantAutosQuePasaronPor(p,t,dameUno(cs)))
			else aux(p,sinUno(cs),t,cont)
		 fi
fi
//Recorro todas las cabinas en donde la cant de vehiculos que pasaron del tipo t es igual a cantMax y guardo el idCabina
obtenerCabinasConCantDeYTipo(p,cs,cantMax,t) ≡ aux1(p,cs,cantMax,t,vacio)
aux1(p,cs,cantMax,t,res)
if vacia?(cs)
	then res
	else if cantAutosQuePasaronPor(p,t,dameUno(cs)) = cantMax
			then aux1(p,sinUno(cs),cantMax,t,Ag(dameUno(cs),res))
			else aux1(p,sinUno(cs),cantMax,t,res)
		 fi
fi