#include <cstdint> // For int64_t
#include <vector>  // Keep if used by your headers/logic
#include <string>  // Keep if used
// #include <chrono> // Be cautious with std::chrono if precise timing from C++ is critical in Wasm
// #include <limits> // Keep if used

// Emscripten header for exporting functions
#include <emscripten/emscripten.h>

// Your class definitions
#include "Tabuleiro.h"
#include "procuraRastros.h"

// Forward declaration of jogadaAI if its definition is in another .cpp file
// Ensure its signature matches exactly what you have elsewhere.
int jogadaAI(Tabuleiro& jogo, int dificuldade, bool iterativo, bool euristica, int tempoLimite);

// Functions like torneio, jogarContraPC, etc., are not directly exported to Wasm
// unless you explicitly prepare them like jogadaSite.
// For this Wasm module, we only care about jogadaSite.

// We need to wrap the function to be exported in extern "C"
// to prevent C++ name mangling, making it easier to call from JavaScript.
extern "C" {

EMSCRIPTEN_KEEPALIVE // This macro tells Emscripten to keep this function, even if unreferenced from C++, and export it.
int jogadaSite(uint64_t initial_board_state, int dificuldade, int altura, int largura, int tempo) {
    // Create the Tabuleiro object using the input from JavaScript
    Tabuleiro manual(static_cast<uint64_t>(initial_board_state), altura, largura);

    // Call your existing AI logic
    // The parameters (dificuldade, iterativo, euristica, tempoLimite) are hardcoded here.
    // You could also pass them from JavaScript if needed, by adding more parameters to jogadaSite.
    int ai_move_or_result = jogadaAI(manual, dificuldade, true, false, tempo);

    // Return the result to JavaScript.
    // If jogadaAI modifies 'manual' and you need to return the state of 'manual',
    // you'd need a method on Tabuleiro like: return manual.getBoardStateAsInt();
    // For now, we assume ai_move_or_result is what you want.
    return ai_move_or_result;
}

} // extern "C"

// Note: No main() function is needed when compiling a module for JS to call.
// Any std::cout or std::cerr from your C++ code (including Tabuleiro, procuraRastros, jogadaAI)
// will, by default, go to the browser's developer console (Module.print/printErr).
// Avoid std::cin or other blocking input methods in the code paths called by jogadaSite.//
// Created by topau on 06/05/2025.
//
