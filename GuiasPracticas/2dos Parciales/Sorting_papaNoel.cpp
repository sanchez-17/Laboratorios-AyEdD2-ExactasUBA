Parcial 18/12/2021

"""La idea es que por cada zona horaria se tiene a lo sumo 1000 tuplas con cantidad de regalos mayor a 3n. Entonces por cada zona tendre 2 listas:
 Una para ordenar estos 1000 elementos con insertion: O(#elem^2) 
Pero como #elem <= 1000 =>  queda O(1)
 Otra para ordenar con counting ya que el valor de la tupla que refiere a la cant de regalos esta acotada por 3.n 
 """

 OrdenEntregas(in z:nat, in pedidos:arreglo(tupla(nat,nat)))-> res:arreglo(tupla(nat,nat))
  porZona <- arreglo[1...z] de (lista(tupla(nat,nat),lista(tupla(nat,nat))   
  n <- tam(pedidos)  
  for i<-1 ... z do
    zonaIAcotada <- vacia()
    zonaINoAcotada <- vacia()
    porZona[i] <- <zonaIAcotada,zonaINoAcotada>
  endfor

  for i<-1..n do
    k <- pi_1(pedidos[i])
    listaDeZona <- porZona[k]
    if pi_2(pedidos[i]) >3.n then
      agregarAtras(pi_2(listaDeZona),pedidos[i])
    else
      agregarAtras(pi_1(listaDeZona),pedidos[i])
    endif
  endfor

  resConAcotados <- vacia()
  //Ordenamos los no acotados
  for i<-1 ... z do
    insertionSort(pi_2(porZona[i]))
    concatenar(resConAcotados,pi_1(porZona[i]))
  endfor

  countingSort(resConAcotados)
  l <- 1
  i<- 1
  while i< z  do
    while(l<n & pi_1(resConAcotados[l]) == pi_2(resConAcotados[l+1])) do
      l++
    endwhile
    concatenarEn(resConAcotados,l,pi_2(porZona[i]))
    l <- l + tam(pi_2(porZona[i]))
    i++
  endwhile

  return resConAcotados