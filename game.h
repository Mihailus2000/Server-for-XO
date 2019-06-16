#ifndef GAME_H
#define GAME_H

#include <QString>
#include <vector>
#include <QObject>

const char X = 'X';
const char O = 'O';

extern int MapSize;

// Состояние игры
enum State {
  X_MOVE, // Ход крестиков
  O_MOVE, // Ход ноликов
  X_WIN,  // Крестики выиграли
  O_WIN,  // Нолики выиграли
  DRAW    // Ничья
};

// Все что происодит на поле и логика игрового мира
// Ходы, выйгрыш/проигрыш
class Game : public QObject{

  Q_OBJECT

  State state; // Текущее состояние игры
  // Игровое поле
  std::vector<std::vector<char> > Map;
  // Проверка выигрыша.
  // Проверяется одна строка,
  // один столбец или одна диагональ
  void checkLine(std::vector<char> a);
 public:
  // Конструктор
  Game();
  // Новая игра без пересоздания объекта
  void newGame();
  // Получаем строку, соответствующую состоянию игры
  QString getStateString();
  // Совершаем ход, возвращает строку для клетки на форме
  QString makeMove(int row, int col);
  // Проверяем на окончание игры
  void checkGameOver();

  // Состояние ячейки
  const char* getCell(int i, int j);
  void resizeMap();
  void mapResize();
};

#endif // GAME_H
