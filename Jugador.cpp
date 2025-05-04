#include <iostream>
#include "Jugador.h"

CJugador::CJugador() {};

CJugador::~CJugador() {};

CJugador::CJugador(int x, int y) {
  this->x = x;
  this->y = y;
  dx = 0;
  dy = 0;
  ultimaTecla = EDireccion::Abajo;
  direccion = EDireccion::Ninguna;
  indiceX = 10;
  indiceY = 0;
  for (int i = 0; i < HABILIDADES; i++) {
    habilidades[i] = false;
  }
  colisionandoConPared = false;
}

void CJugador::setDireccion(EDireccion direccion) {
  this->direccion = direccion;
}

void CJugador::controlarLimitesMovimiento(const CanchaArray& cancha) {
  int X = 0, Y = 0;
  colisionandoConPared = false;
  for (int i = 0; i < FILAS; i++) {
    X = 0;
    for (int j = 0; j < COLUMNAS; j++) {
      //std::cout << "cancha[i][j] = " << cancha[i][j] << std::endl;
      Rectangle intersecta = Rectangle(X, Y, ANCHOIMAGEN, ALTOIMAGEN);
      if ((cancha[i][j]->getTipo() == EElementos::paredes) || (cancha[i][j]->getTipo() == EElementos::rrompible)) {
          if (limiteArribaAbajo.IntersectsWith(intersecta)) {
              dy = 0;
              colisionandoConPared = true;
          }
          if (limiteDerechaIzquierda.IntersectsWith(intersecta)) {
              dx = 0;
              colisionandoConPared = true;
          }

      }
      X += ANCHOIMAGEN;
    }
    Y += ALTOIMAGEN;
  }
}

void CJugador::dibujar(Graphics^ g, Bitmap^ bmpJugador, const CanchaArray& cancha) {
    // Ajustamos los límites de colisión con valores enteros para evitar errores de redondeo
    int anchoColision = static_cast<int>((ANCHOJUGADOR - 10) * FACTORZOOM);
    int altoColision = static_cast<int>((ALTOJUGADOR - 20) * FACTORZOOM);

    limiteDerechaIzquierda = Rectangle(x + dx + 1, y + 8, anchoColision, altoColision);
    limiteArribaAbajo = Rectangle(x + 1, y + dy + 8, anchoColision, altoColision);

    // Dibujar colisiones para depurar si quieres
    // g->DrawRectangle(Pens::Red, limiteDerechaIzquierda);
    // g->DrawRectangle(Pens::Blue, limiteArribaAbajo);

    // Validar colisiones ANTES de mover
    controlarLimitesMovimiento(cancha);


// Quita el + ESPACIO_HORIZONTAL si no hay separación real entre personajes
Rectangle rectangulo = Rectangle(indiceX * ANCHOJUGADOR, indiceY * ALTOJUGADOR, ANCHOJUGADOR, ALTOJUGADOR);

  Rectangle zoom = Rectangle(x, y, ANCHOJUGADOR * FACTORZOOM, ALTOJUGADOR * FACTORZOOM);
   g->DrawImage(bmpJugador, zoom, rectangulo, GraphicsUnit::Pixel);
  
   if (colisionandoConPared) {
       Pen^ lapiz = gcnew Pen(Color::OrangeRed, 3); // borde más grueso y visible

       int ancho = static_cast<int>(ANCHOJUGADOR * FACTORZOOM);
       int alto = static_cast<int>(ALTOJUGADOR * FACTORZOOM);
       int margen = 20; // tamaño extra para hacerlo más visible
       Rectangle colisionVisual;

       switch (direccion) {
       case EDireccion::Arriba:
           colisionVisual = Rectangle(x, y - margen, ancho, margen);
           break;
       case EDireccion::Abajo:
           colisionVisual = Rectangle(x, y + alto, ancho, margen);
           break;
       case EDireccion::Izquierda:
           colisionVisual = Rectangle(x - margen, y, margen, alto);
           break;
       case EDireccion::Derecha:
           colisionVisual = Rectangle(x + ancho, y, margen, alto);
           break;
       default:
           break;
       }

       g->DrawRectangle(lapiz, colisionVisual);
       delete lapiz;
   }


	 x += dx;
	 y += dy;
}

void CJugador::mover(Graphics^ g, Bitmap^ bmpJugador, const CanchaArray& cancha) {
  switch (direccion) {
    case EDireccion::Arriba:
      indiceY = 0;
      if ((indiceX >= 0) && (indiceX < 2)) {
        indiceX++;
      } else {
        indiceX = 0;
      }
      dx = 0;
      dy = -10;
      ultimaTecla = EDireccion::Arriba;
      break;
    case EDireccion::Abajo:
      indiceY = 2;
      if ((indiceX >= 0) && (indiceX < 2)) {
        indiceX++;
      } else {
        indiceX = 0;
      }
      dx = 0;
      dy = 10;
      ultimaTecla = EDireccion::Abajo;
      break;
    case EDireccion::Izquierda:
      indiceY = 3;
      if ((indiceX >= 0) && (indiceX < 2)) {
        indiceX++;
      } else {
        indiceX = 0;
      }
      dx = -10;
      dy = 0;
      ultimaTecla = EDireccion::Izquierda;
      break;
    case EDireccion::Derecha:
      indiceY = 1;
      if ((indiceX >= 0) && (indiceX < 2)) {
        indiceX++;
      } else {
        indiceX = 0;
      }
      dx = 10;
      dy = 0;
      ultimaTecla = EDireccion::Derecha;
      break;
    case EDireccion::Ninguna:
      dx = 0;
      dy = 0;
      switch (ultimaTecla) {
        case EDireccion::Abajo:
          indiceX = 0;
          indiceY = 2;
          break;
        case EDireccion::Arriba:
          indiceX = 0;
          indiceY = 0;
          break;
        case EDireccion::Izquierda:
          indiceX = 1;
          indiceY = 3;
          break;        
        case EDireccion::Derecha:
          indiceX = 1;
          indiceY = 1;
          break;
      }
      break;      
  }

  dibujar(g, bmpJugador, cancha);
}
