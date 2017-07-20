#ifndef __VERTEX_DATA_H__
#define __VERTEX_DATA_H__

#include <vector>

#include <GL\glew.h>
#include "..\Component\GLObject\DrawArraysIndirectCommand.h"
#include "VertexAttribData.h"

class VertexData
{
public:

    // =============== Initialization =================
    VertexData                                              (void* data, GLuint vertex_count, GLsizei size, GLsizei stride, GLuint offset);

    VertexData                                              (const VertexData& rhs) = delete;
    VertexData&                         operator=           (const VertexData& rhs) = delete;

    VertexData                                              (VertexData&& rhs) = delete;
    VertexData&                         operator=           (VertexData&& rhs) = delete;

    void                                SetDrawCommand      (const DrawArraysIndirectCommand& command);
    void                                SetDrawCommand      (DrawArraysIndirectCommand&& command);

    // ================ General ==================

    void                                Bind                () const;
    void                                BindDrawCommand     () const;
    void                                BindVAO             () const;

    // Size of internal data array in bytes.
    GLsizei                             DataRawSize         () const;

    void*                               RawData             () const;
    GLuint                              VertexCount         () const;

    // Offset of the vertex data in the internal array.
    GLuint                              Offset              () const; 

    // Stride between vertices in the internal array.
    GLsizei                             Stride              () const;



    // ================ Attributes data manipulation ===================
    
    void                    AddVAOVertexAttrib              (const VertexAttribData& data);

    virtual ~VertexData                                     ();

protected:
    void                    CreateVAO                       ();
    void                    DeleteVAO                       ();

    void                    CreateAndFillVertexBuffer       ();
    void                    DeleteVertexBuffer              ();

protected:
    void*                                                   vertex_data_;

    // ========= Discriptional general data ==========

    GLsizei                                                 data_size_;
    GLsizei                                                 stride_;
    GLuint                                                  vertex_count_;
    GLuint                                                  vertex_data_offset_;
    
    // ========= GL objects =============

    GLuint                                                  vertex_buffer_object_;
    GLuint                                                  vertex_array_object_;
    
    // ========= DrawInfoDescription ===========

    DrawArraysIndirectCommand                               draw_arrays_command_;
};

#endif