#include "VertexArray.hpp"

namespace Engine::Render
{
	VertexArray& VertexArray::operator=(VertexArray&& target) noexcept
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

		target.array_id = 0;
		return *this;
	}

}