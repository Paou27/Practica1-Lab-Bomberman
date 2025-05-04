#pragma once
#include "Cancha.h"
#include "Jugador.h"

class CControladora {
private:
	CCancha* cancha;
	CJugador* jugador;

public:
	CControladora();
	~CControladora() {};

	void inicializar();
	void Dibujar();
	void dibujarCancha(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpIrrompible, Bitmap^ bmpRrompible);
	void dibujarJugador(Graphics^ g, Bitmap^ bmpJugador);
	void moverJugador(Graphics^ g, Bitmap^ bmpJugador);
	CJugador* getJugador();
};
