#pragma once

#include "String.h"

#include <unordered_map>

CStdString sssss;

namespace std {
	template<>
	struct hash<CStdString> {
		std::size_t operator()(const CStdString& s) const noexcept {
			return 1;
		}
	};
}

 namespace cstd {
	template<typename KeyType, typename ValueType>
	class CStdUnorderedMap {
		using POSITION = typename std::unordered_map<KeyType, ValueType>::iterator*;
	public:
		

		size_t GetCount() const {
			return map.size();
		}

		void GetNextAssoc(POSITION& aNextPosition, KeyType& aKey, ValueType& aValue) const {
			if (!aNextPosition) {
				return;
			}
			aKey = (*aNextPosition)->first;
			aValue = (*aNextPosition)->second;
			++(*aNextPosition);
			if (*aNextPosition == map.cend()) {
				aNextPosition = nullptr;
			}
		}

		size_t GetSize() const {
			return map.size();
		}

		POSITION GetStartPosition() {
			if (map.empty()) {
				return nullptr;
			}
			else {
				m_begin = map.begin();
				return &m_begin;
			}
		}

		BOOL IsEmpty() const {
			return map.empty();
		}

		BOOL Lookup(KeyType key, ValueType& rValue) const {
			auto iter = map.find(key);
			if (iter == map.cend()) {
				return false;
			}
			else {
				rValue = iter->second;
				return true;
			}
		}

		void SetAt(KeyType key, ValueType newValue) {
			map[key] = newValue;
		}

		void RemoveAll() {
			map.clear();
		}

	private:
		using Iterator = typename std::unordered_map<KeyType, ValueType>::iterator;
		std::unordered_map<KeyType, ValueType> map;
		mutable Iterator m_begin;
	};	

	class ByteArray {
	public:
		unsigned char& operator[] (size_t n) {
			return m_v[n];
		}

		void RemoveAll() {
			m_v.clear();
		}
		
		void Copy(const ByteArray src) {
			m_v = src.m_v;
		}

		unsigned char* GetData() {
			return m_v.data();
		}

		size_t GetSize() const {
			return m_v.size();
		}

		void SetSize(int n) {
			m_v.resize(n);
		}

	private:
		std::vector<unsigned char> m_v;
	};

} // namespace cstd

#ifdef USE_CSTD_WRAPPERS

#define CMapStringToString cstd::CStdUnorderedMap<CStdString, CStdString>
template<typename KeyType, typename KeyArg, typename ValueType, typename ValueArg>
using CStdMap = cstd::CStdUnorderedMap<KeyType, ValueType>;
#define CMap CStdMap
#define CMapWordToPtr cstd::CStdUnorderedMap<WORD, void*>
#define CByteArray cstd::ByteArray

#define POSITION auto

#endif // USE_CSTD_WRAPPERS
