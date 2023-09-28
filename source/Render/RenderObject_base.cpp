#include "RenderObject_base.hpp"

namespace Engine::Render
{
        void renderobject_base::Use(VertexBuffer& target, const data_range& range, bool enable)
        {
            size_t offset = 0;
            for (GLuint i = range.offset; i < range.offset + range.length;i++)
            {
                const layout_element& val = target.getLayout() [i];
                if ((val.isNormalised() == GL_FALSE) && IsInteger(val.type))
                {
                    glVertexAttribIPointer(i, val.getCount(), val.type, target.getSize(),
                        (const void*)offset);
                }
                else if (val.type == GL_DOUBLE)
                {
                    glVertexAttribLPointer(i, val.getCount(), val.type, target.getSize(),
                        (const void*)offset);
                }
                else
                {
                    glVertexAttribPointer(i, val.getCount(), val.type, val.isNormalised(),
                        target.getSize(), (const void*)offset);
                }
                val.setIndex(this->layout_index);
                this->index_map.insert(pair<GLuint, const layout_element*>(this->layout_index, &val));
                if (enable)
                {
                    glEnableVertexAttribArray(this->layout_index);
                }
                val.setEnable(enable);
                this->layout_index++;
                offset += val.size;
            }
        }
        void renderobject_base::Use_reset(VertexBuffer& target)
        {
            size_t offset = 0;
            for (GLuint i = 0; i < GLuint(target.getLayout().size());i++)
            {
                const layout_element& val = target.getLayout() [i];
                if ((val.isNormalised() == GL_FALSE) && IsInteger(val.type))
                {
                    glVertexAttribIPointer(i, val.getCount(), val.type, target.getSize(),
                        (const void*)offset);
                }
                else if (val.type == GL_DOUBLE)
                {
                    glVertexAttribLPointer(i, val.getCount(), val.type, target.getSize(),
                        (const void*)offset);
                }
                else
                {
                    glVertexAttribPointer(i, val.getCount(), val.type, val.isNormalised(),
                        target.getSize(), (const void*)offset);
                }
                val.setIndex(layout_index);
                this->index_map.insert(pair<GLuint, const layout_element*>(layout_index, &val));
                if (val.isEnable())
                {
                    glEnableVertexAttribArray(this->layout_index);
                }
                this->layout_index++;
                offset += val.size;
            }
        }
        renderobject_base& renderobject_base::operator=(renderobject_base&& target) noexcept
	    {
            if (&target == this)
            {
#ifdef _DEBUG
                ERROR("C++","自移动警告")
#endif
                return *this;
            }

            array_id = target.array_id;
            layout_index = target.layout_index;
            render_vbos = forward<vector<VertexBuffer> >(target.render_vbos);
            index_map = forward<map<GLuint, const layout_element*> >(target.index_map);

            target.array_id = 0;

 		    return *this;       
        }
        void renderobject_base::setStatic(GLuint index, const void* v)
        {
            const layout_element& val = *(index_map[index]);
            if (IsInteger(val.type))
            {
                if ((val.isNormalised() == GL_FALSE))
                {
                    if (val.type == GL_INT)
                    {
                        switch (val.getCount())
                        {
                        case 1:
                            glVertexAttribI1iv(index, (const GLint*)v);
                            return;
                        case 2:
                            glVertexAttribI2iv(index, (const GLint*)v);
                            return;
                        case 3:
                            glVertexAttribI3iv(index, (const GLint*)v);
                            return;
                        case 4:
                            glVertexAttribI4iv(index, (const GLint*)v);
                            return;
                        default:
                            throw;
                        }
                    }
                    else if (GL_UNSIGNED_BYTE)
                    {
                        switch (val.getCount())
                        {
                        case 1:
                            glVertexAttribI1uiv(index, (const GLuint*)v);
                            return;
                        case 2:
                            glVertexAttribI2uiv(index, (const GLuint*)v);
                            return;
                        case 3:
                            glVertexAttribI3uiv(index, (const GLuint*)v);
                            return;
                        case 4:
                            glVertexAttribI4uiv(index, (const GLuint*)v);
                            return;
                        default:
                            throw;
                        }
                    }
                    else if (val.getCount() == 4)
                    {
                        switch (val.type)
                        {
                        case GL_BYTE:
                            glVertexAttribI4bv(index, (const GLbyte*)v);
                            return;
                        case GL_UNSIGNED_BYTE:
                            glVertexAttribI4ubv(index, (const GLubyte*)v);
                            return;
                        case GL_SHORT:
                            glVertexAttribI4sv(index, (const GLshort*)v);
                            return;
                        case GL_UNSIGNED_SHORT:
                            glVertexAttribI4usv(index, (const GLushort*)v);
                            return;
                        default:
                            throw;
                        }
                    }
                    else
                    {
                        throw;
                    }
                }
                else
                {
                    switch (val.type)
                    {
                    case GL_BYTE:
                        glVertexAttrib4Nbv(index, (const GLbyte*)v);
                        return;
                    case GL_UNSIGNED_BYTE:
                        glVertexAttrib4Nubv(index, (const GLubyte*)v);
                        return;
                    case GL_SHORT:
                        glVertexAttrib4Nsv(index, (const GLshort*)v);
                        return;
                    case GL_UNSIGNED_SHORT:
                        glVertexAttrib4Nusv(index, (const GLushort*)v);
                        return;
                    case GL_INT:
                        glVertexAttrib4Niv(index, (const GLint*)v);
                        return;
                    case GL_UNSIGNED_INT:
                        glVertexAttrib4Nuiv(index, (const GLuint*)v);
                        return;
                    default:
                        break;
                    }
                }
            }
            if (val.type == GL_DOUBLE)
            {
                switch (val.getCount())
                {
                case 1:
                    glVertexAttribL1dv(index, (const GLdouble*)v);
                    return;
                case 2:
                    glVertexAttribL1dv(index, (const GLdouble*)v);
                    return;
                case 3:
                    glVertexAttribL3dv(index, (const GLdouble*)v);
                    return;
                case 4:
                    glVertexAttribL4dv(index, (const GLdouble*)v);
                    return;
                default:
                    break;
                }
            }
            switch (val.getCount())
            {
            case 1:
                switch (val.type)
                {
                case GL_FLOAT:		
                    glVertexAttrib1fv(index, (const GLfloat*)v);
                    return;
                // case GL_DOUBLE:
                // 	glVertexAttrib1dv(index, (const GLdouble*)v);
                // 	return;
                case GL_SHORT:
                    glVertexAttrib1sv(index, (const GLshort*)v);
                    return;
                default:
                    throw;
                }
            case 2:	
                switch (val.type)
                {
                case GL_FLOAT:		
                    glVertexAttrib2fv(index, (const GLfloat*)v);
                    return;
                // case GL_DOUBLE:
                // 	glVertexAttrib2dv(index, (const GLdouble*)v);
                // 	return;
                case GL_SHORT:
                    glVertexAttrib2sv(index, (const GLshort*)v);
                    return;
                default:
                    throw;
                }
            case 3:	
                switch (val.type)
                {
                case GL_FLOAT:		
                    glVertexAttrib3fv(index, (const GLfloat*)v);
                    return;
                // case GL_DOUBLE:
                // 	glVertexAttrib3dv(index, (const GLdouble*)v);
                // 	return;
                case GL_SHORT:
                    glVertexAttrib3sv(index, (const GLshort*)v);
                    return;
                default:
                    throw;
                }
            case 4:
                switch (val.type)
                {
                case GL_FLOAT:		
                    glVertexAttrib4fv(index, (const GLfloat*)v);
                    return;
                // case GL_DOUBLE:
                // 	glVertexAttrib4dv(index, (const GLdouble*)v);
                // 	return;
                case GL_SHORT:
                    glVertexAttrib4sv(index, (const GLshort*)v);
                    return;
                case GL_BYTE: 
                    glVertexAttrib4bv(index, (const GLbyte*)v);
                    return;
                case GL_UNSIGNED_BYTE: 
                    glVertexAttrib4ubv(index, (const GLubyte*)v);
                    return;
                case GL_INT: 
                    glVertexAttrib4iv(index, (const GLint*)v);
                    return;
                case GL_UNSIGNED_INT: 
                    glVertexAttrib4uiv(index, (const GLuint*)v);
                    return;
                default:
                    throw;
                }
            default:
                break;
            }
        }
}