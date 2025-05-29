// game.cpp
#include "game.h"
#include "Board.h"
#include <iostream>
#include <cctype>
#include <cmath>

// Comprueba si la posicion proporcionada por el usuario esta dentro del tablero (1..8)
static bool isValidUserPos(const Position& p) {
    return p.x >= 1 && p.x <= BOARD_SIZE
        && p.y >= 1 && p.y <= BOARD_SIZE;
}

// Convierte coordenadas de usuario (1-based, origen abajo-izq) a indices de matriz (fila, col)
static Position toIndex(const Position& p) {
    // Columna interna: p.x - 1
    // Fila interna:  BOARD_SIZE - p.y  (0=arriba, BOARD_SIZE-1=abajo)
    return { p.x - 1, BOARD_SIZE - p.y };
}

// Devuelve true si pc es una pieza del jugador actual
static bool isFriendly(char pc, bool whiteTurn) {
    if (pc == CHAR_BG_BOARD) return false;
    if (whiteTurn) {
        // Blancas = mayusculas
        return std::isupper(pc);
    }
    else {
        // Negras = minusculas
        return std::islower(pc);
    }
}

// Devuelve true si pc es una pieza del oponente
static bool isOpponent(char pc, bool whiteTurn) {
    if (pc == CHAR_BG_BOARD) return false;
    if (whiteTurn) {
        // Blancas juegan, oponente = minusculas
        return std::islower(pc);
    }
    else {
        // Negras juegan, oponente = mayusculas
        return std::isupper(pc);
    }
}

// Verifica que el camino entre origen y destino este libre (sin incluir destino)
static bool pathClear(const char b[BOARD_SIZE][BOARD_SIZE],
    int dr, int dc, int sr, int sc) {
    // dr = delta filas, dc = delta columnas
    int stepR = (dr == 0 ? 0 : (dr > 0 ? 1 : -1));
    int stepC = (dc == 0 ? 0 : (dc > 0 ? 1 : -1));
    int r = sr + stepR;
    int c = sc + stepC;
    // Avanzar casilla a casilla
    while (r != sr + dr || c != sc + dc) {
        if (b[r][c] != CHAR_BG_BOARD) {
            // Hay una pieza bloqueando
            return false;
        }
        r += stepR;
        c += stepC;
    }
    return true;
}

// Reglas de movimiento para peones
static bool canMovePawn(const char b[BOARD_SIZE][BOARD_SIZE],
    const Position& f, const Position& t,
    bool whiteTurn) {
    int sr = f.y;        // fila origen
    int sc = f.x;        // col origen
    int tr = t.y;        // fila destino
    int tc = t.x;        // col destino
    int dir = whiteTurn ? -1 : +1;          // direccion de movimiento
    int startRow = whiteTurn ? BOARD_SIZE - 2 : 1; // fila inicial

    // Movimiento de avance sencillo
    if (tc == sc && tr == sr + dir
        && b[tr][tc] == CHAR_BG_BOARD) {
        return true;
    }
    // Doble avance desde fila inicial
    if (tc == sc && sr == startRow
        && tr == sr + 2 * dir
        && b[sr + dir][sc] == CHAR_BG_BOARD
        && b[tr][tc] == CHAR_BG_BOARD) {
        return true;
    }
    // Captura diagonal
    if (std::abs(tc - sc) == 1 && tr == sr + dir
        && isOpponent(b[tr][tc], whiteTurn)) {
        return true;
    }
    // Ninguna condicion cumplida => movimiento no valido
    return false;
}

// Reglas de movimiento para caballos
static bool canMoveKnight(const char b[BOARD_SIZE][BOARD_SIZE],
    const Position& f, const Position& t,
    bool whiteTurn) {
    int dr = std::abs(t.y - f.y);
    int dc = std::abs(t.x - f.x);
    // L en cualquier orientacion: 2+1
    if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2))) {
        return false;
    }
    // Destino no puede contener pieza amiga
    return !isFriendly(b[t.y][t.x], whiteTurn);
}

// Reglas de movimiento para torres
static bool canMoveRook(const char b[BOARD_SIZE][BOARD_SIZE],
    const Position& f, const Position& t,
    bool whiteTurn) {
    int dr = t.y - f.y;
    int dc = t.x - f.x;
    // Debe moverse en linea recta (solo filas o solo columnas)
    if (!((dr == 0) ^ (dc == 0))) {
        return false;
    }
    // Verificar que no haya piezas bloqueando en el camino
    if (!pathClear(b, dr, dc, f.y, f.x)) {
        return false;
    }
    // Destino no debe ser pieza amiga
    return !isFriendly(b[t.y][t.x], whiteTurn);
}

// Reglas de movimiento para alfiles
static bool canMoveBishop(const char b[BOARD_SIZE][BOARD_SIZE],
    const Position& f, const Position& t,
    bool whiteTurn) {
    int dr = t.y - f.y;
    int dc = t.x - f.x;
    // Debe moverse en diagonal perfecta
    if (std::abs(dr) != std::abs(dc)) {
        return false;
    }
    // Verificar bloqueo en el camino
    if (!pathClear(b, dr, dc, f.y, f.x)) {
        return false;
    }
    // Destino no debe ser pieza amiga
    return !isFriendly(b[t.y][t.x], whiteTurn);
}

// Reglas de movimiento para reina (combinacion de torre y alfil)
static bool canMoveQueen(const char b[BOARD_SIZE][BOARD_SIZE],
    const Position& f, const Position& t,
    bool whiteTurn) {
    // Se permite si torre o alfil permiten ese movimiento
    if (canMoveRook(b, f, t, whiteTurn)) return true;
    if (canMoveBishop(b, f, t, whiteTurn)) return true;
    return false;
}

// Reglas de movimiento para rey (una casilla en cualquier direccion)
static bool canMoveKing(const char b[BOARD_SIZE][BOARD_SIZE],
    const Position& f, const Position& t,
    bool whiteTurn) {
    int dr = std::abs(t.y - f.y);
    int dc = std::abs(t.x - f.x);
    // Maximo 1 en filas y 1 en columnas
    if (dr > 1 || dc > 1) {
        return false;
    }
    // Destino no debe contener pieza amiga
    return !isFriendly(b[t.y][t.x], whiteTurn);
}

// Funcion general de validacion que selecciona segun la pieza
static bool validateMove(const char b[BOARD_SIZE][BOARD_SIZE],
    const Position& from, const Position& to,
    bool whiteTurn) {
    // Convertir coords usuario a indices de matriz
    Position fi = toIndex(from);
    Position ti = toIndex(to);
    char pc = b[fi.y][fi.x]; // pieza a mover

    // Debe ser pieza propia
    if (!isFriendly(pc, whiteTurn)) {
        return false;
    }
    // Destino no puede tener pieza amiga
    if (isFriendly(b[ti.y][ti.x], whiteTurn)) {
        return false;
    }

    // Llamar a funcion segun tipo (minusc y mayusc tratados igual)
    char lower = std::tolower(pc);
    if (lower == 'p') return canMovePawn(b, fi, ti, whiteTurn);
    if (lower == 'h') return canMoveKnight(b, fi, ti, whiteTurn);
    if (lower == 't') return canMoveRook(b, fi, ti, whiteTurn);
    if (lower == 'b') return canMoveBishop(b, fi, ti, whiteTurn);
    if (lower == 'q') return canMoveQueen(b, fi, ti, whiteTurn);
    if (lower == 'k') return canMoveKing(b, fi, ti, whiteTurn);

    // Pieza desconocida
    return false;
}

// Bucle principal del juego: imprime tablero, pide movimientos valida y ejecuta
void gameLoop(char board[BOARD_SIZE][BOARD_SIZE]) {
    bool whiteTurn = true;  // true = turno de blancas, false = turno de negras
    bool gameOver = false; // se pone true cuando se captura un rey

    // Repetir hasta fin de juego
    while (!gameOver) {
        // Mostrar estado actual del tablero
        printChessBoard(board);

        // Indicar turno actual
        if (whiteTurn) {
            std::cout << "Turno BLANCAS\n";
        }
        else {
            std::cout << "Turno NEGRAS\n";
        }

        Position from; // coordenadas de pieza origen
        Position to;   // coordenadas de destino

        // ----- SELECCIONAR ORIGEN -----
        while (true) {
            std::cout << "Origen (col fila): ";
            // Leer dos enteros; si falla, limpiar cin y reintentar
            if (!(std::cin >> from.x >> from.y)) {
                std::cin.clear();               // reset estado de error
                std::cin.ignore(1000, '\n');  // descartar entrada invalida
                std::cout << "Coordenadas invalidas\n";
                continue;                       // volver a pedir origen
            }
            // Verificar rango
            if (!isValidUserPos(from)) {
                std::cout << "Coordenadas invalidas\n";
                continue;
            }
            // Traducir a indices internos
            Position fi = toIndex(from);
            char pc = board[fi.y][fi.x];
            // Debe haber una pieza alli
            if (pc == CHAR_BG_BOARD) {
                std::cout << "No hay pieza ahi\n";
                continue;
            }
            // Debe ser pieza del jugador actual
            if (!isFriendly(pc, whiteTurn)) {
                std::cout << "Esa pieza no es tuya\n";
                continue;
            }
            // Origen valido
            break;
        }

        // ----- SELECCIONAR DESTINO -----
        while (true) {
            std::cout << "Destino (col fila): ";
            if (!(std::cin >> to.x >> to.y)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Coordenadas invalidas\n";
                continue;
            }
            // Verificar rango
            if (!isValidUserPos(to)) {
                std::cout << "Coordenadas invalidas\n";
                continue;
            }
            // No permitir seleccionar mismo casillero
            if (to.x == from.x && to.y == from.y) {
                std::cout << "Mismo sitio\n";
                continue;
            }
            // Validar reglas de movimiento segun pieza
            if (!validateMove(board, from, to, whiteTurn)) {
                std::cout << "Movimiento no valido\n";
                continue;
            }
            // Destino valido
            break;
        }

        // ----- EJECUTAR MOVIMIENTO -----
        // Convertir coords usuario a indices internos
        Position fi = toIndex(from);
        Position ti = toIndex(to);
        // Guardar pieza capturada (puede ser fondo '*')
        char captured = board[ti.y][ti.x];
        // Mover pieza
        board[ti.y][ti.x] = board[fi.y][fi.x];
        // Vaciar origen
        board[fi.y][fi.x] = CHAR_BG_BOARD;

        // ----- PROMOCION DE PEON -----
        // Si un peon alcanza el extremo contrario, se convierte en reina
        char moved = board[ti.y][ti.x];
        if (moved == WHITE_PAWN && ti.y == 0) {
            board[ti.y][ti.x] = WHITE_QUEEN;
        }
        else if (moved == BLACK_PAWN && ti.y == BOARD_SIZE - 1) {
            board[ti.y][ti.x] = BLACK_QUEEN;
        }

        // ----- FIN DE PARTIDA -----
        // Si la pieza capturada era un rey, termina el juego
        if (captured == WHITE_KING || captured == BLACK_KING) {
            printChessBoard(board);
            if (whiteTurn) {
                std::cout << "BLANCAS ganan\n";
            }
            else {
                std::cout << "NEGRAS ganan\n";
            }
            gameOver = true;  // salir del bucle
        }
        else {
            // Cambiar turno
            whiteTurn = !whiteTurn;
        }
    }
}
