#pragma once

/* A simple pair struct in which only the Key is important when comparing.
   This is useful for generic containers that depend on sorting. */
template<typename K, typename V>
struct Associative
{
	Associative(const K& key, const V& value) : Key(key), Value(value)
	{};
	
	Associative(const K& key) : Key(key)
	{};
	
	Associative() = default;
	
	Associative<K, V>& operator=(const Associative<K, V>& other)
	{
		Key = other.Key;
		Value = other.Value;
		return *this;
	};
	
	Associative<K, V>& operator=(const V& val)
	{
		Value = val;
		return *this;
	};
	
	K Key;
	V Value;
	
	bool operator> (const Associative<K, V>& other) const { return Key >  other.Key; };
	bool operator< (const Associative<K, V>& other) const { return Key <  other.Key; };
	bool operator>=(const Associative<K, V>& other) const { return Key >= other.Key; };
	bool operator<=(const Associative<K, V>& other) const { return Key <= other.Key; };
	bool operator==(const Associative<K, V>& other) const { return Key == other.Key; };
	bool operator!=(const Associative<K, V>& other) const { return Key != other.Key; };
};