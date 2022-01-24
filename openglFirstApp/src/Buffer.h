#pragma once
namespace glclass {

	class Buffer
	{
	private:
		unsigned int m_RenderId;

	public:
		Buffer();
		void SetData(const void* data, unsigned int size);
		~Buffer();

		void Bind() const;
		void Unbind() const;
	};
}
