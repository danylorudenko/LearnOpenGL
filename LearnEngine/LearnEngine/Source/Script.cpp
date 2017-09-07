#include <Engine\Component\Script\Script.h>
#include <Engine\ScriptingSystem\ScriptingSystem.h>

namespace Engine
{

Script::Script() : Component(), is_ticking_(false)
{

}

void Script::SetTicking(bool value)
{
    is_ticking_ = value;
    if (is_ticking_) {
        ScriptingSystem::Instance().RegisterTicker(this);
    }
    else {
        ScriptingSystem::Instance().UnregisterTicker(this);
    }
}

Component::DestructionFunction Script::GetDestructionFunc()
{
    return [](Component* this_component) {
        ComponentFactory<Script>::DestroyComponent(dynamic_cast<Script*>(this_component));
    };
}

void Script::RegisterStart()
{
    ScriptingSystem::Instance().RegisterStarter(this);
}

Script::~Script() {
    SetTicking(false);
}

} // namespace Engine