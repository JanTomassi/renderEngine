#pragma once
namespace glclass {

	class IndexBuffer
	{
	private:
		unsigned int m_RenderId;

	public:
		IndexBuffer();
		~IndexBuffer();

		void SetData(const unsigned int* data, size_t count);

		void Bind() const;
		void Unbind() const;
	};
}
