#pragma once
#include <string>
#include <vector>

class BinaryWriter
	{
	public:
		BinaryWriter(uint8_t* data, const std::size_t& pos = 0) : m_data(data) {
			this->m_pos = pos;
			this->m_delete_after = false;
		}
		BinaryWriter(const std::size_t& size) {
			this->m_pos = 0;
			this->m_size = size;

			m_data = (uint8_t*)std::malloc(size);
			std::memset(m_data, 0, size);
		}
		~BinaryWriter() {
			if (this->m_delete_after)
				std::free(m_data);
		}

		template <typename T>
		void write(T val) {
			std::memcpy(m_data + m_pos, &val, sizeof(T));
			m_pos += sizeof(T);
		}
		void write(const std::string& val, const std::size_t& data_length_size = 2) {
			std::size_t len = val.length();
			std::memcpy(m_data + m_pos, &len, data_length_size);
			m_pos += data_length_size;
			std::memcpy(m_data + m_pos, val.c_str(), len);
			m_pos += len;
		}
		void write(const uint8_t* val, const std::size_t& len) {
			std::memcpy(m_data + m_pos, val, len);
			m_pos += len;
		}
		void write(const char* val, std::size_t len) {
			std::memcpy(m_data + m_pos, val, len);
			m_pos += len;
		}
		void set_pos(const std::size_t& pos) {
			this->m_pos = pos;
		}
		void skip_pos(size_t len) {
			this->m_pos += len;
		}

		[[nodiscard]] uint8_t* get() {
			return m_data;
		}
		[[nodiscard]] std::size_t get_pos() const {
			return m_pos;
		}
		[[nodiscard]] std::size_t get_size() const {
			return m_size;
		}
	private:
		uint8_t* m_data;
		std::size_t m_pos;
		std::size_t m_size;

		bool m_delete_after{ true };
};