#include "bloom_filter.h"


BloomFilter::BloomFilter(size_t Hashes, size_t Bits):
  _hashes(Hashes), _bits(Bits), _filter(Bits, false) {}


void BloomFilter::add(const std::string &str) {
  // Обновляем состояние битов.
  for (size_t i = 0; i < _hashes; ++i) {
    size_t hashValue = _get_hash(i, str);
    _filter[hashValue % _bits] = true;
  }
  // Вставляем.
  _raw_set.insert(str);
}

bool BloomFilter::verify(const std::string &str) {
  // Увеличиваем счетчик, проверяем биты.
  ++cnt;
  for (size_t i = 0; i < _hashes; ++i) {
    size_t hashValue = _get_hash(i, str);
    if (!_filter[hashValue % _bits]) {
        return false;
    }
  }
  // Увеличиваем счетчик false_positive.
  if (_raw_set.find(str) == _raw_set.end()) {
      ++false_positive_cnt;
  }
  return true;
}

double BloomFilter::getFPRate() const {
  return cnt == 0 ? 0.0 : static_cast<double>(false_positive_cnt) / cnt;
}


size_t BloomFilter::numberOfHashFunctions() const {
  return _hashes;
}


size_t BloomFilter::numberOfBits() const {
  return _bits;
}


inline size_t BloomFilter::_get_hash(int i, const std::string &str) const {
  return std::hash<std::string>{}(str + std::to_string(i));
}

int main() {

}
