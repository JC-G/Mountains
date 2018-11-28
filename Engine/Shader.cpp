#include "Shader.h"
#include "Util.h"

Shader::Shader(const char* vert, const char* frag)
{
    ID = Util::LoadShaders(vert,frag);
}
