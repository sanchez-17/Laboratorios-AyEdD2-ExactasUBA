#include "gtest-1.8.1/gtest.h"
#include "Taxonomia.h"

TEST(test_taxonomia_iterator, taxonomia_iterator_begin) {
	Taxonomia<int> tax("11 { 22 33 }");
	Taxonomia<int>::iterator it = tax.begin();
	ASSERT_EQ(*it, 11);
}

TEST(test_taxonomia_iterator, taxonomia_iterator_cantSubcategorias) {
	Taxonomia<int> tax("1 { 2 3 4 }");
	Taxonomia<int>::iterator it = tax.begin();
	ASSERT_EQ(it.cantSubcategorias(), 3);
}

TEST(test_taxonomia_iterator, taxonomia_iterator_subcategoria) {
	Taxonomia<int> tax("1 { 2 { 3 4 5 6 } 7 { 8 9 } }");
	Taxonomia<int>::iterator it = tax.begin();
	ASSERT_EQ(*it, 1);
	it.subcategoria(0);
	ASSERT_EQ(*it, 2);
	it.subcategoria(3);
	ASSERT_EQ(*it, 6);
}

TEST(test_taxonomia_iterator, taxonomia_iterator_esRaiz) {
	Taxonomia<int> tax("1 { 2 { 3 4 5 6 } 7 { 8 9 } }");
	Taxonomia<int>::iterator it = tax.begin();
	ASSERT_EQ(*it, 1);
	ASSERT_TRUE(it.esRaiz());
	it.subcategoria(1);
	ASSERT_EQ(*it, 7);
	ASSERT_FALSE(it.esRaiz());
	it.subcategoria(1);
	ASSERT_EQ(*it, 9);
	ASSERT_FALSE(it.esRaiz());
}

TEST(test_taxonomia_iterator, taxonomia_iterator_supercategoria) {
	Taxonomia<string> tax("a { b { c { d } e } f { g } h }");
	Taxonomia<string>::iterator it = tax.begin();
	ASSERT_EQ(*it, "a");
	it.subcategoria(0);
	ASSERT_EQ(*it, "b");
	it.subcategoria(0);
	ASSERT_EQ(*it, "c");
	it.subcategoria(0);
	ASSERT_EQ(*it, "d");
	it.supercategoria();
	ASSERT_EQ(*it, "c");
	it.supercategoria();
	ASSERT_EQ(*it, "b");
	it.subcategoria(1);
	ASSERT_EQ(*it, "e");
	it.supercategoria();
	ASSERT_EQ(*it, "b");
	it.supercategoria();
	ASSERT_EQ(*it, "a");
	it.subcategoria(1);
	ASSERT_EQ(*it, "f");
	it.subcategoria(0);
	ASSERT_EQ(*it, "g");
	it.supercategoria();
	ASSERT_EQ(*it, "f");
	it.supercategoria();
	ASSERT_EQ(*it, "a");
	it.subcategoria(2);
	ASSERT_EQ(*it, "h");
}

TEST(test_taxonomia_iterator, taxonomia_iterator_dos_iteradores) {
	Taxonomia<string> tax("a { b c }");
	Taxonomia<string>::iterator it1 = tax.begin();
	Taxonomia<string>::iterator it2 = tax.begin();
	ASSERT_EQ(*it1, "a");
	ASSERT_EQ(*it2, "a");
	it1.subcategoria(0);
	ASSERT_EQ(*it1, "b");
	ASSERT_EQ(*it2, "a");
	it2.subcategoria(1);
	ASSERT_EQ(*it1, "b");
	ASSERT_EQ(*it2, "c");
	it1.supercategoria();
	ASSERT_EQ(*it1, "a");
	ASSERT_EQ(*it2, "c");
}


Taxonomia<int> taxonomia_numeros(
	"0 {"
	"  1 {"
	"    10"
	"    11"
	"  }"
	"  2 {"
	"    20"
	"    21"
	"    22 { 220 }"
	"  }"
	"  3 {"
	"    30 { 300 301 }"
	"    31"
	"    32"
	"    33"
	"  }"
	"  4 {"
	"    40"
	"    41"
	"    42 { 420 421 422 }"
	"    43"
	"  }"
	"}"
);

std::vector<int> lista_numeros {
	0, 1, 10, 11, 2, 20, 21, 22, 220,
	3, 30, 300, 301, 31, 32, 33,
	4, 40, 41, 42, 420, 421, 422, 43,
};

TEST(test_taxonomia_iterator, taxonomia_iterator_avanzar) {
	Taxonomia<int>::iterator it = taxonomia_numeros.begin();
	ASSERT_EQ(*it, 0);
	for (int i = 1; i < lista_numeros.size(); i++) {
		++it;
		ASSERT_EQ(*it, lista_numeros[i]);
	}
	ASSERT_EQ(*it, 43);
}

Taxonomia<string> taxonomia_eucariotas(
	"eucariotas {\n"
	"  animales {\n"
	"    vertebrados {\n"
	"      mamiferos {\n"
	"        ballenas\n"
	"        jirafas\n"
	"        murcielagos\n"
	"        zorros\n"
	"      }\n"
	"      peces {\n"
	"        esturiones\n"
	"        truchas\n"
	"      }\n"
	"      reptiles {\n"
	"        serpientes\n"
	"      }\n"
	"    }\n"
	"    invertebrados {\n"
	"      insectos {\n"
	"        abejas\n"
	"        hormigas\n"
	"        moscas\n"
	"      }\n"
	"      moluscos {\n"
	"        caracoles\n"
	"      }\n"
	"    }\n"
	"  }\n"
	"  plantas {\n"
	"    angiospermas {\n"
	"      manzanos\n"
	"    }\n"
	"    gimnospermas {\n"
	"      araucarias\n"
	"      cedros\n"
	"    }\n"
	"  }\n"
	"}\n"
);

std::vector<string> lista_eucariotas {
	"eucariotas", "animales", "vertebrados", "mamiferos",
	"ballenas", "jirafas", "murcielagos", "zorros",
	"peces", "esturiones", "truchas", "reptiles",
	"serpientes", "invertebrados", "insectos", "abejas",
	"hormigas", "moscas", "moluscos", "caracoles",
	"plantas", "angiospermas", "manzanos",
	"gimnospermas", "araucarias", "cedros",
};

TEST(test_taxonomia_iterator, taxonomia_iterator_avanzar_al_final) {
	Taxonomia<string>::iterator it = taxonomia_eucariotas.begin();
	ASSERT_EQ(*it, "eucariotas");
	for (int i = 1; i < lista_eucariotas.size(); i++) {
		++it;
		ASSERT_EQ(*it, lista_eucariotas[i]);
	}
	ASSERT_EQ(*it, "cedros");
	++it;
	ASSERT_EQ(it, taxonomia_eucariotas.end());
}

TEST(test_taxonomia_iterator, taxonomia_iterator_retroceder) {
	Taxonomia<int>::iterator it1 = taxonomia_numeros.begin();
	ASSERT_EQ(*it1, 0);
	for (int i = 1; i < lista_numeros.size(); i++) {
		++it1;
		ASSERT_EQ(*it1, lista_numeros[i]);
	}
	for (int i = lista_numeros.size() - 1; i > 0; i--) {
		ASSERT_EQ(*it1, lista_numeros[i]);
		--it1;
	}
	ASSERT_EQ(*it1, 0);

	Taxonomia<string>::iterator it2 = taxonomia_eucariotas.begin();
	ASSERT_EQ(*it2, "eucariotas");
	for (int i = 1; i < lista_eucariotas.size(); i++) {
		++it2;
		ASSERT_EQ(*it2, lista_eucariotas[i]);
	}
	for (int i = lista_eucariotas.size() - 1; i > 0; i--) {
		ASSERT_EQ(*it2, lista_eucariotas[i]);
		--it2;
	}
	ASSERT_EQ(*it2, "eucariotas");
}

TEST(test_taxonomia_iterator, taxonomia_iterator_insertarSubcategoria) {
	Taxonomia<string> t("a");
	Taxonomia<string>::iterator it = t.begin();
	ASSERT_EQ(*it, "a");
	it.insertarSubcategoria(0, "d");
	it.insertarSubcategoria(0, "b");
	it.insertarSubcategoria(1, "c");
	it.insertarSubcategoria(3, "f");
	it.insertarSubcategoria(3, "e");
	ASSERT_EQ(*it, "a");

	it.subcategoria(0);
	ASSERT_EQ(*it, "b");
	it.insertarSubcategoria(0, "ba");
	it.insertarSubcategoria(1, "bb");
	it.insertarSubcategoria(2, "bc");
	it.subcategoria(0);
	ASSERT_EQ(*it, "ba");
	it.supercategoria();
	it.subcategoria(1);
	ASSERT_EQ(*it, "bb");
	it.supercategoria();
	it.subcategoria(2);
	ASSERT_EQ(*it, "bc");
	it.supercategoria();
	it.supercategoria();

	it.subcategoria(1);
	ASSERT_EQ(*it, "c");
	it.supercategoria();

	it.subcategoria(2);
	ASSERT_EQ(*it, "d");
	it.supercategoria();

	it.subcategoria(3);
	ASSERT_EQ(*it, "e");
	it.supercategoria();

	it.subcategoria(4);
	ASSERT_EQ(*it, "f");
	it.supercategoria();
}

TEST(test_taxonomia_iterator, taxonomia_iterator_eliminarCategoria) {
	Taxonomia<string> t("a { b { ba bb bc } c d e f }");
	Taxonomia<string>::iterator it = t.begin();
	ASSERT_EQ(it.cantSubcategorias(), 5);
	it.subcategoria(1);
	ASSERT_EQ(*it, "c");
	it.eliminarCategoria();
	ASSERT_EQ(*it, "a");
	ASSERT_EQ(it.cantSubcategorias(), 4);
	it.subcategoria(1);
	ASSERT_EQ(*it, "d");
	it.eliminarCategoria();
	ASSERT_EQ(*it, "a");
	ASSERT_EQ(it.cantSubcategorias(), 3);
	it.subcategoria(0);
	ASSERT_EQ(*it, "b");
	it.eliminarCategoria();
	ASSERT_EQ(*it, "a");
	ASSERT_EQ(it.cantSubcategorias(), 2);
	it.subcategoria(1);
	ASSERT_EQ(*it, "f");
	it.eliminarCategoria();
	ASSERT_EQ(*it, "a");
	ASSERT_EQ(it.cantSubcategorias(), 1);
	it.subcategoria(0);
	ASSERT_EQ(*it, "e");
	it.eliminarCategoria();
	ASSERT_EQ(*it, "a");
	ASSERT_EQ(it.cantSubcategorias(), 0);
}

