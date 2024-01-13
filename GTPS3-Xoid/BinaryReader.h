#pragma once
#include <string>
#include <vector>

class BinaryReader
	{
	public:
		BinaryReader(uint8_t* data)
			: m_data(data), m_pos(0) {}
		BinaryReader(uint8_t* data, std::size_t alloc) : m_pos(0) {
			m_data = (uint8_t*)std::malloc(alloc);
			std::memcpy(m_data, data, alloc);
		}
		BinaryReader(const std::vector<uint8_t>& data) : m_pos(0) {
			auto alloc = data.size();
			m_data = (uint8_t*)std::malloc(alloc);
			std::memcpy(m_data, data.data(), alloc);
		}
		~BinaryReader() {
			std::free(m_data);
		}

		template <typename T>
		T read() {
			T val;
			std::memcpy(&val, this->m_data + this->m_pos, sizeof(T));
			this->m_pos += sizeof(T);
			return val;
		}
		template <typename T>
		void read(T& val) {
			std::memcpy(&val, this->m_data + this->m_pos, sizeof(T));
			this->m_pos += sizeof(T);
		}
		std::string read_string() {
			const uint16_t& len{ this->read<uint16_t>() };
			std::string val = std::string(reinterpret_cast<char*>(m_data + m_pos), len);
			this->m_pos += len;
			return val;
		}
		void read(std::string& val) {
			const uint16_t& len{ this->read<uint16_t>() };
			val = std::string(reinterpret_cast<char*>(m_data + m_pos), len);
			this->m_pos += len;
		}

		void skip(const std::size_t& len) {
			this->m_pos += len;
		}
		uint8_t* get() const {
			return m_data;
		}
		std::size_t get_pos() const {
			return m_pos;
		}
	private:
		uint8_t* m_data;
		std::size_t m_pos;
};
