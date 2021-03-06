#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "..\Component.h"

template<typename TComponent> class ComponentFactory;

class Light : public Component
{
    friend class ComponentFactory<Light>;

protected:
    Light                                   ();

public:
    Light                                   (const Light& rhs) = delete;
    Light                                   (Light&& rhs) = delete;
    Light&              operator=           (const Light& rhs) = delete;
    Light&              operator=           (Light&& rhs) = delete;

    virtual DestructionFunction GetDestructionFunc () override;
};

#endif