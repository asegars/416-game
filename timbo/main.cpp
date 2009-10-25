// Brian Malloy        Game Construction

#include "manager.h"
Viewport *Viewport::instance = NULL;

int main(int, char*[]) {
   try {
      Manager game_manager;
      game_manager.play();
   }
   catch (const std::string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
