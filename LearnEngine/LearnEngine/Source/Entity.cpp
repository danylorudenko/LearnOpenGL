#include "..\Include\Entity\Entity.h"
#include "..\Include\Component\ComponentRegistrationAttorney.h"
#include "..\Include\World\World.h"

Entity* Entity::CreateEntity()
{
    Entity* new_entity = new Entity(nullptr);
    World::Instance().AddToRoot(new_entity);
    return new_entity;
}

Entity * Entity::CreateRootEnitity()
{
    return new Entity(nullptr);
}

Entity* Entity::FindEntity(std::string& name)
{
    if (name_ == name) {
        return this;
    }

    if (!children_.empty()) {
        std::for_each(children_.begin(), children_.end(),
            [&name, this](HierarchyMember<Entity>* candidate) {
            return dynamic_cast<Entity*>(this->FindEntity(name));
        });
    }
    
    return nullptr;
}

std::string & Entity::Name()
{
    return name_;
}

const std::string & Entity::Name() const
{
    return name_;
}

GLTransform & Entity::Transform()
{
    return *transform_;
}

const GLTransform & Entity::Transform() const
{
    return *transform_;
}

Entity::Entity(Entity* parent) :
    HierarchyMember<Entity>(parent),
    transform_(new GLTransform()),
    name_("new_entity")
{

}

Entity::~Entity()
{
    RemoveAllComponents();
}

void Entity::AddComponent(Component* component)
{
    components_.push_back(component);
    ComponentRegistrationAttorney::SetComponentOwner(component, this);
    ComponentRegistrationAttorney::RegisterInSystem(component);
}

void Entity::RemoveComponent(Component* component)
{
    components_.remove_if(
        [component](Component* candidate) {
        if (component == candidate) {
            ComponentRegistrationAttorney::UnregisterFromSystem(candidate);
            ComponentRegistrationAttorney::SetComponentOwner(component, nullptr);
            return true;
        }
        else {
            return false;
        }
    });
}

void Entity::RemoveAllComponents()
{
    for (auto component : components_) {
        ComponentRegistrationAttorney::UnregisterFromSystem(component);
        ComponentRegistrationAttorney::SetComponentOwner(component, nullptr);
        delete component;
    }

    components_.clear();
}
