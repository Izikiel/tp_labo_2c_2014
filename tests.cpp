// g++ -g tests.cpp -o tests
// valgrind --leak-check=full -v ./tests
#include "mini_test.h"
#include "arturo.h"
template<typename T>
string to_s(const T &m)
{
    ostringstream os;
    os << m;
    return os.str();
}


void testPrimeroArturo()
{
    Arturo<int> mesa;
    ASSERT(mesa.arturoPresente() == false);
    mesa.sentarArturo(0);
    ASSERT_EQ(mesa.arturoPresente(), true);
    ASSERT_EQ(mesa.caballeroActual(), 0);
}

void testMesaVaciaYTamanio()
{
    Arturo<int> mesa;
    ASSERT_EQ(mesa.esVacia(), true);
    ASSERT_EQ(mesa.tamanio(), 0);
    mesa.sentarArturo(0);
    ASSERT_EQ(mesa.esVacia(), false);
    ASSERT_EQ(mesa.tamanio(), 1);
    mesa.incorporarCaballero(1);
    ASSERT_EQ(mesa.esVacia(), false);
    ASSERT_EQ(mesa.tamanio(), 2);
    mesa.incorporarCaballero(2);
    ASSERT_EQ(mesa.esVacia(), false);
    ASSERT_EQ(mesa.tamanio(), 3);
}


void testNuevosCaballeros()
{
    Arturo<int> mesa;
    mesa.sentarArturo(0);
    mesa.incorporarCaballero(1);
    ASSERT_EQ(mesa.caballeroActual(), 0);
    mesa.incorporarCaballero(2);
    ASSERT_EQ(mesa.caballeroActual(), 0);
    mesa.incorporarCaballero(3);
    ASSERT_EQ(mesa.caballeroActual(), 0);
}
void testMuestraBien()
{
    Arturo<int> mesa;
    ASSERT_EQ(to_s(mesa), "[]");
    mesa.sentarArturo(0);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0)]");
    mesa.incorporarCaballero(1);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 1]");
    mesa.incorporarCaballero(2);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 2, 1]");
}

void testBorraComoLaGente()
{
    Arturo<int> mesa;
    mesa.sentarArturo(0);
    mesa.incorporarCaballero(1);
    mesa.incorporarCaballero(2);
    mesa.incorporarCaballero(3);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 3, 2, 1]");
    mesa.expulsarCaballero(2);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 3, 1]");
    ASSERT_EQ(mesa.tamanio(), 3);
    mesa.proximoCaballero();
    mesa.expulsarCaballero(3);
    ASSERT_EQ(to_s(mesa), "[1, ARTURO(0)]");
    mesa.incorporarCaballero(2);
    mesa.incorporarCaballero(3);
    mesa.proximoCaballero();
    mesa.proximoCaballero();
    mesa.hablaArturo();
    mesa.expulsarCaballero(3);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 2, 1]");
    ASSERT_EQ(mesa.tamanio(), 3);
    mesa.expulsarCaballero(2);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 1]");
    ASSERT_EQ(mesa.tamanio(), 2);
    mesa.expulsarCaballero(1);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0)]");
    ASSERT_EQ(mesa.tamanio(), 1);
    mesa.expulsarCaballero(0);
    ASSERT_EQ(to_s(mesa), "[]");
    ASSERT_EQ(mesa.tamanio(), 0);
}

void testCaballeroQueHablaNoMuerde()
{
    Arturo<int> mesa;
    mesa.sentarArturo(0);
    mesa.incorporarCaballero(1);
    mesa.proximoCaballero();
    ASSERT_EQ(mesa.caballeroActual(), 1);
    ASSERT_EQ(to_s(mesa), "[1, ARTURO(0)]");
    mesa.proximoCaballero();
    mesa.hablaArturo();
    ASSERT_EQ(mesa.caballeroActual(), 0);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 1]");
    mesa.proximoCaballero();
    ASSERT_EQ(mesa.caballeroActual(), 1);
    ASSERT_EQ(to_s(mesa), "[1, ARTURO(0)]");
}

void testElCaballoAndaPaTras()
{
    Arturo<int> mesa;
    mesa.sentarArturo(0);
    mesa.incorporarCaballero(1);
    mesa.caballeroAnterior();
    ASSERT_EQ(mesa.caballeroActual(), 1);
    ASSERT_EQ(to_s(mesa), "[1, ARTURO(0)]");
    mesa.hablaArturo();
    ASSERT_EQ(mesa.caballeroActual(), 0);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), *1]");
    mesa.caballeroAnterior();
    ASSERT_EQ(mesa.caballeroActual(), 0);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 1]");
}

void testArturitoEsta()
{
    Arturo<int> mesa;
    ASSERT_EQ(mesa.arturoPresente(), false);
    mesa.sentarArturo(0);
    ASSERT_EQ(mesa.arturoPresente(), true);
    mesa.incorporarCaballero(1);
    ASSERT_EQ(mesa.arturoPresente(), true);
    mesa.expulsarCaballero(1);
    ASSERT_EQ(mesa.arturoPresente(), true);
    mesa.expulsarCaballero(0);
    ASSERT_EQ(mesa.arturoPresente(), false);
}


void testCambiaQueCambia()
{
    Arturo<int> mesa;
    mesa.sentarArturo(0);
    mesa.incorporarCaballero(1);
    mesa.incorporarCaballero(2);
    mesa.cambioDeLugar(2);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 1, 2]");
    mesa.proximoCaballero();
    ASSERT_EQ(to_s(mesa), "[1, 2, ARTURO(0)]");
    mesa.cambioDeLugar(2);
    ASSERT_EQ(to_s(mesa), "[1, 2, ARTURO(0)]");
    mesa.cambioDeLugar(1);
    ASSERT_EQ(to_s(mesa), "[1, ARTURO(0), 2]");
    mesa.hablaArturo();
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 2, *1]");
    mesa.cambioDeLugar(2);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), *1, 2]");
    mesa.incorporarCaballero(3);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), 3, *1, 2]");
    mesa.cambioDeLugar(3);
    ASSERT_EQ(to_s(mesa), "[ARTURO(0), *1, 2, 3]");
}

void testIgualdadesMagicas()
{
    Arturo<int> mesa1;
    Arturo<int> mesa2;
    ASSERT_EQ(mesa1 == mesa2, true);
    mesa1.sentarArturo(0);
    mesa2.sentarArturo(0);
    ASSERT_EQ(mesa1 == mesa2, true);
    mesa1.incorporarCaballero(1);
    ASSERT_EQ(mesa1 == mesa2, false);
    mesa2.incorporarCaballero(1);
    ASSERT_EQ(mesa1 == mesa2, true);
    mesa1.incorporarCaballero(2);
    ASSERT_EQ(mesa1 == mesa2, false);
    mesa2.incorporarCaballero(2);
    ASSERT_EQ(mesa1 == mesa2, true);
    mesa1.proximoCaballero();
    ASSERT_EQ(mesa1 == mesa2, false);
    mesa2.proximoCaballero();
    ASSERT_EQ(mesa1 == mesa2, true);
    mesa1.hablaArturo();
    ASSERT_EQ(mesa1 == mesa2, false);
    mesa2.hablaArturo();
    ASSERT_EQ(mesa1 == mesa2, true);
}




int main()
{
    RUN_TEST(testPrimeroArturo);
    RUN_TEST(testMesaVaciaYTamanio);

    RUN_TEST(testNuevosCaballeros);
    RUN_TEST(testMuestraBien);
    RUN_TEST(testBorraComoLaGente);
    RUN_TEST(testCaballeroQueHablaNoMuerde)
    RUN_TEST(testElCaballoAndaPaTras);
    RUN_TEST(testArturitoEsta);
    RUN_TEST(testCambiaQueCambia)
    RUN_TEST(testIgualdadesMagicas);
    return 0;
}
