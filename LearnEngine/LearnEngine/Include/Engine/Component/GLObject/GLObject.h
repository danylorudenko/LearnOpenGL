#ifndef __GL_OBJECT__
#define __GL_OBJECT__

#include <memory>

#include <Engine\Component\Component.h>
#include <Engine\Material\Material.h>
#include <Engine\VertexData\VertexData.h>

namespace Engine {

// Represents component that allows Entity to be drawn in the scene.
// Contains logic for setting context of OpenGL.
class GLObject : public Component
{
protected:

public:
    // ========== Construction and operators ==========

    GLObject                                        (Entity* owner);
    GLObject                                        (const GLObject& rhs) = delete;
                                                    
    GLObject&                operator=              (const GLObject& rhs) = delete;
    GLObject                                        (GLObject&& rhs) = delete;
    GLObject&                operator=              (GLObject&& rhs) = delete;

    virtual ~GLObject();


    // ========== GL API ==========
public:

    // Set vertex data to be used for rendering.
    // Vertex data can be shared and used by many GLObjects.
    virtual void                        SetVertexData               (const std::shared_ptr<VertexData>& vertex_data);

    // Perform binding of all conventional and additional buffers needed for rendering of GLObject.
    virtual void                        BindToRender                ();

    void                                SetMainMaterial             (const std::shared_ptr<Material>& material);
    virtual std::shared_ptr<Material>   GetMainMaterialShared       ();
    virtual Material&                   GetMainMaterial             ();

protected:
    // Binding data for the standartized shader uniform block.
    // GLOjbect is responisble only for binding transfrom block of the owner (for now).
    virtual void                        BindStandardUnifromBlocks   ();

protected:
    std::shared_ptr<Material>           main_material_;
    std::shared_ptr<VertexData>         vertex_data_;

};

} // namespace Engine

#endif