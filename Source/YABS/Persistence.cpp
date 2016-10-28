#include "../YABS.hpp"

static bool g_Persistence = false;
static std::string g_PersistentString;

bool YABS::Persistence(void) { return g_Persistence; }
void YABS::SetPersistence(bool persistence) { g_Persistence = persistence; }
std::string &YABS::PersistenceString(void) { return g_PersistentString; }