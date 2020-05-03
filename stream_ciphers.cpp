#include <iostream>
#include <cmath>

char* encode(char* plaintext, unsigned long key); 
char* decode(char ciphertext, unsigned long key);

char* encode(char* plaintext, unsigned long key)
{
	unsigned char S[256];
	unsigned long num{ 0 };
	unsigned long long i{ 0 };
	unsigned long long j{ 0 };

	//Initializing the array 
	for (int counter{ 0 }; counter < 256; ++counter)
	{
		S[counter] = num;
		num = num + 1;
	}

	// Start scrambling the array S
	unsigned char temp{ 0 };


	for (int counter2{ 0 }; counter2 < 256; ++counter2)
	{
		unsigned long k = i % 64;
		j = (j + S[i] + ((key >> k) & 1)) % 256; 
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;

		i = (i + 1) % 256;
	}

	//for (int p = 0; p < 256; p++) {
		//std::cout << static_cast <int> (S[p]) << " "; // OUTPUTING THE SCRAMBLE
	//}

	//Finding the length of plaintext
	//char message[] = { "Hello World!" }; /////////////////////////// HARD CODED VALUE
	char* code_plaintext = plaintext;          /////////////////////////// FOR PLAINTEXT


	unsigned long long length{ 0 };
	long m{ 0 }; 
	while (code_plaintext[m] != '\0')
	{
		length = length + 1;
		++m; 
	}
	//std::cout << std::endl;             // OUTPUTING THE LENGTH 
	//std::cout << length << std::endl;   // OF PLAINTEXT 

	//plaintext = message;

	////////////////////////////////////////////////
	//EVERYTHING ABOVE THIS WORKS PERFECTLY GREAT //
	////////////////////////////////////////////////

	//std::cout << plaintext << std::endl;

	//Making sure plaintext is a multiple of 4
	int extra_char{ 0 };
	if (length % 4 == 0)
	{
		extra_char = 0;
	}
	else
	{
		extra_char = 4 - (length % 4);
	}

	unsigned char* new_plaintext{ new unsigned char[length + extra_char]{} };

	for (int counter6{ 0 }; counter6 < length; ++counter6)
	{
		new_plaintext[counter6] = code_plaintext[counter6];
	}

	//for (int counter3{ 0 }; counter3 < (length + extra_char); ++counter3)
	//{
		//std::cout << new_plaintext[counter3];
		//std::cout << std::endl;
	//}

	//XOR every byte of new_plaintext with R
	unsigned char temp2{ 0 };
	unsigned long R{ 0 };
	unsigned long r{ 0 };

	for (int counter4{ 0 }; counter4 < (length + extra_char); ++counter4)
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		temp2 = S[i];
		S[i] = S[j];
		S[j] = temp2;
		r = (S[i] + S[j]) % 256;
		R = S[r];
		new_plaintext[counter4] = new_plaintext[counter4] ^ R;

		//std::cout << new_plaintext[counter4];
	}

	/////////////////
	// ASCII ARMOR //
	/////////////////

	int amount_of_groups{ 0 };
	amount_of_groups = ((length + extra_char) / 4);
	unsigned long a{ 0 };
	unsigned long b{ 0 };
	unsigned long c{ 0 };
	unsigned long d{ 0 };
	unsigned long total{ 0 };
	unsigned long remainder{ 0 };
	char* new_array{ new char[length + extra_char + amount_of_groups + 1]{} };

	for (long counter{ 0 }; counter < amount_of_groups; ++counter)
	{
		a = new_plaintext[4 * counter];
		b = new_plaintext[(4 * counter) + 1];
		c = new_plaintext[(4 * counter) + 2];
		d = new_plaintext[(4 * counter) + 3];

		total = d | (c << 8) | (b << 16) | (a << 24);

		remainder = (total % 85);
		remainder = remainder + '!';
		total = total / 85;
		new_array[5 * counter + 4] = remainder;

		remainder = (total % 85);
		remainder = remainder + '!';
		total = total / 85;
		new_array[5 * counter + 3] = remainder;

		remainder = (total % 85);
		remainder = remainder + '!';
		total = total / 85;
		new_array[5 * counter + 2] = remainder;

		remainder = (total % 85);
		remainder = remainder + '!';
		total = total / 85;
		new_array[5 * counter + 1] = remainder;

		remainder = (total % 85);
		remainder = remainder + '!';
		total = total / 85;
		new_array[5 * counter] = remainder;


	}
	return new_array;
}

///////////////////
//SECOND FUNCTION// 
///////////////////

char* decode(char* ciphertext, unsigned long key)
{
	unsigned char S[256];
	unsigned long num{ 0 };
	unsigned long long i{ 0 };
	unsigned long long j{ 0 };

	//Initializing the array 
	for (int counter{ 0 }; counter < 256; ++counter)
	{
		S[counter] = num;
		num = num + 1;
	}

	// Start scrambling the array S
	unsigned char temp{ 0 };


	for (int counter2{ 0 }; counter2 < 256; ++counter2)
	{
		unsigned long k = i % 64;
		j = (j + S[i] + ((key >> k) & 1)) % 256;
		temp = S[i];
		S[i] = S[j];
		S[j] = temp;

		i = (i + 1) % 256;
	}

	//////////////////////////
	//REVERSING ASCII ARMOR//
	/////////////////////////

	char* code_ciphertext = ciphertext;          


	unsigned long long length{ 0 };
	long m{ 0 };
	while (code_ciphertext[m] != '\0')
	{
		length = length + 1;
		++m;
	}

	int extra_char{ 0 };
	extra_char = length % 4;
	

	unsigned char* new_ciphertext{ new unsigned char[length]{} };

	for (int counter6{ 0 }; counter6 < length; ++counter6)
	{
		new_ciphertext[counter6] = code_ciphertext[counter6];
	}


	int amount_of_groups{ 0 };
	amount_of_groups = (length / 5);

	unsigned long a{ 0 };
	unsigned long b{ 0 };
	unsigned long c{ 0 };
	unsigned long d{ 0 };
	unsigned long e{ 0 }; 
	unsigned long total{ 0 }; 

	unsigned char a2{ 0 };
	unsigned char b2{ 0 };
	unsigned char c2{ 0 };
	unsigned char d2{ 0 };

	char* new_array{ new char[(length) + 1]{} };

	for (long counter{ 0 }; counter < amount_of_groups; ++counter)
	{
		a = new_ciphertext[5 * counter];
		b = new_ciphertext[(5 * counter) + 1];
		c = new_ciphertext[(5 * counter) + 2];
		d= new_ciphertext[(5 * counter) + 3];
		e = new_ciphertext[(5 * counter) + 4]; 

		a = a - '!'; 
		a = a * (85 * 85 * 85 * 85); 

		b = b - '!';
		b = b * (85 * 85 * 85);

		c = c - '!';
		c = c * (85 * 85);

		d = d - '!';
		d = d * 85;

		e = e - '!'; 

		total = a + b + c + d + e; 

		a2 = (total >> 24);
		b2 = (total >> 16) & 255;
		c2 = (total >> 8) & 255;
		d2 = (total & 255); 

		new_array[4 * counter] = a2;
		new_array[(4 * counter) + 1] = b2;
		new_array[(4 * counter) + 2] = c2;
		new_array[(4 * counter) + 3] = d2;
	}
	//XOR every byte of new_ciphertext with R
	unsigned char temp2{ 0 };
	unsigned long R{ 0 };
	unsigned long r{ 0 };

	for (int counter4{ 0 }; counter4 < length - extra_char; ++counter4)
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		temp2 = S[i];
		S[i] = S[j];
		S[j] = temp2;
		r = (S[i] + S[j]) % 256;
		R = S[r];
		new_array[counter4] = new_array[counter4] ^ R;
	}

	return new_array;
}


#ifndef MARMOSET_TESTING
int main(); 
#endif

#ifndef MARMOSET_TESTING
int main()
{
	char str0[]{ "Hello World" };         
	char str1[]{ "A Elbereth Gilthoniel\nsilivren penna miriel\n"
		"o menel aglar elenath!\nNa-chaered palan-diriel\n"                      
		"o galadhremmin ennorath,\nFanuilos, le linnathon\n"                     
		"nef aear, si nef aearon!" };  // [1] 

	std::cout << "\"" << str0 << "\"" << std::endl;

	char* ciphertext{ encode(str0, 51323) };

	std::cout << "\"" << ciphertext << "\"" << std::endl;

	char* plaintext{ decode(ciphertext, 51323) };

	std::cout << "\"" << plaintext << "\"" << std::endl;

	delete[] plaintext;        
	plaintext = nullptr;         
	delete[] ciphertext;         
	ciphertext = nullptr;
	
	std::cout << "\"" << str1 << "\"" << std::endl;

	ciphertext = encode(str1, 51323);

	std::cout << "\"" << ciphertext << "\"" << std::endl;

	plaintext = decode(ciphertext, 51323);

	std::cout << "\"" << plaintext << "\"" << std::endl;

	delete[] plaintext;         
	plaintext = nullptr;         
	delete[] ciphertext;         
	ciphertext = nullptr;
	
	return 0;
}
#endif 
