#pragma once

// NOTE: Il faut que l'expression soit "type-dependent" sinon on se mange vraiment l'erreur de compilation !!
// C'est pas non plus fiable à 100%, il se peut que ça compile vraiment pas sans que ça soit détecté ici
#define CHECK_DOES_NOT_COMPILE(expr) static_assert(not requires { expr; }, "expression `" #expr "` compiles but shouldn't")
