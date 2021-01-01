#pragma once
#include"BitVector.h"
#include<iostream>
#include<random>
#include<chrono>

using namespace std;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

class BloomFilter
{
	BitVector bvec;
	int a[6] = { 0 };
	int p;
public:
	BloomFilter() :bvec(728000)
	{
		for (int i = 0; i < 6; i++)
		{
			a[i]= uniform_real_distribution<double>(0, 16777212)(rng);
		}
		p = 16777213;
	}

	void insert(string key)
	{
		for (int i = 0; i < 6; i++)
		{
			bvec.set(hashFunction(key, a[i]));
		}
		
	}

	int powerCalculation(int number, int power)
	{
		if (power == 0)
		{
			return 1;
		}
		else if (power == 1)
		{
			return number % p;
		}
		else
		{
			unsigned long long int n = number;
			for (int i = 0; i < power - 1; i++)
			{
				n = ((n % p) * (number % p)) % p;
			}

			return n;
		}
	}

	int hashFunction(string key, int a)
	{
		int i = 0;
		int power = key.size() - 1;
		int bit = 0;
		while (key[i] != '\0')
		{
			bit += (key[i] * (powerCalculation(a, power--))) % p;
			i++;
		}
		return (bit % p) % 728000;
	}

	bool lookUp(string key)
	{
		for (int i = 0; i < 6; i++)
		{
			if (!bvec.get(hashFunction(key, a[i])))
			{
				return false;
			}
		}
		return true;
	}

	~BloomFilter()
	{
	}

};