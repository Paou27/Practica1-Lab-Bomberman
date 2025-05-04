#include <iostream>

#define FILAS 7  //9
#define COLUMNAS 9 //7
#define ANCHOIMAGEN 120
#define ALTOIMAGEN 120
#define HABILIDADES 7

enum EElementos {
  piso = 0,
  paredes,
  rrompible,
  libre,
  obstaculos,
  poder,
  jugador,
  explosion,
  bomba,
  enemigos
};

enum EHabilidades {
  fuego = 0,
  bombas,
  golpe,
  resistencia,
  muerte,
  velocidad,
  alto
};

class CBloque {
	int x;
	int y;
	EElementos tipo;
  std::string apariencia;
  int resistencia;
  bool habilidades[HABILIDADES];
public:
  CBloque();
  CBloque(int x, int y, EElementos tipo, std::string apariencia, int resistencia);

  void setX(int x);
  int getX();
  void setY(int y);
  int getY();
  void setTipo(EElementos tipo);
  EElementos getTipo();
  void setApariencia(std::string apariencia);  
  std::string getApariencia();
  void setResistencia(int resistencia);
  int getResistencia();  
  void adicionarHabilidad(EHabilidades habilidad);
  void quitarHabilidad(EHabilidades habilidad);
  bool getHabilidad(EHabilidades habilidad);
};
