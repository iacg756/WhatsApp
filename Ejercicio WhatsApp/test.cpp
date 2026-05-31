#include "pch.h"
#include "Whatsapp.h"
#include <string>

#include "SingletonDeUsuarios.h"

/*
#include "Mensaje.h"
#include "Archivo.h"
#include "Texto.h"
#include "Chat.h"
#include "Whatsapp.h"
*/

using namespace std;

static int NOTA_TOTAL = 0;

TEST(TestSingletonDeUsuarios, RegistrarUsuarios) {
    string usuariosEsperados = R"([{"telefono":70700001,"nombre":"Paola","chats":[]},{"telefono":70700002,"nombre":"Leonardo","chats":[]},{"telefono":70700003,"nombre":"Elena","chats":[]}])";

    // El singleton debe tener como maximo 4 usuarios
    // registrarUsuario(new Usuario(telefono, nombre, cantidadDeChats))
    SingletonDeUsuarios::getInstancia().registrarUsuario(new Usuario(70700001, "Paola", 5));
    SingletonDeUsuarios::getInstancia().registrarUsuario(new Usuario(70700002, "Leonardo", 5));
    SingletonDeUsuarios::getInstancia().registrarUsuario(new Usuario(70700003, "Elena", 5));
    ASSERT_THROW(
        SingletonDeUsuarios::getInstancia().registrarUsuario(new Usuario(70700003, "Laura", 5)),
        exception
    );

    ASSERT_EQ(SingletonDeUsuarios::getInstancia().toJson(), usuariosEsperados);
    NOTA_TOTAL += 30;
}

TEST(TestSingletonDeUsuarios, RegistrarChat) {
    string usuariosEsperados = R"([{"telefono":70700001,"nombre":"Paola","chats":[{"numero":70700002,"mensajesEnviados":[],"mensajesRecibidos":[]},{"numero":70700003,"mensajesEnviados":[],"mensajesRecibidos":[]}]},{"telefono":70700002,"nombre":"Leonardo","chats":[{"numero":70700001,"mensajesEnviados":[],"mensajesRecibidos":[]}]},{"telefono":70700003,"nombre":"Elena","chats":[{"numero":70700001,"mensajesEnviados":[],"mensajesRecibidos":[]}]}])";

    int telefonoPaola = 70700001;
    int telefonoLeonardo = 70700002;
    int telefonoElena = 70700003;
    // registrarChat(telefono, new Chat(telefonoDestino, cantidadDeMensajes))
    // Registrar Chat entre Paola y Leonardo
    SingletonDeUsuarios::getInstancia().registrarChat(telefonoPaola, new Chat(telefonoLeonardo, 2));
    // Registrar Chat entre Paola y Elena
    SingletonDeUsuarios::getInstancia().registrarChat(telefonoPaola, new Chat(telefonoElena, 2));
    // Registrar Chat entre Leonardo y Paola 
    SingletonDeUsuarios::getInstancia().registrarChat(telefonoLeonardo, new Chat(telefonoPaola, 2));
    // Registrar Chat entre Elena y Paola
    SingletonDeUsuarios::getInstancia().registrarChat(telefonoElena, new Chat(telefonoPaola, 2));

    ASSERT_EQ(SingletonDeUsuarios::getInstancia().toJson(), usuariosEsperados);

    NOTA_TOTAL += 10;
}

TEST(TestSingletonDeUsuarios, EnviarRecibirMensaje) {
    string usuariosEsperados = R"([{"telefono":70700001,"nombre":"Paola","chats":[{"numero":70700002,"mensajesEnviados":[{"fecha":20241201,"tipo":"texto","contenido":"Mandame la foto"}],"mensajesRecibidos":[{"fecha":20241201,"tipo":"archivo","nombre":"Familia","extension":"jpg"}]},{"numero":70700003,"mensajesEnviados":[{"fecha":20241202,"tipo":"texto","contenido":"Como estas?"}],"mensajesRecibidos":[]}]},{"telefono":70700002,"nombre":"Leonardo","chats":[{"numero":70700001,"mensajesEnviados":[{"fecha":20241201,"tipo":"archivo","nombre":"Familia","extension":"jpg"}],"mensajesRecibidos":[{"fecha":20241201,"tipo":"texto","contenido":"Mandame la foto"}]}]},{"telefono":70700003,"nombre":"Elena","chats":[{"numero":70700001,"mensajesEnviados":[],"mensajesRecibidos":[{"fecha":20241202,"tipo":"texto","contenido":"Como estas?"}]}]}])";

    // Paola envia mensaje a Leonardo
    int telefonoPaola = 70700001;
    int telefonoLeonardo = 70700002;
    int telefonoElena = 70700003;

    // Texto(fecha, contenido)
    Mensaje* mensajeTexto1 = new Texto(20241201, "Mandame la foto");
    // enviarMensaje(telefonoOrigen, telefonoDestino, Mensaje*)
    SingletonDeUsuarios::getInstancia().enviarMensaje(telefonoPaola, telefonoLeonardo, mensajeTexto1);
    // recibirMensaje(telefonoDestino, telefonoOrigen, Mensaje*)
    SingletonDeUsuarios::getInstancia().recibirMensaje(telefonoLeonardo, telefonoPaola, mensajeTexto1);

    // Archivo(fecha, nombre, extension)
    Mensaje* mensajeArchivo1 = new Archivo(20241201, "Familia", "jpg");
    // enviarMensaje(telefonoOrigen, telefonoDestino, Mensaje*)
    SingletonDeUsuarios::getInstancia().enviarMensaje(telefonoLeonardo, telefonoPaola, mensajeArchivo1);
    // recibirMensaje(telefonoDestino, telefonoOrigen, Mensaje*)
    SingletonDeUsuarios::getInstancia().recibirMensaje(telefonoPaola, telefonoLeonardo, mensajeArchivo1);

    // Texto(fecha, contenido)
    Mensaje* mensajeTexto2 = new Texto(20241202, "Como estas?");
    // enviarMensaje(telefonoOrigen, telefonoDestino, Mensaje*)
    SingletonDeUsuarios::getInstancia().enviarMensaje(telefonoPaola, telefonoElena, mensajeTexto2);
    // recibirMensaje(telefonoDestino, telefonoOrigen, Mensaje*)
    SingletonDeUsuarios::getInstancia().recibirMensaje(telefonoElena, telefonoPaola, mensajeTexto2);

    // Texto(fecha, contenido)
    Mensaje* mensajeTexto3 = new Texto(20241202, "Hola, como estas?");
    // enviarMensaje(telefonoOrigen, telefonoDestino, Mensaje*)
    // genera un exception porque no hay chat registrado entre Leonardo y Elena
    ASSERT_THROW(
        SingletonDeUsuarios::getInstancia().enviarMensaje(telefonoLeonardo, telefonoElena, mensajeTexto3),
        exception
    );

    ASSERT_EQ(SingletonDeUsuarios::getInstancia().toJson(), usuariosEsperados);

    NOTA_TOTAL += 30;
}


TEST(TestWhatsapp, EnviarMensaje) {
    string whatsappEsperado = R"({"usuarios":[{"telefono":70700001,"nombre":"Paola","chats":[{"numero":70700002,"mensajesEnviados":[{"fecha":20241201,"tipo":"texto","contenido":"Mandame la foto"}],"mensajesRecibidos":[{"fecha":20241201,"tipo":"archivo","nombre":"Familia","extension":"jpg"}]},{"numero":70700003,"mensajesEnviados":[{"fecha":20241202,"tipo":"texto","contenido":"Como estas?"}],"mensajesRecibidos":[{"fecha":20241203,"tipo":"texto","contenido":"Estoy bien y tu?"}]}]},{"telefono":70700002,"nombre":"Leonardo","chats":[{"numero":70700001,"mensajesEnviados":[{"fecha":20241201,"tipo":"archivo","nombre":"Familia","extension":"jpg"}],"mensajesRecibidos":[{"fecha":20241201,"tipo":"texto","contenido":"Mandame la foto"}]}]},{"telefono":70700003,"nombre":"Elena","chats":[{"numero":70700001,"mensajesEnviados":[{"fecha":20241203,"tipo":"texto","contenido":"Estoy bien y tu?"}],"mensajesRecibidos":[{"fecha":20241202,"tipo":"texto","contenido":"Como estas?"}]}]}],"grupos":[]})";
    Whatsapp whatsapp(2);
    int telefonoPaola = 70700001;
    int telefonoElena = 70700003;
    int telefonoLaura = 70700004;
    // Nota: enviarYRecibirMensaje debe llamar al enviarMensaje y recibirMensaje de SingletonDeUsuarios
    // Elena envia mensaje a Paola y Paola recibe mensaje de Elena.
    whatsapp.enviarYRecibirMensaje(telefonoElena, telefonoPaola, new Texto(20241203, "Estoy bien y tu?"));
    // Laura envia mensaje a Paola y Paola recibe mensaje de Laura
    whatsapp.enviarYRecibirMensaje(telefonoLaura, telefonoPaola, new Texto(20241203, "Hola!!!"));

    ASSERT_EQ(whatsapp.toJson(), whatsappEsperado);

    NOTA_TOTAL += 10;
}



TEST(TestWhatsapp, RegistrarGrupoYAgregarParticipante) {
    string whatsappEsperado = R"({"usuarios":[{"telefono":70700001,"nombre":"Paola","chats":[{"numero":70700002,"mensajesEnviados":[{"fecha":20241201,"tipo":"texto","contenido":"Mandame la foto"}],"mensajesRecibidos":[{"fecha":20241201,"tipo":"archivo","nombre":"Familia","extension":"jpg"}]},{"numero":70700003,"mensajesEnviados":[{"fecha":20241202,"tipo":"texto","contenido":"Como estas?"}],"mensajesRecibidos":[{"fecha":20241203,"tipo":"texto","contenido":"Estoy bien y tu?"}]}]},{"telefono":70700002,"nombre":"Leonardo","chats":[{"numero":70700001,"mensajesEnviados":[{"fecha":20241201,"tipo":"archivo","nombre":"Familia","extension":"jpg"}],"mensajesRecibidos":[{"fecha":20241201,"tipo":"texto","contenido":"Mandame la foto"}]}]},{"telefono":70700003,"nombre":"Elena","chats":[{"numero":70700001,"mensajesEnviados":[{"fecha":20241203,"tipo":"texto","contenido":"Estoy bien y tu?"}],"mensajesRecibidos":[{"fecha":20241202,"tipo":"texto","contenido":"Como estas?"}]}]}],"grupos":[{"nombre":"Programacion 2","descripcion":"Paralelo 3 del semestre 2-2024","participantes":[{"telefono":70700001,"nombre":"Paola"},{"telefono":70700002,"nombre":"Leonardo"}]}]})";
    Whatsapp whatsapp(2);

    int telefonoPaola = 70700001;
    int telefonoLeonardo = 70700002;
    whatsapp.registrarGrupo(1, "Programacion 2", "Paralelo 3 del semestre 2-2024", 10);

    whatsapp.agregarParticipante(1, telefonoPaola);
    whatsapp.agregarParticipante(1, telefonoLeonardo);

    ASSERT_EQ(whatsapp.toJson(), whatsappEsperado);

    NOTA_TOTAL += 20;
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int resultado = RUN_ALL_TESTS();
    printf("NOTA TOTAL OBTENIDA: %d/100\n", NOTA_TOTAL);
    return resultado;
}
