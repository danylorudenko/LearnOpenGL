#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "..\Component.h"

class ScriptingSystem;

class Script : public Component
{
public:
    Script                                                  ();
    Script                                                  (const Script& rhs);
    Script                                                  (Script&& rhs);

    Script&                     operator=                   (const Script& rhs);
    Script&                     operator=                   (Script&& rhs);

    void                        RegisterStart               ();
    void                        SetTicking                  (bool value);

protected:
    virtual void                RegisterInSystem            () override;
    virtual void                UnregisterFromSystem        () override;

    virtual void                OnStart                     () = 0;
    virtual void                OnRegistered                () = 0;
    virtual void                OnUnregistered              () = 0;
    virtual void                Tick                        () = 0;

protected:
    bool                        is_ticking_;

    friend class ScriptingSystemCallbackAttorney;
};

class ScriptingSystemCallbackAttorney
{
    using ScriptingSystemTickCallback                                           = void(Script::*)();
    using ScriptingSystemStartCallback                                          = void(Script::*)();

    static constexpr ScriptingSystemTickCallback    s_standard_tick_callback    = &Script::Tick;
    static constexpr ScriptingSystemStartCallback   s_standard_start_callback   = &Script::OnStart;

    friend ScriptingSystem;
};

#endif